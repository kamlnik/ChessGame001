#ifndef MY_LIB_WORLD_HPP
#define MY_LIB_WORLD_HPP

#include <My_lib/ResourceHolder.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
//#include <My_lib/SceneNode.hpp>
//#include <My_lib/SpriteNode.hpp>
#include <My_lib/Figure.hpp>
#include <My_lib/Pawn.hpp>
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
    sf::RenderWindow& mWindow;
    sf::View  mWorldView;
    TextureHolder mTextures;
    Kdtree Chesstree;
    sf::Sprite Chess_board;
    sf::FloatRect mWorldBounds;
};
#endif