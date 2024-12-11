#include <My_lib/Entity.hpp>

void Entity::mysetPosition(sf::Vector2f position) {
	mPosition = position;
}

void Entity::mysetPosition(float vx, float vy) {
	mPosition.x = vx;
	mPosition.y = vy;
}

sf::Vector2f Entity::mygetPosition() const {
	return mPosition;
}