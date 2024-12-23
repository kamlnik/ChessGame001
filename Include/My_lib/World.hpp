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
    explicit World(sf::RenderWindow& window);
//    void update(sf::Time dt);
    void draw();
private:
    void loadTextures();
    void buildScene();
    void World_processEvents();
private:
    enum Layer
    {
        Background,
        LayerCount// количество слоёв
    };

private:
    bool Whoose_move = 1;
    sf::RenderWindow& mWindow;
    sf::View  mWorldView;
    TextureHolder mTextures;
    Kdtree Chesstree;
    sf::Sprite Chess_board;
    sf::FloatRect mWorldBounds;
    unsigned Chess_board_for_figures[8][8] = {};
    float Scale_value;
    float Screen_width;
    std::shared_ptr<Figure> BKing;
    std::shared_ptr<Figure> WKing;
};
#endif