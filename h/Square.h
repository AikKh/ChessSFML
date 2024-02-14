#pragma once
#include "Piece.h"

class Square {
public:
	Square() : _hasValue(false) {};

	Square(Piece value) : _hasValue(true), _value(value) {};

	bool HasValue() const {
		return _hasValue;
	}

	void SetValue(Piece&& value) noexcept {
		_value = value;
		_hasValue = true;
	}

	void SetFigurePosition(Vector2u position) noexcept {
		_value.SetSpritePosition(VectorExtentions::Multiply(Vector2f(position), SquareSize));
	}

	Piece& GetValue() {
		if (!_hasValue)
			throw std::exception("Square doesn't have a value");

		return _value;
	}

	Square& operator=(const Square& other) {
		_value = other._value;
		_hasValue = other._hasValue;

		return *this;
	}

	Square& operator=(Square&& other) noexcept {
		if (this != &other) {
			_value = other._value;
			other._value = Piece();

			_hasValue = other._hasValue;
			other._hasValue = false;
		}
		return *this;
	}

private:
	bool _hasValue;
	Piece _value;
};