#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "LinkedStack.h"

using namespace std;

int main() {

	LinkedStack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);


	s.pop();

	cout << s.size() << endl;
	cout << s << endl;

	system("PAUSE");
	return 0;
}