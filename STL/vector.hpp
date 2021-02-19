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
    typedef T* Iterator;

private:
    T* ts;
    unsigned long long sizeV;
    unsigned long long memorySize;

public:

    Vector() {
        createNewVector();
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

    Vector<T>& operator=(const Vector<T>& rhs) {
        sizeV = rhs.sizeV;
        memorySize = rhs.memorySize;

        delete ts;

        ts = new T[memorySize];

        for(int i = 0; i < sizeV; ++i) {
            ts[i] = rhs[i];
        }

        return *this;
    }

    Vector<T>& operator=(Vector<T>&& vector) {
        *this = vector;
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

    const T& operator[](int i) const {
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

    void clear() noexcept {
        delete ts;

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

} /* namespace ostl */
#endif /* vector_hpp */
