#ifndef AIC18_CLIENT_CPP_CONTROLLER_H
#define AIC18_CLIENT_CPP_CONTROLLER_H

#include <string>

#include "../Network/Network.h"

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

    /// The network connection used for talking to server
    Network m_network;

};

#endif // AIC18_CLIENT_CPP_CONTROLLER_H
