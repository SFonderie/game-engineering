#include "Level.h"

Level::Level(Object* parent, int ID, int width, int height, const std::string& name, Sounds& sounds, const sf::Font& font) :
	Object(parent), name(name)
{
	SetScale(sf::Vector2f((float) width, (float) height));
	this->player = new Player(this, width, height, 200);

	// Create the ball and pass it the player and sounds. Ball gets faster per level.
	this->ball = new Ball(this, this->player, sounds, width, height, (float) (200 + 50 * ID));

	// Define the bounds.
	RectangleObject* lBound = new RectangleObject(this);
	RectangleObject* rBound = new RectangleObject(this);
	RectangleObject* uBound = new RectangleObject(this);

	lBound->SetPosition(sf::Vector2f((float) (width / 16 * 1), (float) (height / 2)));
	rBound->SetPosition(sf::Vector2f((float) (width / 16 * 15), (float) (height / 2)));
	uBound->SetPosition(sf::Vector2f((float) (width / 2), (float) (height / 15)));

	lBound->SetScale(sf::Vector2f((float) (width / 100), (float) (height / 15 * 13 + height / 75)));
	rBound->SetScale(sf::Vector2f((float) (width / 100), (float) (height / 15 * 13 + height / 75)));
	uBound->SetScale(sf::Vector2f((float) (width / 16 * 14 + width / 100), (float) (height / 75)));

	lBound->SetEntity(true); // Enable collision.
	rBound->SetEntity(true); // Enable collision.
	uBound->SetEntity(true); // Enable collision.

	for (int row = 0; row < ROWS; row++)
	{
		for (int i = 0; i < BRICKS; i++)
		{
			Brick* brick = new Brick(this, ID + 1);
			brick->SetPosition(sf::Vector2f((float) (width / (BRICKS + 1) * (i + 1)), (float) (height / 15 * (2 + row))));
			brick->SetScale(sf::Vector2f((float) (width / 8), (float) (height / 40)));
			this->bricks.push_back(brick);
		}
	}

	this->levelLabel = new TextObject(this, font);
	this->livesLabel = new TextObject(this, font);

	this->levelLabel->SetPosition(sf::Vector2f((float) (width - 16), (float) (height / 8 * 1)));
	this->livesLabel->SetPosition(sf::Vector2f((float) (width - 16), (float) (height / 8 * 2)));

	this->levelLabel->GetText().setCharacterSize(32);
	this->livesLabel->GetText().setCharacterSize(32);

	this->levelLabel->GetText().setString("LEVEL " + std::to_string(ID + 1));
}

Level::~Level()
{
	// Player and ball are deleted by Object (as children).
}

const std::string& Level::GetName() const
{
	return this->name;
}

Player& Level::GetPlayer() const
{
	return *this->player;
}

Ball& Level::GetBall() const
{
	return *this->ball;
}

bool Level::HasBricks() const
{
	bool alive = false;

	for (Brick* brick : this->bricks)
	{
		alive = alive || brick->IsAlive();
	}

	return alive;
}

bool Level::HasBall() const
{
	return this->ball->IsInRange();
}

bool Level::HasLives() const
{
	return this->lives > 0;
}

void Level::ResetAll()
{
	this->lives = 3; // Player gets three lives.
	this->ResetPlayer();

	for (Brick* brick : this->bricks)
	{
		brick->Reset();
	}
}

void Level::ResetPlayer()
{
	this->player->Reset();
	this->ball->Reset();

	// Update the player's lives counter.
	this->livesLabel->GetText().setString("Lives: " + std::to_string(this->lives));
}

void Level::DamagePlayer()
{
	this->lives--;
}
