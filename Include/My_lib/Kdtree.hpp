/*********************************************************************
 * @file  Kdtree.cpp
 *
 * @brief Contains figure kd tree 
 *********************************************************************/
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
    /**
    * @brief Pointer to Figure.
    */
    std::shared_ptr <Figure> ptr;
    /**
    * @brief Pointer to right node.
    */
    std::shared_ptr <kdNode> right;
    /**
    * @brief Pointer to left node.
    */
    std::shared_ptr <kdNode> left;
    /**
    * @brief Pointer to parent node.
    */
    std::shared_ptr <kdNode> parent;
    /**
    * @brief Show coord.
    */
    bool mcoordx;

public:
    /**
    * @brief kdNode costructor.
    *
    */
    kdNode() : ptr(nullptr), right(nullptr), left(nullptr), parent(nullptr), mcoordx(true) {};
    /**
    * @brief kdNode costructor.
    *
    * @param hptr is pointer to figure
    */
    kdNode(std::shared_ptr <Figure> hptr) : ptr(hptr), right(nullptr), left(nullptr), parent(nullptr), mcoordx(true) {};
    /**
    * @brief kdNode copy costructor.
    *
    * @param element wich we want to copy
    * @param chessboard
    */
    kdNode(const kdNode& need_to_copy, unsigned (&chessboard)[8][8]);
    /**
    * @brief kdNode  rightchild setter.
    *
    * @param kdNode new pointer
    */
    void setrightchild(std::shared_ptr <kdNode> newright) { right = newright; }
    /**
    * @brief kdNode  leftchild setter.
    *
    * @param kdNode new pointer
    */
    void setleftchild(std::shared_ptr <kdNode> newleft) { left = newleft; }
    /**
    * @brief kdNode  parent setter.
    *
    * @param kdNode new pointer
    */
    void setparent(std::shared_ptr <kdNode> newparent) { parent = newparent; }
    /**
    * @brief kdNode  coord setter.
    *
    * @param new coord
    */
    void setcoord(bool coord) { mcoordx = coord; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @param Figure new pointer
    */
    void setthis(std::shared_ptr <Figure> newptr) { ptr = newptr; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @return right Node
    */
    std::shared_ptr <kdNode> getrightchild() { return right; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @return left Node
    */
    std::shared_ptr <kdNode> getleftchild() { return left; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @return parent Node.
    */
    std::shared_ptr <kdNode> getparent() { return parent; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @return figure pointer.
    */
    std::shared_ptr <Figure> getthis() { return ptr; }
    /**
    * @brief kdNode pointer to figure setter.
    *
    * @return coord.
    */
    bool getcoord() { return mcoordx; }
};

class Kdtree {
private:
    /**
    * @brief kdNode root pointer.
    *
    */
    std::shared_ptr <kdNode> root;
    /**
    * @brief Func that make Figure list.
    *
    * @param fptr is pointer to this kdNode.
    * @param Figure_list is vector of figures.
    * @param whoose_move is whoose move.
    */
    void tree_bypass_help_func( std::shared_ptr<kdNode> fptr, std::vector<std::shared_ptr<kdNode>>& Figure_list, unsigned whoose_move);
public:
    /**
    * @brief Kd tree construcor.
    */
    Kdtree() : root(nullptr) {};
    /**
    * @brief Kd tree construcor.
    * 
    * @param kdNode pointer.
    */
    Kdtree(kdNode* newroot) : root(newroot) {};
    /**
    * @brief Kd tree  copy construcor.
    *
    * @param need_to_copy is element wich we want to copy.
    */
    Kdtree(const Kdtree& need_to_copy, unsigned(&chessboard)[8][8]);
    /**
    * @brief Func that add Node.
    *
    * @param newNode is pointer to element wich we want to add.
    */
    void AddNode(std::shared_ptr <kdNode> newNode);
    /**
    * @brief Func that delete Node.
    *
    * @param fptr is pointer to element wich we want to delete.
    */
    void delete_kdNode(std::shared_ptr<kdNode> fptr);
    /**
    * @brief Func that delete Node.
    *
    * @param xc is x position of element wich we want to delete
    * @param yc is y position of element wich we want to delete
    */
    void DeleteNode(float xc, float yc);
    /**
    * @brief Func that delete Node.
    *
    * @param fptr is pointer to element wich we want to delete.
    */
    void DeleteNode(std::shared_ptr <kdNode> fptr);
    /**
    * @brief Func that Find Node.
    *
    * @param xc is x position of element wich we want to find
    * @param yc is y position of element wich we want to find
    * @return pointer to finded element
    */
    std::shared_ptr<kdNode> FindNode(float xc, float yc);
    /**
    * @brief Func that Find min Node in x coord.
    *
    * @param fprt is pointer to node
    * @return pointer to finded element
    */
    std::shared_ptr<kdNode> findminx(std::shared_ptr<kdNode> fptr);
    /**
    * @brief Func that Find min Node in y coord.
    *
    * @param fprt is pointer to node
    * @return pointer to finded element
    */
    std::shared_ptr<kdNode> findminy(std::shared_ptr<kdNode> fptr);
    /**
    * @brief Kdtree root getter.
    *
    * @return Kdtree pointer to root
    */
    std::shared_ptr<kdNode> getroot() { return root; }
    /**
    * @brief Func that update all figures move.
    *
    * @param Screen_size id Screen size
    * @param chessboard is chessboard
    */
    void update(float Screen_size , unsigned(&chessboard)[8][8]);
    /**
    * @brief Func that check move.
    *
    * 
    * @param Wking is pointer to white king
    * @param Bking is pointer to black king
    * @param fptr is pointer to this kdNode
    * @param Previos_position is previos position of moved Figure
    * @param New_position is new position of moved Figure
    * @param is_delete is if we delete
    * @param Screen_size is screen size
    * @param chessboard is chessboard
    * @return bool 0 if we can make else 1
    */
    bool can_make_this_move(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8]);
    /**
    * @brief Func that draw Kdtree.
    *
    *
    * @param target is target to screen
    */
    void drawtree(sf::RenderTarget& target);
    /**
    * @brief Func that check mate.
    *
    *
    * @param ptr id pointer to this kdNode
    * @param chessboard is chessboard
    * // need to update discription 
    * @return 0 if mate else 1
    */
    unsigned IS_MATE(float Screensize, unsigned(chessboard)[8][8], bool whoose_move);
    /**
    * @brief Func that help check mate with threads.
    *
    *
    * @param ptr id pointer to this kdNode
    * @param chessboard is chessboard
    */
    bool func_check_mate( bool whoose_move, float Screensize, unsigned(chessboard)[8][8]);
    void putTree2(std::shared_ptr <kdNode> ptr, int level);
    void help_func_for_copy_constructor(std::shared_ptr<kdNode> ptr, unsigned(&chessboard)[8][8]);
};


#endif 