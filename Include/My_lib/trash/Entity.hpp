#ifndef MY_LIB_ENTITY_HPP
#define MY_LIB_ENTITY_HPP

#include <MY_LIB/SceneNode.hpp>


class Entity : public SceneNode
{
public:
   virtual void mysetPosition(sf::Vector2f position);
   virtual void mysetPosition(float vx, float vy);
   sf::Vector2f mygetPosition() const;
private:
    // virtual void updateCurrent(sf::Time dt); // ��� �� ����� ��� ��� ��� �������� � ����-�� ��� ���������� �� �������� ����� ��������� 
    sf::Vector2f mPosition;
};

#endif