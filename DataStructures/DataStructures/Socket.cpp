#include "stdafx.h"
#include "Socket.h"
#include <Ws2tcpip.h>
#include <thread>

#include <iostream>

namespace Network {

	int Socket::nbSockets = 0;

	/////////////////////////////////////////

	void Socket::addSocket() {
		if (Socket::nbSockets == 0) {
			WSADATA WSAData;
			WSAStartup(MAKEWORD(2, 0), &WSAData);
		}
		Socket::nbSockets++;
	}

	void Socket::closeSocket() {
		Socket::nbSockets--;
		if (Socket::nbSockets == 0) {
			WSACleanup();
		}
	}

	/////////////////////////////////////////

	Socket::Socket(std::string ip, int port) throw (std::logic_error) {
		Socket::addSocket();

		// Create the socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		inet_pton(AF_INET, ip.c_str(), &(sin.sin_addr));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);

		// Connect the socket
		if (connect(sock, (SOCKADDR *)&sin, sizeof sin) == SOCKET_ERROR) {
			throw std::logic_error("Connect error : " + WSAGetLastError());
		}

	}

	Socket::Socket(SOCKET s, SOCKADDR_IN sin) {
		sock = s;
		this->sin = sin;
	}

	Socket::~Socket() {
		closesocket(sock);
		Socket::closeSocket();
	}

	/////////////////////////////////////////

	void Socket::sendMessage(SocketMessage m) {
		char *buff;
		int length = m.serialize(&buff);
		send(sock, buff, length, 0);
	}

	SocketMessage Socket::receiveMessage() {
		int length = SocketMessage::MSG_MAXSIZE;
		char* buff = new char[length];
		int size = recv(sock, buff, length, 0);

		SocketMessage m(buff, size);
		return m;
	}

	///////////////////////////////////////////////////////////////////////////////////

	SocketServer::SocketServer(std::string ip, int port) throw (std::logic_error) {
		Socket::addSocket();

		// Create the socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		inet_pton(AF_INET, ip.c_str(), &(sin.sin_addr));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		if (bind(sock, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR) {
			throw std::logic_error("Bind error : " + WSAGetLastError());
		}

		if (listen(sock, 1) == SOCKET_ERROR) {
			throw std::logic_error("Listen error : " + WSAGetLastError());
		}

		listening = false;
	}

	SocketServer::~SocketServer() {
		closesocket(sock);
		Socket::closeSocket();
	}

	/////////////////////////////////////////

	void SocketServer::listenSocket(std::function<void(Socket*)> f) {
		if (!listening) {
			std::thread t(&SocketServer::threadListen, this, f);
			t.join();
			listening = true;
		} else {
			throw std::logic_error("The server socket is already listening");
		}
	}

	void SocketServer::threadListen(std::function<void(Socket*)> f) {
		while (true) {
			SOCKADDR_IN sin_aux;
			int sizeof_sin = sizeof(sin_aux);
			SOCKET s = accept(sock, (SOCKADDR *)&sin_aux, &sizeof_sin);
			if (s != INVALID_SOCKET)
			{
				Socket* client = new Socket(s, sin_aux);
				std::thread t(f, client);
				t.detach();
			}
		}
	}
}