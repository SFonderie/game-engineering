#include "Object.h"

// Static methods get defined first.
bool Object::Compare(Object* a, Object* b)
{
	return a->depth < b->depth;
}

// Explicit constructor just handles the parent.
Object::Object(Object* parent) : parent(parent)
{
	if (this->parent)
	{
		this->parent->AddChild(this);
	}

	// Set the scale to a default.
	this->scale = sf::Vector2f(1, 1);
}

// Default just invokes explicit.
Object::Object() : Object(nullptr)
{
	// Default constructor doesn't do anything!
}

Object::~Object()
{
	// Clear our parent.
	this->SetParent(nullptr);

	// Clear all children.
	this->ClearChildren();

	// Confirmation that we have no memory leaks.
	//std::cout << "Deleting Object" << std::endl;
}

void Object::Update(const sf::Time& delta)
{
	// Skip update if inactive.
	if (!this->active) return;

	// Handle the object physics.
	float time = delta.asSeconds();
	this->AddVelocity(this->GetForce() * time);
	this->AddPosition(this->GetVelocity() * time);

	// Propogate update to children.
	for (Object* child : this->children)
	{
		child->Update(delta);
	}
}

void Object::Render(sf::RenderWindow& canvas)
{
	// Skip render if invisible.
	if (!this->visible) return;

	// Propogate render to children.
	for (Object* child : this->children)
	{
		child->Render(canvas);
	}
}

Object* Object::GetParent() const
{
	return this->parent;
}

const std::vector<Object*>& Object::GetChildren() const
{
	return this->children;
}

sf::Vector2f Object::GetPosition(bool relative) const
{
	// If there is a parent and we want absolute position, return the sum of all positions.
	if (this->parent && !relative) return this->position + this->parent->GetPosition();

	// Otherwise, just position.
	return this->position;
}

sf::Vector2f Object::GetVelocity() const
{
	return this->velocity;
}

sf::Vector2f Object::GetForce() const
{
	return this->force;
}

sf::Vector2f Object::GetScale() const
{
	return this->scale;
}

int Object::GetDepth() const
{
	return this->depth;
}

bool Object::IsActive() const
{
	return this->active;
}

bool Object::IsVisible() const
{
	return this->visible;
}

bool Object::IsEntity() const
{
	return this->entity;
}

void Object::SetParent(Object* parent)
{
	// Remove ourselves from our parent's children.
	if (this->parent) this->parent->RemoveChild(this);

	// Actually switch parents.
	this->parent = parent;

	// Add ourselves to our new parent's children.
	if (this->parent) this->parent->AddChild(this);
}

void Object::AddChild(Object* child)
{
	// Add the new child object.
	this->children.push_back(child);

	// Sort the children based on their depth values.
	std::sort(this->children.begin(), this->children.end(), Compare);
}

void Object::RemoveChild(Object* child)
{
	// Do this standard-library-mess-of-a-command to get a pointer to the child value we want to remove.
	std::vector<Object*>::iterator it = std::find(this->children.begin(), this->children.end(), child);

	// Perform the removal only if the value at the iterator is actually our target.
	if (*it == child) this->children.erase(it);
}

void Object::ClearChildren()
{
	while (this->children.size() > 0)
	{
		// Extract the last child pointer.
		Object* child = this->children.back();

		// Delete the child.
		if (child) delete child;
	}
}

void Object::AddPosition(const sf::Vector2f& offset)
{
	this->position += offset;
}

void Object::SetPosition(const sf::Vector2f& position, bool relative)
{
	// Set position relatively.
	this->position = position;

	// Subtract parent position to make absolute.
	if (this->parent && !relative)
	{
		this->position -= this->parent->GetPosition();
	}
}

void Object::AddVelocity(const sf::Vector2f& impulse)
{
	this->velocity += impulse;
}

void Object::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Object::AddForce(const sf::Vector2f& jolt)
{
	this->force += jolt;
}

void Object::SetForce(const sf::Vector2f& force)
{
	this->force = force;
}

void Object::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
}

void Object::SetDepth(int depth)
{
	this->depth = depth;
}

void Object::SetActive(bool active)
{
	this->active = active;
}

void Object::SetVisible(bool visible)
{
	this->visible = visible;
}

void Object::SetEntity(bool entity)
{
	this->entity = entity;
}

bool Object::CheckCollision(const Object* object, float& outTime, sf::Vector2f& outNormal) const
{
	// Only do a collision check if both are entities.
	// Only do a collision check if both are active.
	if (!this->entity || !object->entity) return false;
	if (!this->active || !object->active) return false;

	// Extract values for an AABB-ray collision.
	sf::Vector2f positionA = this->GetPosition();
	sf::Vector2f positionB = object->GetPosition();
	sf::Vector2f velocityA = this->GetVelocity();
	sf::Vector2f velocityB = object->GetVelocity();
	sf::Vector2f scaleA = this->GetScale();
	sf::Vector2f scaleB = object->GetScale();

	// I stole this algorithm from Stack Overflow. It works nicely because it coverts an
	// AABB collision into a simple inclusion check by making THE BIG AABB and a point.

	// So, because I decided it would work, this object will be reduced to a single moving point.
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
	if (TEnter == TimeLeft) outNormal = sf::Vector2f(-1, 0); // Left collision.
	if (TEnter == TimeRight) outNormal = sf::Vector2f(1, 0); // Right collision.
	if (TEnter == TimeUpper) outNormal = sf::Vector2f(0, -1); // Upper collision.
	if (TEnter == TimeLower) outNormal = sf::Vector2f(0, 1); // Lower collision.

	// Load in the time.
	outTime = TEnter;

	// And done!
	return true;
}

void Object::OnCollision(const sf::Time& delta, const Object* object, float time, const sf::Vector2f& normal)
{
	// Do nothing by default.
}

void Object::HandleCollision(const sf::Time& delta, Object* objectA, Object* objectB)
{
	float time = 0;
	sf::Vector2f normalA;
	sf::Vector2f normalB;

	if (objectA->CheckCollision(objectB, time, normalA))
	{
		// Create a reflection.
		normalB -= normalA;

		// Notify both objects about collision.
		objectA->OnCollision(delta, objectB, time, normalA);
		objectB->OnCollision(delta, objectA, time, normalB);
	}
}
