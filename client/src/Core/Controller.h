#ifndef AIC18_CLIENT_CPP_CONTROLLER_H
#define AIC18_CLIENT_CPP_CONTROLLER_H

#include <string>
#include <thread>

#include <Network/Network.h>
#include <Model/World.h>
#include <AI/AI.h>

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

    /// Instance of the game world
    World m_world;

    /// Instance of the client AI
    AI m_client;
};

#endif // AIC18_CLIENT_CPP_CONTROLLER_H
