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
