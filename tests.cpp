#include "Intersect.h"

#include <cassert>
#include <string>

int main()
{
	std::string squareA = "0 0,0 4,4 4,4 0,0 0";
	std::string squareB = "2 2,2 6,6 6,6 2,2 2";
	std::string squareC = "1 1,1 3,3 3,3 1,1 1";
	std::string disjointSquare = "10 10,10 12,12 12,12 10,10 10";
	std::string containedSquare = "2.5 2.5,2.5 3,3 3,3 2.5,2.5 2.5";
	std::string sharedPointSquare = "4 4,4 5,5 5,5 4,4 4";
	std::string horizontalRectangle = "0 0,0 2,10 2,10 0,0 0";
	std::string verticalRectangle = "0 0,0 10,2 10,2 0,0 0";
	std::string diagonalTriangle = "1 4,4 1,10 10,1 4";

	assert(Intersect::overlap(squareA, squareB));
	assert(Intersect::overlap(squareA, squareB, squareC));
	assert(!Intersect::overlap(squareA, squareB, disjointSquare));
	assert(Intersect::overlap(horizontalRectangle, verticalRectangle));
	assert(Intersect::overlap(horizontalRectangle, diagonalTriangle));
	assert(Intersect::overlap(verticalRectangle, diagonalTriangle));
	assert(!Intersect::overlap(horizontalRectangle, verticalRectangle, diagonalTriangle));
	assert(Intersect::overlap(squareA, squareB, containedSquare));
	assert(Intersect::overlap(squareA, squareB, sharedPointSquare));

	bool invalidThirdPolygonThrew = false;
	try
	{
		Intersect::overlap(squareA, squareB, "0 0,1");
	}
	catch (std::string &error)
	{
		invalidThirdPolygonThrew = (error == "ERROR!! Input contains invalid no:of polygon co-ordinates.");
	}
	assert(invalidThirdPolygonThrew);

	return 0;
}
