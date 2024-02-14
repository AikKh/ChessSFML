#pragma once
#include "AvailableMoves.h"

class Board {
public:
    Board() {
        _board = new Square * [SquareCount];

        for (int i = 0; i < SquareCount; i++) {
            _board[i] = new Square[SquareCount]{ };
        }
    }

    void InitBoard() {
        

#define ADD_FIGURE(y, x, type) _board[y][x] = Square(Piece::CreatePiece(type, x, y));

        ADD_FIGURE(0, 0, B_Rook);
        ADD_FIGURE(0, 7, B_Rook);
        ADD_FIGURE(7, 0, W_Rook);
        ADD_FIGURE(7, 7, W_Rook);

        ADD_FIGURE(0, 1, B_Knight);
        ADD_FIGURE(0, 6, B_Knight);
        ADD_FIGURE(7, 1, W_Knight);
        ADD_FIGURE(7, 6, W_Knight);

        ADD_FIGURE(0, 2, B_Bishop);
        ADD_FIGURE(0, 5, B_Bishop);
        ADD_FIGURE(7, 2, W_Bishop);
        ADD_FIGURE(7, 5, W_Bishop);

        ADD_FIGURE(0, 3, B_Queen);
        ADD_FIGURE(7, 3, W_Queen);

        ADD_FIGURE(0, 4, B_King);
        ADD_FIGURE(7, 4, W_King);

#undef ADD_FIGURE


        for (int i = 0; i < SquareCount; i++)
        {
            _board[1][i] = Square(Piece::CreatePiece(B_Pawn, i, 1));
            _board[6][i] = Square(Piece::CreatePiece(W_Pawn, i, 6));
        }
    }

    Square& operator[](Vector2u position) const {
        if (VectorExtentions::InBounds(position)) {
            return _board[position.y][position.x];
        }
        std::cerr << "Index out of bounds!" << std::endl;
        exit(EXIT_FAILURE);
    }

    void MoveFigure(Move move) {
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