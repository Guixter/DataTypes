#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "CardGame.h"
#include "Factory.h"

#include "LinkedList.h"

/*
- Normaliser les textes dans les exceptions
- const T& ou T ou T& ?
- ajouter des méthodes à queue et stack
*/

using namespace std;

void LaunchCardGame();
void LaunchFactory();
void LaunchDictionnary();
void LaunchFamilyTree();
void LaunchDoubleLinkedList();
void Menu();

int main() {

	LinkedList<int> *l = new LinkedList<int>();
	l->add(0, 1);
	l->add(0, 2);
	l->add(0, 3);
	l->add(3, 4);
	cout << *l << endl;

	List<int> *l2 = new LinkedList<int>(*l);
	cout << *l2 << endl;

	system("PAUSE");
	
	//Menu();
	return 0;
}

// Launch the card game
void LaunchCardGame() {
	CardGame cg;
	cg.launch();
	system("PAUSE");
}

// Launch the factory
void LaunchFactory() {
	Factory f;
	f.launch();
	system("PAUSE");
}

// Launch the dictionnary
void LaunchDictionnary() {
}

// Launch the family tree
void LaunchFamilyTree() {
}

// Launch the double linked list
void LaunchDoubleLinkedList() {
}

// Show the menu
void Menu() {
	int choice = -1;
	while (choice != 0) {
		cout << "------------------------" << endl;
		cout << "Choose the exercice :" << endl << endl;
		cout << "1 - Cardgame :" << endl;
		cout << "2 - Factory" << endl;
		cout << "3 - TODO" << endl;
		cout << "4 - TODO" << endl;
		cout << "5 - TODO" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			LaunchCardGame();
			break;
		case 2:
			LaunchFactory();
			break;
		case 3:
			LaunchDictionnary();
			break;
		case 4:
			LaunchFamilyTree();
			break;
		case 5:
			LaunchDoubleLinkedList();
			break;
		default:
			break;
		}
	}
}