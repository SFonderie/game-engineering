#ifndef OBJECT_H
#define OBJECT_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

/// <summary>
/// Represents a basic game object with a position.
/// </summary>
class Object
{

private:

	/// <summary>
	/// Pointer to the transform parent.
	/// </summary>
	Object* parent = nullptr;

	/// <summary>
	/// Array list of pointers to children.
	/// </summary>
	std::vector<Object*> children;

	/// <summary>
	/// Position of the object relative to its parent.
	/// </summary>
	sf::Vector2f position;

	/// <summary>
	/// Velocity of the object.
	/// </summary>
	sf::Vector2f velocity;

	/// <summary>
	/// Acceleration of the object.
	/// </summary>
	sf::Vector2f force;

	/// <summary>
	/// Object scale.
	/// </summary>
	sf::Vector2f scale;

	/// <summary>
	/// Represents the visual depth or z-position of this object.
	/// </summary>
	int depth = 0;

	/// <summary>
	/// Allows the object to update.
	/// </summary>
	bool active = true;

	/// <summary>
	/// Allows the object to render.
	/// </summary>
	bool visible = true;

	/// <summary>
	/// True if the object is an entity.
	/// </summary>
	bool entity = false;

	/// <summary>
	/// Compares two object pointers for custom sorting.
	/// </summary>
	static bool Compare(Object* a, Object* b);

public:

	/// <summary>
	/// Initializes the object at the local zero on the given parent.
	/// </summary>
	explicit Object(Object* parent);

	/// <summary>
	/// Initializes the object at the world zero.
	/// </summary>
	Object();

	/// <summary>
	/// Deletes children and removes itself from the parent.
	/// </summary>
	virtual ~Object();

	/// <summary>
	/// Invoked to update the object.
	/// </summary>
	virtual void Update(const sf::Time& delta);

	/// <summary>
	/// Invoked to render the object.
	/// </summary>
	virtual void Render(sf::RenderWindow& canvas);

	/// <summary>
	/// Returns a pointer to the parent object.
	/// </summary>
	Object* GetParent() const;

	/// <summary>
	/// Returns the children of this object.
	/// </summary>
	const std::vector<Object*>& GetChildren() const;

	/// <summary>
	/// Returns the object position in absolute or relative space.
	/// </summary>
	sf::Vector2f GetPosition(bool relative = false) const;

	/// <summary>
	/// Returns the object velocity.
	/// </summary>
	sf::Vector2f GetVelocity() const;

	/// <summary>
	/// Returns the object acceleration.
	/// </summary>
	sf::Vector2f GetForce() const;

	/// <summary>
	/// Returns the object scale.
	/// </summary>
	sf::Vector2f GetScale() const;

	/// <summary>
	/// Returns the visual depth of this object.
	/// </summary>
	int GetDepth() const;

	/// <summary>
	/// Check if the object is updating.
	/// </summary>
	bool IsActive() const;

	/// <summary>
	/// Check if the object is rendering.
	/// </summary>
	bool IsVisible() const;

	/// <summary>
	/// Check if the object is an entity.
	/// </summary>
	bool IsEntity() const;

	/// <summary>
	/// Sets the parent object.
	/// </summary>
	void SetParent(Object* parent);

	/// <summary>
	/// Adds the given object as a child. Children objects are managed by their parent.
	/// </summary>
	void AddChild(Object* child);

	/// <summary>
	/// Attempts to remove the given child.
	/// </summary>
	void RemoveChild(Object* child);

	/// <summary>
	/// Removes and destroys all child objects.
	/// </summary>
	void ClearChildren();

	/// <summary>
	/// Adds the given vector to the object position.
	/// </summary>
	void AddPosition(const sf::Vector2f& offset);

	/// <summary>
	/// Sets the object position to the given vector in absolute or relative space.
	/// </summary>
	void SetPosition(const sf::Vector2f& position, bool relative = false);

	/// <summary>
	/// Adds the given vector to the object velocity.
	/// </summary>
	void AddVelocity(const sf::Vector2f& impulse);

	/// <summary>
	/// Sets the object velocity to the given vector.
	/// </summary>
	void SetVelocity(const sf::Vector2f& velocity);

	/// <summary>
	/// Adds the given vector to the object acceleration.
	/// </summary>
	void AddForce(const sf::Vector2f& jolt);

	/// <summary>
	/// Sets the object acceleration to the given vector.
	/// </summary>
	void SetForce(const sf::Vector2f& force);

	/// <summary>
	/// Sets the object scale.
	/// </summary>
	void SetScale(const sf::Vector2f& scale);

	/// <summary>
	/// Sets the object visual depth or z-position.
	/// </summary>
	void SetDepth(int depth);

	/// <summary>
	/// Allows or blocks object updating.
	/// </summary>
	void SetActive(bool active);

	/// <summary>
	/// Allows or blocks object rendering.
	/// </summary>
	void SetVisible(bool visible);

	/// <summary>
	/// Sets the object's entity status.
	/// </summary>
	void SetEntity(bool entity);

	/// <summary>
	/// If both objects are entities, performs a collision check with the given object.
	/// Uses Axis-Aligned Bounding Box Ray Collision for calculation.
	/// </summary>
	/// <param name="object">Object with which to check collision.</param>
	/// <param name="outTime">Output time until collision in seconds.</param>
	/// <param name="outVector">Output collision normal vector.</param>
	/// <returns></returns>
	bool CheckCollision(const Object* object, float& outTime, sf::Vector2f& outNormal) const;

	/// <summary>
	/// Invoked whenever this object collides with another object.
	/// </summary>
	/// <param name="object">Collision object.</param>
	/// <param name="time">Time until collision in seconds.</param>
	/// <param name="normal">Collision normal.</param>
	virtual void OnCollision(const sf::Time& delta, const Object* object, float time, const sf::Vector2f& normal);

	/// <summary>
	/// Processes collision between the given objects.
	/// </summary>
	static void HandleCollision(const sf::Time& delta, Object* objectA, Object* objectB);
};

#endif
