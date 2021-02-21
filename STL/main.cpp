//
//  main.cpp
//  STL
//
//  Created by Cosme Jordan on 26.08.20.
//  Copyright © 2020 Cosme Jordan. All rights reserved.
//

#include <iostream>
#include <utility>
#include <vector>
#include <string>

// TODO: Potentially change references (&) to rvalue references (&&)
// TODO: Delete prints

// TODO: Check that every functions are in sync with C++11
// TODO: Change the way I initialize paramaeters in the constructor

#include "tuple.hpp"
#include "vector.hpp"

template<class T>
void printVector(const ostl::Vector<T>& vector) {
    for(int i = 0; i < vector.size(); ++i) {
        std::cout << vector[i] << " ";
    }

    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    return 0;
}
