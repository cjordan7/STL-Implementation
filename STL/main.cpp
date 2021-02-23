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
#include "stack.hpp"
#include "list.hpp"
#include "deque.hpp"
#include "queue.hpp"

int main(int argc, const char * argv[]) {
    ostl::Tuple<int, std::string> t(42, "My Own STL");

    std::cout << ostl::get<0>(t) << std::endl;
    std::cout << ostl::get<1>(t) << std::endl;
    return 0;
}
