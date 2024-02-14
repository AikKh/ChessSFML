#pragma once
#include "Square.h"

struct Move {
	Move(Vector2u start, Vector2u end) : Start(start), End(end) {};

	sf::Vector2u Start;
	sf::Vector2u End;

	bool operator==(const Move& other) const {
		return Start == other.Start && End == other.End;
	}
};