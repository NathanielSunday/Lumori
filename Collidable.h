#pragma once

#include <vector>
#include <SFML/Graphics/Transformable.hpp>


class Collidable {
public:
	/// <summary>
	/// Basic box collider constructor
	/// </summary>
	/// <param name="collider">is the </param>
	Collidable(sf::Vector2f position, sf::FloatRect collider, bool isFixed = false);
	~Collidable();
	static void CheckGlobalCollision();
	static bool CheckCollision(Collidable a, Collidable b);
	bool checkCollision(Collidable other);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getSize();
	sf::Vector2f getPosition();
protected:
	
private:
	
	void recalculate();

	static std::vector<Collidable> _colliders;
	sf::FloatRect _collider;
	sf::Vector2f _position;
	sf::Vector2f _size;
	bool _isFixed;
};

