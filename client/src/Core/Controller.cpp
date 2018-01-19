#include "Controller.h"

#include <iostream>
#include "../Network/NetworkError.h"

Controller::Controller(const std::string& host, uint16_t port)
        : m_network(host, port)
{
}

Controller::~Controller() {
    m_network.disconnect();
}

void Controller::run() {
    m_network.connect();

    while (m_network.is_connected()) {
        try {
            Message msg = m_network.receive();

            // TODO: Parse the message
            std::cout << msg.to_string() << std::endl;
        }
        catch (NetworkEOFError& e) {
            m_network.disconnect();
        }
        catch (Json::Exception& e) {
            std::cerr << "Warning: Received malformed json string" << std::endl;
        }
    }
}