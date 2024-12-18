#include <My_lib/Figure.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


void Figure::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	drawCurrent(target, states);
}

void Figure::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
}

std::vector<sf::Vector2f>& Figure::all_move() {
	std::vector<sf::Vector2f> test;
	return test;
}

void Figure::update_move() {
}
//Figure::Figure(): mType(NUll), mColor(null)  {}
//Figure::Figure(Type type, const TextureHolder& textures) : mType(type), mSprite(textures.get(toTextureID(type))) {}