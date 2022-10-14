#include "Game.h"

void Game::Start(int width, int height, const std::string& name)
{
	sf::RenderWindow window(sf::VideoMode(width, height), name);
	sf::Clock clock;

	// Allocate an array of garbage pointers.
	effects = new ParticleEffect * [EFFECT_BUFFER];

	// Replace the garbage with null pointers.
	for (int i = 0; i < EFFECT_BUFFER; i++)
	{
		effects[i] = nullptr;
	}

	// Game loop.
	while (window.isOpen())
	{
		sf::Time delta = clock.restart();
		sf::Event query;

		while (window.pollEvent(query))
		{
			OnInput(query, window);
		}

		OnUpdate(delta, window);
		OnRender(window);
	}

	// Clean the effects array.
	for (int i = 0; i < EFFECT_BUFFER; i++)
	{
		// Delete and reset each pointer.
		if (effects[i]) delete effects[i];
		effects[i] = nullptr;
	}

	// Delete.
	delete effects;
	effects = nullptr;
}

void Game::OnInput(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::Closed) window.close();

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(window);

		float x = (float)mouse.x;
		float y = (float)mouse.y;

		// Create the new effect at the mouse position with 16 particles.
		ParticleEffect* effect = new ParticleEffect(sf::Vector2f(x, y), 16);

		// Iterator.
		int cursor = 0;

		// Keep looping until we find a slot.
		while (effects[cursor])
		{
			// Advance.
			cursor++;

			// No slot found; clear instead.
			if (cursor >= EFFECT_BUFFER)
			{
				// Oldest slot.
				delete effects[0];
				effects[0] = nullptr;

				// Reset.
				cursor = 0;
			}
		}

		// Slot found; assign.
		effects[cursor] = effect;
	}
}

void Game::OnUpdate(const sf::Time& delta, sf::RenderWindow& window)
{
	for (int i = 0; i < EFFECT_BUFFER; i++)
	{
		if (effects[i])
		{
			// Update the generator.
			effects[i]->Update(delta);

			// Check for expiration.
			if (!effects[i]->IsAlive())
			{
				delete effects[i];
				effects[i] = nullptr;
			}
		}
	}
}

void Game::OnRender(sf::RenderWindow& canvas)
{
	canvas.clear();

	for (int i = 0; i < EFFECT_BUFFER; i++)
	{
		if (effects[i])
		{
			// Update the generator.
			effects[i]->Render(canvas);
		}
	}

	canvas.display();
}
