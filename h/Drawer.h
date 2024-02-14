#pragma once
#include "Validator.h"

class Drawer {
    // TODO: Make this look not like a static class

public:
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

    void DrawSelected(Vector2u selected, RenderWindow& window) const {
        // Refactor this part

        static const float radius = 10.0f;
        static sf::CircleShape circle(radius, 20);
        static sf::RectangleShape square(sf::Vector2f(SquareSize, SquareSize));

        square.setFillColor(Cyan);
        circle.setFillColor(Grey);

        auto pos = VectorExtentions::Unnormalize(selected);
        
        square.setPosition(pos);
        circle.setPosition(VectorExtentions::Add(pos, SquareSize / 2.0f - radius));

        window.draw(square);
        window.draw(circle);
    }

private:
    static const Color GetSquareColor(int x, int y) {
        return (x + y) % 2 == 0 ? Light : Dark;
    }
};