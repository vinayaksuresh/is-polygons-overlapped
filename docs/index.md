# Polygon Intersection Detection

## Overview
This header-only C++ library determines whether two 2D polygons overlap. It combines robust line-segment intersection with point-in-segment checks and simple polygon validation. Input polygons are provided as strings (e.g., "0,0 1,0 1,1 0,1 0,0").

Real-world applications include:
- Game development: collision and sprite overlap
- Computer graphics: clipping and visibility
- GIS systems: map overlays and spatial analysis
- CAD: interference checking
- Robotics: path planning and obstacle avoidance

## Features
- Header-only: drop in Intersect.h, no linking required
- String-based input parsing (comma or space-delimited)
- Determinant-based segment intersection
- Basic polygon validation (closed polygon with at least 3 vertices)
- Clear error messages on malformed input

## Quickstart

1) Add Intersect.h to your project.
2) Compile your program with a C++ compiler (e.g., g++).

Example minimal program:

```cpp
#include <iostream>
#include "Intersect.h"

int main() {
    std::string polyA = "0,0 2,0 2,2 0,2 0,0";  // square
    std::string polyB = "1,1 3,1 3,3 1,3 1,1";  // overlapping square

    bool overlaps = Intersect::overlap(polyA, polyB);
    std::cout << (overlaps ? "overlap" : "no overlap") << std::endl;
}
```

Build and run (example):

```bash
g++ -std=c++17 -O2 -o demo main.cpp
./demo
```

Notes:
- Ensure Intersect.h is on your compiler include path or in the same directory as your source file.
- Polygons must be closed (first point == last point).
