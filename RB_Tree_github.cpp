#include <vector>
#include <algorithm>
#include <iostream>

struct Node {
    int key;
    Node * parent;
    Node * left;
    Node * right;
    char color;

    Node(): parent(nullptr), left(nullptr), right(nullptr), color('B')
    {}

    explicit Node(int x): key(x),
                 parent(nullptr), left(nullptr), right(nullptr), color('R') {}

    Node * findNode(int x) {
        Node * curNode = this;
        if (curNode->key == x) {
            return curNode;
        }
        if (curNode->key > x) {
            if (curNode->left == nullptr) {
                return curNode;
            } else {
                return curNode->left->findNode(x);
            }
        } else {
            if (curNode->right == nullptr) {
                return curNode;
            } else {
                return curNode->right->findNode(x);
            }
        }
    }

    void insert(int x) {
        Node * place = this->findNode(x);
        if (place->key == x) {
            return;
        }
        if (place->key > x) {
            place->left = new Node(x);
            place->left->parent = place;
        } else {
            place->right = new Node(x);
            place->right->parent = place;
        }

        if (place->color == 'B') {
            return;
        }
        if (place->right != nullptr && place->right->key == x) {
            place->right->rotate_left();
            place->repair();
        } else {
            place->left->repair();
        }
    }

    void rotate_left() {
        Node * child = this;
        Node * curParent = child->parent;
        curParent->right = child->left;
        if (child->left != nullptr) {
            child->left->parent = curParent;
        }
        child->parent = curParent->parent;
        if (curParent->parent != nullptr) {
            if (curParent->parent->right != nullptr && curParent == curParent->parent->right) {
                curParent->parent->right = child;
            } else {
                curParent->parent->left = child;
            }
        }
        curParent->parent = child;
        child->left = curParent;
    }

    void rotate_right() {
        Node * child = this;
        Node * curParent = child->parent;
        curParent->left = child->right;
        if (child->right != nullptr) {
            child->right->parent = curParent;
        }
        child->parent = curParent->parent;
        if (curParent->parent != nullptr) {
            if (curParent->parent->right != nullptr && curParent == curParent->parent->right) {
                curParent->parent->right = child;
            } else {
                curParent->parent->left = child;
            }
        }
        curParent->parent = child;
        child->right = curParent;
    }

    void repair() {
        Node * child = this;
        if (child->parent == nullptr) {
            child->color = 'B';
            return;
        }
        if (child->parent->parent == nullptr) {
            return;
        }
        if (child->parent->color == 'B') {
            return;
        }
        if (child->parent->right != nullptr && child->parent->right == child) {
            child->rotate_left();
            child = child->left;
        }
        Node * grParent = child->parent->parent;
        if (grParent->left != nullptr && grParent->left == child->parent) {
            if (grParent->right == nullptr) {
                child->parent->rotate_right();
                child->parent->color = 'B';
                grParent->color = 'R';
                return;
            } else if (grParent->right->color == 'R') {
                grParent->color = 'R';
                grParent->right->color = 'B';
                grParent->left->color = 'B';
                grParent->repair();
            } else {
                child->parent->rotate_right();
                grParent->color = 'R';
                child->parent->color = 'B';
                return;
            }
        } else {
            if (grParent->left == nullptr) {
                child->rotate_right();
                child->rotate_left();
                child->color = 'B';
                grParent->color = 'R';
                return;
            } else if (grParent->left->color == 'R') {
                grParent->color = 'R';
                grParent->left->color = 'B';
                grParent->right->color = 'B';
                grParent->repair();
            } else {
                child->rotate_right();
                child->rotate_left();
                child->color = 'B';
                grParent->color = 'R';
                return;
            }
        }
    }

    bool find(int x) {
        if (this->key == x) {
            return true;
        }
        if (this->key > x) {
            if (this->left != nullptr) {
                return this->left->find(x);
            } else {
                return false;
            }
        } else {
            if (this->right != nullptr) {
                return this->right->find(x);
            } else {
                return false;
            }
        }
    }

    int vertexNum() {
        int leftSubtree = 0;
        int rightSubtree = 0;
        if (this->left != nullptr) {
            leftSubtree = this->left->vertexNum();
        }
        if (this->right != nullptr) {
            rightSubtree = this->right->vertexNum();
        }
        return rightSubtree + leftSubtree + 1;
    }

    void printNode() {
        if (this->left != nullptr) {
            this->left->printNode();
        }

        std::cout << key << " ";
        if (this->left == nullptr) {
            std::cout << "null ";
        } else {
            std::cout << this->left->key << " ";
        }
        if (this->right == nullptr) {
            std::cout << "null ";
        } else {
            std::cout << this->right->key << " ";
        }
        std::cout << color << "\n";

        if (this->right != nullptr) {
            this->right->printNode();
        }
    }
};

class rbTree {
 private:
    Node * root;

 public:
    rbTree(): root(nullptr) {}

    void add(int x) {
        if (root == nullptr) {
            root = new Node(x);
            root->color = 'B';
        } else {
            root->insert(x);
            while (root->parent != nullptr) {
                root = root->parent;
            }
        }
    }

    void findKey(int x) {
        if (root != nullptr) {
            if (root->find(x)) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else {
            std::cout << "No\n";
        }
    }

    void print() {
        if (root != nullptr) {
            std::cout << root->vertexNum() << "\n";
            root->printNode();
        } else {
            std::cout << "0\n";
        }
    }
};
