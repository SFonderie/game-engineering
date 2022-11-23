#include "Engine.h"

void Engine::Start(int width, int height, const std::string& name)
{
	// Actually create the SFML window using the parameters.
	sf::RenderWindow window(sf::VideoMode(width, height), name);

	// Define a clock to track delta time.
	sf::Clock clock;

	// Initialize the game board.
	this->board = new Board(sf::Color(10, 10, 10));
	Object* space = new Object(this->board);

	// Create the ball.
	this->ball = new Ball(space, this->sounds, width, height, 200);

	// Create the two paddles.
	this->player = new Player(space, width, height, 200);
	this->enemy = new Enemy(space, this->ball, width, height, 200);

	this->victory = new Board(sf::Color(10, 10, 10));

	sf::Font font;

	if (font.loadFromFile("Assets/Font/MontserratBlack.ttf"))
	{
		// Add the score trackers.
		this->pScore = new TextObject(this->board, font);
		this->eScore = new TextObject(this->board, font);
		this->timer = new TextObject(this->board, font);
		this->message = new TextObject(this->victory, font);

		this->pScore->SetPosition(sf::Vector2f((float)(width / 4) - 24, (float)(height / 6)));
		this->eScore->SetPosition(sf::Vector2f((float)(width / 4 * 3) - 24, (float)(height / 6)));
		this->timer->SetPosition(sf::Vector2f((float)(width / 2) - 24, (float)(height / 4)));
		this->message->SetPosition(sf::Vector2f((float)(width / 2) - 330, (float)(height / 4)));

		this->pScore->GetText().setCharacterSize(48);
		this->eScore->GetText().setCharacterSize(48);
		this->timer->GetText().setCharacterSize(72);
		this->message->GetText().setCharacterSize(72);
	}

	// Starts the game state.
	this->ResetScore();
	this->Reset();

	// Add the board bounding objects.
	RectangleObject* upper = new RectangleObject(space);
	RectangleObject* lower = new RectangleObject(space);

	upper->SetPosition(sf::Vector2f((float)(width / 2), (float)(height / 16)));
	lower->SetPosition(sf::Vector2f((float)(width / 2), (float)(height / 16 * 15)));

	upper->SetScale(sf::Vector2f((float)(width / 10 * 9), (float)(10)));
	lower->SetScale(sf::Vector2f((float)(width / 10 * 9), (float)(10)));

	// Load sounds.
	// You may recognize these sounds from Winnie's project.
	// That would be because I yoinked them from his GitHub.
	// With permission, of course.
	// So credit to "Winnie" Nanxiang Wang for finding these sounds.
	this->sounds.LoadSound("Assets/Sounds/Paddle.wav", "Paddle");
	this->sounds.LoadSound("Assets/Sounds/Score.wav", "Score");
	this->sounds.LoadSound("Assets/Sounds/Wall.wav", "Wall");
	this->sounds.LoadSound("Assets/Sounds/Win.wav", "Win");

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

	// Delete the board and victory if it exists.
	// Doing so will also delete all child objects.
	if (this->board) delete this->board;
	if (this->victory) delete this->victory;

	// Nullify bad pointers.
	this->board = nullptr;
	this->player = nullptr;
	this->enemy = nullptr;
	this->ball = nullptr;
	this->pScore = nullptr;
	this->eScore = nullptr;
	this->timer = nullptr;
	this->victory = nullptr;
	this->message = nullptr;
}

void Engine::OnInput(const sf::Event& event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W) this->player->MoveUp(true);
		if (event.key.code == sf::Keyboard::S) this->player->MoveDown(true);

		if (event.key.code == sf::Keyboard::Space && !this->reset)
		{
			this->reset = true;
			this->ResetScore();
			this->Reset();
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W) this->player->MoveUp(false);
		if (event.key.code == sf::Keyboard::S) this->player->MoveDown(false);
		if (event.key.code == sf::Keyboard::Space && reset) this->reset = false;
	}
}

void Engine::OnUpdate(const sf::Time& delta, sf::RenderWindow& window)
{
	//Increment the timer.
	this->time += delta.asSeconds();

	// Handle the timer.
	if (this->timer && this->time < 3)
	{
		// Get a nice timer value.
		int rounded = (int)(4 - this->time);

		// Update the timer and force it to be visible.
		this->timer->GetText().setString(std::to_string(rounded));
		this->timer->SetVisible(true);
	}
	else
	{
		this->timer->SetVisible(false);
	}

	// Update the victory screen if we're in a victory condition.
	if (this->message && (this->score.x == 3 || this->score.y == 3))
	{
		this->victory->Update(delta);

		if (this->score.x == 3) this->message->GetText().setString("PLAYER VICTORY");
		if (this->score.y == 3) this->message->GetText().setString("ENEMY VICTORY");
	}

	// Update the board otherwise!
	else if (this->board)
	{
		this->board->Update(delta);
	}

	// Check for the ball escaping bounds.
	if (this->ball)
	{
		sf::Vector2f position = this->ball->GetPosition();

		// Ball slipped past the player.
		if (position.x < 0)
		{
			this->score.y++;
			this->Reset();
		}

		// Ball slipped past the enemy.
		if (position.x > window.getSize().x)
		{
			this->score.x++;
			this->Reset();
		}
	}
}

void Engine::OnRender(sf::RenderWindow& window)
{
	window.clear();

	// Update the victory screen if we're in a victory condition.
	if (this->score.x == 3 || this->score.y == 3)
	{
		if (this->victory) this->victory->Render(window);
	}

	// Update the board otherwise!
	else if (this->board)
	{
		this->board->Render(window);
	}

	window.display();
}

void Engine::Reset()
{
	this->player->Reset();
	this->enemy->Reset();
	this->ball->Reset();

	if (this->pScore) this->pScore->GetText().setString(std::to_string(this->score.x));
	if (this->eScore) this->eScore->GetText().setString(std::to_string(this->score.y));

	// Reset time.
	this->time = 0;

	if (this->score.x == 3 || this->score.y == 3)
	{
		this->sounds.PlaySound("Win");
	}
	else if (this->score.x > 0 || this->score.y > 0)
	{
		this->sounds.PlaySound("Score");
	}
}

void Engine::ResetScore()
{
	this->score.x = 0;
	this->score.y = 0;
}
