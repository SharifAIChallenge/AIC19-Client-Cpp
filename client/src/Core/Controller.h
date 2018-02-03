#ifndef AIC18_CLIENT_CPP_CONTROLLER_H
#define AIC18_CLIENT_CPP_CONTROLLER_H

#include <string>
#include <thread>

#include "../Network/Network.h"
#include "EventQueue.h"
#include "../Model/World.h"
#include "../AI/AI.h"

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
     */
    Controller(const std::string& host, uint16_t port);

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

    /// The network connection used for talking to server
    Network m_network;

    /// The event queue holding events to send
    EventQueue m_event_queue;

    /// Thread object that will run @see event_handling_loop
    std::thread m_event_handling_thread;

    /// Instance of the game world
    World m_world;

    /// Instance of the client AI
    AI m_client;
};

#endif // AIC18_CLIENT_CPP_CONTROLLER_H
