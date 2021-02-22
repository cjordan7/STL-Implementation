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

template<class T>
class Node {
    T data;
    Node<T>* next = nullptr;
    Node<T>* previous = nullptr;

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

    T& getData() {
        return data;
    }

    const T& getData() const {
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
    Node<T>* head = nullptr;

    // Last element of the list
    Node<T>* tail = nullptr;

    // Size of the list
    unsigned long long sizeV = 0;
public:
    class Iterator {
        private:
        friend class List;
        Node<T>* pointTo;

        public:
        Iterator(): pointTo(nullptr) {
        }

        Iterator(const Iterator& it): pointTo(it.pointTo) {
        }

        ~Iterator() {
        }

        Iterator& operator=(const Iterator& it) {
            pointTo = it.pointTo;

            return *this;
        }

        bool operator==(const Iterator& rhs){
            return pointTo == rhs.pointTo;
        }

        bool operator!=(const Iterator& rhs){
            return pointTo != rhs.pointTo;
        }

        Iterator& operator++() {
            pointTo = pointTo->getPrevious();

            return *this;
        }

        Iterator& operator--() {
            pointTo = pointTo->getNext();

            return *this;
        }

        Iterator operator+=(const int& right) {

            return *this;
        }

        Iterator operator+(const int& right) {
            int temp = right;
            while(right != 0) {
                if(right < 0) {
                    ++temp;
                    --(*this);
                } else {
                    --temp;
                    ++(*this);
                }
            }

            return *this;
        }

        T& operator*() const {
            return pointTo->getData();
        }
    };
public:
    // Schema of Doubly linked list
    // head ---> Previous Nodes ---> tail

    // head <--- Next Nodes <--- tail

    List() {
    }

    List(List<T> const& list) {
        for(Iterator it = list.cbegin(); it != list.cend(); ++it) {
            std::cout << *it << std::endl;
            std::cout << sizeV << std::endl;
            pushBack(*it);
        }
    }

    ~List() {

    }

    Iterator begin() {
        Iterator iterator;
        iterator.pointTo = head;
        return iterator;
    }

    Iterator end() {
        Iterator iterator;
        iterator.pointTo = tail->getPrevious();
        return iterator;
    }

    const Iterator cbegin() const noexcept {

        Iterator iterator;
        iterator.pointTo = head;
        return iterator;
    }

    const Iterator cend() const noexcept {
        Iterator iterator;
        iterator.pointTo = tail->getPrevious();
        return iterator;
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

    T& front() {
        return head->getData();
    }

    const T& front() const {
        return head->getData();
    }

    T& back() {
        return tail->getData();
    }

    const T& back() const {
        return tail->getData();
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

    bool empty() const noexcept {
        return sizeV == 0;
    }
};

} /* namespace ostl */
#endif /* list_hpp */
