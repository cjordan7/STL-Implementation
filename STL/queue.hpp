//
//  queue.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include "deque.hpp"

namespace ostl {

template<class T>
class Queue {
private:
    Deque<T> deque;
public:
    Queue() {
        deque = Deque<T>();
    }

    Queue(Queue<T> const& queue) {
        deque = queue.deque;
    }

    unsigned long long size() const {
        return deque.size();
    }

    bool empty() const {
        return deque.empty();
    }

    T& front() {
        return deque.front();
    }

    const T& front() const {
        return deque.front();
    }

    T& back() {
        return deque.back();
    }

    const T& back() const {
        return deque.back();
    }

    void push(const T& t) {
        deque.pushBack(t);
    }

    void push(T&& t) {
        deque.pushBack(t);
    }

    void pop() {
        deque.popFront();
    }

    void swap(Queue& queue) noexcept {
        deque.swap(queue.deque);
    }

};


} /* namespace ostl */
#endif /* queue_hpp */
