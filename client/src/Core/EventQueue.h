#ifndef AIC19_CLIENT_CPP_EVENT_QUEUE_H
#define AIC19_CLIENT_CPP_EVENT_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>

#include "Message/Message.h"

/**
 * A thread-safe queue of @see Message objects
 */
class EventQueue final {
public:

    /**
     * Default constructor
     */
    EventQueue();

    /**
     * Destructor
     */
    ~EventQueue();

    EventQueue(const EventQueue&) = delete;
    EventQueue& operator= (const EventQueue&) = delete;

    /**
     * Push a message into the queue
     *
     * @param message The message to push
     */
    void push(const Message& message);

    /**
     * Pop a message from the queue
     * @note This functions blocks until a message is available to pop or @see terminate is called
     *
     * @return nullptr if the waiting process is interrupted by a call to @see terminate
     * A unique_ptr to the message popped from queue otherwise
     */
    std::unique_ptr<Message> pop();

    /**
     * Terminate the process, causing any thread that waits on @see pop to return
     */
    void terminate();

private:

    /// The actual queue holding messages
    std::queue<std::unique_ptr<Message>> m_queue;

    /// The mutex used to synchronize access to @see m_queue
    std::mutex m_mutex;

    /// The condition variable used to signal threads waiting to pop a message when a push happens
    std::condition_variable m_cv;

    /// The flag used to indicate if terminating is requested
    std::atomic_bool m_terminating;
};

#endif // AIC19_CLIENT_CPP_EVENT_QUEUE_H
