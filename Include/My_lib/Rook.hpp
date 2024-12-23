#ifndef MY_LIB_ROOK_HPP
#define MY_LIB_ROOK_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Rook : public Figure
{
public:
    void set_Rook_type(Type newtype) { mType = newtype; }// не факт что нужно вообще 
    unsigned getColor() { return mColor; }
    Type getType() { return mType; }
    Rook(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    //virtual void can_move(Type type);
    std::vector<sf::Vector2f>& all_move() override { return rook_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    void update_move(float screensize) override;

public:
    std::vector<sf::Vector2f> rook_all_move;
    unsigned(&chess_board)[8][8];
    sf::Sprite mSprite; // вообще не нужно 
};
#endif