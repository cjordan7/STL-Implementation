//
//  set.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef set_hpp
#define set_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

namespace ostl {

// TODO: Consider put in other class as private
template<class T, class Comparator = std::less<T>>
class Set {
private:

private:
    Comparator compare;

    struct Node {
        T data;
        Node* left;
        Node* right;
    };

    Node* root;

public:
    class Iterator {
        friend class Set;
    private:
        Comparator compareInside;
        Node* node;
        Node* root;

#define setElement(node, sideOne, sideTwo)\
if(root->sideOne != nullptr) {\
    Node* n = root->sideOne;\
    while(n->sideTwo) {\
        n = n->sideTwo;\
    }\
    node = n;\
}

        void findPredAndSuccess(Node* root, Node*& predecessor,
                                Node*& successor, T data) {
            if(root == nullptr) {
                return;
            }

            if(!compareInside(root->data, data) and
               !compareInside(data, root->data)) {
                setElement(predecessor, left, right);
                setElement(successor, right, left);
                return;
            }

            if(compareInside(data, root->data)) {
                successor = root;
                findPredAndSuccess(root->left, predecessor, successor, data);
            } else {
                predecessor = root;
                findPredAndSuccess(root->right, predecessor, successor, data);
            }
        }

        void setNode(Node* node, Node* root) {
            this->node = node;
            this->root = root;
        }

    public:

        Iterator() {
            node = nullptr;
            root = nullptr;
        }

        Iterator(const Iterator& iterator) {
            this->node = iterator.node;
            this->root = iterator.root;
        }

        T operator*() {
            return node->data;
        }

        Iterator& operator++() {
            Node* predecessor = nullptr;
            Node* successor = nullptr;
            findPredAndSuccess(root, predecessor, successor, node->data);

            node = successor;
            return *this;
        }

        Iterator operator++(int) {
            return operator++();
        }

        bool operator==(const Iterator& rhs){
            return root == rhs.root and node == rhs.node;
        }

        bool operator!=(const Iterator& rhs){
            return !(*this == rhs);
        }

        Iterator& operator--() {
            Node* predecessor = nullptr;
            Node* successor = nullptr;
            findPredAndSuccess(root, predecessor, successor, node->data);

            node = predecessor;
            return *this;
        }

        Iterator operator--(int) {
            return operator--();
        }
    };

    Node* buildNode(T data) {
        Node* node = new Node();
        node->left = nullptr;
        node->right = nullptr;
        node->data = data;
        return node;
    }

public:
    Set() {
        root = nullptr;
    }

    Set(std::initializer_list<T> il) {
        for(auto& it:il) {
            insert(it);
        }
    }

    ~Set() {
        cleanMemory(root);
    }

    void clear() noexcept {
        cleanMemory(root);
    }

private:
    void cleanMemory(Node* node) {
        if(node == nullptr) {
        } else if(node->left == nullptr and node->right == nullptr) {
            delete node;
        } else if(node->left == nullptr) {
            cleanMemory(node->right);
        } else if(node->right == nullptr) {
            cleanMemory(node->left);
        }
    }

    Node* getFirstNode(Node* node) const {
        if(node->left == nullptr) {
            return node;
        } else {
            return getFirstNode(node->left);
        }
    }

    Node* getLastNode(Node* node) const {
        if(node->right == nullptr) {
            return node;
        } else {
            return getLastNode(node->right);
        }
    }

public:

    Iterator begin() {
        return cbegin();
    }

    const Iterator cbegin() const noexcept{
        Iterator it;
        it.setNode(getFirstNode(root), root);
        return it;
    }

    Iterator end() noexcept {
        return cend();
    }

    const Iterator cend() const noexcept{
        Iterator it;
        it.setNode(getLastNode(root), root);
        ++it;
        return it;
    }

    bool empty() const {
        return root == nullptr;
    }

    void insert(const T& data) {
        if(root == nullptr) {
            root = insertNode(root, data);
        } else {
            insertNode(root, data);
        }
    }

private:
    Node* insertNode(Node* node, const T& data) {
        if(node == nullptr) {
            return buildNode(data);
        }

        if(compare(data, node->data)) {
            node->left = insertNode(node->left, data);
        } else {
            node->right = insertNode(node->right, data);
        }

        return node;
    }

public:
    Iterator insert(Iterator position, const T& data) {
        return Iterator(insertNode(position.node, data));
    }

    void insert(Iterator first, Iterator last) {
        for(Iterator position = first; position != last; ++position) {
            insert(position, position->node->data);
        }
    }

    Iterator erase(Iterator position) {
        Iterator newPos = ++position;
        eraseNode(root, position.node->data);
        return newPos;
    }

private:
    Node* eraseNode(Node* root, int data) {
        if(root == nullptr) {
            return root;
        }
        if(compare(data, root->data)) {
            root->left = eraseNode(root->left, data);
        } else if(compare(root->data, data)) {
            root->right = eraseNode(root->right, data);
        } else {
            if(root->right == nullptr) {
                Node* n = root->left;
                delete root;
                return n;
            } else if(root->left == nullptr) {
                Node* n = root->right;
                delete root;
                return n;
            }

            Node* temp = minNode(root->right);

            root->data = temp->data;
            root->right = eraseNode(root->right, temp->data);
        }
        return root;
    }

    Node* minNode(Node* node) {
        Node* current = node;

        while(current and current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

public:
    unsigned long long erase(const T& data) {
        return eraseNode(root, data) != nullptr;
    }

    Iterator erase(Iterator first, Iterator last) {
        for(Iterator e = first; e != last; ++e) {
            erase(e);
        }
    }

    void swap(Set& set) {
        Node* temp = set.root;
        set.root = root;
        root = temp;
    }

private:
    Node* find(Node* root, const T& data) const {
        if(root == nullptr) {
            return nullptr;
        } else if(compare(data, root->data)) {
            return find(root->left, data);
        } else if(compare(root->data, data)) {
            return find(root->right, data);
        } else {
            return root;
        }
    }

public:
    Iterator find(const T& data) const{
        Iterator it;
        it.setNode(find(root, data), root);
        return it;
    }

private:
    unsigned long long count(Node* node) {
        if(node == nullptr) {
            return 0;
        } else {
            return count(node->left) + count(node->right) + 1;
        }
    }

public:
    unsigned long long size() {
        return count(root);
    }
};

} /* namespace ostl */
#endif /* set_hpp */
