#include "stdafx.h"
#include "DistributedList.h"
#include "Socket.h"
#include "SocketMessage.h"
#include <iostream>
#include <string>

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
				SocketMessage m = s->receiveMessage();
				m.get<int>();
				cout << s << "envoie : " << 2 << endl;
			}
		};
		s->listenSocket(_test);
		delete s;
	} else {
		Socket *s = new Socket("127.0.0.1", 3000);
		system("pause");
		SocketMessage m;
		m.add(35);
		s->sendMessage(m);
		system("pause");
		SocketMessage m2;
		m2.add(53);
		s->sendMessage(m2);
		system("pause");
		delete s;
	}

	
}