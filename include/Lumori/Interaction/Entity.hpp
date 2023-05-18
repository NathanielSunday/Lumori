#pragma once
#include <Lumori/Interaction/Collider.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

class Entity : public Collider {
public:
	Entity(std::string spritePath, sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset, bool isFlying = false, bool isFixed = false, bool isActive = true);
	//return true if b should be drawn above a
	//used to determine what order things should be drawn in
	static bool CheckZIndex(Entity a, Entity b);

	virtual void move(sf::Vector2f distance);
	void setFlying(bool isFlying);
private:
	bool m_isFlying;
	sf::Sprite m_sprite;

	virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
};

