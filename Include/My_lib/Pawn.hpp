#ifndef MY_LIB_PAWN_HPP
#define MY_LIB_PAWN_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/ResourceIdentifiers.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Pawn : public Figure
{
public:
  /*  enum Color {
        black, white
    };*/
  //  Type get_Pawn_type() { return Pawn; }
    void set_Pawn_type(Type newtype) { mType = newtype; }// �� ���� ��� ����� ������ 
    unsigned getColor() { return mColor; }
    Type getType() { return mType; }
   // Pawn(Color newColor, sf:Vector2f() vector)
    // explicit Figure(Type type);
    Pawn(Color nColor, const TextureHolder& textures);  
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    //virtual void can_move(Type type);
    std::vector<sf::Vector2f> all_move() override; // virtual void ������ ��� ����� ���� �������������� ����� � ���������������� �������� 
    // virtual void updateCurrent(sf::Time dt);
private:
    sf::Sprite mSprite; // ������ �� ����� 
   // Color mColor; // �� ���� ��� ������ ����� � ����� ��c���� 
};
#endif