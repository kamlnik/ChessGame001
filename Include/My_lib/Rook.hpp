/*********************************************************************
 * @file  Rook.cpp
 *
 * @brief Contains definition of figure "Rook"
 *********************************************************************/
#ifndef MY_LIB_ROOK_HPP
#define MY_LIB_ROOK_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Rook : public Figure
{
public:
    /**
    * @brief Rook Type setter.
    *
    * @param Type of this Figure
    */
    void set_Rook_type(Type newtype) { mType = newtype; }
    /**
    * @brief Rook Color getter.
    *
    * @return Type of this Figure
    */
    unsigned getColor() { return mColor; }
    /**
    * @brief Rook Type getter.
    *
    * @return Type of this Figure
    */
    Type getType() { return mType; }
    /**
    * @brief Rook Constructor.
    *
    * @param nColor is color of figure
    * @param textures is textures container
    * @param new_chess_board is new chessboard desk
    */
    Rook(Color nColor, const TextureHolder& textures, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Rook Constructor.
    *
    * @param nColor is color of figure
    * @param Position is position of this figure
    * @param new_chess_board is new chessboard desk
    */
    Rook(Color nColor, sf::Vector2f Position, unsigned(&new_chess_board)[8][8]);
    /**
    * @brief Func that draw Rook.
    *
    * @param target show where output it
    * @param states is SFML special value
    */
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
    * @brief Func that returns all Rook moves.
    *
    * @return all Queen moves
    */
    std::vector<sf::Vector2f>& all_move() override { return rook_all_move; } // virtual void значит что может быть переопределена потом в наследовательных функциях
    /**
    * @brief Func that update Rook moves
    *
    * @param screensize is value of screen pixels
    */
    void update_move(float screensize) override;

public:
    /**
    * @brief Vector witch contains all possible moves of Rook.
    */
    std::vector<sf::Vector2f> rook_all_move;
    /**
    * @brief Chessboard desk.
    */
    unsigned(&chess_board)[8][8];
    /**
    * @brief Rook sprite.
    */
    sf::Sprite mSprite; 
};
#endif