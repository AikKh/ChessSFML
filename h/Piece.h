#pragma once
#include "AvailableMoves.h"

using namespace Constants;

class Piece {
public:
	Piece() = default;
	Piece(PieceColor color, PieceType type) : _color(color), _type(type) {};

	PieceColor GetColor() const {
		return _color;
	}

	PieceType GetType() const {
		return _type;
	}

	const Sprite& GetSprite() const {
		return _sprite;
	}

	void SetTexture(const Texture& texture) {
		_sprite.setTexture(texture);
	}

	void SetSpritePosition(Vector2f position) {
		_sprite.setPosition(position);
	}

	static Piece CreatePiece(PieceColor color, PieceType type, int x, int y) {
		Piece piece(color, type);

		piece.SetTexture(Loader::GetTexture(color, type));
		piece.SetSpritePosition(Vector2f(x * SquareSize, y * SquareSize));

		return piece;
	}

private:
	PieceColor _color;
	PieceType _type;
	Sprite _sprite;
};