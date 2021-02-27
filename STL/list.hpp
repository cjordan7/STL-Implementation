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
class List;
// A useful class for the list.
template<class T>
class Node {
    friend class List<T>;
    T data;
    Node<T>* next = nullptr;
    Node<T>* previous = nullptr;

public:
    Node() {
        next = nullptr;
        previous = nullptr;
    }

    // Set the node with some data.
    Node(T data) {
        this->data = data;
    }

    // Copy a node.
    Node(Node<T>& node) {
        data = node.data;
        next = node.next;
        previous = node.previous;
    }

    ~Node() {
        // I've decided to let the list delete the node's left and right.
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

    Node<T>* getNext() const {
        return next;
    }

    Node<T>* getPrevious() const {
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

        // What node the iterator points to.
        Node<T>* pointTo;

        public:
        // Default constructor.
        Iterator(): pointTo(nullptr) {
        }

        // Copy it to this
        Iterator(const Iterator& it): pointTo(it.pointTo) {
        }

        ~Iterator() {
            // It should the list itself that has the job
            // to delete the pointTo.
        }

        // Assign it to this
        Iterator& operator=(const Iterator& it) {
            pointTo = it.pointTo;

            return *this;
        }

        // Check equality of pointers.
        bool operator==(const Iterator& rhs){
            return pointTo == rhs.pointTo;
        }

        // Check non equality of pointers.
        bool operator!=(const Iterator& rhs){
            return pointTo != rhs.pointTo;
        }

        // Get next of node.
        Iterator& operator++() {
            pointTo = pointTo->getPrevious();

            return *this;
        }

        // Get previous of node.
        Iterator& operator--() {
            pointTo = pointTo->getNext();

            return *this;
        }

        // 
        Iterator operator+=(const int& right) {
            // TODO: Implement
            return *this;
        }

        // Add element to this.
        Iterator operator+(const int& right) {
            Iterator it(this);
            int temp = right;
            while(right != 0) {
                if(right < 0) {
                    ++temp;
                    --it;
                } else {
                    --temp;
                    ++it;
                }
            }
            return it;
        }

        // Return the data of the node.
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

    // Init with initializer list.
    List(std::initializer_list<T> il) {
        for(auto& it: il) {
            pushFront(it);
        }
    }

    // Init with a list. (Copy constructor).
    List(List<T> const& list) {
        for(Iterator it = list.cbegin(); it != list.cend(); ++it) {
            pushBack(*it);
        }
    }

    ~List() {
        clear();
    }

    // Clear memory
    void clear() noexcept {
        Node<T>* current = head;

        // While current is not null,
        // then we delete the current.
        while(current != nullptr) {
            // Get next.
            Node<T>* next = current->next;

            // Delete the current.
            delete current;

            // Set current to next one as we have to delete it.
            current = next;
        }

        // Reset head
        head = nullptr;

        // Reset tail
        tail = nullptr;

        // Reset Size.
        sizeV = 0;
    }

    Iterator begin() {
        return cbegin();
    }

    Iterator end() {
        return cend();
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

    void pushFront(T&& t) {
        pushFront(t);
    }

    // Put data in a new node as the new head
    void pushFront(const T& data) {
        Node<T>* t = new Node<T>(data);

        // Update size
        ++sizeV;

        // If head is null then update the tail
        if(head == nullptr) {
            tail = t;
        } else {
            // Set the previous and the next
            t->setPrevious(head);
            head->setNext(t);
        }

        // Update the head
        head = t;
    }

    // Return the front of the list
    T& front() {
        //
        return head->getData();
    }

    // Return the front of the list
    const T& front() const {
        // Return the data of the head, which is the begining of the list.
        return head->getData();
    }

    // Return the back of the list
    T& back() {
        // Return the data of the tail, which is the back of the list.
        return tail->getData();
    }

    // Return the back of the list
    const T& back() const {
        // Return the data of the tail, which is the back of the list.
        return tail->getData();
    }

    // Put data in a new node as the new tail
    void pushBack(T data) {
        Node<T>* t = new Node<T>(data);

        // Update size
        ++sizeV;

        // If tail is null then update the head
        if(tail == nullptr) {
            head = t;
        } else {
            // Set the next and previous
            t->setNext(tail);
            tail->setPrevious(t);
        }

        // Update the tail
        tail = t;
    }

    // Pop front
    void popFront() {
        Node<T>* temp = head;

        // If head is null, nothing to do
        if(head == nullptr) {
            return;
        } else if(head == tail) {
            // Set the head and the tail to null.
            // We need to do it because a part of the
            // implementation depends on it.
            head = nullptr;
            tail = nullptr;
        } else {
            // Else set the previous element.
            head = temp->getPrevious();
            temp->setPrevious(nullptr);
        }

        // Delete the node.
        delete temp;

        // Update the size as we have deleted an element.
        --sizeV;
    }

    // Delete the last element, which is the first that was added.
    void popBack() {
        Node<T>* temp = head;

        // If tail is null, there is nothing to do.
        if(tail == nullptr) {
            return;
        } else if(head == tail) {
            // Set the head and the tail to null.
            // We need to do it because a part of the
            // implementation depends on it.
            head = nullptr;
            tail = nullptr;
        } else {
            // Update the tail
            tail = temp->getNext();
            temp->setNext(nullptr);
        }

        // Delete the node that was removed.
        delete temp;

        // Update the size.
        --sizeV;
    }

    // Return the size of the list.
    unsigned long long size() {
        return sizeV;
    }

    // Returns wether the list is empty or not.
    bool empty() const noexcept {
        // Simply compare the size to zero.
        return sizeV == 0;
    }
};

} /* namespace ostl */
#endif /* list_hpp */
