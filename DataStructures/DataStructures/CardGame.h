#pragma once
#include "Stack.h"

// A card color
enum Color { RED, BLACK };

/*
* A card, which has a color, a number and a bonus.
*/
struct Card {
public:
	Color color;
	int number;
	int bonus;

	// Surcharging the operator <
	friend bool operator<(const Card& l, const Card& r)
	{
		if (l.number < r.number) {
			return true;
		}

		if (l.number == r.number && (l.color == Color::BLACK && r.color == Color::RED)) {
			return true;
		}

		return false;
	}

	// Surcharging the operator ==
	friend bool operator==(const Card& l, const Card& r)
	{
		return (l.number == r.number && l.color == r.color);
	}
};

/*
* The cardgame, which arbitrates the game.
*/
class CardGame
{
public:
	CardGame();
	~CardGame();

	void launch();
private:

	// The initial deck
	Stack<Card> *deck;
	// The players' decks
	Stack<Card> *p1Deck, *p2Deck;
	// The players' gain decks
	Stack<Card> *p1Gained, *p2Gained;
};
