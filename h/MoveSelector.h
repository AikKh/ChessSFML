#pragma once
#include "Board.h"

class Selector {
public:
	AvailableMoves GetFigureMoves(const Vector2u& position, const Board& board) const {
		Square& square = board[position];

		PieceType type = square.GetValue().GetType();
		PieceColor color = square.GetValue().GetColor();

		switch (type)
		{
		case King:
			return KingMoves(position, color, board);
		case Queen:
			return QueenMoves(position, color, board);
		case Rook:
			return RookMoves(position, color, board);
		case Bishop:
			return BishopMoves(position, color, board);
		case Knight:
			return KnightMoves(position, color, board);
		case Pawn:
			return PawnMoves(position, color, board);
		default:
			throw std::exception("Unknown piece type");
		}
	}

private:
	virtual AvailableMoves PawnMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;

	virtual AvailableMoves KnightMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;

	virtual AvailableMoves BishopMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;

	virtual AvailableMoves RookMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;

	virtual AvailableMoves QueenMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;

	virtual AvailableMoves KingMoves(const Vector2u& position, PieceColor color, const Board& board) const = 0;
};

class ClassicSelector : public Selector {
private:
	AvailableMoves PawnMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		AvailableMoves moves;

		int direction = color == White ? -1 : 1;

		Vector2u forward = Vector2u(position.x, position.y + direction);

		if (VectorExtentions::InBounds(forward) && !board[forward].HasValue()) {
			Move move = Move(position, forward);
			moves.Add(move);

			if (position.y == 1 || position.y == SquareCount - 2) {
				move.End = Vector2u(position.x, position.y + direction * 2);
				moves.Add(move);
			}
		}

		for (int side = -1; side <= 1; side += 2) {
			Vector2u sidePos = Vector2u(forward.x + side, forward.y);

			if (!VectorExtentions::InBounds(sidePos))
				continue;

			if (board[sidePos].HasValue() && color != board[sidePos].GetValue().GetColor()) {
				moves.Add(Move(position, sidePos));
			}
		}

		return moves;
	}

	AvailableMoves KnightMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		static int knightDirections[] = {
			-2, -1,
			-1, -2,
			-2,  1,
			 1, -2,
			 2, -1,
			-1,  2,
			 2,  1,
			 1,  2
		};

		AvailableMoves moves;

		for (int i = 0; i < sizeof(knightDirections) / sizeof(int); i += 2) {
			int x = knightDirections[i], y = knightDirections[i + 1];

			Vector2u end = VectorExtentions::Add(position, Vector2u(x, y));

			if (ValidPosition(color, end, board)) {
				moves.Add(Move(position, end));
			}
		}

		return moves;
	}

	AvailableMoves BishopMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		AvailableMoves moves;

		for (int x : {-1, 1}) {
			for (int y : {-1, 1}) {
				Vector2u end;

				auto lineMoves = LineMoves(Vector2u(x, y), position, color, board);
				moves += lineMoves;
			}
		}

		return moves;
	}

	AvailableMoves RookMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		AvailableMoves moves;

		static int rookDirections[] = {
			-1, 0,
			1, 0,
			0, -1,
			0, 1
		};

		for (int i = 0; i < sizeof(rookDirections) / sizeof(int); i += 2) {
			int x = rookDirections[i], y = rookDirections[i + 1];

			auto lineMoves = LineMoves(Vector2u(x, y), position, color, board);
			moves += lineMoves;
		}

		return moves;
	}

	AvailableMoves QueenMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		auto bMoves = BishopMoves(position, color, board);
		return bMoves + RookMoves(position, color, board);
	}

	AvailableMoves KingMoves(const Vector2u& position, PieceColor color, const Board& board) const override {
		AvailableMoves moves;

		for (int x : {-1, 0, 1}) {
			for (int y : {-1, 0, 1}) {
				if (x == 0 && y == 0)
					continue;

				Vector2u end = VectorExtentions::Add(position, Vector2u(x, y));

				if (ValidPosition(color, end, board)) {
					moves.Add(Move(position, end));
				}
			}
		}

		return moves;
	}

private:
	static AvailableMoves LineMoves(Vector2u direction, const Vector2u& position, PieceColor color, const Board& board) {
		AvailableMoves moves;
		Vector2u end;

		for (end = VectorExtentions::Add(position, direction);
			VectorExtentions::InBounds(end) && !board[end].HasValue();
			end = VectorExtentions::Add(end, direction))
		{
			moves.Add(Move(position, end));
		}
		if (ValidPosition(color, end, board)) {
			moves.Add(Move(position, end));
		}

		return moves;
	}

	inline static bool SameColor(PieceColor color, Square& square) {
		return color == square.GetValue().GetColor();
	}

	inline static bool ValidPosition(PieceColor color, Vector2u position, const Board& board) {
		if (VectorExtentions::InBounds(position)) {
			Square& square = board[position];

			if (square.HasValue() && SameColor(color, square)) {
				return false;
			}
			return true;
		}

		return false;
	}
};