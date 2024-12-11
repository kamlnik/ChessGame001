#ifndef MY_LIB_SCENENODE_HPP
#define MY_LIB_SCENENODE_HPP

#include <SFML/System/Time.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable // наследственный класс от drawable Transformable и Noncopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
public:
    SceneNode(); // пока работает по умолчанию 
    void attachChild(Ptr child);
    Ptr  detachChild(const SceneNode& node);
    void update(sf::Time dt); // функция обновления, которая получает временной промежуток 
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // virtual void значит что может быть переопределена потом в наследовательных функциях 
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);
private:
    std::vector<Ptr>  mChildren;
    SceneNode* mParent;
};

#endif