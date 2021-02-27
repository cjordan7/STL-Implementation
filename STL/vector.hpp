//
//  Vector.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

namespace ostl {

template<class T>
class Vector {
public:
    // The iterator is a pointer to the element of the c-array
    typedef T* Iterator;

private:
    T* ts = nullptr;

    // Actual size in memory
    unsigned long long sizeV = 0;

    // Full size of memory
    unsigned long long memorySize = 0;

public:

    Vector() {
        createNewVector();
    }

    Vector(size_t size) {
        ts = new T[size];
        this->sizeV = size;
        memorySize = size;

        // Initialize to zero
        for(int i = 0; i < size; ++i) {
            this->ts[i] = 0;
        }
    }

    Vector(T ts[], size_t size) {
        this->ts = new T[size];

        this->sizeV = size;
        memorySize = size;

        // Copy c-array
        for(int i = 0; i < size; ++i) {
            this->ts[i] = ts[i];
        }
    }

    Vector(Vector<T>& t): Vector(t.ts, t.size()) {
    }

    ~Vector() {
        delete ts;
    }

    Vector<T>& operator=(const Vector<T>& rhs) {
        // Copy variables
        sizeV = rhs.sizeV;
        memorySize = rhs.memorySize;

        delete ts;

        ts = new T[memorySize];

        // Copy array
        for(int i = 0; i < sizeV; ++i) {
            ts[i] = rhs[i];
        }

        return *this;
    }

    Vector<T>& operator=(Vector<T>&& vector) {
        sizeV = vector.sizeV;
        memorySize = vector.memorySize;

        delete ts;

        ts = new T[memorySize];

        for(int i = 0; i < sizeV; ++i) {
            ts[i] = vector[i];
        }

        return *this;
    }

    Vector<T>& operator=(std::initializer_list<T> il) {
        sizeV = il.size();
        memorySize = sizeV;

        delete ts;

        ts = new T[memorySize];

        for(int i = 0; i < sizeV; ++i) {
            ts[i] = il[i];
        }

        return *this;
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
        testOutOfBounds(i);
        return ts[i];
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
        return ts;
    }

    void swap(Vector& vector) {
        T* temp = vector.ts;
        unsigned long long sizeVTemp = vector.sizeV;
        unsigned long long memorySizeTemp = vector.memorySize;

        vector.ts = ts;
        vector.sizeV = sizeV;
        vector.memorySize = memorySize;

        ts = temp;
        sizeV = sizeVTemp;
        memorySize = memorySizeTemp;
    }

    T& back() {
        return ts[sizeV-1];
    }

    const T& back() const {
        return back();
    }

    T& operator[](int i) {
        return ts[i];
    }

    const T& operator[](int i) const {
        return ts[i];
    }

    void pushBack(T&& t) {
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

    bool empty() const noexcept {
        return sizeV == 0;
    }

    unsigned long long size() const {
        return sizeV;
    }

    unsigned long long capacity() const {
        return memorySize;
    }

    Iterator insert(const Iterator position, const T& t) {
        reallocOnTest(sizeV++);

        for(Iterator i = end(); i != position; --i) {
            *(i+1) = *i;
        }

        *position = t;

        return position;
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

        ++previous;
        return previous;
    }

    Iterator erase(const Iterator first, const Iterator last) {
        unsigned long long size = 0;
        for(Iterator i = first; i != last; ++i) {
            ++size;
        }

        T* newTs = new T[memorySize];
        Iterator newIt = newTs;

        // Set the elements before the iterator first
        for(Iterator i = begin(); i != first; ++i, ++newIt) {
            *newIt = *i;
        }

        // What we return
        Iterator point = newIt;

        // Set the elements after the iterator last
        for(Iterator i = last; i != end(); ++i, ++newIt) {
            *newIt = *i;
        }

        // Reset ts
        delete ts;
        ts = newTs;

        // New size, we have deleted size elements
        this->sizeV = this->sizeV - size;

        return point;
    }

    void clear() noexcept {
        delete ts;
        ts = nullptr;

        createNewVector();
    }

private:
    void createNewVector() {
        sizeV = 0;
        memorySize = 1;

        ts = new T[memorySize];
    }

    void realloc(unsigned long long size) {
        T* tsNew = new T[size];

        unsigned long long smallest = size < sizeV ? size: sizeV;

        for(int i = 0; i < smallest; ++i) {
            tsNew[i] = ts[i];
        }

        delete ts;

        ts = tsNew;
    }

    void reallocOnTest(unsigned long long size) {
        if(sizeV == size) {
            size *= 2;

            realloc(size);
        }
    }

    void testOutOfBounds(unsigned long long i) {
        if(i >= sizeV) {
            throw std::out_of_range("Out of bounds");
        }
    }
};

} /* namespace ostl */
#endif /* vector_hpp */
