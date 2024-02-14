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
	AdvancedValidator(const Selector& selector) : _selector(selector) {}

	bool Validate(Move move, const Board& board) const override {
		Square& square = board[move.Start];

		AvailableMoves moves = _selector.PawnMoves(move.Start, square);

		for (auto& m : moves) {
			if (move.End == m.End) {
				return true;
			}
		}

		return false;
	};

private:
	const Selector& _selector;
};