#ifndef MY_LIB_KDTREE_HPP
#define MY_LIB_KDTREE_HPP

#include <My_lib/Figure.hpp>
#include <My_lib/Pawn.hpp>
#include <My_lib/King.hpp>
#include <My_lib/Bishop.hpp>
#include <My_lib/Knight.hpp>
#include <My_lib/Queen.hpp>
#include <My_lib/Rook.hpp>
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
    kdNode(const kdNode& need_to_copy, unsigned (&chessboard)[8][8]);
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
    Kdtree(const Kdtree& need_to_copy, unsigned(&chessboard)[8][8]);
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
    bool can_make_this_move(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8]);
    void drawtree(sf::RenderTarget& target);
    void help_func_for_copy_constructor(std::shared_ptr<kdNode> ptr, unsigned(&chessboard)[8][8]);
    unsigned IS_MATE(float Screensize, unsigned(chessboard)[8][8]);
    bool func_check_mate( bool whoose_move, float Screensize, unsigned(chessboard)[8][8]);
    void putTree2(std::shared_ptr <kdNode> ptr, int level);
};


#endif 