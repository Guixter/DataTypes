#pragma once
#include "LinkedStack.h"

class CardGame
{
public:
	CardGame();
	~CardGame();

	void launch();

	enum Color { RED, BLACK };
private:

	class Card {
	public:
		Color color;
		int number;
		int bonus;

		friend bool operator<(const Card& l, const Card& r)
		{
			if (l.number < r.number) {
				return true;
			}

			if (l.number == r.number && (l.color == CardGame::BLACK && r.color == CardGame::RED)) {
				return true;
			}

			return false;
		}

		friend bool operator==(const Card& l, const Card& r)
		{
			return (l.number == r.number && l.color == r.color);
		}
	};

	LinkedStack<Card> *deck;
	LinkedStack<Card> *p1Deck, *p2Deck;
	LinkedStack<Card> *p1Gained, *p2Gained;

};

