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
#include <memory>

// TODO: Potentially change references (&) to rvalue references (&&)
// TODO: Delete prints

// TODO: Check that every functions are in sync with C++11
// TODO: Change the way I initialize paramaeters in the constructor

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

} /* namespace ostl */

#endif /* stl_hpp */
