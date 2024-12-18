#include <My_lib/Kdtree.hpp>
#include <algorithm>


unsigned newmindex_correct_position(float position) {
    float returned_val = 0.f;
    int per = position / 50;
    if (per % 2 == 0) {
        returned_val = (per) / 2;
        return returned_val;
    }
    returned_val = (per - 1) / 2;
    return returned_val;
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
    return minNodey(fptr, hfindminx(fptr->getleftchild()), hfindminx(fptr->getrightchild()));
}
std::shared_ptr<kdNode> Kdtree::findminx(std::shared_ptr<kdNode> fptr) {
    return hfindminx(fptr);
}
std::shared_ptr<kdNode> Kdtree::findminy(std::shared_ptr<kdNode> fptr) {
    return hfindminy(fptr);
}
/*std::shared_ptr <kdNode> delete_kdNode(std::shared_ptr<kdNode> fptr) {
    if (fptr != nullptr) {
        if (fptr->getrightchild() != nullptr) {

            if (fptr->getcoord() == true) { // ломается при 5 5 
                std::shared_ptr <kdNode> findp = hfindminx(fptr->getrightchild());  // find min in right subtree
                fptr->setthis(findp->getthis());
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                //   fptr->setthis((hfindp->getthis()));
                fptr->setcoord(true);
            }
            else {
                std::shared_ptr <kdNode> findp = hfindminy(fptr->getrightchild());
                fptr->setthis(findp->getthis());
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                //   fptr->setthis(hfindp->getthis()); // вроде как мы просто теряем, но типа тут умный указатель и мб всё окей 
                fptr->setcoord(false);
            }
        }
        else if (fptr->getleftchild() != nullptr) {
            if (fptr->getcoord() == true) {
                std::shared_ptr <kdNode> findp = hfindminx(fptr->getleftchild());
                fptr->setthis(findp->getthis());
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                fptr->setrightchild(fptr->getleftchild());
                fptr->setleftchild(nullptr);
                //  fptr->setthis(hfindp->getthis());
                fptr->setcoord(true);

            }
            else {
                std::shared_ptr <kdNode> findp = hfindminy(fptr->getleftchild());
                fptr->setthis(findp->getthis());
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                fptr->setrightchild(fptr->getleftchild());
                fptr->setleftchild(nullptr);
                // fptr->setthis(hfindp->getthis());
                fptr->setcoord(false);
            }
        }
        else {
            std::shared_ptr<kdNode> mparent = fptr->getparent();
            if (mparent != nullptr) {   // подчищаем parent
                if (fptr->getparent()->getcoord() == true) {
                    if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                        fptr->getparent()->setrightchild(nullptr);
                        fptr->setparent(nullptr);
                    }
                    else {
                        fptr->getparent()->setleftchild(nullptr);
                        fptr->setparent(nullptr);
                    }
                }
                else {
                    if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                        fptr->getparent()->setrightchild(nullptr);
                        fptr->setparent(nullptr);
                    }
                    else {
                        fptr->getparent()->setleftchild(nullptr);
                        fptr->setparent(nullptr);
                    }
                }
                fptr.~shared_ptr();
            }
            // else {
              //   return nullptr;
             //}
            // return nullptr; // удаление этого узла 
        }
    }
    else {
        throw std::logic_error("not found deleted element");
    }
    return fptr;
}*/
/*std::shared_ptr <kdNode> Kdtree::delete_kdNode(std::shared_ptr<kdNode> fptr) {
    if (fptr != nullptr) {
        if (fptr->getrightchild() != nullptr) {

            if (fptr->getcoord() == true) { // ломается при 5 5 
                std::shared_ptr <kdNode> findp = hfindminx(fptr->getrightchild());  // find min in right subtree
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                hfindp->setrightchild(fptr->getrightchild());
                hfindp->setleftchild(fptr->getleftchild());
                if (fptr->getparent() != nullptr) {
                    if (fptr->getparent()->getcoord() == true) {
                        if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                    else {
                        if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                }
                else {
                    root = hfindp;
                }
                hfindp->setparent(fptr->getparent());
                fptr->setrightchild(nullptr);
                fptr->setleftchild(nullptr);
                hfindp->setcoord(true);
                fptr->setparent(nullptr);
            }
            else {
                std::shared_ptr <kdNode> findp = hfindminy(fptr->getrightchild());  // find min in right subtree
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                hfindp->setrightchild(fptr->getrightchild());
                hfindp->setleftchild(fptr->getleftchild());
                if (fptr->getparent() != nullptr) {
                    if (fptr->getparent()->getcoord() == true) {
                        if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                    else {
                        if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                }
                else {
                    root = hfindp;
                }
                hfindp->setparent(fptr->getparent());
                fptr->setrightchild(nullptr);
                fptr->setleftchild(nullptr);
                hfindp->setcoord(false);
                fptr->setparent(nullptr);
            }
        }
        else if (fptr->getleftchild() != nullptr) {
            if (fptr->getcoord() == true) {
                std::shared_ptr <kdNode> findp = hfindminx(fptr->getleftchild());  // find min in right subtree
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                hfindp->setrightchild(fptr->getleftchild());
                hfindp->setleftchild(nullptr);
                if (fptr->getparent() != nullptr) {

                    if (fptr->getparent()->getcoord() == true) {
                        if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                    else {
                        if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                }
                else {
                    root = hfindp;
                }
                hfindp->setparent(fptr->getparent());
                fptr->setrightchild(nullptr);
                fptr->setleftchild(nullptr);
                fptr->setparent(nullptr);
                hfindp->setcoord(true);
            }
            else {
                std::shared_ptr <kdNode> findp = hfindminy(fptr->getleftchild());  // find min in right subtree
                // fptr->setthis(findp->getthis());
                std::shared_ptr <kdNode> hfindp = delete_kdNode(findp);
                hfindp->setrightchild(fptr->getleftchild());
                hfindp->setleftchild(nullptr);
                if (fptr->getparent() != nullptr) {
                    if (fptr->getparent()->getcoord() == true) {
                        if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                    else {
                        if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                            fptr->getparent()->setrightchild(hfindp);
                        }
                        else {
                            fptr->getparent()->setleftchild(hfindp);
                        }
                    }
                }
                else {
                    root = hfindp;
                }
                hfindp->setparent(fptr->getparent());
                fptr->setrightchild(nullptr);
                fptr->setleftchild(nullptr);
                fptr->setparent(nullptr);
                //   fptr->setthis((hfindp->getthis()));
                hfindp->setcoord(false);
            }
        }
        else {
            std::shared_ptr<kdNode> mparent = fptr->getparent();
            if (mparent != nullptr) {   // подчищаем parent
                if (fptr->getparent()->getcoord() == true) {
                    if (fptr->getthis()->getPosition().x >= fptr->getparent()->getthis()->getPosition().x) {
                        fptr->getparent()->setrightchild(nullptr);
                        fptr->setparent(nullptr);
                        // fptr.~shared_ptr();
                    }
                    else {
                        fptr->getparent()->setleftchild(nullptr);
                        fptr->setparent(nullptr);
                        // fptr.~shared_ptr();
                    }
                }
                else {
                    if (fptr->getthis()->getPosition().y >= fptr->getparent()->getthis()->getPosition().y) {
                        fptr->getparent()->setrightchild(nullptr);
                        fptr->setparent(nullptr);
                        //fptr.~shared_ptr();
                    }
                    else {
                        fptr->getparent()->setleftchild(nullptr);
                        fptr->setparent(nullptr);
                        //  fptr.~shared_ptr();
                    }
                }
            }
            // else {
              //   return nullptr;
             //}
            // return nullptr; // удаление этого узла 
        }
    }
    else {
        throw std::logic_error("not found deleted element");
    }
    return fptr;
}*/
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
    return 2;
}
void Kdtree::delete_kdNode(std::shared_ptr<kdNode> fptr) { /// not work 
    if (fptr == nullptr) {
        return;
    }
    if (fptr->getrightchild() != nullptr) {
        //std::shared_ptr<kdNode> needed; // needed - min элемент, fptr - удаляемый узел 
        std::shared_ptr<kdNode> valptr;
        if (fptr->getcoord() == true) {
            valptr = findminx(fptr->getrightchild()); // needed - min элемент, fptr - удаляемый узел     
        }
        else {
            valptr = findminy(fptr->getrightchild());
        }
        delete_kdNode(valptr); // это рекурсия от правого узла, дальше замена указателей

        valptr->setrightchild(fptr->getrightchild()); // необходимо корректно определять в конце 
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
        // std::shared_ptr<kdNode> needed; // needed - min элемент, fptr - удаляемый узел 
        std::shared_ptr<kdNode> valptr;
        if (fptr->getcoord() == true) {
            valptr = findminx(fptr->getleftchild());
        }
        else {
            valptr = findminy(fptr->getleftchild());
        }
        delete_kdNode(valptr);
        // fptr->getleftchild()->setparent(valptr);
        valptr->setrightchild(fptr->getleftchild()); // необходимо корректно определять в конце 
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
void Kdtree::AddNode(std::shared_ptr <kdNode> newNode) { // надо сделать проверку на дубликаты 
    if (FindNode(newNode->getthis()->getPosition().x, newNode->getthis()->getPosition().y) != nullptr) {
        throw std::logic_error("add duplicate");
    }
    if (root == nullptr) {
        root = newNode;
        newNode->setleftchild(nullptr);
        newNode->setrightchild(nullptr);
        newNode->setparent(nullptr);
        //    newNode->setcoord(true);
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
            else if (newNode->getthis()->getPosition().x < val->getthis()->getPosition().x) {
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
            else if (newNode->getthis()->getPosition().y < val->getthis()->getPosition().y) {
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
std::shared_ptr<kdNode> Kdtree::FindNode(float xc, float yc) { // работает
    std::shared_ptr<kdNode> val = root;
    bool coordx = { true };
    bool coordy = { false };
    std::shared_ptr <kdNode> pred;
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

void Kdtree::ChangeNode(std::shared_ptr<kdNode> fptr, sf::Vector2f Previos_position, sf::Vector2f New_position) {
    if (fptr == nullptr) {
        throw std::runtime_error("ChangeNode Error: pointer = nullptr");
    }
    fptr->getthis()->setPosition(Previos_position.x, Previos_position.y);
    DeleteNode(fptr);
    fptr->getthis()->setPosition(New_position.x, New_position.y);
    AddNode(fptr);
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
        target.draw(*(ptr->getthis())); // интересно будет ли работать 
        putTree(target, ptr->getleftchild(), level + 1);

    }
}
void Kdtree::drawtree(sf::RenderTarget& target) {
    putTree(target, root, 0);
}

void  help_func_for_update_move(std::shared_ptr <kdNode> ptr) {
    if (ptr != nullptr) {
        help_func_for_update_move(ptr->getleftchild());
        ptr->getthis()->update_move();
        help_func_for_update_move(ptr->getrightchild());
    }
}
void Kdtree::update_all_move() {
    help_func_for_update_move(root);
}

void  help_func_for_update_status(std::shared_ptr <kdNode> ptr, const unsigned(&chessboard)[8][8]) {
    if (ptr != nullptr) {

        help_func_for_update_status(ptr->getleftchild(), chessboard);
        unsigned xc = newmindex_correct_position(ptr->getthis()->getPosition().x);
        unsigned yc = newmindex_correct_position(ptr->getthis()->getPosition().y);
        ptr->getthis()->set_is_under_attack(0);
        if (ptr->getthis()->getColor() == 0 && chessboard[yc][xc] == 3) {
            ptr->getthis()->set_is_under_attack(1);
        }
        if (ptr->getthis()->getColor() == 1 && chessboard[yc][xc] == 4) {
            ptr->getthis()->set_is_under_attack(1);
        }
        help_func_for_update_status(ptr->getrightchild(), chessboard);
    }
}

void Kdtree::update_all_status( const unsigned (&chessboard)[8][8]) {
    help_func_for_update_status(root, chessboard);
}

void tree_bypass_help_func(std::shared_ptr<kdNode> fptr, float xc, float yc) {
    std::cout << 1 << std::endl;
    if (fptr != nullptr) {

        tree_bypass_help_func(fptr->getrightchild(), xc, yc);
        //if ....
        std::cout << fptr->getthis()->getPosition().x << fptr->getthis()->getPosition().y << std::endl;
        //if (fptr->getthis()->boundingBox.contains(xc, yc) && Needed_element == nullptr ) {
        //	std::cout << fptr->getthis()->boundingBox.left << std::endl;
        //	*Needed_element = fptr;
        //}
        tree_bypass_help_func(fptr->getleftchild(), xc, yc);

    }
}
void Kdtree::tree_bypass( float xc, float yc ) {
    tree_bypass_help_func(this->root, xc, yc);
}