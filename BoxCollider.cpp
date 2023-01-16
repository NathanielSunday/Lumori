#include "BoxCollider.h"

BoxCollider::BoxCollider(float width, float height, sf::Vector2f center) {
	_width = width;
	_height = height;
	_center = center;
}

bool BoxCollider::checkCollision(BoxCollider other) {
	return false;
}

bool BoxCollider::checkCollision(BoxCollider a, BoxCollider b) {
	return false;
}