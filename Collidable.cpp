#include "Collidable.h"

std::vector<Collidable> Collidable::_colliders;

Collidable::Collidable(sf::Vector2f position, sf::FloatRect collider, bool isFixed) {
	Collidable::_collider = collider;
}

void Collidable::CheckGlobalCollision() {
	if (_colliders.size() < 2) return;
	for (int i = 0; i < _colliders.size(); ++i) {
		for (int j = i; j < _colliders.size(); ++j) {
			//check how far the object is in, and back it off in that direction
			//use Rect<T>::intersects to find the intersection
			//if one is static and not the other, move the non static one the width and height of the rectangle
			
		}
	}
}

bool Collidable::CheckCollision(Collidable a, Collidable b) {
	return a._collider.intersects(b._collider);
}

bool Collidable::checkCollision(Collidable other) {
	return _collider.intersects(other._collider);
}

void Collidable::setSize(sf::Vector2f size) {
	_size = size;
	recalculate();
}

void Collidable::setPosition(sf::Vector2f position) {
	_position = position;
	recalculate();
}

sf::Vector2f Collidable::getSize() {
	return _size;
}

sf::Vector2f Collidable::getPosition() {
	return _position;
}

void Collidable::recalculate() {
	_collider.width = _size.x;
	_collider.height = _size.y;
	_collider.left = _position.x - _collider.width;
	_collider.top = _position.y - _collider.height;
}

Collidable::~Collidable() { 
}
