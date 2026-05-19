# Getting Started

This library is a single header (Intersect.h). Include it in your C++ project and call the static API.

- Include Intersect.h in your translation unit
- Provide polygons as strings of pairs: "x,y x,y ... x,y" where the first and last points are identical (closed polygon)
- Build with any modern C++ compiler

## Installation
Copy Intersect.h into your project (e.g., next to main.cpp) or place it in an include directory.

## Input format
- Coordinates are floats
- Delimiters: commas between x and y, spaces between points (commas are normalized to spaces internally)
- Example (square):
  - "0,0 2,0 2,2 0,2 0,0"
- Requirements:
  - Even number of numeric values after parsing
  - At least 4 points with closure (first == last)

## Build examples

Single-file demo:

```bash
g++ -std=c++17 -O2 -o demo main.cpp
./demo
```

If Intersect.h is in an include directory:

```bash
g++ -std=c++17 -O2 -Iinclude -o demo src/main.cpp
```

## Minimal example

```cpp
#include <iostream>
#include "Intersect.h"

int main() {
    std::string a = "0,0 1,0 1,1 0,1 0,0";
    std::string b = "2,2 3,2 3,3 2,3 2,2";
    std::cout << (Intersect::overlap(a, b) ? "overlap" : "no overlap") << "\n";
}
```
