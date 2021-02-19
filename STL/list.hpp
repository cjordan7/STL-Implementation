//
//  List.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef list_hpp
#define list_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

namespace ostl {

// TODO: Move class to List class
template<class T>
class Node {
    T data;
    Node<T>* next;
    Node<T>* previous;

public:
    Node() {
        next = nullptr;
        previous = nullptr;
    }

    Node(T data) {
        this->data = data;
    }

    Node(Node<T>& node) {
        data = node.data;
        next = node.next;
        previous = node.previous;
    }

    ~Node() {
    }

    void setData(T data) {
        this->data = data;
    }

    void setNext(Node<T>* node) {
        next = node;
    }

    void setPrevious(Node<T>* node) {
        previous = node;
    }

    T getData() {
        return data;
    }

    Node<T>* getNext() {
        return next;
    }

    Node<T>* getPrevious() {
        return previous;
    }
};

template<class T>
class List { // or in other words a DoublyLinkedList
private:
    // Beginning of the list
    Node<T>* head;

    // Last element of the list
    Node<T>* tail;

    // Size of the list
    unsigned long long sizeV;
public:

    // Schema of Doubly linked list
    // head ---> Previous Nodes ---> tail

    // head <--- Next Nodes <--- tail

    List() {
        head = nullptr;
        tail = nullptr;
        sizeV = 0;
    }

    List(List<T> const& List) {
        // TODO: Implement
    }

    ~List() {
        // TODO: Free memory
    }

    void pushFront(const T& t) {
        pushFront(t);
    }

    void pushFront(T&& t) {
        pushFront(t);
    }

    // Put data in a new node as the new head
    void pushFront(T data) {
        Node<T>* t = new Node<T>(data);

        ++sizeV;

        if(head == nullptr) {
            tail = t;
        } else {
            t->setPrevious(head);
            head->setNext(t);
        }

        head = t;
    }

    // Put data in a new node as the new tail
    void pushBack(T data) {
        Node<T>* t = new Node<T>(data);

        ++sizeV;

        if(tail == nullptr) {
            head = t;
        } else {
            t->setNext(tail);
            tail->setPrevious(t);
        }

        tail = t;
    }

    void popFront() {
        Node<T>* temp = head;

        if(head == nullptr) {
            return;
        } else if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = temp->getPrevious();
            temp->setPrevious(nullptr);
        }

        --sizeV;
        delete temp;
    }

    void popBack() {
        Node<T>* temp = head;

        if(tail == nullptr) {
            return;
        } else if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = temp->getNext();
            temp->setNext(nullptr);
        }

        --sizeV;
        delete temp;
    }

    unsigned long long size() {
        return sizeV;
    }

    // TODO Implement other functions of List

};

} /* namespace ostl */
#endif /* list_hpp */
