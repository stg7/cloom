/**
    c++ header only counting bloom filter implementation

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

#ifndef CLOOM_HEADER_HPP_
#define CLOOM_HEADER_HPP_
#include <iostream>
#include <functional>
#include <vector>

#include "primes.hpp"

#define DEBUG 1

template<typename T>
class Cloom {
 private:
    std::hash<T> _hash_function;
    size_t _filter_size;
    std::vector<short> _counts;

 public:
    Cloom(): Cloom(100) {}

    /**
        \param filter_size size of the used filter
    **/
    Cloom(size_t filter_size): _filter_size(filter_size) {
        _filter_size = utils::primes::larger_prime(filter_size);
#ifdef DEBUG
        std::cout << "create filter: filter_size: " << _filter_size << std::endl;
#endif
        _hash_function = std::hash<T>{};
        _counts.reserve(_filter_size);
    }
    void insert(const T element) {
        std::size_t hash_value = _hash_function(element) % _filter_size;

#ifdef DEBUG
        std::cout << "insert element " << element << std::endl;
        std::cout << "hash value: " << hash_value << std::endl;
#endif
        for(int k = 0; k < 3; k++) {
            std::size_t position = hash_value;
            _counts[position] ++;
            hash_value *=2;
            hash_value += k;
            hash_value %= _filter_size;
        }
    }
    const bool has(const T element) {
#ifdef DEBUG
        std::cout << "has element " << element << std::endl;
#endif
        return true;
    }
};

#endif