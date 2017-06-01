#include "stdafx.h"
#include "DistributedList.h"
#include "Socket.h"
#include <iostream>

using namespace std;
using namespace Network;

DistributedList::DistributedList() { }

DistributedList::~DistributedList() { }

void DistributedList::launch() {

	int choice = -1;
	cin >> choice;

	if (choice == 0) {
		SocketServer *s = new SocketServer("127.0.0.1", 3000);
		auto _test = [](Socket* s) {
			cout << s << " accepte" << endl;
			while (true) {
				s->receiveMessage();
				cout << s << "envoie un ping" << endl;
			}
		};
		s->listenSocket(_test);
		delete s;
	} else {
		Socket *s = new Socket("127.0.0.1", 3000);
		system("pause");
		s->sendMessage(SocketMessage());
		system("pause");
		s->sendMessage(SocketMessage());
		system("pause");
		delete s;
	}

	
}