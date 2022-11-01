#include "Engine.h"

void Engine::Start(int width, int height, const std::string& name)
{
	// Actually create the SFML window using the parameters.
	sf::RenderWindow window(sf::VideoMode(width, height), name);

	// Define a clock to track delta time.
	sf::Clock clock;

	// Set the members.
	this->effect = nullptr;
	this->palette = 0;

	// Game management loop.
	while (window.isOpen())
	{
		// Capture the time since the last frame.
		sf::Time delta = clock.restart();

		// Define an event query.
		sf::Event query;

		// Handle each event this frame.
		while (window.pollEvent(query))
		{
			// We need to add a manually-invoked escape clause.
			if (query.type == sf::Event::Closed) window.close();

			// Handle events for this frame.
			OnInput(query, window);
		}

		// Update for this frame.
		OnUpdate(delta, window);

		// Render this frame.
		OnRender(window);
	}

	// Clean up the particle effect.
	if (this->effect) delete this->effect;
}

void Engine::OnInput(const sf::Event& event, sf::RenderWindow& window)
{
	bool clear = false;

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1 && this->palette != 0)
	{
		std::cout << "Switched to Small Firework!" << std::endl;
		this->palette = 0;
		clear = true;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2 && this->palette != 1)
	{
		std::cout << "Switched to Large Firework!" << std::endl;
		this->palette = 1;
		clear = true;
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3 && this->palette != 2)
	{
		std::cout << "Switched to Sparkler!" << std::endl;
		this->palette = 2;
		clear = true;
	}

	if (this->effect && clear)
	{
		delete this->effect;
		this->effect = nullptr;
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (!this->effect)
		{
			switch (this->palette)
			{
			case 0:
				this->effect = new EffectFirework(3, 6, 3);
				break;
			case 1:
				this->effect = new EffectFirework(4, 8, 4);
				break;
			case 2:
				this->effect = new EffectSparkler(2.0f, 0.2f, 2);
				break;
			default:
				this->effect = new EffectFirework(4, 8, 4);
				break;
			}
		}

		sf::Vector2i mouse = sf::Mouse::getPosition(window);

		float x = (float)mouse.x;
		float y = (float)mouse.y;

		this->effect->Start(sf::Vector2f(x, y));
	}
}

void Engine::OnUpdate(const sf::Time& delta, sf::RenderWindow& window)
{
	if (this->effect) this->effect->Update(delta);
}

void Engine::OnRender(sf::RenderWindow& window)
{
	window.clear();

	if (this->effect) this->effect->Render(window);

	window.display();
}
