#pragma once
#include "Dragger.h"

class Game {
public:
	Game(string title, Drawer& drawer, Dragger& dragger, const Selector& selector)
        :  _window(VideoMode(BoardSize, BoardSize), title), _drawer(drawer), _dragger(dragger), _selector(selector) {
        
        _board.InitBoard();
        UpdateBoard();
    }

	void Run() {
        while (_window.isOpen())
        {
            HandleEvent();

            _window.clear();
            HandleDrawing();
            _window.display();
        }
	}

private:
    void HandleDrawing() {
        _drawer.DrawBoard(_window);

        if (_dragger.Selected()) {
            Vector2u selected = _dragger.GetSelected();

            _drawer.DrawSelected(selected, _window);
            _drawer.MarkPossibleMoves(_board[selected], _window);
        }

        _drawer.DrawFigures(_board, _window);
    }

    void HandleEvent() {
        Event event;
        while (_window.pollEvent(event))
        {
            HandleClosing(event);
            HandlePress(event);
            HandleMoving();
            HandleRelease(event);
        }
    }

    void HandleClosing(const Event& event)
    {
        if (event.type == Event::Closed)
            _window.close();
    }

    void HandlePress(const Event& event) 
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            _dragger.PressedAt(VectorExtentions::Normalize(GetMousePosition()), _board);
        }
    }

    void HandleMoving()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _dragger.MovingAt(Centered(GetMousePosition()), _board);
        }
    }

    void HandleRelease(const Event& event)
    {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (_dragger.ReleasedAt(VectorExtentions::Normalize(GetMousePosition()), _board)) {
                UpdateBoard();
            }
        }
    }

    void UpdateBoard() const {
        for (int i = 0; i < SquareCount; i++)
        {
            for (int j = 0; j < SquareCount; j++)
            {
                auto position = Vector2u(j, i);

                Square& square = _board[position];

                if (!square.HasValue())
                    continue;

                square.SetMoves(_selector.GetFigureMoves(position, _board));
            }
        }
    }

    inline Vector2i GetMousePosition() {
        return sf::Mouse::getPosition(_window);
    }

    // Move to extentions
    inline static Vector2f Centered(Vector2i position) {
        return Vector2f(position.x - SquareSize / 2, position.y - SquareSize / 2);
    }

    void DrawBoard() const {
        for (int i = 0; i < SquareCount; i++)
        {
            for (int j = 0; j < SquareCount; j++)
            {
                auto position = Vector2u(j, i);
                Square& square = _board[position];
                cout << square.HasValue() << " ";
            }
            cout << "\n";
        }
    }

private:
    Board _board;
	RenderWindow _window;

    Dragger& _dragger;
    Drawer& _drawer;
    const Selector& _selector;
};


