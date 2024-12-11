#ifndef MY_LIB_SCENENODE_HPP
#define MY_LIB_SCENENODE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable // �������������� ����� �� drawable Transformable � Noncopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
public:
    SceneNode(); // ���� �������� �� ��������� 
    void attachChild(Ptr child);
    Ptr  detachChild(const SceneNode& node);
    void update(sf::Time dt); // ������� ����������, ������� �������� ��������� ���������� 
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // virtual void ������ ��� ����� ���� �������������� ����� � ���������������� �������� 
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
private:
    std::vector<Ptr>  mChildren;
    SceneNode* mParent;
};

#endif