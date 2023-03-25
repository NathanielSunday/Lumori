#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Collidable : public sf::Drawable {
public:
	//Basic box collider constructor
	Collidable(sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset = sf::Vector2f(0, 0), bool isFixed = false, bool isActive = true);
	Collidable(std::string spritePath, sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset = sf::Vector2f(0, 0), bool isFlying = false, bool isFixed = false, bool isActive = true);
	~Collidable();
	//Checks if any colliders are currently colliding, and attempts to fix them. This should be called every loop.
	static void CheckGlobalCollision();
	static bool CheckCollision(Collidable a, Collidable b);
	//return true if a's y position is less than b's
	//used to determine what order things should be drawn in
	static bool zIndex(Collidable* a, Collidable* b);
	//do you want colliders to be displayed?
	static void SetDisplayColliders(bool display = true);
	bool checkCollision(Collidable other);
	//Move the position of the object by a certain distance.
	void move(sf::Vector2f distance);
	//Set the position of the object.
	void setPosition(sf::Vector2f position);
	void setColliderSize(sf::Vector2f colliderSize);
	void setColliderOffset(sf::Vector2f colliderOffset);
	void setFlying(bool isFlying = true);
	void setFixed(bool isFixed = true);
	void setActive(bool isActive = true);
	sf::Vector2f getPosition();
	bool isFlying();
	bool isFixed();
	bool isActive();
private:
	void recalculate();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//should colliders be displayed?
	static bool DisplayColliders;
	static std::vector<Collidable*> Colliders;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::FloatRect m_collider;
	sf::Vector2f m_colliderOffset;
	//used for zIndex checks
	bool m_isFlying;
	//immoveable object
	bool m_isFixed;
	//if this is interactable at all
	bool m_isActive;
};