/*********************************************************************
 * @file  Queen.cpp
 *
 * @brief Contains definition of figure "Queen"
 *********************************************************************/
#ifndef MY_LIB_QUEEN_HPP
#define MY_LIB_QUEEN_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Queen : public Figure
{
public:
    /**
    * @brief Queen Type setter.
    *
    * @param Type of this Figure
    */
    void set_Queen_type(Type newtype) { mType = newtype; }
    /**
    * @brief Queen Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief Queen Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief Queen Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    Queen(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Queen Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    Queen::Queen(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw Queen.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all Queen moves.
    *
    * @return all Queen moves
    */
    std::vector<sf::Vector2f>& all_move() override { return queen_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update Queen moves
    *
    * @param screensize is value of screen pixels
    */
    void update_move(float screensize) override;

public:
    /**
    * @brief Vector witch contains all possible moves of Queen.
    */
    std::vector<sf::Vector2f> queen_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned(&chess_board)[8][8];
    /**
    * @brief Queen sprite.
    */
    sf::Sprite mSprite; 
};
#endif