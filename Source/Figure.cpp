#include <My_lib/Figure.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


void Figure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	drawCurrent(target, states);
}
Figure::Figure(const Figure& need_to_copy) {

	this->mType = need_to_copy.mType;
	this->mColor = need_to_copy.mColor;
	this->is_under_attack = need_to_copy.is_under_attack;
	this->setPosition(need_to_copy.getPosition());
}

void Figure::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
}

std::vector<sf::Vector2f>& Figure::all_move() {
	std::vector<sf::Vector2f> test;
	return test;
}

void Figure::update_move(float t) {
}