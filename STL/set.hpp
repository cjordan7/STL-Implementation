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
    struct IteratorValue;

public:
    typedef IteratorValue* Iterator;

private:
    Comparator compare;

    struct Node {
        T data;
        Node* left;
        Node* right;
    };

    Node* root;

    class IteratorValue {
        friend class Set;
    private:
        Iterator it;
        Node* node;
    public:

        IteratorValue(Node* n) {
            node = n;
        }

        IteratorValue &operator++() {

        }

        IteratorValue operator++(int) {

        }

        IteratorValue& operator--() {

        }

        IteratorValue operator--(int) {

        }

        IteratorValue operator+=(const int& right) {

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

    ~Set() {
        cleanMemory(root);
    }

    void cleanMemory(Node* node) {
        if(node == nullptr) {
            return;
        } else if(node->left == nullptr and node->right == nullptr) {
            delete node;
            return;
        } else if(node->left == nullptr) {
            cleanMemory(node->right);
        } else if(node->right == nullptr) {
            cleanMemory(node->left);
        }
    }

private:
    Node* getFirstNode(Node* node) {
        if(node->left == nullptr) {
            return node;
        } else {
            getFirstNode(node->left);
        }
    }

    Node* getLastNode(Node* node) {
        if(node->right == nullptr) {
            return node;
        } else {
            getlastNode(node->right);
        }
    }

public:
    Iterator begin() {
        std::unique_ptr<IteratorValue> iV(new IteratorValue(getFirstNode(root)));
        return iV;
    }

    const Iterator begin() const {
        std::unique_ptr<IteratorValue> it(new IteratorValue(getFirstNode(root)));
        return it;
    }

    Iterator end() noexcept {
        std::unique_ptr<IteratorValue> it(new IteratorValue(getLastNode(root)));
        return it;
    }

    const Iterator end() const noexcept{
        std::unique_ptr<IteratorValue> it(new IteratorValue(getLastNode(root)));
        return it;
    }

    bool empty() const {
        return root == nullptr;
    }

    void insert(const T& data) {
        IteratorValue it = IteratorValue(root);
        insert(root, data);
    }

private:
    Node* insert(Node* node, T& data) {
        if(node == nullptr) {
            node = buildNode(data);
            return node;
        } else if(compare(data, node->data)) {
            node->left = insert(node->left, data);
        } else if(compare(node->data, data)) {
            node->right = insert(node->right, data);
        }
    }

public:
    Iterator insert(Iterator position, const T& data) {
        Node* node = insert(position->node, data);
        std::unique_ptr<IteratorValue> it(new IteratorValue(position));
        return it;
    }

    void insert(Iterator first, Iterator last) {
        for(Iterator position = first; position != last; ++position) {
            insert(position, position->node->data);
        }
    }

    Iterator erase(Iterator position) {
        Iterator it = --position;

        Node* node = position->node == it->node->left ? node->left : node->right;

        if(position->node == it->node->left) {
            it->node->left = node->left;
        } else {
            it->node->right = node->right;
        }

        delete node;

        return it;
    }

    unsigned long long erase(const T& data) {
        Iterator it = find(data);

        if(it == nullptr) {
            return 0;
        } else {
            erase(data);
            return 1;
        }
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
    Node* find(Node* root, const T& data) const{
        if(root == nullptr) {
            return nullptr;
        } else if(compare(data, root->data)){
            return find(root->left, data);
        } else if(compare(data, root->data)){
            return find(root->right, data);
        } else {
            return root;
        }
    }

public:
    Iterator find(const T& data) const{
        Node* node = find(root, data);

        std::unique_ptr<IteratorValue> it(new IteratorValue(node));

        return it;
    }

private:
    unsigned long long count(Node* node, int size) {
        if(node == nullptr) {
            return size;
        } else {
            ++size;
            return count(node->left, size) + count(node->right, size);
        }
    }

public:
    unsigned long long count() {
        return count(root, 0);
    }

};

} /* namespace ostl */
#endif /* set_hpp */
