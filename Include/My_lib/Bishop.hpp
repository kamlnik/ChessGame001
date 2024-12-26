#ifndef MY_LIB_BISHOP_HPP
#define MY_LIB_BISHOP_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bishop : public Figure
{
public:
    void set_Bishop_type(Type newtype) { mType = newtype; } 
    unsigned getColor() { return mColor; }
    Type getType() { return mType; }
    Bishop(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    Bishop(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::vector<sf::Vector2f>& all_move() override { return bishop_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    void update_move(float screensize) override;

public:
    std::vector<sf::Vector2f> bishop_all_move;
    unsigned(&chess_board)[8][8];
    sf::Sprite mSprite; 
};
#endif