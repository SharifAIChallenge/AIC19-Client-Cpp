#include "Network.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <utility>
#include <cstring>

#include <Utility/Utility.h>
#include <Utility/Logger.h>

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
#ifdef _WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2,2), &wsa_data);
    if (result != 0)
        throw NetworkError("WSAStartup failed");
#endif

    FileDescriptor fd(socket(AF_INET, SOCK_STREAM, 0));
    if (!fd)
        throw NetworkError(std::strerror(errno));

    struct hostent* server = gethostbyname(m_host.c_str());
    if (!server)
        throw NetworkError(hstrerror(h_errno));

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

#ifdef _WIN32
    WSACleanup();
#endif
}

void Network::send(std::string message) {
    Logger::Get(LogLevel_TRACE) << "Enter Network::send" << std::endl;
    Logger::Get(LogLevel_DEBUG) << "Trying to send " << message << std::endl;

    message.push_back('\0');

    if (!is_connected())
        throw NetworkError("Cannot send message because the connection is not established.");

    if (::send(m_sockfd.get(), message.c_str(), message.size(), 0) < 0)
        throw NetworkError(std::strerror(errno));

    Logger::Get(LogLevel_TRACE) << "Exit Network::send" << std::endl;
}

std::string Network::receive() {
    Logger::Get(LogLevel_TRACE) << "Enter Network::receive" << std::endl;

    constexpr size_t MAX_MESSAGE_LENGTH = 66000;
    static char buffer[MAX_MESSAGE_LENGTH];

    if (!is_connected())
        throw NetworkError("Cannot receive message because the connection is not established.");

    memset(buffer, -1, MAX_MESSAGE_LENGTH);

    ssize_t bytes_received = 0;
    do {
        bytes_received += ::recv(m_sockfd.get(), buffer + bytes_received, MAX_MESSAGE_LENGTH, 0);
        if (bytes_received == 0)
            throw NetworkEOFError();
        else if (bytes_received < 0)
            throw NetworkError(std::strerror(errno));
    } while (buffer[bytes_received - 1] != '\0');

    std::string result(buffer, static_cast<size_t>(bytes_received));

    Logger::Get(LogLevel_DEBUG) << "Received " << std::string(result.begin(), result.end() - 1) << std::endl;
    Logger::Get(LogLevel_TRACE) << "Exit Network::receive" << std::endl;
    return result;
}

bool Network::is_connected() const {
    return m_sockfd.get() >= 0;
}

