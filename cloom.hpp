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
#include <fstream>
#include <vector>

#include "primes.hpp"

//#define DEBUG 1

template<typename T>
class Cloom {
 private:
    std::hash<T> _hash_function;
    size_t _filter_size;
    std::vector<short> _counts;
    int _hash_iterations;

    /**
        calculate initial hash value
    **/
    inline std::size_t _get_hash_value(T element) {
        std::size_t hash_value = _hash_function(element) % _filter_size;
        return hash_value;
    }

 public:
    Cloom(): Cloom(101) {}

    /**
        \param filter_size size of the used filter,
            next larger prime number will be used
    **/
    Cloom(size_t filter_size): _filter_size(filter_size) {
        _filter_size = utils::primes::larger_prime(filter_size);
#ifdef DEBUG
        std::cout << "create filter: filter_size: " << _filter_size << std::endl;
#endif
        _hash_function = std::hash<T>{};
        _counts.reserve(_filter_size);
        _hash_iterations = 3;
    }


    void insert(const T element) {
        std::size_t hash_value = _get_hash_value(element);
#ifdef DEBUG
        std::cout << "insert element " << element << std::endl;
        std::cout << "hash value: " << hash_value << std::endl;
#endif
        for(int k = 0; k < _hash_iterations; k++) {
            std::size_t position = hash_value;
            _counts[position] ++;
            hash_value *=2;
            hash_value += k;
            hash_value %= _filter_size;
        }
    }

    void remove(const T element) {
        if (!has(element)) {
            return;
        }
        std::size_t hash_value = _get_hash_value(element);

        for(int k = 0; k < _hash_iterations; k++) {
            std::size_t position = hash_value;
            if (_counts[position] > 0) {
                _counts[position] --;
            }
            hash_value *=2;
            hash_value += k;
            hash_value %= _filter_size;
        }
    }

    const bool has(const T element) {
#ifdef DEBUG
        std::cout << "has element " << element << std::endl;
#endif
        std::size_t hash_value = _get_hash_value(element);
        int checks = 0;
        // generate some hash values
        for(int k = 0; k < _hash_iterations; k++) {
            std::size_t position = hash_value;
            if (_counts[position] > 0) {
                checks ++;
            }
            hash_value *= 2;
            hash_value += k;
            hash_value %= _filter_size;
        }

        // element is stored if for each hash a count was registered
        return checks == _hash_iterations;
    }

    // FIXME: better use MMFiles for storage,
    //        however this approach also works under windows

    /**
        store bloom filter to disk
    **/
    void store(const auto filename) {
        std::ofstream file;
        file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
        file << _filter_size;
        file << _hash_iterations;
        for(size_t i = 0; i < _filter_size; i++) {
            file << _counts[i];
        }
        file.close();
    }

    /**
        load bloom filter from disk
    **/
    void load(const std::string filename) {
        std::ifstream file;
        file.open(filename, std::ios::in | std::ios::trunc | std::ios::binary);
        file >> _filter_size;
        file >> _hash_iterations;
        _counts.reserve(_filter_size);
        for(size_t i = 0; i < _filter_size; i++) {
            file >> _counts[i];
        }
        file.close();
    }
};

#endif