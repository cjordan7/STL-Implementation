//
//  map.hpp
//  STL
//
//  Created by Cosme Jordan on 19.02.21.
//  Copyright © 2021 Cosme Jordan. All rights reserved.
//

#ifndef map_hpp
#define map_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

#include "tuple.hpp"
#include "list.hpp"

namespace ostl {

template<class K,
class V,
int tableSize = 1000,
class HashFunction = std::hash<K>,
class KeyEqual = std::equal_to<K>
>
class UnorderedMap {
private:
    class Bucket {
    private:
        ostl::Pair<K, V> pair;
        // next bucket with the same key
        Bucket* next = nullptr;
        Bucket* previous = nullptr;

        Bucket(const Bucket&);
        Bucket & operator=(const Bucket&);

    public:
        Bucket(const K& key): next(nullptr) {
            pair.first = key;
        }

        Bucket(const K& key, const V& value): pair(key, value), next(nullptr) {
        }

        K getKey() const {
            return pair.first;
        }

        V& getValue() {
            return pair.second;
        }

        K getKey() {
            return pair.first;
        }

        void setValue(V value) {
            pair.second = value = value;
        }

        Bucket* getNext() const {
            return next;
        }

        Bucket* getPrevious() const {
            return previous;
        }

        void setNext(Bucket* next) {
            this->next = next;
            next->previous = this;
        }

        ostl::Pair<K, V>* getPair() {
            return &pair;
        }

    };

private:

    // hash table
    Bucket* table[tableSize] = {};
    Bucket* bucketFirst = nullptr;
    Bucket* bucketEnd = nullptr;
    unsigned long firstIndex = INFINITY;
    unsigned long lastIndex = 0;

    HashFunction hashFunction;
    int sizeV = 0;
    KeyEqual keyEqual;
public:
    class Iterator {
    private:
        friend class UnorderedMap;
        Bucket* b;
        Bucket** table = nullptr;

        unsigned long long position;

    private:
        void setTable(Bucket** table) {
            this->table = table;
        }

        void setBucket(Bucket* bucket, unsigned long long position) {
            b = bucket;
            pair.first = b->getKey();
            pair.second = b->getValue();
            this->position = position;

        }

        ostl::Pair<K, V> pair;
    public:
        Iterator(): b(nullptr), position(0) {
        }

        Iterator(const Iterator& it): pair(it.pair), b(it.b), position(it.position), table(it.table) {
        }

        ~Iterator() {
        }

        Iterator& operator=(const Iterator& it) {
            b = it.b;
            pair = it.pair;
            table = it.table;
            position = it.position;
            return *this;
        }

        bool operator==(const Iterator& rhs){
            return b == rhs.b;
        }

        bool operator!=(const Iterator& rhs){
            return !(*this==rhs);
        }

        ostl::Pair<K, V>* operator->() {
            return &pair;
        }

        Iterator& operator++() {
            Bucket* nextBucket = b->getNext();
            ++position;
            while(nextBucket == nullptr and position < tableSize) {
                // TODO: Bug
                nextBucket = table[position];
                ++position;
            }

            if(nextBucket == nullptr) {
                b = nullptr;
                return *this;
            }

            b = nextBucket;
            pair.first = b->getPair()->first;
            pair.second = b->getPair()->second;
            return *this;
        }

        Iterator& operator--() {
            Bucket* nextBucket = b->getPrevious();
            while(nextBucket == nullptr and position >= 0) {
                nextBucket = table[--position];
            }

            b = nextBucket;
            return *this;
        }

        Iterator operator+=(const int& right) {
            return this->operator+(right);
        }

        Iterator operator+(const int& right) {
            Iterator it = Iterator(*this);
            int temp = right;
            if(temp > 0) {
                --temp;
                ++it;
            } else {
                ++temp;
                --it;
            }

            return it;
        }

        const ostl::Pair<K, V>& operator*() {
            return pair;
        }
    };


    UnorderedMap() {
        // TODO: Implement
    }

    UnorderedMap(std::initializer_list<ostl::Pair<K, V>> il) {
        setUsingIL(il);
    }

    ~UnorderedMap() {
        clear();
    }

private:
    void setThis(const UnorderedMap& x) {
        table = x.table;

        bucketFirst = x.bucketFirst;
        bucketEnd = x.bucketEnd;
        firstIndex = x.firstIndex;
        lastIndex = x.lastIndex;

        hashFunction = x.hashFunction;
        sizeV = x.sizeV;
        keyEqual = x.keyEqual;
    }

public:
    UnorderedMap& operator=(const UnorderedMap& x) {
        setThis(x);
        return *this;
    }

    UnorderedMap& operator=(UnorderedMap&& x) {
        setThis(x);
        return *this;
    }

private:
void setUsingIL(std::initializer_list<ostl::Pair<K, V>> il) {
    for(auto it = il.begin(); it != il.end(); ++it) {
        this->operator[]((*it).first) = (*it).second;
    }
}

public:
    UnorderedMap& operator=(std::initializer_list<ostl::Pair<K, V>> il) {
        setUsingIL(il);
        return *this;
    }

    void clear() noexcept {
        for(std::size_t i = 0; i < tableSize; ++i) {
            Bucket* bucket = table[i];

            while(bucket != nullptr) {
                Bucket* previous = bucket;
                bucket = bucket->getNext();
                delete previous;
            }

            table[i] = nullptr;
        }
    }

    const Iterator cbegin() const noexcept {
        return begin();
    }

    const Iterator cend() const noexcept {
        return end();
    }

    Iterator begin() {
        Iterator it;
        it.setTable(table);
        it.setBucket(bucketFirst, firstIndex);
        return it;
    }

    const Iterator begin() const {
        return begin();
    }

    Iterator end() {
        Iterator it;

        it.setTable(table);
        it.setBucket(bucketEnd, lastIndex);
        ++it;
        return it;
    }

    const Iterator end() const {
        return end();
    }

    bool get(const K& key, V& value) {
        unsigned long hashValue = hashFunction(key) % tableSize;
        Bucket* current = table[hashValue];

        while(current != nullptr) {
            if(keyEqual(current->getKey(), key)) {
                value = current->getValue();
                ++sizeV;
                return true;
            }

            current = current->getNext();
        }

        return false;
    }

    V& at(const K& key) {
        unsigned long hashValue = hashFunction(key) % tableSize;
        Bucket* previous = nullptr;
        Bucket* current = table[hashValue];
        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }

        return current->getValue();
    }

    Iterator erase(const Iterator position) {
        Iterator next = Iterator(position);
        if(next == begin()) {
            Iterator e = begin();
            ++e;
            bucketFirst = e.b;
            firstIndex = e.position;
        } else if(next == end()) {
            Iterator e = end();
            --e;
            bucketEnd = e.b;
            lastIndex = e.position;
        }

        next += 1;
        remove(position.b->getKey());
        return next;
    }

    V& operator[](const K& k) {
        return insert(k);
        //        return at(k);
    }

    V& operator[](K&& k) {
        return insert(k);
        //        return at(k);
    }

    const V& at(const K& key) const {
        try {
            return atSecond(key);
        } catch(std::exception& e) {
            throw std::out_of_range("Out of bounds");
        }
    }

    bool empty() const {
        return sizeV == 0;
    }

    void remove(const K& key) {
        unsigned long hashValue = hashFunction(key) % tableSize;
        Bucket* previous = nullptr;
        Bucket* current = table[hashValue];
        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }
        if(current == nullptr) {
            return;
        } else {
            if(previous == nullptr) {
                table[hashValue] = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
            --sizeV;
            delete current;
        }
    }

    unsigned long long size() {
        return sizeV;
    }

private:
    V& insert(const K& key) {
        unsigned long hashValue = hashFunction(key) % tableSize;
        Bucket* previous = nullptr;
        Bucket* current = table[hashValue];
        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }

        if(current == nullptr) {
            current = new Bucket(key);
            if(previous == nullptr) {
                table[hashValue] = current;
                ++sizeV;

                if(hashValue < firstIndex) {
                    firstIndex = hashValue;
                    bucketFirst = current;
                }

                if(hashValue > lastIndex) {
                    lastIndex = hashValue;
                    bucketEnd = current;
                }
            } else {
                previous->setNext(current);
            }
        }
        return current->getPair()->second;
    }
};

} /* namespace ostl */
#endif /* map_hpp */
