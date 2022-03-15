# Fixed Point Library

A C++ fixed-point library.

## Quick Start

```
./configure.sh
./build.sh
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


## Reference List

https://github.com/MikeLankamp/fpm
https://stackoverflow.com/questions/79677/whats-the-best-way-to-do-fixed-point-math
