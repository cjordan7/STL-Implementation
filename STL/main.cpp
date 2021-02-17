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
    ostl::Tuple<int, std::string, int, int, int> t11(1, "Hi", 3, 5, 7);

    std::cout << ostl::get<1>(t11) << std::endl;
    std::cout << ostl::get<2>(t11) << std::endl;
    std::cout << ostl::get<3>(t11) << std::endl;
    std::cout << ostl::get<4>(t11) << std::endl;
    std::cout << ostl::get<5>(t11) << std::endl;

    ostl::Tuple<int> d(1);
    std::cout << "Hello, World!\n";
    return 0;
}
