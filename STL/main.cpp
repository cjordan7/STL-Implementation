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

#include "stl.hpp"
//#include <tuple>

int main(int argc, const char * argv[]) {
    
    std::vector<int> t;
    
    ostl::Pair<double, double> pair(5.1, 4.2);
    ostl::Pair<double, double> pair2(2.1, 2.2);
    
    //ostl::TupleStorage<2, int, int> hello(1, 2);
    std::cout << ostl::get<0>(pair) << std::endl;
    ostl::get<0>(pair) = 3.4;
    
    // std::cout << pair << std::endl;
    // std::cout << pair2 << std::endl;
    std::cout << ostl::get<0>(pair) << std::endl;
    std::cout << ostl::get<1>(pair) << std::endl;
    //std::tuple<int, int, int> tuple(1, 2, 3);

    ostl::Tuple<int> d(1);
    std::cout << "Hello, World!\n";
    return 0;
}
