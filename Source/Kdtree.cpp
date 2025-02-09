#include <My_lib/Kdtree.hpp>
#include <algorithm>
#include <thread>
#include <future>

unsigned newmindex_correct_position(float position, float Screen_size) {
    float returned_val = 0.f;
    int per = position / (Screen_size/16);
    if (per % 2 == 0) {
        returned_val = (per) / 2;
        return returned_val;
    }
    returned_val = (per - 1) / 2;
    return returned_val;
}

kdNode::kdNode(const kdNode& need_to_copy, unsigned(&chessboard)[8][8]) {
   if (need_to_copy.ptr->getType() == Figure::Pawn) {
        std::shared_ptr<Pawn> newptr(new Pawn(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
        this->ptr = newptr;
   }else
   if (need_to_copy.ptr->getType() == Figure::Bishop) {
       std::shared_ptr<Bishop> newptr(new Bishop(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
       this->ptr = newptr;
   }else
   if (need_to_copy.ptr->getType() == Figure::King) {
       std::shared_ptr<King> newptr(new King(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
      // newptr->set_is_first_move();
       this->ptr = newptr;
   }else
   if (need_to_copy.ptr->getType() == Figure::Knight) {
       std::shared_ptr<Knight> newptr(new Knight(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
       this->ptr = newptr;
   }else
   if (need_to_copy.ptr->getType() == Figure::Queen) {
       std::shared_ptr<Queen> newptr(new Queen(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
       this->ptr = newptr;
   }else
   if (need_to_copy.ptr->getType() == Figure::Rook) {
       std::shared_ptr<Rook> newptr(new Rook(need_to_copy.ptr->getColor(), need_to_copy.ptr->getPosition(), chessboard));
       this->ptr = newptr;
   }
   // std::shared_ptr<Figure> newptr(new Figure( *(need_to_copy.ptr) ) );
    this->left = nullptr;
    this->right = nullptr;
    this->mcoordx = true;
    this->parent = nullptr;
}

std::shared_ptr<kdNode> minNodex(std::shared_ptr<kdNode> x, std::shared_ptr<kdNode> y, std::shared_ptr<kdNode> z) {
    std::shared_ptr<kdNode> res = x;
    if (y != nullptr && y->getthis()->getPosition().x < res->getthis()->getPosition().x) {
        res = y;
    }
    if (z != nullptr && z->getthis()->getPosition().x < res->getthis()->getPosition().x) {
        res = z;
    }
    return res;
}

std::shared_ptr<kdNode> minNodey(std::shared_ptr<kdNode> x, std::shared_ptr<kdNode> y, std::shared_ptr<kdNode> z) {
    std::shared_ptr<kdNode> res = x;
    if (y != nullptr && y->getthis()->getPosition().y < res->getthis()->getPosition().y) {
        res = y;
    }
    if (z != nullptr && z->getthis()->getPosition().y < res->getthis()->getPosition().y) {
        res = z;
    }
    return res;
}

std::shared_ptr<kdNode> hfindminx(std::shared_ptr<kdNode> fptr) {
    if (fptr == nullptr) {
        return nullptr;
    }
    if (fptr->getcoord() == true) {
        if (fptr->getleftchild() == nullptr) {
            return fptr;
        }
        return minNodex(fptr, hfindminx(fptr->getleftchild()), nullptr);
    }
    return minNodex(fptr, hfindminx(fptr->getleftchild()), hfindminx(fptr->getrightchild()));
}

std::shared_ptr<kdNode> hfindminy(std::shared_ptr<kdNode> fptr) {
    if (fptr == nullptr) {
        return nullptr;
    }
    if (fptr->getcoord() == false) {
        if (fptr->getleftchild() == nullptr) {
            return fptr;
        }
        return minNodey(fptr, hfindminy(fptr->getleftchild()), nullptr);
    }
    return minNodey(fptr, hfindminy(fptr->getleftchild()), hfindminy(fptr->getrightchild()));
}

std::shared_ptr<kdNode> Kdtree::findminx(std::shared_ptr<kdNode> fptr) {
    return hfindminx(fptr);
}

std::shared_ptr<kdNode> Kdtree::findminy(std::shared_ptr<kdNode> fptr) {
    return hfindminy(fptr);
}

unsigned help_to_find_node_for_delete(std::shared_ptr<kdNode> fptr) {
    std::shared_ptr<kdNode> parent = fptr->getparent();
    std::shared_ptr<Figure> figure = fptr->getthis();
    if (parent == nullptr) {
        return 2;
    }
    std::shared_ptr<Figure> pfigure = parent->getthis();
    bool coord = parent->getcoord();
    if (coord == true) {
        if (figure->getPosition().x >= pfigure->getPosition().x) {
            return 1;
        }
        else {
            return 0;
        }
    }
    if (coord == false) {
        if (figure->getPosition().y >= pfigure->getPosition().y) {
            return 1;
        }
        else {
            return 0;
        }
    }
    throw std::exception("Incorrect value on help_to_find_node_for_delete");
}

void Kdtree::delete_kdNode(std::shared_ptr<kdNode> fptr) { /// not work 
    if (fptr == nullptr) {
        return;
    }
    if (fptr->getrightchild() != nullptr) {
        //std::shared_ptr<kdNode> needed; // needed - min �������, fptr - ��������� ���� 
        std::shared_ptr<kdNode> valptr;
        if (fptr->getcoord() == true) {
            valptr = findminx(fptr->getrightchild()); // needed - min �������, fptr - ��������� ����     
        }
        else {
            valptr = findminy(fptr->getrightchild());
        }
        delete_kdNode(valptr); // ��� �������� �� ������� ����, ������ ������ ����������

        valptr->setrightchild(fptr->getrightchild()); // ���������� ��������� ���������� � ����� 
        valptr->setleftchild(fptr->getleftchild());
        valptr->setcoord(fptr->getcoord());
        valptr->setparent(fptr->getparent());
        if (fptr->getrightchild() != nullptr) {
            fptr->getrightchild()->setparent(valptr);
        }
        if (fptr->getleftchild() != nullptr) {
            fptr->getleftchild()->setparent(valptr);
        }
        unsigned per = help_to_find_node_for_delete(fptr);
        if (per == 2) {
            root = valptr;
        }
        if (per == 0) {
            fptr->getparent()->setleftchild(valptr);
        }
        if (per == 1) {
            fptr->getparent()->setrightchild(valptr);
        }
        // fptr->setleftchild(nullptr);
        // fptr->setrightchild(nullptr);
    }
    else if (fptr->getleftchild() != nullptr) {
        // std::shared_ptr<kdNode> needed; // needed - min �������, fptr - ��������� ���� 
        std::shared_ptr<kdNode> valptr;
        if (fptr->getcoord() == true) {
            valptr = findminx(fptr->getleftchild());
        }
        else {
            valptr = findminy(fptr->getleftchild());
        }
        delete_kdNode(valptr);
        // fptr->getleftchild()->setparent(valptr);
        valptr->setrightchild(fptr->getleftchild()); // ���������� ��������� ���������� � ����� 
        valptr->setleftchild(nullptr);
        valptr->setcoord(fptr->getcoord());
        valptr->setparent(fptr->getparent());
        if (fptr->getrightchild() != nullptr) {
            fptr->getrightchild()->setparent(valptr);
        }
        if (fptr->getleftchild() != nullptr) {
            fptr->getleftchild()->setparent(valptr);
        }
        unsigned per = help_to_find_node_for_delete(fptr);
        if (per == 2) {
            root = valptr;
        }
        if (per == 0) {
            fptr->getparent()->setleftchild(valptr);
        }
        if (per == 1) {
            fptr->getparent()->setrightchild(valptr);
        }
        //fptr->setleftchild(nullptr);
        //fptr->setrightchild(nullptr);
    }
    else {
        if (fptr->getparent() == nullptr) {
            root = nullptr;
        }
        else {
            unsigned per = help_to_find_node_for_delete(fptr);
            if (per == 0) {
                (fptr->getparent())->setleftchild(nullptr);
                fptr->setparent(nullptr);
            }
            else if (per == 1) {
                (fptr->getparent())->setrightchild(nullptr);
                fptr->setparent(nullptr);
            }
        }
    }
    //return fptr;
}

void Kdtree::AddNode(std::shared_ptr <kdNode> newNode) { // ���� ������� �������� �� ��������� 
    if (FindNode(newNode->getthis()->getPosition().x, newNode->getthis()->getPosition().y) != nullptr) {
        throw std::logic_error("add duplicate");
    }
    if (root == nullptr) {
        root = newNode;
        newNode->setleftchild(nullptr);
        newNode->setrightchild(nullptr);
        newNode->setparent(nullptr);
        newNode->setcoord(true);
        return;
    }
    bool coordx = { true };
    bool coordy = { false };
    std::shared_ptr <kdNode> val;
    std::shared_ptr <kdNode> pred;
    val = root;
    pred = val;
    while (val != nullptr) {
        if (coordx == true) {
            if (newNode->getthis()->getPosition().x >= val->getthis()->getPosition().x) {
                pred = val;
                val = val->getrightchild();
                coordx = false;
                coordy = true;
            }
            else {
                pred = val;
                val = val->getleftchild();
                coordx = false;
                coordy = true;
            }
        }
        else if (coordy == true) {
            if (newNode->getthis()->getPosition().y >= val->getthis()->getPosition().y) {
                pred = val;
                val = val->getrightchild();
                coordx = true;
                coordy = false;
            }
            else {
                pred = val;
                val = val->getleftchild();
                coordx = true;
                coordy = false;
            }
        }
        else {
            throw std::logic_error("Add error");
        }
    }
    newNode->setleftchild(nullptr);
    newNode->setrightchild(nullptr);
    if (coordx == false) {
        newNode->setcoord(false);
        if (newNode->getthis()->getPosition().x >= pred->getthis()->getPosition().x) {
            pred->setrightchild(newNode);
            newNode->setparent(pred);
        }
        else {
            pred->setleftchild(newNode);
            newNode->setparent(pred);
        }
    }
    else {
        newNode->setcoord(true);
        if (newNode->getthis()->getPosition().y >= pred->getthis()->getPosition().y) {
            pred->setrightchild(newNode);
            newNode->setparent(pred);
        }
        else {
            pred->setleftchild(newNode);
            newNode->setparent(pred);
        }
    }
}

std::shared_ptr<kdNode> Kdtree::FindNode(float xc, float yc) { // ��������
    std::shared_ptr<kdNode> val = root;
    bool coordx = { true };
    bool coordy = { false };
    std::shared_ptr <kdNode> pred = nullptr;
    val = root;
    pred = val;
    while (val != nullptr) {
        if (xc == val->getthis()->getPosition().x && yc == val->getthis()->getPosition().y) {
            return val;
        }
        if (coordx == true) {
            if (xc >= val->getthis()->getPosition().x) {
                pred = val;
                val = val->getrightchild();
                coordx = false;
                coordy = true;
            }
            else if (xc < val->getthis()->getPosition().x) {
                pred = val;
                val = val->getleftchild();
                coordx = false;
                coordy = true;
            }
        }
        else if (coordy == true) {
            if (yc >= val->getthis()->getPosition().y) {
                pred = val;
                val = val->getrightchild();
                coordx = true;
                coordy = false;
            }
            else if (yc < val->getthis()->getPosition().y) {
                pred = val;
                val = val->getleftchild();
                coordx = true;
                coordy = false;
            }
        }
        else {
            throw std::logic_error("Add error");
        }
    }
    return nullptr;
}

void Kdtree::DeleteNode(float xc, float yc) {
    std::shared_ptr<kdNode> fptr = FindNode(xc, yc);
    if (fptr == nullptr) {
        throw std::logic_error("DeleteNode Error: Not found deleted element");
    }
    if (fptr == root && fptr->getrightchild() == nullptr && fptr->getleftchild() == nullptr) {
        root = nullptr;
        return;
    }
    delete_kdNode(fptr);
}

void Kdtree::DeleteNode(std::shared_ptr <kdNode> fptr) {
    if (fptr != nullptr) {
        if (fptr == root && fptr->getrightchild() == nullptr && fptr->getleftchild() == nullptr) {
            root = nullptr;
            return;
        }
        delete_kdNode(fptr);
    }
    else {
        throw std::logic_error(" DeleteNode Error: Incorrect ptr to deleted elment ");
    }
    
}

void putTree(sf::RenderTarget& target, std::shared_ptr <kdNode> ptr, int level)
{
    int i = level;
    if (ptr != nullptr) {
        
        putTree(target, ptr->getrightchild(), level+1);
      //  while (i-- > 0) {
      //      std::cout << "      ";
      //  }
      //  std::cout << ptr.get()->getthis()->getPosition().x << " , " << ptr.get()->getthis()->getPosition().y << "\n";
        target.draw(*(ptr->getthis())); // ��������� ����� �� �������� 
        putTree(target, ptr->getleftchild(), level + 1);

    }
}

void Kdtree::drawtree(sf::RenderTarget& target) {
    putTree(target, root, 0);
}

void  help_func_for_update_move(float Screen_size, std::shared_ptr <kdNode> ptr) {
    if (ptr != nullptr) {
        help_func_for_update_move(Screen_size,ptr->getleftchild());
        ptr->getthis()->update_move(Screen_size);
        help_func_for_update_move(Screen_size, ptr->getrightchild());
    }
}

void  help_func_for_update_status(std::shared_ptr <kdNode> ptr, unsigned(&chessboard)[8][8], float Screen_size) {
    if (ptr != nullptr) {

        help_func_for_update_status(ptr->getleftchild(), chessboard, Screen_size);
        unsigned xc = newmindex_correct_position(ptr->getthis()->getPosition().x, Screen_size);
        unsigned yc = newmindex_correct_position(ptr->getthis()->getPosition().y, Screen_size);
        ptr->getthis()->set_is_under_attack(0);
        if (ptr->getthis()->getColor() == 0 && chessboard[yc][xc] == 3) {
            ptr->getthis()->set_is_under_attack(1);
        }
        if (ptr->getthis()->getColor() == 1 && chessboard[yc][xc] == 4) {
            ptr->getthis()->set_is_under_attack(1);
        }
       // chessboard[yc][xc] = ptr->getthis()->getColor() + 1;
        help_func_for_update_status(ptr->getrightchild(), chessboard, Screen_size);
    }
}

void help_func_for_initialization(std::shared_ptr <kdNode> ptr, unsigned(&chessboard)[8][8], float Screen_size) {
    if (ptr != nullptr) {
        help_func_for_initialization(ptr->getleftchild(), chessboard, Screen_size);
        unsigned xc = newmindex_correct_position(ptr->getthis()->getPosition().x, Screen_size);
        unsigned yc = newmindex_correct_position(ptr->getthis()->getPosition().y, Screen_size);
        chessboard[yc][xc] = ptr->getthis()->getColor() + 1;
        help_func_for_initialization(ptr->getrightchild(), chessboard, Screen_size);
    }
}

unsigned index_correct_position(float position, float Screen_size) {
    float returned_val = 0.f;
    int per = position / (Screen_size / 16);
    if (per % 2 == 0) {
        returned_val = (per) / 2;
        return returned_val;
    }
    returned_val = (per - 1) / 2;
    return returned_val;
}

void Kdtree::putTree2(std::shared_ptr <kdNode> ptr, int level)
{
    int i = level;
    if (ptr != nullptr) {

        putTree2(ptr->getrightchild(), level + 1);
        while (i-- > 0) {
            std::cout << "        ";
        }
        std::cout << ptr.get()->getthis()->getPosition().x << " , " << ptr.get()->getthis()->getPosition().y << " , " << ptr->getthis()->get_is_under_attack() << std::endl;
        putTree2(ptr->getleftchild(), level + 1);

    }
}

void Kdtree::update(float Screen_size , unsigned(&chessboard)[8][8]) {
    help_func_for_initialization(this->root, chessboard, Screen_size);
    help_func_for_update_move(Screen_size, this->root);
    help_func_for_update_status(this->root, chessboard, Screen_size);
}

bool Kdtree::can_make_this_move(std::shared_ptr<Figure> Wking, std::shared_ptr<Figure> Bking, std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(&chessboard)[8][8]) {
    fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
    DeleteNode(fptr);
    unsigned Nx = index_correct_position(New_position.x, Screensize);
    unsigned Ny = index_correct_position(New_position.y, Screensize);
    unsigned Px = index_correct_position(Previos_position.x, Screensize);
    unsigned Py = index_correct_position(Previos_position.y, Screensize);
    std::shared_ptr<kdNode> deleted_element = nullptr;
    if (is_delete == 1) {
        deleted_element = FindNode(New_position.x, New_position.y);
        DeleteNode(New_position.x, New_position.y);
    }
    if (fptr->getthis()->getColor() == 1 && fptr->getthis()->getType() == Figure::King && Nx == 6 && Ny == 7 && fptr->getthis()->is_first_move() == 1) {
        std::shared_ptr<kdNode> Rook = nullptr;
        Rook = FindNode(750, 750);
        if (Rook != nullptr && Rook->getthis()->is_first_move() == 1) {
            DeleteNode(Rook);
            Rook->getthis()->setPosition(New_position.x - 100, New_position.y);
            AddNode(Rook);
            fptr->getthis()->setPosition(New_position.x, New_position.y);
            AddNode(fptr);
            chessboard[7][7] = 0;
            chessboard[7][5] = 2;
            chessboard[Py][Px] = 0;
            chessboard[Ny][Nx] = 2;
            update(Screensize, chessboard);
            if (Wking->get_is_under_attack() == 1) {
                DeleteNode(fptr);
                fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
                AddNode(fptr);
                chessboard[Ny][Nx] = 0;
                chessboard[7][7] = 2;
                chessboard[7][5] = 0;
                chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
                DeleteNode(Rook);
                Rook->getthis()->setPosition(750, 750);
                AddNode(Rook);
                update(Screensize, chessboard);
                return 1;
            }
            fptr->getthis()->set_is_first_move();
            Rook->getthis()->set_is_first_move();
            return 0;
        }
    }
    else if(fptr->getthis()->getColor() == 1 && fptr->getthis()->getType() == Figure::King && Nx == 2 && Ny == 7 && fptr->getthis()->is_first_move() == 1){
        std::shared_ptr<kdNode> Rook = nullptr;
        Rook = FindNode(50, 750);
        if (Rook != nullptr && Rook->getthis()->is_first_move() == 1) {
            DeleteNode(Rook);
            Rook->getthis()->setPosition(New_position.x + 100, New_position.y);
            AddNode(Rook);
            fptr->getthis()->setPosition(New_position.x, New_position.y);
            AddNode(fptr);
            chessboard[7][0] = 0;
            chessboard[7][3] = 2;
            chessboard[Py][Px] = 0;
            chessboard[Ny][Nx] = 2;
            update(Screensize, chessboard);
            if (Wking->get_is_under_attack() == 1) {
                DeleteNode(fptr);
                fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
                AddNode(fptr);
                chessboard[Ny][Nx] = 0;
                chessboard[7][0] = 2;
                chessboard[7][3] = 0;
                chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
                DeleteNode(Rook);
                Rook->getthis()->setPosition(50, 750);
                AddNode(Rook);
                update(Screensize, chessboard);
                return 1;
            }
            fptr->getthis()->set_is_first_move();
            Rook->getthis()->set_is_first_move();
            return 0;
        }
    }
    else if (fptr->getthis()->getColor() == 0 && fptr->getthis()->getType() == Figure::King && Nx == 1 && Ny == 0 && fptr->getthis()->is_first_move() == 1) {
        std::shared_ptr<kdNode> Rook = nullptr;
        Rook = FindNode(50, 50);
        if (Rook != nullptr && Rook->getthis()->is_first_move() == 1) {
            DeleteNode(Rook);
            Rook->getthis()->setPosition(New_position.x + 100, New_position.y);
            AddNode(Rook);
            fptr->getthis()->setPosition(New_position.x, New_position.y);
            AddNode(fptr);
            chessboard[0][0] = 0;
            chessboard[0][2] = 1;
            chessboard[Py][Px] = 0;
            chessboard[Ny][Nx] = 1;
            update(Screensize, chessboard);
            if (Wking->get_is_under_attack() == 1) {
                DeleteNode(fptr);
                fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
                AddNode(fptr);
                chessboard[Ny][Nx] = 0;
                chessboard[0][0] = 1;
                chessboard[0][2] = 0;
                chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
                DeleteNode(Rook);
                Rook->getthis()->setPosition(50, 50);
                AddNode(Rook);
                update(Screensize, chessboard);
                return 1;
            }
            fptr->getthis()->set_is_first_move();
            Rook->getthis()->set_is_first_move();
            return 0;
        }
    }
    else if (fptr->getthis()->getColor() == 0 && fptr->getthis()->getType() == Figure::King && Nx == 5 && Ny == 0 && fptr->getthis()->is_first_move() == 1) {
        std::shared_ptr<kdNode> Rook = nullptr;
        Rook = FindNode(750, 50);
        if (Rook != nullptr && Rook->getthis()->is_first_move() == 1) {
            DeleteNode(Rook);
            Rook->getthis()->setPosition(New_position.x - 100, New_position.y);
            AddNode(Rook);
            fptr->getthis()->setPosition(New_position.x, New_position.y);
            AddNode(fptr);
            chessboard[0][7] = 0;
            chessboard[0][4] = 1;
            chessboard[Py][Px] = 0;
            chessboard[Ny][Nx] = 1;
            update(Screensize, chessboard);
            if (Wking->get_is_under_attack() == 1) {
                DeleteNode(fptr);
                fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
                AddNode(fptr);
                chessboard[Ny][Nx] = 0;
                chessboard[0][7] = 1;
                chessboard[0][4] = 0;
                chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
                DeleteNode(Rook);
                Rook->getthis()->setPosition(750, 50);
                AddNode(Rook);
                update(Screensize, chessboard);
                return 1;
            }
            fptr->getthis()->set_is_first_move();
            Rook->getthis()->set_is_first_move();
            return 0;
        }
    }
    fptr->getthis()->setPosition(New_position.x, New_position.y);
    AddNode(fptr);
    chessboard[Py][Px] = 0;
    chessboard[Ny][Nx] = (fptr->getthis()->getColor()) + 1;
    unsigned t = fptr->getthis()->getColor();
    update(Screensize, chessboard);
    if ((t == 1 && Wking->get_is_under_attack() == 1) || (t == 0 && Bking->get_is_under_attack() == 1)) {
        DeleteNode(fptr);
        fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
        AddNode(fptr);
        chessboard[Ny][Nx] = 0;
        chessboard[Py][Px] = fptr->getthis()->getColor() + 1;
        if (deleted_element != nullptr) {
            AddNode(deleted_element);
            chessboard[Ny][Nx] = deleted_element->getthis()->getColor() + 1;
        }
        update(Screensize, chessboard);
        return 1;
    }
    if (fptr->getthis()->getType() == Figure::King || fptr->getthis()->getType() == Figure::Rook) { // ��������� �������������� ������ ��� ����� � ������ 
        fptr->getthis()->set_is_first_move();
    }
    return 0;
}

void func_copy_board(unsigned (&board)[8][8], const unsigned (board_to_copy)[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int t = 0; t < 8; t++) {
            board[i][t] = board_to_copy[i][t];
        }
    }
}

void Kdtree::tree_bypass_help_func(std::shared_ptr<kdNode> fptr, std::vector<std::shared_ptr<kdNode>>& Figure_list, unsigned whoose_move) {
    if (fptr != nullptr) {
        tree_bypass_help_func(fptr->getrightchild(), Figure_list, whoose_move);
        if (fptr->getthis()->getColor() == whoose_move) { // ���� ������ ���� ����� 
            Figure_list.push_back(fptr);
        }
        tree_bypass_help_func(fptr->getleftchild(), Figure_list, whoose_move);

    }
}

void print(const unsigned(board)[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int t = 0; t < 8; t++) {
            std::cout << board[i][t];
        }
        std::cout << std::endl;
    }
}

void Kdtree::help_func_for_copy_constructor(std::shared_ptr<kdNode> ptr, unsigned(&chessboard)[8][8]) {
    if (ptr != nullptr) {
        std::shared_ptr<kdNode> hptr(new kdNode(*ptr, chessboard));
        this->AddNode(hptr);
        help_func_for_copy_constructor(ptr->getrightchild(), chessboard);
        help_func_for_copy_constructor(ptr->getleftchild(), chessboard);
         
    }
}

Kdtree::Kdtree(const Kdtree& need_to_copy, unsigned(&chessboard)[8][8]) {
    this->root = nullptr;
    this->help_func_for_copy_constructor(need_to_copy.root, chessboard);
}

void func_find_king(std::shared_ptr<Figure>* Wking, std::shared_ptr<Figure>* Bking, std::shared_ptr<kdNode> ptr) {
    if (ptr != nullptr) {
        func_find_king(Wking, Bking, ptr->getrightchild());
        if (ptr->getthis()->getType() == 1 && ptr->getthis()->getColor() == 0) {
            *Bking = ptr->getthis();
        }
        if (ptr->getthis()->getType() == 1 && ptr->getthis()->getColor() == 1) {
            *Wking = ptr->getthis();
        }
        func_find_king(Wking, Bking, ptr->getleftchild());
    }

}

bool new_help_func_check_mate_with_threads( sf::Vector2f Previos_position, sf::Vector2f New_position, unsigned is_delete, float Screensize, unsigned(chessboard)[8][8], Kdtree* ptr) {
    unsigned newchessboard[8][8];
    func_copy_board(newchessboard, chessboard);
    Kdtree copy(*ptr, newchessboard);
    std::shared_ptr<Figure> Wking;
    std::shared_ptr<Figure> Bking;
    func_find_king(&Wking, &Bking, copy.getroot());
    std::shared_ptr<kdNode> fptr = nullptr;
    fptr = copy.FindNode(Previos_position.x, Previos_position.y);
    copy.DeleteNode(fptr);
    std::shared_ptr<kdNode> deleted_element = nullptr;
    if (is_delete == 1) {
        deleted_element = copy.FindNode(New_position.x, New_position.y);
        copy.DeleteNode(New_position.x, New_position.y);
    }
    fptr->getthis()->setPosition(New_position.x, New_position.y);
    copy.AddNode(fptr);
    unsigned Nx = index_correct_position(New_position.x, Screensize);
    unsigned Ny = index_correct_position(New_position.y, Screensize);
    unsigned Px = index_correct_position(Previos_position.x, Screensize);
    unsigned Py = index_correct_position(Previos_position.y, Screensize);
    newchessboard[Py][Px] = 0;
    newchessboard[Ny][Nx] = (fptr->getthis()->getColor()) + 1;
    unsigned t = fptr->getthis()->getColor();
    copy.update(Screensize, newchessboard);
    unsigned per = 0;
    if ((t == 0 && Bking->get_is_under_attack() == 0) || (t == 1 && Wking->get_is_under_attack() == 0)) {
        per = 1;
    }
    copy.update(Screensize, newchessboard);
    if (per == 1) {
        return 1;
    }
    return 0;
}

bool Kdtree::func_check_mate( bool whoose_move, float Screensize, unsigned(chessboard)[8][8]){
    std::vector<std::shared_ptr<kdNode>> Figure_list;
    tree_bypass_help_func(root, Figure_list, whoose_move);
    std::vector<std::future<bool>> futures;
    for (auto fptr : Figure_list) {
        std::vector<sf::Vector2f> val = fptr->getthis()->all_move();
        float Previos_positionx = fptr->getthis()->getPosition().x;
        float Previos_positiony = fptr->getthis()->getPosition().y;
        unsigned Px = index_correct_position(Previos_positionx, Screensize);
        unsigned Py = index_correct_position(Previos_positiony, Screensize);
        for (auto s : val) {
            float New_positionx = s.x;
            float New_positiony = s.y;
            unsigned Nx = index_correct_position(New_positionx, Screensize);
            unsigned Ny = index_correct_position(New_positiony, Screensize);
            fptr->getthis()->setPosition(Previos_positionx, Previos_positiony);
            if ((chessboard[Ny][Nx] == 3 && fptr->getthis()->getColor() == 1) || (chessboard[Ny][Nx] == 4 && fptr->getthis()->getColor() == 0)) {
                futures.push_back(std::async(new_help_func_check_mate_with_threads, sf::Vector2f(Previos_positionx, Previos_positiony), sf::Vector2f(New_positionx, New_positiony), 1, Screensize, chessboard, this));
            }
            else {
                futures.push_back(std::async(new_help_func_check_mate_with_threads, sf::Vector2f(Previos_positionx, Previos_positiony), sf::Vector2f(New_positionx, New_positiony), 0, Screensize, chessboard, this));
            }
        }
        
    }
    for (auto& future : futures) {
        if (future.get() == 1) {
            return 1;
        }
    }
    return 0;
}

unsigned Kdtree::IS_MATE(float Screensize, unsigned(chessboard)[8][8], bool whoose_move) {
    std::shared_ptr<Figure> Wking;
    std::shared_ptr<Figure> Bking;
    func_find_king(&Wking, &Bking, root);
    if (Wking->get_is_under_attack() == 1 && whoose_move == 1) {
        if (func_check_mate(whoose_move, Screensize, chessboard) == 0) {
            return 1;
        }
    }
    else if (Bking->get_is_under_attack() == 1 && whoose_move == 0) {
        if (func_check_mate(whoose_move, Screensize, chessboard) == 0) {
            return 1;
        }
    }
    else {
        if ( (func_check_mate(1, Screensize, chessboard) == 0 && whoose_move == 0) || (func_check_mate(0, Screensize, chessboard) == 0) && whoose_move == 1) {
            return 2;
        }
    }
    return 0;
}