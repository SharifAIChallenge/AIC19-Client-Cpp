#ifndef AIC19_CLIENT_CPP_CONTROLLER_H
#define AIC19_CLIENT_CPP_CONTROLLER_H

#include <string>
#include <thread>

#include <Network/Network.h>
#include <Model/Interface/World.h>
#include <AI/AI.h>
#include <memory>

#include "EventQueue.h"

/**
 * High level client logic is implemented here
 */
class Controller final {
public:

    /**
     * Constructor
     *
     * @param host The server host to connect to
     * @param port The server port
     * @param token Authentication token to send to server
     * @param retry_delay Number of milliseconds to wait before retrying connection
     */
    Controller(const std::string& host, uint16_t port, const std::string& token, unsigned retry_delay);

    /**
     * Destructor
     */
    ~Controller();

    Controller(const Controller&) = delete;
    Controller& operator= (const Controller&) = delete;

    /**
     * Start the game
     */
    void run();

private:

    /**
     * The loop to dequeue events and send them across the network
     */
    void event_handling_loop() noexcept;

    /// Authentication token to send to server
    std::string m_token;

    /// Number of milliseconds to wait before retrying connection
    unsigned m_retry_delay;

    /// The network connection used for talking to server
    Network m_network;

    /// The event queue holding events to send
    EventQueue m_event_queue;

    /// Thread object that will run @see event_handling_loop
    std::thread m_event_handling_thread;

    /// Vector of threads that are made by receiving every pick or turn message
    std::vector<std::thread*> m_thread_list;

    /// Instance of the game world
    World m_world;

    /// Instance of the client AI
    AI m_client;

    /// Functions which one of them will be called in a new thread
    static void preProcess_event(AI* client,World* tmp_world,EventQueue* m_event_queue);
    static void pick_event(AI* client,World* tmp_world,EventQueue* m_event_queue);
    static void move_event(AI* client,World* tmp_world,EventQueue* m_event_queue);
    static void action_event(AI* client,World* tmp_world,EventQueue* m_event_queue);

public:
    static int thread_count;

};

#endif // AIC19_CLIENT_CPP_CONTROLLER_H
