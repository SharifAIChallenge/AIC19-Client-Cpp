#ifndef AIC19_CLIENT_CPP_NETWORK_H
#define AIC19_CLIENT_CPP_NETWORK_H

#include <string>

#include "FileDescriptor.h"

/**
 * A TCP connection capable of sending and receiving byte streams
 */
class Network final {
public:

    /**
     * Constructor
     *
     * @param host The host to connect to
     * @param port The port to connect to
     */
    Network(const std::string& host, uint16_t port);

    Network(const Network&) = delete;
    Network& operator= (const Network&) = delete;

    /**
     * Destructor
     */
    ~Network() noexcept;

    /**
     * Connect to the specified host
     * @note Offers strong exception guarantee
     */
    void connect();

    /**
     * Close the connection
     */
    void disconnect();

    /**
     * Synchronously send a message
     *
     * @param message The buffer to send
     */
    void send(std::string message);

    /**
     * Synchronously receive a message
     *
     * @return The buffer that was received
     */
    std::string receive();

    /**
     * @return True if the connection is established and not terminated, false otherwise
     */
    bool is_connected() const;

private:

    /// The host to connect to
    std::string m_host;

    /// The port to connect to
    uint16_t m_port;

    /// The socket file descriptor
    FileDescriptor m_sockfd;
};

#endif // AIC19_CLIENT_CPP_NETWORK_H
