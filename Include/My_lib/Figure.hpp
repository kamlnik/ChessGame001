#ifndef MY_LIB_FIGURE_HPP
#define MY_LIB_FIGURE_HPP
//#include <My_lib/Entity.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class Figure : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    enum Type { // нужно просто Pawn
        NUll, Pawn //, wPawn
    };
    enum Color {
        black, white, null
    };
    
   // explicit Figure(Type type);
  //  Figure(Type type, const TextureHolder& textures); // тоже пока не нужно 
    Figure();
    Figure(Type newType, Color newColor) : mType(newType), mColor(newColor) /*, boundingBox(newboundingBox)*/ {}
    virtual std::vector<sf::Vector2f> all_move(); // virtual void значит что может быть переопределена потом в наследовательных функциях
    void set_boundingBox(sf::FloatRect newboundingBox) { boundingBox = newboundingBox; }
    unsigned getColor() { return mColor; }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // необходимо определение 
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
    virtual void can_move(Type type);
   // virtual void updateCurrent(sf::Time dt);
protected:
    Type mType;
    Color mColor;
    sf::FloatRect boundingBox;
private:
  // sf::Sprite mSprite; // вообще не нужно 
    
};
#endif