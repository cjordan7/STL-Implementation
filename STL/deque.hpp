//
//  deque.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef deque_hpp
#define deque_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include "vector.hpp"
namespace ostl {

template<class T>
class Deque {
// TODO Implement a more efficent Deque
private:
    Vector<T> vector;
public:
    typedef T* Iterator;

    Deque() {
        vector = Vector<T>();
    }

    Deque(size_t size) {
        vector = Vector<T>(size);
    }

    Deque(Deque<T> const& deque) {
        *this = deque;
    }

    Deque<T>& operator=(const Deque& deque) {
        this->vector = deque.vector;

        return *this;
    }

    Deque<T>& operator=(Deque&& deque) {
        this->vector = deque.vector;
        return *this;
    }

    Deque<T>& operator=(std::initializer_list<T> il) {
        this->vector = il;
        return *this;
    }

    Iterator begin() noexcept {
        return vector.begin();
    }

    const Iterator cbegin() const noexcept {
        return vector.at(0);
    }

    Iterator end() noexcept {
        return vector.end();
    }

    const Iterator cend() const noexcept {
        return vector.at(vector.size());
    }

    unsigned long long size() const noexcept {
        return vector.size();
    }

    void resize(unsigned long long size) {
        vector.resize(size);
    }

    T& at(unsigned long long i) {
        return vector.at(i);
    }

    const T& at(unsigned long long i) const {
        return vector.at(i);
    }

    bool empty() const noexcept {
        return vector.empty();
    }

    void shrinkToFit() {
        vector.shrinkToFit();
    }

    T& operator[](int i) {
        return vector[i];
    }

    const T& operator[](int i) const {
        return vector[i];
    }

    T& front() {
        return vector[0];
    }

    const T& front() const {
        return vector[0];
    }

    T& back() {
        return vector[(int)vector.size()-1];
    }

    const T& back() const {
        return vector[vector.size()-1];
    }

    void pushBack(const T& t) {
        vector.pushBack(t);
    }

    void pushBack(T&& t) {
        vector.pushBack(t);
    }

    void pushFront(const T& t) {
        vector.insert(0, t);
    }

    void pushFront(T&& t) {
        vector.insert(vector.begin(), t);
    }

    void popBack() {
        vector.popBack();
    }

    void popFront() {
        vector.erase(vector.begin());
    }

    Iterator insert(const Iterator position, const T& t) {
        vector.insert(position, t);

        //add the other inserts
    }

    Iterator erase(const Iterator position) {
        return vector.erase(position);
    }

    Iterator erase(const Iterator first, const Iterator last) {
        return vector.erase(first, last);
    }

    void swap(Deque& deque) {
        vector.swap(deque.vector);
    }

    void clear() noexcept {
        vector.clea();
    }
};

} /* namespace ostl */
#endif /* deque_hpp */
