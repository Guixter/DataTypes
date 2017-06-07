#include "stdafx.h"
#include "SocketMessage.h"
#include <winsock2.h>
#include <string>
#include <sstream>

using namespace std;

namespace Network {

	int SocketMessage::MSG_MAXSIZE = 512;

	SocketMessage::SocketMessage()
	{
		buff = new char[MSG_MAXSIZE];
		size = 0;
		writeCursor = 0;
		ss = NULL;
	}

	SocketMessage::SocketMessage(char* buffer, int size) {
		buff = buffer;
		this->size = size;
		writeCursor = -1;
		ss = new stringstream();
		(*ss) << buff;
	}

	SocketMessage::~SocketMessage()
	{
		delete[] buff;
	}

	int SocketMessage::serialize(char **buffer) {
		buff[writeCursor] = '\0';
		(*buffer) = buff;
		size = writeCursor;
		return size;
	}
}