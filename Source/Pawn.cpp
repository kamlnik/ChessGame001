#include <My_lib/Pawn.hpp>
#include <My_lib/ResourceHolder.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <iostream>

Textures::ID toTextureID(unsigned t)
{
	if (t == 0) { // 0 это чёрное 
		return Textures::bPawn;
	}
	else {
		return Textures::wPawn;
	}
}

Pawn::Pawn(Color ncolor, const TextureHolder& textures) :Figure(Type::Pawn, ncolor), mSprite(textures.get(toTextureID(ncolor))) { this->set_boundingBox(mSprite.getGlobalBounds()); }


void Pawn::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);// вывод пешки 
	}

std::vector<sf::Vector2f> Pawn::all_move() {
	std::vector<sf::Vector2f> test;
	return test;
}