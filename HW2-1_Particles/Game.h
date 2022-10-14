#ifndef GAME_H
#define GAME_H

#include <list>

#include "ParticleEffect.h"

class Game
{

private:

	const int EFFECT_BUFFER = 32;

	ParticleEffect** effects;

public:

	void Start(int width, int height, const std::string& name);

	void OnInput(const sf::Event& event, sf::RenderWindow& window);

	void OnUpdate(const sf::Time& delta, sf::RenderWindow& window);

	void OnRender(sf::RenderWindow& canvas);

};

#endif
