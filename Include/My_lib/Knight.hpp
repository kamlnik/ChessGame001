#ifndef MY_LIB_KNIGHT_HPP
#define MY_LIB_KNIGHT_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Knight : public Figure
{
public:
    void set_Knight_type(Type newtype) { mType = newtype; }
    unsigned getColor() { return mColor; }
    Type getType() { return mType; }
    Knight(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    Knight(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<sf::Vector2f>& all_move() override { return knight_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    void update_move(float screensize) override;

public:
    std::vector<sf::Vector2f> knight_all_move;
    unsigned(&chess_board)[8][8];
    sf::Sprite mSprite; 
};
#endif