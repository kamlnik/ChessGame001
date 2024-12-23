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
 //   kdNode(const kdNode& fptr): ptr(fptr.ptr), right(nullptr), left(nullptr), parent(nullptr), mcoordx(true)
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
    void tree_bypass_help_func( std::shared_ptr<kdNode> fptr, std::vector<std::shared_ptr<kdNode>>& Figure_list, unsigned whoose_move);
public:
    Kdtree() : root(nullptr) {};
    Kdtree(kdNode* newroot) : root(newroot) {};
    void AddNode(std::shared_ptr <kdNode> newNode);
    void delete_kdNode(std::shared_ptr<kdNode> fptr);
    void DeleteNode(float xc, float yc);
    void DeleteNode(std::shared_ptr <kdNode> fptr);
    void ChangeNode(std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete);
    std::shared_ptr<kdNode> FindNode(float xc, float yc);
    std::shared_ptr<kdNode> findminx(std::shared_ptr<kdNode> fptr);
    std::shared_ptr<kdNode> findminy(std::shared_ptr<kdNode> fptr);
    std::shared_ptr<kdNode> getroot() { return root; }
    void update(float Screen_size , unsigned(&chessboard)[8][8]);
   // void update_all_move();
   // void update_all_status(const unsigned(&chessboard)[8][8]);
   // void update(unsigned(&chessboard)[8][8]) { update_all_move; update_all_status(chessboard); }
    bool can_make_this_move(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8]);
    bool IS_MATE(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, float Screensize, unsigned(&chessboard)[8][8]);
    void help_func_for_IS_MATE(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8], std::vector<unsigned>& vect);
    void tree_bypass(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, float Screensize, unsigned(&chessboard)[8][8], std::vector<unsigned>& vect, unsigned whoose_move); // не совсем нужно 
    // std::shared_ptr<kdNode> FindMin(std::shared_ptr<kdNode> fptr);
    void drawtree(sf::RenderTarget& target);
};


#endif 