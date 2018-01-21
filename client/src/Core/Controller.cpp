#include "Controller.h"

#include <iostream>
#include "../Network/NetworkError.h"

Controller::Controller(const std::string& host, uint16_t port)
        : m_network(host, port)
        , m_event_queue()
        , m_event_handling_thread()
{
}

Controller::~Controller() {
    if (m_event_handling_thread.joinable())
        m_event_handling_thread.join();
    if (m_network.is_connected())
        m_network.disconnect();
}

void Controller::run() {
    constexpr size_t MAX_RETRY_COUNT = 3;

    for (size_t i = 1; i <= MAX_RETRY_COUNT && !m_network.is_connected(); ++i)
        try {
            std::cerr << "Trying to connect #" << i << std::endl;
            m_network.connect();
        }
        catch (NetworkError &e) {
            if (i == MAX_RETRY_COUNT)
                throw;
        }
    std::cerr << "Connected" << std::endl;

    m_event_handling_thread = std::thread(&Controller::event_handling_loop, this);

    while (m_network.is_connected()) {
        try {
            Message msg = m_network.receive();

            // TODO: Parse the message
            std::cout << msg.to_string() << std::endl;
        }
        catch (NetworkEOFError& e) {
            break;
        }
        catch (Json::Exception& e) {
            std::cerr << "Warning: Received malformed json string" << std::endl;
        }
    }

    std::cerr << "Closing the connection" << std::endl;
    m_event_queue.terminate();
    m_network.disconnect();
}

void Controller::event_handling_loop() noexcept {
    while (m_network.is_connected()) {
        auto message = m_event_queue.pop();
        if (!message)
            break;
        m_network.send(*message);
    }
}