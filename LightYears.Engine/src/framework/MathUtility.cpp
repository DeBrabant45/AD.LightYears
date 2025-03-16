#include "framework/MathUtility.h"

namespace LightYear 
{
	const float PI = 3.1415926535;

	sf::Vector2f LightYear::RotationToVector(float rotation)
	{
		auto radians = DegreesToRadians(rotation);
		
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.f / PI);
	}
}