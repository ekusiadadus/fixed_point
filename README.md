# Fixed Point Library

A C++ fixed-point library.

## Quick Start

```
./configure.sh
./build.sh
cd build
./fixed_point-test
```

## Usage

To use `fixed_point` library, include `<fixed_point/FixedPoint.hpp>`.

```c++
#include <iostream>

#include "fixed_point/FixedPoint.hpp"
using namespace std;

int main() {
  FixedPoint<uint8_t, 3> i5f3(10.2f);
  cout << float(i5f3) << endl;
}
```

## Tests

C/C++ unit test demo using [GoogleTest](https://google.github.io/googletest/).


## Reference Lists

https://github.com/MikeLankamp/fpm

https://stackoverflow.com/questions/79677/whats-the-best-way-to-do-fixed-point-math

https://codereview.stackexchange.com/questions/184057/fixed-point-arithmetics-in-c-using-templates

https://google.github.io/googletest/

https://github.com/bast/gtest-demo