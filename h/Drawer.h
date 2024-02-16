#pragma once
#include "Validator.h"

class Drawer {
public:
    Drawer() : circle(radius, 20), square(sf::Vector2f(SquareSize, SquareSize)) {
        square.setFillColor(Cyan);
        circle.setFillColor(Grey);
    }

    void DrawFigures(Board& board, RenderWindow& window) const {
        for (int i = 0; i < SquareCount; ++i) {
            for (int j = 0; j < SquareCount; ++j) {
                Square& square = board[Vector2u(i, j)];

                if (!square.HasValue()) {
                    continue;
                }
                window.draw(square.GetValue().GetSprite());
            }
        }
    }

    void DrawBoard(RenderWindow& window) const {
        static sf::RectangleShape square(sf::Vector2f(SquareSize, SquareSize));

        for (int i = 0; i < SquareCount; ++i) {
            for (int j = 0; j < SquareCount; ++j) {
                square.setPosition(i * SquareSize, j * SquareSize);
                square.setFillColor(GetSquareColor(i, j));

                window.draw(square);
            }
        }
    }

    void DrawSelected(Vector2u selectedPos, RenderWindow& window) {
        auto pos = VectorExtentions::Unnormalize(selectedPos);
        
        square.setPosition(pos);
        window.draw(square);
    }

    void MarkPossibleMoves(const Square& selectedSquare, RenderWindow& window) {
        AvailableMoves moves = selectedSquare.GetMoves();

        for (const auto& move : moves) {
            circle.setPosition(CenterCircle(VectorExtentions::Unnormalize(move.End), radius));
            window.draw(circle);
        }
    }

private:
    static Color GetSquareColor(int x, int y) {
        return (x + y) % 2 == 0 ? Light : Dark;
    }

    inline static Vector2f CenterCircle(Vector2f position, float radius) {
        return VectorExtentions::Add(position, SquareSize / 2.0f - radius);
    }

private:
    const float radius = 10.0f;

    sf::CircleShape circle;
    sf::RectangleShape square;
};