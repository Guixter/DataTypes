#pragma once
class SocketMessage
{
public:
	SocketMessage();
	~SocketMessage();

	virtual char* serialize() = 0;
};

