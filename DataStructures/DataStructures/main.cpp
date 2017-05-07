#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "LinkedStack.h"

using namespace std;

int main() {

	LinkedStack<int> s;
	s.push(1);
	s.push(2);

	cout << s << endl;

	system("PAUSE");
	return 0;
}