#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#include <iostream>

#define buf 64 //z g�ry kore�lony bufor przyjmowanych danych

class Network
{
	public:
		Network() = default;
		~Network();

		void createConnection(std::string, int port);
		void sendMessage(std::string msg);
		std::string receiveMassage();


	private:

		//int m_con;
		WSADATA m_wsaData;
		SOCKET m_server;

		std::string m_addres;
		int m_port;
};

