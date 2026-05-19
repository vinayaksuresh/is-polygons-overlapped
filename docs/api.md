# API Reference

## Class: Intersect

Static class providing polygon overlap detection and parsing utilities.

### Public Interface
- overlap(string polygonA, string polygonB) -> bool

### Private Data Structures
- struct Point { float x; float y; }

### Methods
- overlap(string, string) -> bool
- removeSpacesCommas(string) -> vector<float>
- split(string, vector<float>&, char) -> void
- toVectorPointStructure(vector<float>) -> vector<Point>
- checkIntersecting(Point, Point, Point, Point, Point*) -> bool
- checkIfPointIsInsideLineSeg(Point, Point, Point) -> bool
- isValidPolygon(vector<Point>) -> bool

### Details

- overlap
  - Description: Check if two polygons overlap.
  - Input: polygonA, polygonB as strings of coordinates: "x,y x,y ... x,y"; polygons must be closed (first point equals last point)
  - Throws: std::string on invalid coordinate count or invalid polygons

- removeSpacesCommas
  - Description: Replace commas with spaces and split into floats
  - Returns: vector<float> of numeric values

- split
  - Description: Tokenize by a delimiter and convert tokens to floats
  - Throws: std::string when std::stof fails due to invalid numeric input

- toVectorPointStructure
  - Description: Pack the float vector into Point pairs (x,y)

- checkIntersecting
  - Description: Compute intersection of two line segments using determinant method; writes intersection point when lines are not parallel

- checkIfPointIsInsideLineSeg
  - Description: Verify the intersection lies within both segments' bounding boxes

- isValidPolygon
  - Description: A polygon is valid if it has more than 3 points and is closed (first == last)
