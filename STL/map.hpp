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
    // A convenient class for the map
    class Bucket {
    private:
        // The key, value pair the bucket holds.
        ostl::Pair<K, V> pair;

        // next bucket with the same key
        Bucket* next = nullptr;

    public:
        // Create bucket with key
        Bucket(const K& key): next(nullptr) {
            pair.first = key;
        }

        // Create bucket with key and value
        Bucket(const K& key, const V& value): pair(key, value), next(nullptr) {
        }

        // Get the key
        K getKey() const {
            return pair.first;
        }

        // Get the value
        V& getValue() {
            return pair.second;
        }

        // Get the key
        K getKey() {
            return pair.first;
        }

        // Set the value.
        void setValue(V value) {
            pair.second = value = value;
        }

        // Get the next bucket
        Bucket* getNext() const {
            return next;
        }

        // Set the next bucket
        void setNext(Bucket* next) {
            this->next = next;
        }

        // Get the pair key, value
        ostl::Pair<K, V>* getPair() {
            return &pair;
        }

    };

private:

    // The hash table of buckets
    Bucket* table[tableSize] = {};

    // Variables to store the bucket for fast use and their index.
    Bucket* bucketFirst = nullptr;
    Bucket* bucketEnd = nullptr;
    unsigned long firstIndex = INFINITY;
    unsigned long lastIndex = 0;

    // The hash function.

    HashFunction hashFunction;

    // The number of buckets in memory.
    int sizeV = 0;

    // The operator to check equality of keys.
    KeyEqual keyEqual;
public:
    class Iterator {
    private:
        friend class UnorderedMap;
        // The bucket the iterator store, for fast use.
        Bucket* b;

        // Store a pointer to the hash table
        Bucket** table = nullptr;

        // The position in the table where the bucket is.
        unsigned long long position;

    private:
        // Set the table pointer.
        void setTable(Bucket** table) {
            this->table = table;
        }

        // Set the bucket and its position.
        void setBucket(Bucket* bucket, unsigned long long position) {
            b = bucket;

            // Set the first and second element of the pair
            pair.first = b->getKey();
            pair.second = b->getValue();

            // Set the position.
            this->position = position;
        }

        // The pair the bucket stores, for fast use.
        ostl::Pair<K, V> pair;
    public:
        // Default ctor.
        Iterator(): b(nullptr), position(0) {
        }

        // Copy ctor.
        Iterator(const Iterator& it): pair(it.pair), b(it.b), position(it.position), table(it.table) {
        }

        ~Iterator() {
        }

        // Assignment operator
        Iterator& operator=(const Iterator& it) {
            b = it.b;
            pair = it.pair;
            table = it.table;
            position = it.position;
            return *this;
        }

        // Check equality of pointer between two iterators.
        bool operator==(const Iterator& rhs){
            return b == rhs.b;
        }

        // Check inequality of pointer between two iterators.
        bool operator!=(const Iterator& rhs){
            return !(*this==rhs);
        }

        // Get the pair.
        ostl::Pair<K, V>* operator->() {
            return &pair;
        }

        // Get the next bucket
        Iterator& operator++() {
            Bucket* nextBucket = b->getNext();

            while(nextBucket == nullptr and position + 1 < tableSize) {
                nextBucket = table[++position];
            }

            // If next is null then set b to null
            if(nextBucket == nullptr) {
                b = nullptr;
                return *this;
            }

            // Set the values and return this.
            b = nextBucket;
            pair.first = b->getPair()->first;
            pair.second = b->getPair()->second;
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
    }

    // Set the map using an initializer list.
    UnorderedMap(std::initializer_list<ostl::Pair<K, V>> il) {
        setUsingIL(il);
    }

    ~UnorderedMap() {
        // Clear the content of the memory.
        clear();
    }

private:
    // Set the variables of the map using another map.
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
    // Set this with x.
    UnorderedMap& operator=(const UnorderedMap& x) {
        setThis(x);
        return *this;
    }

    // Set this with x.
    UnorderedMap& operator=(UnorderedMap&& x) {
        setThis(x);
        return *this;
    }

private:
    // Set this with a initializer list.
    void setUsingIL(std::initializer_list<ostl::Pair<K, V>> il) {
        for(auto it = il.begin(); it != il.end(); ++it) {
            // Use the already defined operator.
            this->operator[]((*it).first) = (*it).second;
        }
    }

public:
    // Set this with a initializer list.
    UnorderedMap& operator=(std::initializer_list<ostl::Pair<K, V>> il) {
        setUsingIL(il);
        return *this;
    }

    // Clear the memory of the map.
    void clear() noexcept {
        // For each element...
        for(std::size_t i = 0; i < tableSize; ++i) {
            Bucket* bucket = table[i];

            // Clear each bucket list.
            while(bucket != nullptr) {
                Bucket* previous = bucket;
                bucket = bucket->getNext();
                delete previous;
            }

            // Set table[i] to null
            table[i] = nullptr;
        }
    }

    // Return an iterator to the beginning of the map.
    const Iterator cbegin() const noexcept {
        return begin();
    }

    // Return an iterator to the beginning of the map.
    const Iterator cend() const noexcept {
        return end();
    }

    // Return an iterator to the beginning of the map.
    const Iterator begin() const {
        Iterator it;
        it.setTable(table);
        it.setBucket(bucketFirst, firstIndex);
        return it;
    }

    // Return an iterator to the beginning of the map.
    Iterator begin() {
        return begin();
    }

    // Return an iterator to the beginning of the map.
    const Iterator end() const {
        Iterator it;

        it.setTable(table);
        it.setBucket(bucketEnd, lastIndex);
        ++it;
        return it;
    }

    Iterator end() {
        return end();
    }

    // Get element at key
    V& at(const K& key) {
        // Calculate the hash.
        unsigned long hashValue = hashFunction(key) % tableSize;

        Bucket* previous = nullptr;

        // Get element at hash value.
        Bucket* current = table[hashValue];

        // Loop until find the key value
        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }

        // Return it.
        return current->getValue();
    }

    // Delete an element into the bucket list.
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

    // Get element with key k
    V& operator[](const K& k) {
        return insert(k);
    }

    // Get element with key k
    V& operator[](K&& k) {
        return insert(k);
    }

    // Get element at key
    const V& at(const K& key) const {
        // If can't return an exception.
        try {
            return atSecond(key);
        } catch(std::exception& e) {
            throw std::out_of_range("Out of bounds");
        }
    }

    // Returns wether the map is empty or not.
    bool empty() const {
        return sizeV == 0;
    }

    // Remove element at key.
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

    // Return the size.
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
