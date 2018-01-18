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

bool Network::is_connected() const {
    return m_sockfd.get() >= 0;
}
