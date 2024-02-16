#pragma once
#include "Square.h"

class Board {
public:
    Board() {
        _board = new Square * [SquareCount];

        for (int i = 0; i < SquareCount; i++) {
            _board[i] = new Square[SquareCount]{ };
        }
    }

    void InitBoard() {
        
#define ADD_FIGURE(y, x, color, type) _board[y][x] = Square(Piece::CreatePiece(color, type, x, y));

        ADD_FIGURE(0, 0, Black, Rook);
        ADD_FIGURE(0, 7, Black, Rook);
        ADD_FIGURE(7, 0, White, Rook);
        ADD_FIGURE(7, 7, White, Rook);

        ADD_FIGURE(0, 1, Black, Knight);
        ADD_FIGURE(0, 6, Black, Knight);
        ADD_FIGURE(7, 1, White, Knight);
        ADD_FIGURE(7, 6, White, Knight);

        ADD_FIGURE(0, 2, Black, Bishop);
        ADD_FIGURE(0, 5, Black, Bishop);
        ADD_FIGURE(7, 2, White, Bishop);
        ADD_FIGURE(7, 5, White, Bishop);

        ADD_FIGURE(0, 3, Black, Queen);
        ADD_FIGURE(7, 3, White, Queen);

        ADD_FIGURE(0, 4, Black, King);
        ADD_FIGURE(7, 4, White, King);

#undef ADD_FIGURE


        for (int i = 0; i < SquareCount; i++)
        {
            _board[1][i] = Square(Piece::CreatePiece(Black, Pawn, i, 1));
            _board[6][i] = Square(Piece::CreatePiece(White, Pawn, i, 6));
        }
    }

    Square& operator[](Vector2u position) const {
        if (VectorExtentions::InBounds(position)) {
            return _board[position.y][position.x];
        }
        std::cerr << "Index out of bounds!" << std::endl;
        exit(EXIT_FAILURE);
    }

    void MoveFigure(Move move) const {
        this->operator[](move.End) = std::move(this->operator[](move.Start));
        this->operator[](move.End).SetFigurePosition(move.End);
    }

    ~Board() {
        for (int i = 0; i < SquareCount; i++) {
            delete[] _board[i];
        }
        delete[] _board;
    }

private:
	Square** _board;
};