#include "EventQueue.h"

#include <Utility/Utility.h>

EventQueue::EventQueue()
        : m_terminating(false)
{
}

EventQueue::~EventQueue() {
    terminate();
}

void EventQueue::push(const Message& message) {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_queue.push(std::unique_ptr<Message>(new Message(message)));
    m_cv.notify_all();
}

std::unique_ptr<Message> EventQueue::pop() {
    std::unique_lock<std::mutex> lock(m_mutex);

    // If the queue is empty wait for a signal
    while (m_queue.empty() && !m_terminating)
        m_cv.wait(lock);

    if (m_terminating)
        return nullptr;

    std::unique_ptr<Message> result = std::move(m_queue.front());
    m_queue.pop();
    return result;
}

void EventQueue::terminate() {
    m_terminating = true;
    m_cv.notify_all();
}
