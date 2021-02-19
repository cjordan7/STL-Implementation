//
//  Stack.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include "vector.hpp"

namespace ostl {

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

} /* namespace ostl */
#endif /* stack_hpp */
