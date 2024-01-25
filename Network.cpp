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
    std::string data = msg;
    msg.append("\n");
    send(m_server, msg.c_str(), buf, 0);
}

std::string Network::receiveMassage()
{
    std::string data = "";
    std::string garbage = "";

    //int rc = read(m_con, buf, sizeof(buf));

    bool EOM = false; // end of messege

    while(!EOM)
    {
        char tmp[buf];
        int rc = recv(m_server, tmp, buf, 0);

        for (int i = 0; i < rc; i++)
        {
            if (tmp[i] == '\n')
            {
                EOM = true;

                for (int j = i; j <= buf; j++)
                    garbage += tmp[j];

                break;
            }
            data += tmp[i];
        }

    }

    

    std::cout << "Received: " << data << std::endl;

    return data;
}
