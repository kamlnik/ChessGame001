#ifndef MY_LIB_KDTREE_HPP
#define MY_LIB_KDTREE_HPP

#include <My_lib/Figure.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

class kdNode {
private:

    std::shared_ptr <Figure> ptr;
    std::shared_ptr <kdNode> right;
    std::shared_ptr <kdNode> left;
    std::shared_ptr <kdNode> parent;
    bool mcoordx;

public:
    kdNode() : ptr(nullptr), right(nullptr), left(nullptr), parent(nullptr), mcoordx(true) {};
    kdNode(std::shared_ptr <Figure> hptr) : ptr(hptr), right(nullptr), left(nullptr), parent(nullptr), mcoordx(true) {};
    void setrightchild(std::shared_ptr <kdNode> newright) { right = newright; }
    void setleftchild(std::shared_ptr <kdNode> newleft) { left = newleft; }
    void setparent(std::shared_ptr <kdNode> newparent) { parent = newparent; }
    void setcoord(bool coord) { mcoordx = coord; }
    void setthis(std::shared_ptr <Figure> newptr) { ptr = newptr; }
    std::shared_ptr <kdNode> getrightchild() { return right; }
    std::shared_ptr <kdNode> getleftchild() { return left; }
    std::shared_ptr <kdNode> getparent() { return parent; }
    std::shared_ptr <Figure> getthis() { return ptr; }
    bool getcoord() { return mcoordx; }
};

class Kdtree {
private:
    std::shared_ptr <kdNode> root;
public:
    Kdtree() : root(nullptr) {};
    Kdtree(kdNode* newroot) : root(newroot) {};
    void AddNode(std::shared_ptr <kdNode> newNode);
    void DeleteNode(float xc, float yc);
    void DeleteNode(std::shared_ptr <kdNode> fptr);
    void ChangeNode(kdNode* delNode, int nx, int ny);
    std::shared_ptr<kdNode> FindNode(float xc, float yc);
    std::shared_ptr<kdNode> findminx(std::shared_ptr<kdNode> fptr);
    std::shared_ptr<kdNode> findminy(std::shared_ptr<kdNode> fptr);
    // std::shared_ptr<kdNode> FindMin(std::shared_ptr<kdNode> fptr);
    void drawtree(sf::RenderTarget& target) {
        putTree(target, root);
    }
    void putTree(sf::RenderTarget& target, std::shared_ptr <kdNode> ptr)
    {
        if (ptr != nullptr) {
            putTree(target, ptr->getleftchild());
            target.draw(*(ptr->getthis())); // интересно будет ли работать 
            putTree(target, ptr->getrightchild());

        }
    }
};


#endif 