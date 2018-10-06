# cloom
Cloom is a header only c++ counting bloom filter implementation.
You need to know that bloom filters are probabilistic datastructures,
a check if a `value` is stored will result in the following answers

* yes: the `value` is probably stored
* no: the `value` is definitly not stored

Counting bloom filters use more main memory in contrast to pure bloom filters,
however with counting bloom filteres it is also possible to remove values from the filter.

## requirements
* c++ compiler, e.g. gcc
* scons

## example
run `scons` to build the example, now you can run
```bash
./cloom
# output
# example cloom usage
# insert 123
# 123 in filter
# remove 123
# 123 NOT in filter
...
```


## usage
You can simply include in your c++ application the header file:
```cpp
#include "cloom.hpp"
...

Cloom<int> cl(123);

cl.insert(123);

if (cl.has(123)) {
    // probably 123 is stored in the bloom filter
}


cl.remove(123);

```

See `main.cpp` for more examples.