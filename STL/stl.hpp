//
//  stl.hpp
//  STL
//
//  Created by Cosme Jordan on 26.08.20.
//  Copyright © 2020 Cosme Jordan. All rights reserved.
//

#ifndef stl_hpp
#define stl_hpp

#include <stdio.h>

#include <iostream>

// TODO: Potentially change references (&) to rvalue references (&&)
// TODO: Refactor stack class to use vector
// TODO: Delete prints

namespace ostl {
template<int x, class T>
struct PairStorage {
    T data;
    
    PairStorage(T t) {
        this->data = t;
    }
};

template<int N, class T>
T& get(PairStorage<N, T>& pairStorage) {
    return pairStorage.data;
}

template<int N, class T>
T const& get(PairStorage<N, T> const& pairStorage) {
    return pairStorage.data;
}

//template<int N, class T>
//T const& get(PairStorage<N, T> const& pairStorage) {
//    return pairStorage.data;
//}

template<class T1, class T2>
struct Pair: PairStorage<0, T1>, PairStorage<1, T2> {
    T1 first;
    T2 second;
    
    Pair() {
    }
    
    Pair(T1 t1, T2 t2): PairStorage<0, T1>(t1), PairStorage<1, T2>(t2) {
        first = t1;
        second = t2;
    }
    
    Pair(const Pair<T1, T2>& p): PairStorage<0, T1>(p.first), PairStorage<1, T2>(p.second) {
        first = p.first;
        second = p.second;
    }
    
    Pair operator=(const Pair<T1,T2> & pair) {
        first = pair.first;
        second = pair.second;
        return *this;
    }
    
    bool operator==(const Pair<T1,T2>& pair) {
        return first == pair.first and second == pair.second;
    }
    
    bool operator!=(const Pair<T1,T2>& pair) {
        return !(*this==pair);
    }
    
    bool operator<(const Pair<T1,T2>& pair) {
        return first < pair.first and second < pair.second;
    }
    bool operator<=(const Pair<T1,T2>& pair) {
        return first <= pair.first and second <= pair.second;
    }
    
    bool operator>(const Pair<T1,T2>& pair) {
        return first > pair.first and second > pair.second;
    }
    
    bool operator>=(const Pair<T1,T2>& pair) {
        return first >= pair.first and second >= pair.second;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Pair<T1, T2>& pair) {
        os << '(' << pair.first << ", "<< pair.second << ')';
        return os;
    }

    Pair swap(Pair<T1, T2>& pair) {
        T1 tempFirst = first;
        T2 tempSecond = second;
        
        first = pair.first;
        second = pair.second;
        
        first = tempFirst;
        second = tempSecond;
        
        *this;
    }
};

template<class T1, class T2>
void swap(Pair<T1, T2>& pairOne, Pair<T1, T2>& pairTwo) {
    T1 tempFirst = pairOne.first;
    T2 tempSecond = pairOne.second;
    
    pairOne.first = pairTwo.first;
    pairOne.second = pairTwo.second;
    
    pairTwo.first = tempFirst;
    pairTwo.second = tempSecond;
}

template<class T, class A = std::allocator<T>>
class Vector {
public:
    typedef T* Iterator;

private:
    T* ts;
    A allocator;
    unsigned long long sizeV;
    unsigned long long memorySize;

public:

    Vector() {
        ts = new T[1];
        sizeV = 0;
        memorySize = 1;
    }
    
    Vector(size_t size) {
        ts = new T[size];
        this->sizeV = size;
        memorySize = size;
    }
    
    Vector(T ts[]) {
        size_t size = sizeof(ts);
        this->ts = new T[size];
        
        this->sizeV = size;
        memorySize = size;
        
        for(int i = 0; i < size; ++i) {
            this->ts = ts[i];
        }
    }
    
    Vector(Vector<T>& t) {
        this->Vector(t.ts);
    }
    
    ~Vector() {
        delete ts;
    }
    
    void reserve(size_t memorySize) {
        ts = new T[memorySize];
        sizeV = 0;
        this->memorySize = memorySize;
    }

    void resize(unsigned long long n) {
        realloc(n);

        memorySize = n;
    }

    void shrinkToFit() {
        if(memorySize > sizeV) {
            realloc(sizeV);
        }
        memorySize = sizeV;
    }

    T& at(unsigned long long i) {
        testOutOfBounds(i);
        return ts[i];
    }

    const T& at(unsigned long long i) const {
        //testOutOfBounds(i);
        return at(i);
    }

    T& front() {
        return ts[0];
    }

    const T& front() const {
        return front();
    }

    T* data() noexcept {
        return ts;
    }

    const T* data() const noexcept {
        return data();
    }

    void swap(Vector& vector) {
        T* temp = vector.ts;
        unsigned long long sizeVTemp = vector.sizeV;
        unsigned long long memorySizeTemp = vector.memorySize;

        vector.ts = ts;
        vector.sizeV = sizeV;
        vector.memorySize = memorySize;

        sizeV = sizeVTemp;
        memorySize = memorySizeTemp;
    }

    T& back() {
        return ts[sizeV];
    }

    const T& back() const {
        return back();
    }

    T& operator[](int i) {
        return ts[i];
    }

    void pushBack(T t) {
        reallocOnTest(memorySize);

        ts[sizeV++] = t;
    }

    void pushBack(const T& t) {
        reallocOnTest(memorySize);

        ts[sizeV++] = t;
    }

    void popBack() {
        if(sizeV > 0) {
            --sizeV;
        }
    }

    bool empty() {
        return sizeV == 0;
    }

    unsigned long long size() {
        return sizeV;
    }

    unsigned long long capacity() {
        return memorySize;
    }

    Iterator begin() {
        return ts;
    }

    Iterator end() {
        return ts+sizeV;
    }

    Iterator erase(const Iterator position) {
        Iterator previous = position-1;
        for(Iterator i = position+1; i != end(); ++i) {
            *(i-1) = *i;
        }
        --sizeV;

        // TODO: Check that using the documentation
        ++previous;
        return previous;
    }

    Iterator erase(const Iterator first, const Iterator last) {
        unsigned long long size = 0;
        Iterator previous = first-1;
        for(Iterator i = first; i != last; ++i) {
            ++size;
        }

        T* newTs = new T[sizeV-size];

        Iterator newIt = newTs;

        for(Iterator i = begin(); i != first; ++i, ++newIt) {
            *newIt = *i;
        }

        newIt = last;

        for(Iterator i = last; i != end(); ++i, ++newIt) {
            *newIt = *i;
        }

        delete ts;

        ts = newTs;

        // TODO: Check that using the documentation
        return ++previous;
    }

private:
    void realloc(unsigned long long size) {
        T* tsNew = new T[size];

        unsigned long long smallest = size < sizeV ? size: sizeV;

        for(int i = 0; i < smallest; ++i) {
            tsNew[i] = ts[i];
        }

        // FIXME TODO Check if ts null
        delete ts;

        ts = tsNew;
    }

    // FIXME: REFACTOR THAT
    void reallocOnTest(unsigned long long size) {
        if(sizeV == size) {
            size *= 2;

            realloc(size);
        }
    }

    void testOutOfBounds(unsigned long long i) {
        if(i > sizeV) {
            throw std::out_of_range("Out of bounds");
        }
    }

};

template<size_t I, class T>
struct TupleStorageUnique {
public:
    T data;
    TupleStorageUnique(T t) {
        this->data = t;
    }
    
    T get();
};

template<int N, class T>
T& get(TupleStorageUnique<N, T>& tupleStorageUnique) {
    return tupleStorageUnique.data;
}

template<int N, class T>
T const& get(TupleStorageUnique<N, T> const& tupleStorage) {
    return tupleStorage.data;
}

template<size_t I, class T, class... Ts>
class TupleStorage: public TupleStorageUnique<I+1, T>, public TupleStorage<I+1, Ts...>  {
public:
    T data;
    TupleStorage(T t): TupleStorageUnique<I+1, T>(t) {

    }

    TupleStorage(T t, Ts... ts): TupleStorageUnique<I+1, T>(t), TupleStorage<I+1, Ts...>(ts...) {
        this->data = t;
    }
};

template<size_t I, class T1, class T2>
class TupleStorage<I, T1, T2>: public TupleStorageUnique<I+1, T1>, public TupleStorageUnique<I+2, T2> {
public:
    TupleStorage(T1 t1, T2 t2): TupleStorageUnique<I+1, T1>(t1), TupleStorageUnique<I+2, T2>(t2) {

    }
};

template<class... Ts>
class Tuple: public TupleStorage<0, Ts...>  {
public:
    Tuple(Ts... ts): TupleStorage<0, Ts...>(ts...) {
        std::cout << "Ctor 2" << std::endl;
    }
    
    ~Tuple() {
    }
};

template<class T>
class Tuple<T>: public TupleStorageUnique<0, T> {
public:
    Tuple(T t): TupleStorageUnique<0, T>(t) {
        std::cout << "Ctor 1" << std::endl;
    }
};

template<class T1, class T2>
class Map {
public:

};

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

    }

    ~List() {

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

};

template<class T>
class CircularLinkedList { // just for the fun of implementing it
private:
    Node<T>* head;
    Node<T>* tail;
public:
    CircularLinkedList() {

    }
    
    CircularLinkedList(CircularLinkedList<T> const& CircularlinkedList) {

    }
};

template<class T>
class Stack {
private:
    Vector<T> vector;

public:
    Stack() {
        vector = Vector<T>();
    }
    
    Stack(Stack<T> const& stack) {
        vector = stack.vector;
    }

    Stack(size_t size) {
        vector = Vector<T>(size);
    }

    ~Stack() {
    }

    bool empty() const {
        return vector.empty();
    }

    
    void push(T& t) {
        vector.pushBack(t);
    }

    void push(const T& t) {
        vector.pushBack(t);
    }

    T& top() {
        return vector[vector.size()-1];
    }

    const T& top() const {
        return vector[vector.size()-1];
    }

    void pop() {
        vector.popBack();
    }

    unsigned long long size() {
        return vector.size();
    }

    void swap(Stack& stack) noexcept {
        vector.swap(stack.vector);
    }
};


template<class T>
class StackLinkedList {
private:
public:
    
};


template<class T>
class Queue {
public:
    Queue() {

    }
    
    Queue(Queue<T> const& queue) {

    }
};

template<class T>
class Dequeue {
public:
    Dequeue() {
    }
    
    Dequeue(Dequeue<T> const& dequeue) {

    }
};

}

#endif /* stl_hpp */
