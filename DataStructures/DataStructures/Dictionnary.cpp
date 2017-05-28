#include "stdafx.h"
#include "Dictionnary.h"
#include <iostream>
#include <fstream>

using namespace std;

Dictionnary::Dictionnary()
{
	tree = new BinaryTree<DCell>();

	// Add the root
	DCell c;
	tree->add(c, NULL, BinaryTree<DCell>::INSERTION_TYPE::LEFT);
}

Dictionnary::~Dictionnary()
{
	delete tree;
}


void Dictionnary::launch() {
	menu();
}

void Dictionnary::menu() {
	int choice = -1;
	while (choice != 0) {
		cout << endl;
		cout << "------------------------" << endl;
		cout << "1 - Add a word :" << endl;
		cout << "2 - Remove a word" << endl;
		cout << "3 - Show the dictionnary" << endl;
		cout << "4 - Search for a word" << endl;
		cout << "5 - Load a file" << endl;
		cout << "0 - EXIT" << endl;

		cin >> choice;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl;

		switch (choice) {
		case 0:
			break;
		case 1:
			initAddWord();
			break;
		case 2:
			initRemoveWord();
			break;
		case 3:
			initShowDictionnary();
			break;
		case 4:
			initSearchWord();
			break;
		case 5:
			initLoadFile();
			break;
		default:
			break;
		}
	}
}

void Dictionnary::initAddWord() {
	// Ask for the word to add
	cout << "Which word ? ";
	string word;
	getline(cin, word);
	if (searchWord(word)) {
		cout << "The word " << word << " is already in the dictionnary." << endl;
		return;
	}

	// Add the word to the dictionnary
	addWord(word);
}

void Dictionnary::initRemoveWord() {
	// Ask for the word to remove
	cout << "Which word ? ";
	string word;
	getline(cin, word);
	if (!searchWord(word)) {
		cout << "The word " << word << " is not in the dictionnary." << endl;
		return;
	}

	// Remove the word from the dictionnary
	removeWord(word);
}

void Dictionnary::initShowDictionnary() {
	// Create a buffer
	char* buffer = new char[100];

	// Show the dictionnary
	showDictionnary(buffer, tree->root()->getLeftChild(), 0);

	// Delete the buffer
	delete[] buffer;
}

void Dictionnary::initSearchWord() {
	// Ask for the word to search
	cout << "Which word ? ";
	string word;
	getline(cin, word);

	// Search the word in the dictionnary
	if (searchWord(word)) {
		cout << "The word " << word << " is in the dictionnary." << endl;
	} else {
		cout << "The word " << word << " is not in the dictionnary." << endl;
	}
}

void Dictionnary::initLoadFile() {
	// Ask for the file to search
	cout << "Which file ? Dictionnaries/";
	string file;
	getline(cin, file);

	ifstream *input = new ifstream("Dictionnaries/" + file);

	if (input->fail()) {
		cout << "The file " << file << " is not available." << endl;
	} else {
		this->loadFile(input);
		cout << "The dictionnary " << file << " has been loaded." << endl;
	}
	
	input->close();
	delete input;
}

void Dictionnary::addWord(string w) {
	BTNode<DCell>* parent = tree->root();
	for (string::size_type i = 0; i < w.size(); i++) {
		BTNode<DCell>* firstChild = parent->getLeftChild();

		// If there is no alternative
		if (firstChild == NULL) {
			DCell c;
			c.setLetter(w[i]);
			tree->add(c, parent, BinaryTree<DCell>::INSERTION_TYPE::LEFT);
			parent = parent->getLeftChild();
			continue;
		}

		// Search the current letter in the alternatives
		BTNode<DCell>* n = firstChild;
		BTNode<DCell>* lastNode = NULL;
		while (n != NULL && (n->getData().compareLetter(w[i]) < 0)) {
			lastNode = n;
			n = n->getRightChild();
		}

		if (n == NULL) {
			// The current letter is to be added at the end
			DCell c;
			c.setLetter(w[i]);
			parent = tree->add(c, lastNode, BinaryTree<DCell>::INSERTION_TYPE::RIGHT);
		} else if (n->getData().compareLetter(w[i]) == 0) {
			// The current letter is in the alternatives
			parent = n;
		} else if (lastNode == NULL) {
			// The current letter is to be added at the beginning
			DCell c;
			c.setLetter(w[i]);
			BTNode<DCell>* newNode = new BTNode<DCell>(c);
			BTNode<DCell>* nextNode = parent->getLeftChild();

			newNode->setRightChild(nextNode);
			if (nextNode != NULL) {
				nextNode->setParent(newNode);
			}

			newNode->setParent(parent);
			parent->setLeftChild(newNode);

			parent = newNode;
		} else {
			// The current letter is to be added between two others
			DCell c;
			c.setLetter(w[i]);
			BTNode<DCell>* newNode = new BTNode<DCell>(c);
			BTNode<DCell>* nextNode = lastNode->getRightChild();

			newNode->setRightChild(nextNode);
			if (nextNode != NULL) {
				nextNode->setParent(newNode);
			}

			newNode->setParent(lastNode);
			lastNode->setRightChild(newNode);

			parent = newNode;
		}
	}

	// Set the end of word
	DCell c = parent->getData();
	c.endOfWord = true;
	parent->setData(c);
}

void Dictionnary::removeWord(string w) {
	BTNode<DCell>* n = tree->root();
	for (string::size_type i = 0; i < w.size(); i++) {
		n = n->getLeftChild();

		// Search the current letter in the alternatives
		while (n != NULL && (n->getData().compareLetter(w[i]) != 0)) {
			n = n->getRightChild();
		}

		if (n == NULL || (n->getData().compareLetter(w[i]) != 0)) {
			return;
		}
	}

	// Set the end of word
	DCell c = n->getData();
	c.endOfWord = false;
	n->setData(c);
}

void Dictionnary::showDictionnary(char* buffer, BTNode<DCell> *c, int cursor) const {
	if (c == NULL) {
		return;
	}

	// Set the current letter in the buffer
	buffer[cursor] = c->getData().getLetter();

	// Print the buffer if this is an end of word
	if (c->getData().endOfWord) {
		for (int i = 0; i <= cursor; i++) {
			cout << buffer[i];
		}
		cout << endl;
	}

	// Print the "children words"
	showDictionnary(buffer, c->getLeftChild(), cursor + 1);

	// Print the alternatives
	showDictionnary(buffer, c->getRightChild(), cursor);
}

bool Dictionnary::searchWord(string w) const {
	BTNode<DCell>* n = tree->root();
	for (string::size_type i = 0; i < w.size(); i++) {
		n = n->getLeftChild();

		// Search the current letter in the alternatives
		while (n != NULL && (n->getData().compareLetter(w[i]) < 0)) {
			n = n->getRightChild();
		}

		if (n == NULL || (n->getData().compareLetter(w[i]) != 0)) {
			return false;
		}
	}

	return (n->getData().endOfWord);
}

void Dictionnary::loadFile(ifstream *input) {

	char* buffer = new char[100];
	while (!input->eof()) {
		input->getline(buffer, 100);
		string s(buffer);
		if (!searchWord(s)) {
			addWord(s);
		}
	}

	delete[] buffer;
}