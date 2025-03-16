#pragma once
#include <SFML/Graphics.hpp>

namespace LightYear
{
	class IRender
	{
	public:
		virtual void Render(sf::RenderWindow& window) = 0;
	};
}