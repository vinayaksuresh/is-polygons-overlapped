<b>Author:</b> XHwak

# Polygon Intersection Detection Library - Technical OnePager

## 1. Overview

**Problem Domain**: This C++ header library solves the fundamental computational geometry problem of determining whether two polygons overlap or intersect in 2D space. This is a critical operation in
computer graphics, game development, GIS systems, and CAD applications.

**Real-World Applications**:
- **Game Development**: Collision detection between game objects, sprite overlap detection
- **Computer Graphics**: Polygon clipping for rendering pipelines, visibility determination
- **GIS Systems**: Spatial analysis, map overlay operations, territory boundary analysis
- **CAD Software**: Design validation, interference checking between components
- **Robotics**: Path planning, obstacle avoidance algorithms

**Target Audience**: C++ developers working on graphics engines, game developers, GIS programmers, and anyone needing robust 2D geometric intersection algorithms.

**Unique Features**: This implementation provides a clean, header-only solution with string-based polygon input parsing, making it easy to integrate with text-based data sources. The library combines line
 segment intersection algorithms with point-in-polygon testing for comprehensive overlap detection.

## 2. Key Concepts

### Computational Geometry & Line Intersection Algorithm
The core of polygon intersection detection relies on the mathematical principle of line segment intersection using parametric line equations. The `checkIntersecting` function implements the
determinant-based approach:

```cpp
bool Intersect::checkIntersecting(Point pt_a, Point pt_b, Point pt_c, Point pt_d, Point *intersect)
```

**Mathematical Foundation**: Two line segments AB and CD intersect if their parametric equations have a solution. The algorithm converts each line to the form `ax + by = c` and solves the system using
Cramer's rule:
- Line 1: `a1*x + b1*y = c1`
- Line 2: `a2*x + b2*y = c2`
- Determinant: `det = a1*b2 - a2*b1`

**Why This Works**: When `det ≠ 0`, the lines intersect at exactly one point. When `det = 0`, the lines are parallel (no intersection or infinite intersections).

**Time Complexity**: O(1) - constant time intersection test
**Space Complexity**: O(1) - only stores coefficients and intersection point

### Polygon Validation Framework
The `isValidPolygon` function ensures geometric integrity:

```cpp
bool Intersect::isValidPolygon(std::vector<Point> polygon)
{
    const int MIN_SIZE = 3;
    Point start = polygon.front();
    Point end = polygon.back();
    return (polygon.size() > MIN_SIZE && start.x == end.x && start.y == end.y);
}
```

**Validation Rules**:
1. **Minimum Vertices**: Must have more than 3 points (actual requirement: ≥4 including closure)
2. **Closure Property**: First and last points must be identical (closed polygon)

**Why These Rules**: A polygon needs at least 3 distinct vertices to enclose area, and the closure ensures proper boundary definition for intersection algorithms.

### String Parsing & Data Transformation
The library handles string-based polygon input through a two-stage parsing pipeline:

```cpp
std::vector<float> removeSpacesCommas(std::string polygon)
void split(const std::string &string, std::vector<float> &floats, char ch)
```

**Algorithm Flow**:
1. **Normalization**: Replace commas with spaces for uniform delimiter
2. **Tokenization**: Split on whitespace to extract numeric values
3. **Conversion**: Parse strings to floats with exception handling
4. **Validation**: Ensure even number of values (x,y coordinate pairs)

**Exception Handling**: The `split` function catches `std::invalid_argument` and throws descriptive error messages, preventing silent failures from malformed input.

### Vector Operations & Coordinate Geometry
The Point structure and vector operations form the geometric foundation:

```cpp
struct Point {
    float x;
    float y;
};
```

**Coordinate System**: Uses standard Cartesian coordinates with floating-point precision for sub-pixel accuracy. The choice of `float` over `double` balances precision with memory efficiency for typical
graphics applications.

## 3. Implementation Details

### Core Algorithm: Line Segment Intersection
```cpp
bool checkIntersecting(Point pt_a, Point pt_b, Point pt_c, Point pt_d, Point *intersect)
{
    float a1 = pt_b.y - pt_a.y;           // Line 1 slope component
    float b1 = pt_a.x - pt_b.x;           // Line 1 x-coefficient
    float c1 = a1 * (pt_a.x) + b1 * (pt_a.y);  // Line 1 constant

    float a2 = pt_d.y - pt_c.y;           // Line 2 slope component
    float b2 = pt_c.x - pt_d.x;           // Line 2 x-coefficient
    float c2 = a2 * (pt_c.x) + b2 * (pt_c.y);  // Line 2 constant

    float determinant = (a1 * b2 - a2 * b1);

    if (determinant == 0) return false;    // Parallel lines

    intersect->x = (b2 * c1 - b1 * c2) / determinant;
    intersect->y = (a1 * c2 - a2 * c1) / determinant;
    return true;
}
```

**Worked Example**:
- Input: Line AB from (0,0) to (2,2), Line CD from (0,2) to (2,0)
- Line 1: `2x + (-2)y = 0` → `x - y = 0`
- Line 2: `(-2)x + (-2)y = -4` → `x + y = 2`
- Determinant: `1*(-2) - (-1)*(-2) = -4` (non-zero, intersection exists)
- Intersection: `x = 1, y = 1`

### String Processing Pipeline
```cpp
void split(const std::string &string, std::vector<float> &floats, char ch)
{
    size_t pos = string.find(ch);
    size_t initialPos = 0;
    floats.clear();

    try {
        while (pos != std::string::npos) {
            floats.push_back(std::stof(string.substr(initialPos, pos - initialPos)));
            initialPos = pos + 1;
            pos = string.find(ch, initialPos);
        }
        floats.push_back(std::stof(string.substr(initialPos, std::min(pos, string.size()) - initialPos + 1)));
    }
    catch (std::invalid_argument e) {
        throw std::string("ERROR!! Input string contains invalid values for a point.");
    }
}
```

**Edge Cases Handled**:
- Empty strings
- Non-numeric characters
- Multiple consecutive delimiters
- Trailing/leading whitespace

## 4. Code Structure

**File Organization**:
- `Intersect.h` (Lines 5-128): Complete header-only implementation
- `repository/Intersect.h`: Duplicate header file for distribution

**Class Architecture**:
```
Intersect (Static Class)
├── Public Interface
│   └── overlap(string, string) → bool
├── Private Data Structures
│   └── Point{float x, y}
└── Private Utilities
    ├── removeSpacesCommas() → vector<float>
    ├── split() → void
    ├── toVectorPointStructure() → vector<Point>
    ├── checkIntersecting() → bool
    ├── checkIfPointIsInsideLineSeg() → bool
    └── isValidPolygon() → bool
```

**Data Flow**:
1. String input → `removeSpacesCommas()` → numeric vector
2. Numeric vector → `toVectorPointStructure()` → Point vector
3. Point vector → `isValidPolygon()` → validation
4. Point vectors → intersection algorithms → overlap result

## 5. Practical Testing & Verification

### Test Case 1: Basic Intersection
```cpp
// Input polygons as strings
std::string polyA = "0,0 2,0 2,2 0,2 0,0";  // Square
std::string polyB = "1,1 3,1 3,3 1,3 1,1";  // Overlapping square

// Expected: true (squares overlap)
bool result = Intersect::overlap(polyA, polyB);
assert(result == true);

// Verification: Visual check - squares overlap in region (1,1)-(2,2)
```

### Test Case 2: No Intersection
```cpp
std::string polyA = "0,0 1,0 1,1 0,1 0,0";  // Unit square at origin
std::string polyB = "2,2 3,2 3,3 2,3 2,2";  // Unit square displaced

// Expected: false (no overlap)
bool result = Intersect::overlap(polyA, polyB);
assert(result == false);

// Verification: Minimum distance between polygons > 0
```

### Test Case 3: Edge Case - Shared Edge
```cpp
std::string polyA = "0,0 1,0 1,1 0,1 0,0";
std::string polyB = "1,0 2,0 2,1 1,1 1,0";  // Adjacent squares

// Expected: Depends on implementation (edge touching)
bool result = Intersect::overlap(polyA, polyB);

// Verification: Check if algorithm treats edge contact as intersection
```

### Test Case 4: Invalid Input Handling
```cpp
std::string invalidPoly = "0,0 1,abc 1,1";  // Contains non-numeric data

try {
    bool result = Intersect::overlap(invalidPoly, "0,0 1,0 1,1 0,1 0,0");
    assert(false);  // Should not reach here
} catch (std::string& error) {
    assert(error.find("invalid values") != std::string::npos);
}

// Verification: Exception thrown with descriptive message
```

### Test Case 5: Polygon Validation
```cpp
// Test minimum vertex requirement
std::string triangle = "0,0 1,0 0,1 0,0";     // Valid (4 points, closed)
std::string line = "0,0 1,1 0,0";             // Invalid (only 3 points)
std::string open = "0,0 1,0 1,1 0,1";         // Invalid (not closed)

// Manual validation test
std::vector<Intersect::Point> points = {{0,0}, {1,0}, {1,1}, {0,0}};
bool valid = Intersect::isValidPolygon(points);  // Should be true

// Verification: Check size > 3 AND first == last point
```

### Debugging Verification Methods
```cpp
// 1. Intersection Point Verification
Intersect::Point intersection;
bool hasIntersection = Intersect::checkIntersecting(
    {0,0}, {2,2},  // Line 1
    {0,2}, {2,0},  // Line 2
    &intersection
);
// Verify: intersection.x == 1.0 && intersection.y == 1.0

// 2. Determinant Check for Parallel Lines
// Lines: (0,0)-(1,1) and (0,1)-(1,2) are parallel
bool parallel = !Intersect::checkIntersecting(
    {0,0}, {1,1}, {0,1}, {1,2}, &intersection
);
// Verify: parallel == true (determinant == 0)
```

## 6. Learning Path

### Foundation Level (Start Here)
1. **Study `Point` structure** - Understand coordinate representation
2. **Examine `isValidPolygon()`** - Learn polygon validation rules
3. **Analyze `removeSpacesCommas()`** - String processing fundamentals

### Core Algorithm Level
4. **Master `checkIntersecting()`** - Line intersection mathematics
5. **Understand determinant calculation** - Linear algebra application
6. **Study exception handling in `split()`** - Robust input processing

### Advanced Integration
7. **Analyze `overlap()` public interface** - Complete algorithm integration
8. **Study `toVectorPointStructure()`** - Data structure transformation
9. **Examine `checkIfPointIsInsideLineSeg()`** - Point-line relationships

**Learning Tips**:
- Focus on the determinant calculation in `checkIntersecting()` to understand the mathematical foundation
- Practice with the string parsing pipeline to handle real-world data formats
- Implement test cases for each validation rule to understand edge cases

## 7. Key Takeaways

### Algorithms & Techniques Learned
- **Parametric Line Intersection**: Using determinants to solve 2D line intersection
- **Polygon Validation**: Ensuring geometric integrity through closure and vertex count
- **String Parsing Pipelines**: Robust text-to-geometry data transformation
- **Exception-Safe Programming**: Graceful handling of malformed input data

### Mathematical Concepts Applied
- **Linear Algebra**: Cramer's rule for solving 2x2 systems
- **Computational Geometry**: Point-line relationships and polygon properties
- **Floating-Point Arithmetic**: Precision considerations in geometric calculations

### Performance Characteristics
- **Time Complexity**: O(n×m) where n,m are polygon vertex counts (worst case: test all edge pairs)
- **Space Complexity**: O(n+m) for storing polygon vertices
- **Numerical Stability**: Uses float precision suitable for graphics applications

### Transferable Knowledge
- **Graphics Programming**: Foundation for collision detection, clipping algorithms
- **Game Development**: Essential for 2D physics engines and spatial queries
- **GIS Applications**: Spatial analysis and geometric operations
- **Algorithm Design**: Template for geometric predicate implementation

This implementation demonstrates production-quality computational geometry code with proper error handling, clear interfaces, and mathematical rigor suitable for real-world applications.
Created multiplexed session.
