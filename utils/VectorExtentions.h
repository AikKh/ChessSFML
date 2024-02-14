#pragma once
#include "../h/Constants.h"
using namespace Constants;

#include <SFML/Graphics.hpp>
using sf::Vector2u;

class VectorExtentions {
public:
	static Vector2u Add(Vector2u vector, int value) {
		vector.x += value;
		vector.y += value;
		return vector;
	}

	static Vector2u Add(Vector2u vector, Vector2u other) {
		vector.x += other.x;
		vector.y += other.y;

		return vector;
	}

	static Vector2f Add(Vector2f vector, float value) {
		vector.x += value;
		vector.y += value;

		return vector;
	}

	static Vector2f Multiply(Vector2f vector, int value) {
		vector.x *= value;
		vector.y *= value;

		return vector;
	}

	inline static Vector2u Normalize(Vector2i position) {
		return Vector2u(position.x / SquareSize, position.y / SquareSize);
	}

	inline static Vector2f Unnormalize(Vector2u position) {
		return Vector2f(position.x * SquareSize, position.y * SquareSize);
	}

	inline static bool InBounds(const Vector2u& position) {
		return position.x >= 0 && position.x < SquareCount && position.y >= 0 && position.y < SquareCount;
	}
};