#pragma once

#include <SFML/Graphics.hpp>

namespace LightYear
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	template<typename T>
	float GetVectorLength(const sf::Vector2<T>& vector) 
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amount)
	{
		vectorToScale.x *= amount;
		vectorToScale.y *= amount;

		return vectorToScale;
	}

	template<typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
	{
		auto length = GetVectorLength<T>(vector);
		if (length == 0.f)
			return vector;

		return ScaleVector(vector, 1.0 / length);
	}
}