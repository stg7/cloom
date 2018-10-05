/**
    c++ bloom filter implementation,
    example file

    \author Steve Göring
    \contact stg7@gmx.de

    \date 06.10.2018
**/
/**
    This file is part of cloom.

    cloom is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cloom is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cloom.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include <string>

#include "cloom.hpp"

void int_example() {
    Cloom<int> cloom;
    cloom.insert(123);
    cloom.has(123);

    auto test_int = 123;
    if (cloom.has(test_int)) {
        std::cout << test_int << " in filter" << std::endl;
    } else {
        std::cout << test_int << " NOT in filter" << std::endl;
    }

    test_int = 321;
    if (cloom.has(test_int)) {
        std::cout << test_int << " in filter" << std::endl;
    } else {
        std::cout << test_int << " NOT in filter" << std::endl;
    }

}

void str_example() {
    Cloom<std::string> cloom_str;
    cloom_str.insert(std::string("hello"));

    auto test_str = std::string("hello");
    if (cloom_str.has(test_str)) {
        std::cout << test_str << " in filter" << std::endl;
    } else {
        std::cout << test_str << " NOT in filter" << std::endl;
    }

    test_str = std::string("holla");
    if (cloom_str.has(test_str)) {
        std::cout << test_str << " in filter" << std::endl;
    } else {
        std::cout << test_str << " NOT in filter" << std::endl;
    }
}

/**
    cloom example usage
**/
int main(int argc, const char* argv[]) {
    std::cout << "example cloom usage" << std::endl;

    int_example();
    str_example();

    return 0;
}
