#include <Lumori/Interaction/Collider.hpp>
#include <Lumori/Engine/Console.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

std::vector<Collider*> Collider::m_Colliders;
bool Collider::m_DisplayColliders;

Collider::Collider(sf::Vector2f position, sf::Vector2f size, bool isFixed, bool isActive) {
    m_isFixed = isFixed;
    m_isActive = isActive;
    m_collider = sf::FloatRect(position, size);
	
    m_Colliders.push_back(this);
}

Collider::~Collider() {
	Console::Debug("Destructing collider");
}

void Collider::GlobalCollision() {
	//remove unique shared_ptr when found
	if (m_Colliders.size() < 2) return;
	for (int i = 0; i < m_Colliders.size() - 1; ++i) {
		for (int j = i + 1; j < m_Colliders.size(); ++j) {			
			Collider* iCollider = m_Colliders.at(i);
			Collider* jCollider = m_Colliders.at(j);

			/* desired
			a1 f1 a2 f2 | s
			---------------
			0  0  0  0 | 1
			0  0  0  1 | 1
			0  0  1  0 | 1
			0  0  1  1 | 0
			0  1  0  0 | 1
			0  1  0  1 | 1
			0  1  1  0 | 1
			0  1  1  1 | 1
			1  0  0  0 | 1
			1  0  0  1 | 1
			1  0  1  0 | 0
			1  0  1  1 | 0
			1  1  0  0 | 0
			1  1  0  1 | 1
			1  1  1  0 | 0
			1  1  1  1 | 1
			*/
			if ((!iCollider->isFixed() && !jCollider->isActive()) || (!iCollider->isActive() && !jCollider->isFixed()) || (iCollider->isFixed() && jCollider->isFixed())) continue;

			sf::FloatRect intersection;
			if (!iCollider->collides(*jCollider, intersection)) continue;

			sf::Vector2f overlap(
				(intersection.width <= intersection.height) ? intersection.width : 0.0f,
				(intersection.height <= intersection.width) ? intersection.height : 0.0f
			);

			//the direction object j would have to move
			//i.x - j.x > 0, 1
			//i.y - j.y > 0, 1
			sf::Vector2f iDir(
				iCollider->getPosition().x - jCollider->getPosition().x < 0 ? -1 : 1,
				iCollider->getPosition().y - jCollider->getPosition().y < 0 ? -1 : 1
			);

			if (!iCollider->isFixed() && !jCollider->isFixed()) overlap *= 0.5f;
			if (!iCollider->isFixed()) iCollider->move(sf::Vector2f(overlap.x * iDir.x, overlap.y * iDir.y));
			if (!jCollider->isFixed()) jCollider->move(sf::Vector2f(overlap.x * -iDir.x, overlap.y * -iDir.y));
		}
	}
}

void Collider::SetDisplayColliders(bool display) {
	m_DisplayColliders = display;
	Console::Info("Display colliders: " + std::to_string(display));
}

bool Collider::collides(Collider& other) { 
	return m_collider.intersects(other.m_collider); 
}

bool Collider::collides(Collider& other, sf::FloatRect& intersection) { 
	return m_collider.intersects(other.m_collider, intersection); 
}

void Collider::move(sf::Vector2f distance) {
    m_collider.left += distance.x;
    m_collider.top += distance.y;
}

void Collider::setPosition(sf::Vector2f position) {
    m_collider.left = position.x;
    m_collider.top = position.y;
}

void Collider::setSize(sf::Vector2f size) {
    m_collider.width = size.x;
    m_collider.height = size.y;
}

void Collider::setFixed(bool isFixed) { 
	m_isFixed = isFixed; 
}

void Collider::setActive(bool isActive) { 
	m_isActive = isActive; 
}

sf::Vector2f Collider::getPosition() { 
	return sf::Vector2f(m_collider.left, m_collider.top); 
}

sf::Vector2f Collider::getSize() { 
	return sf::Vector2f(m_collider.width, m_collider.height); 
}

bool Collider::isFixed() { 
	return m_isFixed; 
}

bool Collider::isActive() { 
	return m_isActive; 
}

void Collider::onDraw(sf::RenderTarget & target, sf::RenderStates states) const {
	//cant be pure virtual due to the collider physics stack
}

void Collider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	onDraw(target, states);
	if (!m_DisplayColliders) return;
	float thickness = 0.3f;
	sf::RectangleShape colliderShape;
	colliderShape.setSize(sf::Vector2f(m_collider.width, m_collider.height));
	colliderShape.setPosition(m_collider.left, m_collider.top);
	colliderShape.setOutlineColor(sf::Color::Cyan);
	colliderShape.setOutlineThickness(thickness);
	colliderShape.setFillColor(sf::Color::Transparent);
	sf::RectangleShape point;
	point.setSize(sf::Vector2f(thickness* 2, thickness* 2));
	point.setPosition(m_collider.left - thickness, m_collider.top - thickness);
	point.setFillColor(sf::Color::Red);
	target.draw(colliderShape, states);
	target.draw(point, states);
}