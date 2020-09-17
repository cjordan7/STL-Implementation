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
    class Iterator {
    private:
        T* current;
    
    public:
        T* begin();
        T* end();
    };
    
private:
    T* ts;
    A allocator;
    unsigned long long size;
    unsigned long long memorySize;

public:

    Vector() {
        ts = new T[1];
        size = 0;
        memorySize = 1;
    }
    
    Vector(size_t size) {
        ts = new T[size];
        this->size = size;
        memorySize = size;
    }
    
    Vector(T ts[]) {
        size_t size = sizeof(ts);
        this->ts = new T[size];
        
        this->size = size;
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
    
    }
    
    void pushBack(T t) {
        //this->size = size;
        //memorySize = size;
        
        if(size == memorySize) {
            memorySize *= 2;
        }
    }
    
    void pushBack(const T& t) {
    
    }
    
    void popBack(T t) {
    
    }
    
    void popBack(const T& t) {
    
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
class TupleStorage: public TupleStorageUnique<I+1, T>, public TupleStorage<I+2, Ts...>  {
public:
    T data;
    TupleStorage(T t): TupleStorageUnique<I + 1, T>(t) {

    }

    TupleStorage(T t, Ts... ts): TupleStorage<I+2, Ts...>(ts...),
     TupleStorage<I+1, T>(ts...) {
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
class Tuple: TupleStorage<0, Ts...>  {
public:
    Tuple(Ts... ts): TupleStorage<0, Ts...>(ts...) {
        std::cout << "Ctor 2" << std::endl;
        //Tuple(ts...);
    }
    
    ~Tuple() {
    }
};

template<class T>
class Tuple<T>: TupleStorageUnique<0, T> {
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
struct Node {
    T data;
    Node<T>* next;
    Node<T>* previous;
};

template<class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList() {
        //https://www.geeksforgeeks.org/data-structures/linked-list/
        //https://www.codesdope.com/blog/article/c-linked-lists-in-c-singly-linked-list/
    }
    
    LinkedList(LinkedList<T> const& linkedList) {
    
    }
};

template<class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    DoublyLinkedList() {
    
    }
    
    DoublyLinkedList(LinkedList<T> const& linkedList) {
    
    }
};

template<class T>
class CircularLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    CircularLinkedList() {
    
    }
    
    CircularLinkedList(LinkedList<T> const& linkedList) {
    
    }
};

template<class T>
class Stack {
private:
    T* ts;
public:
    T temp;
    Stack() {
    }
    
    Stack(Stack<T> const& stack) {
    
    }
    
//    Stack(Dequeue<T> dequeue) {
//
//    }
//
//    Stack(Queue<T> queue) {
//
//    }
    
    Stack(T* ts) {
    
    }
    
    Stack(Vector<T> vector) {
    
    }
    
    Stack(size_t size) {
    
    }
    
    void push(T t) {
    
    }
    
    T pop() {
        return temp;
    }
    
    T peek() {
        return temp;
    }
    
    T size() {
        return temp;
    }
    
    bool isEmpty() {
        return false;
    }
    
    bool isFull() {
        return false;
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
