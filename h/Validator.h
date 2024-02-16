#pragma once
#include "MoveSelector.h"

class Validator {
public:
	virtual bool Validate(Move move, const Board& board) const = 0;
};

class BasicValidator : public Validator {
public:
	bool Validate(Move move, const Board& board) const override {
		return true;
	};
};

class AdvancedValidator : public Validator {
public:
	bool Validate(Move move, const Board& board) const override {
		Square& square = board[move.Start];

		AvailableMoves moves = square.GetMoves();

		for (auto& m : moves) {
			if (move.End == m.End) {
				return true;
			}
		}

		return false;
	};
};