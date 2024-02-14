#pragma once
#include "Board.h"

using GetMovesDelegate = std::function<AvailableMoves(Vector2u, const Board&)>;

class Selector {
public:
	//const GetMovesDelegate& GetFigureStrategy(PieceType type);

//private:
	virtual AvailableMoves PawnMoves(const Vector2u& position, Square& square) const = 0;
};

class ClassicSelector : public Selector {
public:
	AvailableMoves PawnMoves(const Vector2u& position, Square& square) const override {
		PieceType type = square.GetValue().GetType();

		int direction = type == W_Pawn ? -1 : 1;

		Move move = Move(position, Vector2u(position.x, position.y + direction));

		AvailableMoves moves;
		moves.Add(move);

		if (position.y == 1 || position.y == 6) {
			move.End = Vector2u(position.x, position.y + direction * 2);
			moves.Add(move);
		}

		return moves;
	}
};