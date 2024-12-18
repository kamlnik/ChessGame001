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
        Pawn //, wPawn
    };
    enum Color {
        black, white
    };

public:
    virtual std::vector<sf::Vector2f>& all_move(); // virtual void значит что может быть переопределена потом в наследовательных функциях
    virtual void update_move();
    void set_boundingBox(sf::FloatRect newboundingBox) { boundingBox = newboundingBox; }
    unsigned getColor() { return mColor; }
    void set_is_under_attack(unsigned t) { is_under_attack = t; }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // необходимо определение 
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
  //  virtual void can_move(Type type);
   // virtual void updateCurrent(sf::Time dt);

protected:
    bool is_under_attack;
    Type mType;
    Color mColor;
    sf::FloatRect boundingBox;
    Figure(Type newType, Color newColor) : mType(newType), mColor(newColor), is_under_attack(0) {}
     /*, boundingBox(newboundingBox)*/ 
  // sf::Sprite mSprite; // вообще не нужно 
};
#endif