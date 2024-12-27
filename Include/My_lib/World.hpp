/*********************************************************************
 * @file  World.cpp
 *
 * @brief Initializing and control all game process
 *********************************************************************/
#ifndef MY_LIB_WORLD_HPP
#define MY_LIB_WORLD_HPP

#include <My_lib/ResourceHolder.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
//#include <My_lib/SceneNode.hpp>
//#include <My_lib/SpriteNode.hpp>
#include <My_lib/Figure.hpp>
#include <My_lib/Pawn.hpp>
#include <My_lib/King.hpp>
#include <My_lib/Queen.hpp>
#include <My_lib/Rook.hpp>
#include <My_lib/Bishop.hpp>
#include <My_lib/Knight.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <My_lib/Kdtree.hpp>

#include <array>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
    friend class Game;
public:
    /**
    * @brief World Initialize.
    */
    explicit World(sf::RenderWindow& window);
    /**
    * @brief Func that draw all game.
    */
    void draw();
private:
    /**
    * @brief Func that load textures.
    */
    void loadTextures();
    /**
    * @brief Func that Initialize all Figures.
    */
    void buildScene();
    /**
    * @brief Func that update image.
    */
    void World_processEvents();
private:
    /**
    * @brief Show which move.
    */
    bool Whoose_move = 1;
    /**
    * @brief Sfml value shows Window.
    */
    sf::RenderWindow& mWindow;
    /**
    * @brief Sfml value shows View.
    */
    sf::View  mWorldView;
    /**
    * @brief Textures container.
    */
    TextureHolder mTextures;
    /**
    * @brief KD tree of Figures.
    */
    Kdtree Chesstree;
    /**
    * @brief Chessboard sprite.
    */
    sf::Sprite Chess_board;
    /**
    * @brief World Bounds.
    */
    sf::FloatRect mWorldBounds;
    /**
    * @brief Chessboard.
    */
    unsigned Chess_board_for_figures[8][8] = {};
    /**
    * @brief Scale Value.
    */
    float Scale_value;
    /**
    * @brief Game screen size.
    */
    float Screen_width;
    /**
    * @brief Pointer to black king.
    */
    std::shared_ptr<Figure> BKing;
    /**
    * @brief Pointer to white king.
    */
    std::shared_ptr<Figure> WKing;
};
#endif