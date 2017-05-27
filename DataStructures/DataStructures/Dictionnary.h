#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include "BinaryTree.h"

/*
* A dictionnary cell.
*/
struct DCell {
public:
	bool endOfWord;

	bool compareLetter(char other) const {
		std::locale loc;
		return (std::toupper(other, loc) == letter);
	}

	void setLetter(char newLetter) {
		std::locale loc;
		letter = std::toupper(newLetter, loc);
	}

	char getLetter() {
		return letter;
	}

	DCell() : endOfWord(false), letter('0') {}
private:
	char letter;
};


class Dictionnary
{
public:
	Dictionnary();
	~Dictionnary();

	void launch();

private:

	void menu();

	void initAddWord();
	void initRemoveWord();
	void initShowDictionnary();
	void initSearchWord();
	void initLoadFile();

	void addWord(std::string word);
	void removeWord(std::string word);
	void showDictionnary(char* buffer, BTNode<DCell> *c, int cursor) const;
	bool searchWord(std::string word) const;
	void loadFile(std::ifstream *input);

	BinaryTree<DCell> *tree;
};
