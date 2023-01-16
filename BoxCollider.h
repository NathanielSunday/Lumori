#pragma once
#include <SFML/System/Vector2.hpp>
class BoxCollider {
public:
	/// <summary>
	/// Basic box collider constructor
	/// </summary>
	/// <param name="width">The width of the collision bo</param>
	/// <param name="height"></param>
	/// <param name="center"></param>
	BoxCollider(float width, float height, sf::Vector2f center);

	static bool checkCollision(BoxCollider a, BoxCollider b);
	bool checkCollision(BoxCollider other);
protected:
	float _width;
	float _height;
	sf::Vector2f _center;

};

