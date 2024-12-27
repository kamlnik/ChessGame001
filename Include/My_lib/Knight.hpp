/*********************************************************************
 * @file  Knight.cpp
 *
 * @brief Contains definition of figure "Knight"
 *********************************************************************/
#ifndef MY_LIB_KNIGHT_HPP
#define MY_LIB_KNIGHT_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Knight : public Figure
{
public:
    /**
    * @brief Knight Type setter.
    *
    * @param Type of this Figure
    */
    void set_Knight_type(Type newtype) { mType = newtype; }
    /**
    * @brief Knight Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief Knight Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief Knight Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    Knight(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Knight Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    Knight(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw Knight.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all Knight moves.
    *
    * @return all  Knight moves
    */
    std::vector<sf::Vector2f>& all_move() override { return knight_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update Knight moves
    *
    * @param screensize is value of screen pixels
    */
    void update_move(float screensize) override;

public:
    /**
    * @brief Vector witch contains all possible moves of Knight.
    */
    std::vector<sf::Vector2f> knight_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned(&chess_board)[8][8];
    /**
    * @brief Knight sprite.
    */
    sf::Sprite mSprite; 
};
#endif