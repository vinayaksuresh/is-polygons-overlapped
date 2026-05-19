# Usage

This page shows typical usage patterns for the Intersect class and highlights common pitfalls when preparing polygon input strings.

## Checking overlap

```cpp
#include <iostream>
#include "Intersect.h"

int main() {
    std::string polyA = "0,0 2,0 2,2 0,2 0,0";  // Square
    std::string polyB = "1,1 3,1 3,3 1,3 1,1";  // Overlapping square

    if (Intersect::overlap(polyA, polyB)) {
        std::cout << "Polygons overlap" << std::endl;
    } else {
        std::cout << "Polygons do not overlap" << std::endl;
    }
}
```

## Non-overlapping example

```cpp
std::string polyA = "0,0 1,0 1,1 0,1 0,0";  // Unit square at origin
std::string polyB = "2,2 3,2 3,3 2,3 2,2";  // Unit square displaced
bool result = Intersect::overlap(polyA, polyB); // false
```

## Edge contact behavior
Depending on interpretation, touching edges can be considered overlapping or not. Review your requirements; this library reports overlap when a computed line intersection lies within both segments.

```cpp
std::string polyA = "0,0 1,0 1,1 0,1 0,0";
std::string polyB = "1,0 2,0 2,1 1,1 1,0";  // Adjacent squares
bool result = Intersect::overlap(polyA, polyB);
```

## Error handling and input validation
The parsing helpers removeSpacesCommas and split enforce numeric input and a valid coordinate count. Typical errors include:
- Non-numeric values (throws with message "invalid values")
- Odd number of coordinates (throws "invalid no:of polygon co-ordinates")
- Not a valid polygon (throws "Inputs are not valid Polygons.")

Example of catching errors:

```cpp
try {
    bool r = Intersect::overlap("0,0 1,abc 1,1", "0,0 1,0 1,1 0,1 0,0");
} catch (std::string& e) {
    std::cerr << e << std::endl;
}
```
