#ifndef PRIMES_H
#define PRIMES_H

#include <algorithm>
#include <cmath>

namespace utils {
    /**
        collection of helper methods for prime numbers
    **/
    namespace primes {
        /**
            check if number is prime
        **/
        inline unsigned long is_prime(unsigned long s) {
            if (s < 2) {
                return false;
            }
            if (s == 2) {
                return true;
            }

            #include "primes.inc" // load primes table
            if (std::binary_search(primes.begin(), primes.end(), s)) {
                return true;
            }

            // TODO: maybe a randomize approach?
            for (unsigned long i = 3; i <= std::sqrt(s); i += 2) {
                if (s % i == 0) {
                    return false;
                }
            }
            return true;
        }

        /**
            return prime that <=s
        **/
        inline unsigned long lesser_prime(unsigned long s) {
            if (s <= 2) {
                return 2;
            }
            if (s % 2 == 0) {
                s --;
            }

            while (!is_prime(s)) {
                s -= 2;
            }

            return s;
        }

        /**
            return prime that is >= s
        **/
        inline unsigned long larger_prime(unsigned long s) {
            if (s <= 2) {
                return 2;
            }
            if (s % 2 == 0) {
                s ++;
            }

            while (!is_prime(s)) {
                s += 2;
            }

            return s;
        }
    }
}

#endif