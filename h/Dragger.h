#pragma once
#include "Drawer.h"

class Dragger {
public:
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

	void ReleasedAt(Vector2u position, Board& board, const Validator& validator) {
		if (!_selected)
			return;

		_selected = false;

		Move move(_selectedPosition, position);

		if (VectorExtentions::InBounds(position) && validator.Validate(move, board)) {
			board.MoveFigure(move);
		}
		else {
			board[_selectedPosition].GetValue().SetSpritePosition(VectorExtentions::Unnormalize(_selectedPosition));
		}
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
};
