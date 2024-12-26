#ifndef MY_LIB_FIGURE_HPP
#define MY_LIB_FIGURE_HPP
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class Figure : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    enum Type { 
        Pawn,
        King,
        Queen,
        Rook, 
        Bishop,
        Knight
    };
    enum Color {
        black, white
    };

public:
    virtual std::vector<sf::Vector2f>& all_move(); // virtual void значит что может быть переопределена потом в наследовательных функциях
    virtual void update_move( float screensize);
    Color getColor() { return mColor; } // переделал из unsigned
    unsigned getType() { return mType;  }
    void set_is_under_attack(unsigned t) { is_under_attack = t; }
    bool get_is_under_attack() { return is_under_attack; }
    Figure(const Figure& need_to_copy);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // необходимо определение 
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
    bool is_under_attack;
    Type mType;
    Color mColor;
    Figure(Type newType, Color newColor) : mType(newType), mColor(newColor), is_under_attack(0) {}
};
#endif