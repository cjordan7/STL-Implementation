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

#include <vector>

namespace ostl {

// TODO: Refactor
template <class K>
struct TrivialHash {
    #define hash reinterpret_cast<unsigned long>
    unsigned long operator()(const K &key) const {
        return hash(key);
    }
};

template<class K,
         class V,
         class tableSize = 10000,
         class HashFunction = TrivialHash<K>,
         class KeyEqual = std::equal_to<K>>
class UnorderedMap {
private:
    class Bucket {
    private:
        K key;
        V value;
        // next bucket with the same key
        Bucket* next;

        Bucket(const Bucket&);
        Bucket & operator=(const Bucket&);

    public:
        Bucket(const K& key, const V& value): key(key), value(value), next(nullptr) {
        }

        K getKey() const {
            return key;
        }

        V getValue() const {
            return value;
        }

        void setValue(V value) {
            this->value = value;
        }

        Bucket* getNext() const {
            return next;
        }

        void setNext(Bucket* next) {
            this->next = next;
        }
    };

private:
    UnorderedMap(const UnorderedMap& unorderedMap);

    // TODO Implement the operators
    // unordered_map& operator=(const unordered_map& other);
    // unordered_map& operator=(unordered_map&& other);
    const UnorderedMap& operator=(const UnorderedMap& unorderedMap);
    // hash table
    Bucket* table[tableSize];
    HashFunction hashFunction;

    KeyEqual keyEqual;
public:

    UnorderedMap(): table(), hashFunction() {
    }

    ~UnorderedMap() {
        clear();
    }

    void clear() noexcept {
        for(std::size_t i = 0; i < size; ++i) {
            Bucket* bucket = table[i];

            while(bucket != nullptr) {
                Bucket* previous = bucket;
                bucket = bucket->getNext();
                delete previous;
            }

            table[i] = nullptr;
        }
    }

    bool get(const K& key, V& value) {
        unsigned long hashValue = hashFunction(key) % size;
        Bucket* current = table[hashValue];

        while(current != nullptr) {
            if(keyEqual(current->getKey(), key)) {
                value = current->getValue();
                return true;
            }

            current = current->getNext();
        }

        return false;
    }


    void insert(const K& key, const V& value) {
        unsigned long hashValue = hashFunction(key) % size;
        Bucket* previous = nullptr;
        Bucket* current = table[hashValue];

        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }

        if(current == nullptr) {
            current = new Bucket(key, value);

            if(previous == nullptr) {
                table[hashValue] = current;
            } else {
                previous->setNext(current);
            }
        } else {
            current->setValue(value);
        }
    }

    V& atSecond(K& key) {
        unsigned long hashValue = hashFunction(key) % size;
        Bucket* previous = nullptr;
        Bucket* current = table[hashValue];

        while(current != nullptr and !keyEqual(current->getKey(), key)) {
            previous = current;
            current = current->getNext();
        }

        return current->getValue();
    }

    V& operator[](K& key) {
        return atSecond(key);
    }

    V& at(K& key) {
        try {
            return atSecond(key);
        } catch(std::exception& e) {
            throw std::out_of_range("Out of bounds");
        }
    }

    const V& at(K& key) const {
        try {
            return atSecond(key);
        } catch(std::exception& e) {
            throw std::out_of_range("Out of bounds");
        }
    }

    void remove(const K& key) {
        unsigned long hashValue = hashFunction(key) % size;
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

            delete current;
        }
    }
};

} /* namespace ostl */
#endif /* map_hpp */
