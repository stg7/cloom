#!/usr/bin/env python3

def is_prime(i):
    for k in range(2, i):
        if i % k == 0:
            return False
    return True

print("auto primes = {")
for i in range(2, 100000):
    if is_prime(i):
        print(i, end=",")
print("};")
