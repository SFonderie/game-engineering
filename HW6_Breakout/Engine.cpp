#include "Engine.h"

void Engine::Start(int width, int height, const std::string& name)
{
	// Actually create the SFML window using the parameters.
	sf::RenderWindow window(sf::VideoMode(width, height), name);

	// Define a clock to track delta time.
	sf::Clock clock;

	// Create a sound manager.
	this->sounds = new Sounds;

	// Load sounds.
	// You may recognize these sounds from Winnie's project.
	// That would be because I yoinked them from his GitHub.
	// With permission, of course.
	// So credit to "Winnie" Nanxiang Wang for finding these sounds.
	if (!this->sounds->LoadSound("Assets/Sounds/Paddle.wav", "Paddle")) return;
	if (!this->sounds->LoadSound("Assets/Sounds/Score.wav", "Score")) return;
	if (!this->sounds->LoadSound("Assets/Sounds/Wall.wav", "Wall")) return;
	if (!this->sounds->LoadSound("Assets/Sounds/Win.wav", "Win")) return;

	// Generate a font.
	// Crash if not font was loaded.
	sf::Font font;
	if (!font.loadFromFile("Assets/Font/MontserratBlack.ttf")) return;

	// Initialize the game board.
	this->board = new Board(sf::Color(10, 10, 10));

	// Creates an array of three typed *pointers*.
	this->levels = new Level * [LEVELS];

	// Now actually create the levels themselves.
	this->levels[0] = new Level(this->board, 0, width / 5 * 4, height, "Level 1", *this->sounds, font);
	this->levels[1] = new Level(this->board, 1, width / 5 * 4, height, "Level 2", *this->sounds, font);
	this->levels[2] = new Level(this->board, 2, width / 5 * 4, height, "Level 3", *this->sounds, font);

	// Create the two game over boards.
	this->winBoard = new Board(sf::Color(10, 200, 10));
	this->loseBoard = new Board(sf::Color(200, 10, 10));

	// Create some text objects. Their memory is managed by the boards.
	TextObject* win = new TextObject(this->winBoard, font, sf::Color::Black);
	TextObject* lose = new TextObject(this->loseBoard, font, sf::Color::Black);

	win->SetPosition(sf::Vector2f((float) (width / 32 * 11), (float) (height / 3)));
	lose->SetPosition(sf::Vector2f((float) (width / 32 * 10), (float) (height / 3)));

	win->GetText().setCharacterSize(48);
	win->GetText().setString("VICTORY!");
	lose->GetText().setCharacterSize(48);
	lose->GetText().setString("GAME OVER");

	// Prepare the game.
	this->Reset();

	// Game management loop.
	while (window.isOpen())
	{
		// Capture the time since the last frame.
		sf::Time delta = clock.restart();

		// Define an event query.
		sf::Event query;

		// First update the levels.
		this->PrepareLevels();

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

		// Check the level.
		OnCheck();
	}

	// Delete the board and victory if it exists.
	// Doing so will also delete all child objects.
	if (this->sounds) delete this->sounds;
	if (this->board) delete this->board;
	if (this->levels) delete this->levels;

	// And now for the decorative boards.
	if (this->winBoard) delete this->winBoard;
	if (this->loseBoard) delete this->loseBoard;
}

void Engine::PrepareLevels()
{
	for (int i = 0; i < LEVELS; i++)
	{
		this->levels[i]->SetActive(i == this->level && !this->victory && !this->failure);
		this->levels[i]->SetVisible(i == this->level && !this->victory && !this->failure);
	}
}

void Engine::OnInput(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (!this->levels[this->level]->GetBall().IsLaunched())
		{
			// GET THE MOUSE LOCATION
			sf::Vector2i iMouse = sf::Mouse::getPosition(window);
			sf::Vector2f fMouse = sf::Vector2f(iMouse);

			// LAUNCH THE MOUSE
			this->levels[this->level]->GetBall().Launch(fMouse);
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left) this->levels[this->level]->GetPlayer().MoveLeft(true);
		if (event.key.code == sf::Keyboard::Right) this->levels[this->level]->GetPlayer().MoveRight(true);

		if (event.key.code == sf::Keyboard::Space && !this->reset)
		{
			this->reset = true;
			this->Reset();
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Left) this->levels[this->level]->GetPlayer().MoveLeft(false);
		if (event.key.code == sf::Keyboard::Right) this->levels[this->level]->GetPlayer().MoveRight(false);
		if (event.key.code == sf::Keyboard::Space && reset) this->reset = false;
	}
}

void Engine::OnUpdate(const sf::Time& delta, sf::RenderWindow& window)
{
	this->board->Update(delta);

	if (this->victory) this->winBoard->Update(delta);
	if (this->failure) this->loseBoard->Update(delta);
}

void Engine::OnRender(sf::RenderWindow& window)
{
	window.clear();

	this->board->Render(window);

	if (this->victory) this->winBoard->Render(window);
	if (this->failure) this->loseBoard->Render(window);

	window.display();
}

void Engine::OnCheck()
{
	// Check if all bricks are destroyed...
	if (!this->levels[this->level]->HasBricks())
	{
		this->level++;

		if (this->level == LEVELS)
		{
			this->level = 0; // Put the level back somewhere normal.
			this->victory = true; // Player wins!

			this->sounds->PlaySound("Win");
		}
		else
		{
			this->sounds->PlaySound("Score");
		}

		this->Reset();
	}

	// Check if the ball is out of bounds...
	if (!this->levels[this->level]->HasBall())
	{
		this->levels[this->level]->DamagePlayer();
		this->levels[this->level]->ResetPlayer();
		this->sounds->PlaySound("Wall");
	}

	if (!this->levels[this->level]->HasLives())
	{
		this->failure = true; // Player loses!
	}
}

void Engine::Reset()
{
	for (int i = 0; i < LEVELS; i++)
	{
		this->levels[i]->ResetAll();
	}

	this->victory = false;
	this->failure = false;
}
