#include "Collidable.hpp"
#include "Console.hpp"
#include "Resource.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

std::vector<Collidable*> Collidable::Colliders;
bool Collidable::DisplayColliders;

Collidable::Collidable(sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset, bool isFixed, bool isActive) {
	m_isFixed = isFixed;
	m_isActive = isActive;
	m_position = position;
	m_colliderOffset = colliderOffset;
	m_collider = sf::FloatRect(position, colliderSize);
	recalculate();
	Colliders.push_back(this);
}

Collidable::Collidable(std::string spritePath, sf::Vector2f position, sf::Vector2f colliderSize, sf::Vector2f colliderOffset, bool isFlying, bool isFixed, bool isActive) : Collidable(position, colliderSize, colliderOffset, isFixed, isActive) {
	m_isFlying = isFlying;
	m_sprite.setTexture(*Resource::GetTexture(spritePath));
	m_sprite.setPosition(position);
}

void Collidable::CheckGlobalCollision() {
	if (Colliders.size() < 2) return;
	for (int i = 0; i < Colliders.size() - 1; ++i) {
		for (int j = i; j < Colliders.size(); ++j) {
			Collidable* iCollider = Colliders.at(i);
			Collidable* jCollider = Colliders.at(j);

			if (iCollider->m_isFixed && jCollider->m_isFixed) continue;
			if (!iCollider->m_isActive || !jCollider->m_isActive) continue;
			if (jCollider == iCollider) continue;

			sf::FloatRect intersection;
			if (!iCollider->m_collider.intersects(jCollider->m_collider, intersection)) continue;

			sf::Vector2f overlap(
				(intersection.width <= intersection.height) ? intersection.width : 0.0f,
				(intersection.height <= intersection.width) ? intersection.height : 0.0f
			);

			//the direction object j would have to move
			//i.x - j.x > 0, 1
			//i.y - j.y > 0, 1
			sf::Vector2f iDir(
				iCollider->m_position.x - jCollider->m_position.x < 0 ? -1 : 1,
				iCollider->m_position.y - jCollider->m_position.y < 0 ? -1 : 1
			);

			if (!iCollider->m_isFixed && !jCollider->m_isFixed) overlap *= 0.5f;
			if (!iCollider->m_isFixed) iCollider->move(sf::Vector2f(overlap.x * iDir.x, overlap.y * iDir.y));
			if (!jCollider->m_isFixed) jCollider->move(sf::Vector2f(overlap.x * -iDir.x, overlap.y * -iDir.y));
		}
	}
}

bool Collidable::CheckCollision(Collidable a, Collidable b) {
	return a.m_collider.intersects(b.m_collider);
}

bool Collidable::zIndex(Collidable* a, Collidable* b) {
	//if a and b are both flying or neither is flying, return true if a is lower in y position
	//otherwise, return false if a is the one flying
	return (a->m_isFlying == b->m_isFlying) ? a->m_position.y < b->m_position.y : !a->m_isFlying;
}

void Collidable::SetDisplayColliders(bool display) {
	DisplayColliders = display;
} 

bool Collidable::checkCollision(Collidable other) {
	return m_collider.intersects(other.m_collider);
}

void Collidable::move(sf::Vector2f distance) {
	m_position += distance;
	recalculate();
}

void Collidable::setPosition(sf::Vector2f position) {
	m_position = position;
	recalculate();
}

void Collidable::setColliderSize(sf::Vector2f colliderSize) {
	m_collider.width = colliderSize.x;
	m_collider.height = colliderSize.y;
	recalculate();
}

void Collidable::setColliderOffset(sf::Vector2f colliderOffset) {
	m_colliderOffset = colliderOffset;
	recalculate();
}

void Collidable::setFlying(bool isFlying) { m_isFlying = isFlying; }
void Collidable::setFixed(bool isFixed) { m_isFixed = isFixed; }
void Collidable::setActive(bool isActive) { m_isActive = isActive; }

sf::Vector2f Collidable::getPosition() { return m_position; }
bool Collidable::isFlying() { return m_isFlying; }
bool Collidable::isFixed() { return m_isFixed; }
bool Collidable::isActive() { return m_isActive; }

void Collidable::recalculate() {
	m_collider.left = m_position.x + m_colliderOffset.x;
	m_collider.top = m_position.y + m_colliderOffset.y;
	m_sprite.setPosition(m_position);
}

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_sprite.getTexture() != nullptr) target.draw(m_sprite, states);
	if (!DisplayColliders) return;
	sf::RectangleShape colliderShape;
	colliderShape.setSize(sf::Vector2f(m_collider.width, m_collider.height));
	colliderShape.setPosition(m_collider.left, m_collider.top);
	colliderShape.setOutlineColor(sf::Color::Cyan);
	colliderShape.setOutlineThickness(0.5f);
	colliderShape.setFillColor(sf::Color::Transparent);
	target.draw(colliderShape, states);
}

Collidable::~Collidable() {
	for (int i = 0; i < Colliders.size(); ++i)
		if (Colliders.at(i) == this) {
			Colliders.erase(Colliders.begin() + i);
			break;
		}

}
