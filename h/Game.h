#pragma once
#include "Dragger.h"

class Game {
public:
	Game(string title, const Drawer& drawer, Dragger& dragger, const Validator& validator)
        :  _window(VideoMode(BoardSize, BoardSize), title), _drawer(drawer), _dragger(dragger), _validator(validator) {
        
        _board.InitBoard();
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
            _drawer.DrawSelected(_dragger.GetSelected(), _window);
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

    void HandleRelease(const Event& event)
    {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            _dragger.ReleasedAt(VectorExtentions::Normalize(GetMousePosition()), _board, _validator);
        }
    }

    void HandleMoving()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _dragger.MovingAt(Centered(GetMousePosition()), _board);
        }
    }

    inline Vector2i GetMousePosition() {
        return sf::Mouse::getPosition(_window);
    }

    inline static Vector2f Centered(Vector2i position) {
        return Vector2f(position.x - SquareSize / 2, position.y - SquareSize / 2);
    }

private:
    Board _board;
	RenderWindow _window;

    Dragger& _dragger;
    const Drawer& _drawer;
    const Validator& _validator;
};


