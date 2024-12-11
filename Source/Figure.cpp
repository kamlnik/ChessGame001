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
void Figure::can_move(Type type) {

}
std::vector<sf::Vector2f> Figure::all_move() {
	std::vector<sf::Vector2f> test;
	return test;
}
Figure::Figure(): mType(NUll), mColor(null)  {}
//Figure::Figure(Type type, const TextureHolder& textures) : mType(type), mSprite(textures.get(toTextureID(type))) {}