#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "CardGame.h"
#include "ArrayStack.h"

#define DECK_SIZE 100	// The size of the deck

using namespace std;

// Constructor
CardGame::CardGame()
{
	srand(time(NULL));

	deck = new ArrayStack<Card>();
	p1Deck = new ArrayStack<Card>();
	p2Deck = new ArrayStack<Card>();
	p1Gained = new ArrayStack<Card>();
	p2Gained = new ArrayStack<Card>();
}

// Destructor
CardGame::~CardGame()
{
	delete deck;
	delete p1Deck;
	delete p2Deck;
	delete p1Gained;
	delete p2Gained;
}

// Launch the process
void CardGame::launch() {

	// build the deck with a stack of 100 cards
	for (int i = 0; i < DECK_SIZE; i++) {
		Card c;
		c.number = (rand() % 10) + 1;
		c.bonus = (rand() % 4) + 1;
		c.color = static_cast<Color>(rand() % 2);

		deck->push(c);
	}

	// ask to the user how many cards per player
	int nbCardsPerPlayer = 0;
	while (nbCardsPerPlayer < 1 || nbCardsPerPlayer > 50) {
		cout << "How many cards per player ? (MIN : 1, MAX : 50)" << endl;
		cin >> nbCardsPerPlayer;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	// distribute the cards in 2 stacks
	for (int i = 0; i < nbCardsPerPlayer; i++) {
		p1Deck->push(deck->pop());
		p2Deck->push(deck->pop());
	}

	// game loop
	for (int i = 0; i < nbCardsPerPlayer; i++) {
		Card c1 = p1Deck->pop();
		Card c2 = p2Deck->pop();

		if (c1 < c2) {
			p2Gained->push(c1);
			p2Gained->push(c2);
		} else if (c1 == c2) {
			p1Gained->push(c1);
			p2Gained->push(c2);
		} else {
			p1Gained->push(c1);
			p1Gained->push(c2);
		}
	}

	// determine the winner
	float score1 = 0;
	while (!p1Gained->empty()) {
		Card c = p1Gained->pop();

		float auxScore = c.number * c.bonus;
		if (c.color == Color::RED) {
			auxScore *= 1.5f;
		}

		score1 += auxScore;
	}

	float score2 = 0;
	while (!p2Gained->empty()) {
		Card c = p2Gained->pop();

		float auxScore = c.number * c.bonus;
		if (c.color == Color::RED) {
			auxScore *= 1.5f;
		}

		score2 += auxScore;
	}

	cout << "Player 1 : " << score1 << endl;
	cout << "Player 2 : " << score2 << endl;
	if (score1 < score2) {
		cout << "Player 2 won !!" << endl;
	} else if (score1 == score2) {
		cout << "This is a draw." << endl;
	} else {
		cout << "Player 1 won !!" << endl;
	}
}