#include "Network.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <utility>
#include <cstring>

#include "NetworkError.h"

Network::Network(const std::string &host, uint16_t port)
        : m_host(host)
        , m_port(port)
        , m_sockfd()
{
}

Network::~Network() noexcept {
    disconnect();
}

void Network::connect() {
    FileDescriptor fd(socket(AF_INET, SOCK_STREAM, 0));
    if (!fd)
        throw NetworkError(std::strerror(errno));

    struct hostent* server = gethostbyname(m_host.c_str());
    if (!server)
        throw std::runtime_error(hstrerror(h_errno));

    sockaddr_in s_addr{};
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(m_port);
    memcpy(&s_addr.sin_addr, server->h_addr_list[0], static_cast<size_t>(server->h_length));

    if (::connect(fd.get(), reinterpret_cast<sockaddr*>(&s_addr), sizeof(s_addr)))
        throw NetworkError(std::strerror(errno));

    using std::swap;
    swap(m_sockfd, fd);
}

void Network::disconnect() {
    m_sockfd.reset();
}

void Network::send(const Message &message) {
    if (!is_connected())
        throw NetworkError("Cannot send message because the connection is not established.");

    std::string buffer = message.to_string();
    if (::send(m_sockfd.get(), buffer.c_str(), buffer.size(), 0) < 0)
        throw NetworkError(std::strerror(errno));
}

Message Network::receive() {
    constexpr size_t MAX_MESSAGE_LENGTH = 66000;
    static char buffer[MAX_MESSAGE_LENGTH];

    if (!is_connected())
        throw NetworkError("Cannot receive message because the connection is not established.");

    memset(buffer, 0, MAX_MESSAGE_LENGTH);
    ssize_t bytes_received = ::recv(m_sockfd.get(), buffer, MAX_MESSAGE_LENGTH, 0);
    if (bytes_received == 0)
        throw NetworkError("Reached EOF");
    else if (bytes_received < 0)
        throw NetworkError(std::strerror(errno));

    return Message(std::string(buffer, static_cast<size_t>(bytes_received)));
}

bool Network::is_connected() const {
    return m_sockfd.get() >= 0;
}

