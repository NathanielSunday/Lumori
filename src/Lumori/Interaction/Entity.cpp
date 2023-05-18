#include <Lumori/Interaction/Entity.hpp>
#include <Lumori/Engine/Resource.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(std::string spritePath, sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset, bool isFlying, bool isFixed, bool isActive) : Collider(position + colliderOffset, colliderSize, isFixed, isActive){
    m_isFlying = isFlying;
	m_sprite.setTexture(*Resource::GetTexture(spritePath));
	m_sprite.setPosition(position);
}

bool Entity::CheckZIndex(Entity a, Entity b) {
	//if a and b are both flying or neither is flying, return true if a's collider is lower in y position
	//otherwise, return false if a is the one flying
	return (a.m_isFlying == b.m_isFlying) ? a.Collider::getPosition().y < b.Collider::getPosition().y : !a.m_isFlying;
}

void Entity::move(sf::Vector2f distance) {
	m_sprite.move(distance);
	Collider::move(distance);
}

void Entity::setFlying(bool isFlying) {
    m_isFlying = isFlying;
}

void Entity::onDraw(sf::RenderTarget & target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
}