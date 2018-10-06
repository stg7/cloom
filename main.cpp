/**
    c++ counting bloom filter implementation,
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

template<typename T>
void test_has(T X, Cloom<T>& C) {
    if (C.has(X)) {
        std::cout << X << " in filter" << std::endl;
    } else {
        std::cout << X << " NOT in filter" << std::endl;
    }
}

template<typename T>
void p(T x) {
    std::cout << x << std::endl;
}

void int_example() {
    Cloom<int> cloom;
    p("insert 123");
    cloom.insert(123);

    auto test_int = 123;
    test_has(test_int, cloom);

    p("remove 123");
    cloom.remove(test_int);
    test_has(test_int, cloom);

    test_int = 321;
    test_has(test_int, cloom);

    cloom.remove(test_int);
    test_has(test_int, cloom);

}

void str_example() {
    Cloom<std::string> cloom;
    p("insert hello");
    cloom.insert(std::string("hello"));

    auto test_str = std::string("hello");
    test_has(test_str, cloom);

    p("remove hello");
    cloom.remove(test_str);
    test_has(test_str, cloom);

    test_str = std::string("holla");
    test_has(test_str, cloom);

    cloom.remove(test_str);
    test_has(test_str, cloom);
}

void storage_example() {
    const char* filename = "storage.cloom";
    {
    Cloom<std::string> cl;
    cl.insert(std::string("hello"));
    cl.insert(std::string("world"));

    cl.store(filename);
    }
    {
    Cloom<std::string> cl;
    cl.load(filename);
    cl.insert(std::string("abc"));

    test_has(std::string("hello"), cl);
    test_has(std::string("world"), cl);
    test_has(std::string("abc"), cl);
    }

}

/**
    cloom example usage
**/
int main(int argc, const char* argv[]) {
    std::cout << "example cloom usage" << std::endl;

    int_example();
    str_example();

    storage_example();
    return 0;
}
