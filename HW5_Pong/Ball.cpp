#include "Ball.h"

Ball::Ball(Object* parent, Sounds& sounds, int width, int height, float speed) : EllipseObject(parent), sounds(sounds)
{
	this->width = width;
	this->height = height;
	this->speed = speed;

	// Balls update last!
	this->SetDepth(10);

	// Balls are entities.
	this->SetEntity(true);
}

void Ball::Update(const sf::Time& time)
{
	// Parent update always goes first.
	EllipseObject::Update(time);

	// Extract the delta time.
	// Increment the life.
	float dt = time.asSeconds();
	this->life += dt;

	// Make sure that the ball is launched if it wasn't yet.
	if (this->life > 3 && !this->launched) this->Launch();

	// After the parent update the ball *might* be clipping into something.
	// Clipping means we can check collisions. So let's do that...

	sf::Vector2f normal; // Collision normal.
	float clip = 0; // Time "until" collision.

	// Iterate through each of the parent's children (siblings).
	for (const Object* sibling : this->GetParent()->GetChildren())
	{
		// Don't check collision with ourselves...
		if (sibling == this) continue;

		// Perform collision, handing in our plane storage by reference.
		bool collision = this->CheckCollision(sibling, clip, normal);

		// If we are clipping into our sibling...
		if (collision)
		{
			// We're going to do a bounce. Doing so has two parts:
			// First, we need to figure out how far we clipped into the triggering collider.
			// We will redirect that "overshoot" movement along the new reflection vector.
			// Second, we'll switch the velocity to the new reflection vector.

			// Reflecting a vector V on normal N is equal to [ V - 2 (V * N) N ].

			sf::Vector2f velocity = this->GetVelocity(); // Current velocity.

			// Get some movement deltas.
			sf::Vector2f movement = velocity * dt; // How far we moved this frame.
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

			// If we bumped an entity, get 10% faster for giggles.
			if (sibling->IsEntity())
			{
				this->SetVelocity(this->GetVelocity() * 1.1f);
				this->sounds.PlaySound("Paddle");
			}
			else
			{
				this->sounds.PlaySound("Wall");
			}
		}
	}
}

void Ball::Reset()
{
	// Automatically drops the ball in the middle of the screen and make it not move.
	this->SetPosition(sf::Vector2f((float)(this->width / 2), (float)(this->height / 2)));
	this->SetScale(sf::Vector2f((float)(this->width / 50), (float)(this->width / 50)));
	this->SetVelocity(sf::Vector2f());
	this->launched = false;
	this->life = 0;
}

void Ball::Launch()
{
	// Determine a random angle, in radians, to launch.
	float angle = Random::Range((float)(-M_PI / 4), (float)(M_PI / 4));

	// Now determine a random direction with PI.
	angle += (float)(Random::Range(0, 1) * M_PI);

	// Actually launch the ball using some trigonometry.
	this->SetVelocity(sf::Vector2f(this->speed * cos(angle), this->speed * sin(angle)));

	// Stops the ball from being launched per-frame.
	this->launched = true;
}

float Ball::GetTime() const
{
	return this->life;
}

bool Ball::CheckCollision(const Object* object, float& OutTime, sf::Vector2f& OutNormal)
{
	// Extract values for an AABB-ray collision.
	sf::Vector2f positionA = this->GetPosition();
	sf::Vector2f positionB = object->GetPosition();
	sf::Vector2f velocityA = this->GetVelocity();
	sf::Vector2f velocityB = object->GetVelocity();
	sf::Vector2f scaleA = this->GetScale();
	sf::Vector2f scaleB = object->GetScale();

	// I stole this algorithm from Stack Overflow. It works nicely because it coverts an
	// AABB collision into a simple inclusion check by making THE BIG AABB and a point.

	// So, because the ball is (almost) always the one moving it will be reduced to a single moving point.
	// The other object will be converted into a fixed AABB with a size equal to the sum of the scales.
	// If our point would move into THE BIG AABB within one time step, then the shape must have collided.

	// So let's get the point information.
	sf::Vector2f positionP = positionA;
	sf::Vector2f velocityP = velocityA - velocityB;

	// If the point isn't moving, there will be no collision.
	// The check goes here to avoid a divide-by-zero fault later.
	if (velocityP.x == 0 && velocityP.y == 0) return false;

	// And THE BIG AABB information.
	sf::Vector2f positionAABB = positionB;
	sf::Vector2f scaleAABB = scaleA + scaleB;

	// But we need the upper left and lower right corners.
	sf::Vector2f AABB_UpperLeft = positionAABB - scaleAABB * 0.5f;
	sf::Vector2f AABB_LowerRight = positionAABB + scaleAABB * 0.5f;

	// From here, we can compute the time it would take the point to enter and exit the box.
	// Those times should be equal to the time it takes the point to pass the certain bounds.
	// So, let's figure out how long it takes the point to pass each bound.
	// Time is equal to the distance divided by velocity.
	// Positive times mean the point has yet to pass.
	// Negative times mean the point has already passed.

	float TimeLeft = (AABB_UpperLeft.x - positionP.x) / velocityP.x;
	float TimeRight = (AABB_LowerRight.x - positionP.x) / velocityP.x;
	float TimeUpper = (AABB_UpperLeft.y - positionP.y) / velocityP.y;
	float TimeLower = (AABB_LowerRight.y - positionP.y) / velocityP.y;

	// Find the minimum times to get the closest bounds.
	float TXEnter = TimeLeft < TimeRight ? TimeLeft : TimeRight;
	float TYEnter = TimeUpper < TimeLower ? TimeUpper : TimeLower;

	// Find the maximum times to get the farthest bounds.
	float TXExit = TimeLeft > TimeRight ? TimeLeft : TimeRight;
	float TYExit = TimeUpper > TimeLower ? TimeUpper : TimeLower;

	// Find the maximum of the two closer-bound times to get the time until collision.
	// Collision starts when the point has passed the closer bounds in both directions.
	// Collision time must therefore be when the further of the two bounds is passed.
	float TEnter = TXEnter > TYEnter ? TXEnter : TYEnter;

	// Find the minimum of the two farther-bound times to get the time until collision ends.
	// Collision ends when the point has passed one of the two farther bounds.
	// Collision time must therefore be when the closer of the two bounds is passed.
	float TExit = TXExit < TYExit ? TXExit : TYExit;

	// If the time until exit is less than 0, then the point is already past the box and will not collide.
	if (TExit < 0) return false;

	// If the time until entry is greater than the time until exit, then the boxes aren't on a collision course.
	if (TEnter > TExit) return false;

	// Finally, if the time until entry is greater than 0, the boxes aren't colliding yet.
	if (TEnter > 0) return false;

	// Otherwise, they do collide and we need to report some NORMALS.
	if (TEnter == TimeLeft) OutNormal = sf::Vector2f(-1, 0); // Left collision.
	if (TEnter == TimeRight) OutNormal = sf::Vector2f(1, 0); // Right collision.
	if (TEnter == TimeUpper) OutNormal = sf::Vector2f(0, -1); // Upper collision.
	if (TEnter == TimeLower) OutNormal = sf::Vector2f(0, 1); // Lower collision.

	// Load in the time.
	OutTime = TEnter;

	// And done!
	return true;
}
