/*********************************************************************
 * @file  Bishop.cpp
 *
 * @brief Contains definition of figure "Bishop"
 *********************************************************************/
#ifndef MY_LIB_BISHOP_HPP
#define MY_LIB_BISHOP_HPP
#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bishop : public Figure
{
public:
    /**
    * @brief Bishop Type setter.
    *
    * @param Type of this Figure
    */
    void set_Bishop_type(Type newtype) { mType = newtype; } 
    /**
    * @brief Bishop Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief Bishop Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief Bishop Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    Bishop(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Bishop Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    Bishop(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw Bishop.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all Bishop moves.
    *
    * @return all  Bishop moves
    */
    std::vector<sf::Vector2f>& all_move() override { return bishop_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update Bishop moves 
    *
    * @param screensize is value of screen pixels
    */
    void update_move(float screensize) override;
public:
    /**
    * @brief Vector witch contains all possible moves of Bishop.
    */
    std::vector<sf::Vector2f> bishop_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned(&chess_board)[8][8];
    /**
    * @brief Bishop sprite.
    */
    sf::Sprite mSprite; 
};
#endif