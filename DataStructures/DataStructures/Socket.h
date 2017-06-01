#pragma once
#include <winsock2.h>
#include <stdexcept>
#include <string>
#include <functional>
#include "SocketMessage.h"

#pragma comment(lib, "ws2_32.lib")

namespace Network {

	class SocketServer;

	// A network socket, allowing to send and receive messages.
	class Socket {
	public:
		Socket(std::string ip, int port) throw (std::logic_error);
		~Socket();

		void sendMessage(SocketMessage m) throw (std::logic_error);
		SocketMessage receiveMessage() throw (std::logic_error);

		friend class SocketServer;

	private:
		Socket(SOCKET s, SOCKADDR_IN sin);

		SOCKADDR_IN sin;
		SOCKET sock;

		static void addSocket();
		static void closeSocket();
		static int nbSockets;
	};

	///////////////////////////////////////////////////////////////////////////////////

	// A network server socket, allowing to accept some socket connections.
	class SocketServer {
	public:
		SocketServer(std::string ip, int port) throw (std::logic_error);
		~SocketServer();

		void listenSocket(std::function<void(Socket*)> f) throw (std::logic_error);
		inline bool isListening() const { return listening; }

	private:

		void threadListen(std::function<void(Socket*)> f);
		SOCKADDR_IN sin;
		SOCKET sock;
		bool listening;
	};
}