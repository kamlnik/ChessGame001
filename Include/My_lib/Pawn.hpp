/*********************************************************************
 * @file  Pawn.cpp
 *
 * @brief Contains definition of figure "Pawn"
 *********************************************************************/
#ifndef MY_LIB_PAWN_HPP
#define MY_LIB_PAWN_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Pawn : public Figure
{
public:
    /**
    * @brief Pawn Type setter.
    *
    * @param Type of this Figure
    */
    void set_Pawn_type(Type newtype) { mType = newtype; }
    /**
    * @brief Pawn Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief Pawn Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief Pawn Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    Pawn(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Pawn Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    Pawn(Color nColor,  const sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw Pawn.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all Pawn moves.
    *
    * @return all  Pawn moves
    */
    std::vector<sf::Vector2f>& all_move() override { return pawn_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update Pawn moves
    *
    * @param screensize is value of screen pixels
    */
    void update_move( float screensize) override;
    
public:
    /**
    * @brief Vector witch contains all possible moves of Pawn.
    */
    std::vector<sf::Vector2f> pawn_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned (&chess_board)[8][8];
    /**
    * @brief Pawn sprite.
    */
    sf::Sprite mSprite;  
};
#endif