/*********************************************************************
 * @file  King.cpp
 *
 * @brief Contains definition of figure "King"
 *********************************************************************/
#ifndef MY_LIB_KING_HPP
#define MY_LIB_KING_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class King : public Figure
{
public:
    /**
    * @brief King Type setter.
    *
    * @param Type of this Figure
    */
    void set_King_type(Type newtype) { mType = newtype; }
    /**
    * @brief King Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief King Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief King Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    King(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief King Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    King::King(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw King.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all King moves.
    *
    * @return all  King moves
    */
    std::vector<sf::Vector2f>& all_move() override { return king_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update King moves 
    *
    * @param screensize is value of screen pixels
    */
    bool is_first_move() override;
    void set_is_first_move() override { first_move = 0; }
    void update_move(float screensize) override;

public:
    /**
    * @brief Vector witch contains all possible moves of King.
    */
    std::vector<sf::Vector2f> king_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned(&chess_board)[8][8];
    /**
    * @brief King sprite.
    */
    sf::Sprite mSprite; 
    bool first_move;
};
#endif