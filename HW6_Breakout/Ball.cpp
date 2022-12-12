#include "Ball.h"

Ball::Ball(Object* parent, const Player* player, Sounds& sounds, int width, int height, float speed) : EllipseObject(parent), sounds(sounds)
{
	this->player = player;

	this->width = width;
	this->height = height;
	this->speed = speed;

	// Balls update last!
	this->SetDepth(10);

	// Balls are entities.
	this->SetEntity(true);
}

void Ball::Update(const sf::Time& delta)
{
	// Parent update always goes first.
	EllipseObject::Update(delta);

	// After the parent update the ball *might* be clipping into something.
	// Clipping means we can check collisions. So let's do that...

	// Iterate through each of the parent's children (siblings).
	for (Object* sibling : this->GetParent()->GetChildren())
	{
		// Don't check collision with ourselves...
		if (sibling == this) continue;

		// Actually handle the collisions!
		HandleCollision(delta, this, sibling);
	}
}

void Ball::OnCollision(const sf::Time& delta, const Object* object, float clip, const sf::Vector2f& normal)
{
	// We're going to do a bounce. Doing so has two parts:
	// First, we need to figure out how far we clipped into the triggering collider.
	// We will redirect that "overshoot" movement along the new reflection vector.
	// Second, we'll switch the velocity to the new reflection vector.

	// Reflecting a vector V on normal N is equal to [ V - 2 (V * N) N ].

	float time = delta.asSeconds(); // Delta time.

	sf::Vector2f velocity = this->GetVelocity(); // Current velocity.

	// Get some movement deltas.
	sf::Vector2f movement = velocity * time; // How far we moved this frame.
	sf::Vector2f clipping = velocity * clip; // Negative "overshoot" vector.

	// Calculate movement segments.
	sf::Vector2f safe = movement + clipping; // The part of movement that DIDN'T collide.
	sf::Vector2f unsafe = movement - safe; // The part of movement that DID collide.

	// There's no vector math (for some reason) so I'll do it myself.
	float uDot = (unsafe.x * normal.x) + (unsafe.y * normal.y);
	float vDot = (velocity.x * normal.x) + (velocity.y * normal.y);

	// Move the ball back by the clip vector.
	this->AddPosition(clipping);

	// Move the ball forward by the reflection [ U - 2 ( U * N ) N ]
	this->AddPosition(unsafe - 2 * uDot * normal);

	// Switch the velocity to the reflection [ V - 2 ( V * N ) N ]
	this->SetVelocity(velocity - 2 * vDot * normal);

	// If we bumped the player paddle, get 10% faster for giggles.
	if (object == this->player)
	{
		this->SetVelocity(this->GetVelocity() * 1.05f);
	}

	this->sounds.PlaySound("Paddle");
}

void Ball::Reset()
{
	// Automatically drops the ball in the middle of the screen and make it not move.
	this->SetPosition(sf::Vector2f((float) (this->width / 2), (float) (this->height / 10 * 8)));
	this->SetScale(sf::Vector2f((float) (this->width / 50), (float) (this->width / 50)));
	this->SetVelocity(sf::Vector2f());
	this->launched = false;
}

void Ball::Launch(const sf::Vector2f& mouse)
{
	sf::Vector2f dir = mouse - this->GetPosition();
	float dot = (dir.x * dir.x) + (dir.y * dir.y);
	dir *= (float) sqrt(1 / dot);

	// Actually launch the ball.
	this->SetVelocity(dir * this->speed);

	// Stops the ball from being launched per-frame.
	this->launched = true;
}

bool Ball::IsLaunched() const
{
	return this->launched;
}

bool Ball::IsInRange() const
{
	sf::Vector2f bound = this->player->GetPosition() + this->player->GetScale();
	return this->GetPosition().y <= bound.y;
}
