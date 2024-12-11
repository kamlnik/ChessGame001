#include <My_lib/Kdtree.hpp>
#include <algorithm>

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
std::shared_ptr <kdNode> delete_kdNode(std::shared_ptr<kdNode> fptr) {
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
void Copy_Info(std::shared_ptr <kdNode> ptr1, std::shared_ptr <kdNode> ptr2) {
    std::shared_ptr<kdNode> hptr = ptr1;
    ptr1->setthis(ptr2->getthis());
}
void Kdtree::ChangeNode(kdNode* delNode, int nx, int ny) {

}
void putTree(sf::RenderTarget& target, std::shared_ptr <kdNode> ptr, int level)
{
    int i = level;
    if (ptr != nullptr) {
        
        putTree(target, ptr->getrightchild(), level+1);
       // while (i-- > 0) {
       //     std::cout << "      ";
       // }
      //  std::cout << ptr.get()->getthis()->getPosition().x << " , " << ptr.get()->getthis()->getPosition().y << "\n";
        target.draw(*(ptr->getthis())); // интересно будет ли работать 
        putTree(target, ptr->getleftchild(), level + 1);

    }
}
void Kdtree::drawtree(sf::RenderTarget& target) {
    putTree(target, root, 0);
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