#include "Network.h"


Network::~Network()
{
    closesocket(m_server);
}

void Network::createConnection(std::string addres, int port)
{
    int result = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
    if (result != NO_ERROR)
        std::cout << "Initialization error" << std::endl;

    m_addres = addres;
    m_port = port;

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(addres.c_str());
    saddr.sin_port = htons(port);

    m_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP
    if (m_server == INVALID_SOCKET)
    {
        std::cout << "Error creating socket: %ld\n" << WSAGetLastError() << std::endl;
    }

    if (connect(m_server, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
    {
        std::cout << "Failed to connect.\n" << WSAGetLastError() << std::endl;
    }
}

void Network::sendMessage(std::string msg)
{
    //write(m_con, tmp, sizeof(tmp));
    send(m_server, msg.c_str(), sizeof(msg), 0);
}

std::string Network::receiveMassage()
{
    char text[1024];
    //int rc = read(m_con, buf, sizeof(buf));
    int rc = recv(m_server, text, sizeof(buf), 0);

    return std::string(text);
}
