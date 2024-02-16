#pragma once
#include "Drawer.h"

class Dragger {
public:
	Dragger(const Validator& validator) : _validator(validator) {};

	void PressedAt(Vector2u position, Board& board) {
		if (board[position].HasValue()) {
			_selected = true;
			_selectedPosition = position;
		}
	}

	void MovingAt(Vector2f positionPx, Board& board) const {
		if (!_selected)
			return;

		board[_selectedPosition].GetValue().SetSpritePosition(positionPx);
	}

	bool ReleasedAt(Vector2u position, Board& board) {
		if (!_selected)
			return false;

		_selected = false;

		Move move(_selectedPosition, position);

		if (VectorExtentions::InBounds(position) && _validator.Validate(move, board)) {
			board.MoveFigure(move);
			return true;
		}
		board[_selectedPosition].GetValue().SetSpritePosition(VectorExtentions::Unnormalize(_selectedPosition));
		return false;
	}

	Vector2u GetSelected() const {
		return _selectedPosition;
	}

	bool Selected() const {
		return _selected;
	}

private:
	bool _selected = false;
	Vector2u _selectedPosition;

	const Validator& _validator;
};
