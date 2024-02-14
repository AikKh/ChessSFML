#pragma once
#include "Loader.h"

using namespace Constants;

class Piece {
public:
	Piece() = default;
	Piece(PieceType type) : _type(type) {};

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

	string ToString() {
		switch (_type) {
			case W_King:   return "White King";
			case W_Queen:  return "White Queen";
			case W_Rook:   return "White Rook";
			case W_Bishop: return "White Bishop";
			case W_Knight: return "White Knight";
			case W_Pawn:   return "White Pawn";
			case B_King:   return "Black King";
			case B_Queen:  return "Black Queen";
			case B_Rook:   return "Black Rook";
			case B_Bishop: return "Black Bishop";
			case B_Knight: return "Black Knight";
			case B_Pawn:   return "Black Pawn";
			default:       return "Unknown Piece";
		}
	}

	static Piece CreatePiece(PieceType type, int x, int y) {
		Piece piece(type);

		piece.SetTexture(Loader::TextureMapper.at(type));
		piece.SetSpritePosition(Vector2f(x * SquareSize, y * SquareSize));

		return piece;
	}

private:
	PieceType _type;
	Sprite _sprite;
};