#include "IEffect.h"

sf::Color IEffect::PickColor()
{
	switch (Random::Range(0, 6))
	{
	case 0: return sf::Color(255, 000, 000); // Full Red
	case 1: return sf::Color(255, 128, 000); // Orange
	case 2: return sf::Color(255, 200, 000); // Yellow
	case 3: return sf::Color(000, 255, 000); // Green
	case 4: return sf::Color(000, 128, 255); // Blue
	case 5: return sf::Color(128, 000, 255); // Purple
	case 6: return sf::Color(255, 000, 255); // Magenta

	default: return sf::Color::White;
	}
}

sf::Vector2f IEffect::GetGravity()
{
	return sf::Vector2f(0, 100);
}
