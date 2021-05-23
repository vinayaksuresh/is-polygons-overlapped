#include "Intersect.h"

int main()
{
	std::string polygonAlpha = "0 0,0 1,2 0,0 0";
	std::string polygonBravo = "1 0,1 1,3 0,1 0";
	std::string polygonCharlie = "2 2,2 3,4 2,2 2";

	/*============================= Additional test case Scenarios ==============================================*/
	std::string squarePolygon1 = "4 2,4 8,10 8,10 2,4 2";
	std::string squarePolygon2 = "8 6,8 12,14 12,14 6,8 6";

	std::string triangle1 = "1 1,1 3,4 1,1 1";
	std::string triangle2 = "3 5,3 7,6 5,3 5";
	std::string triangle3 = "2.38 1.58,4 3,4.32 2.33,2.38 1.58";

	std::string triangle4 = "4 6,4 14,14 6,4 6";
	std::string triangle5 = "4 14,14 14,14 6,4 14";

	std::string pentagon = "-4 2,-4 4,0.72 5.33,2 4.37,2 2,-4 2";
	std::string nonConvexPolyAlpha = "1 1,1 3.43,7.66 -1.07,4.2 -1.37,3 1,1 1";

	std::string triangleAlpha = "4 6,4 14,12 6,4 6}";
	std::string triangleAlphaMirror = "14 6,22 14,22 6,14 6";

	std::string nonConvexPolyBravo = "-2 1,-2 4,4 2,5 5,5 1,-2 1";
	std::string nonConvexPolyCharlie = "-6 -5,9.8 4,7 0,10.3 -1.72,-6 -5";

	std::string hexagon = "-6 -8,-10 -6,-12 -2,-10 2,-6 4,-2 2,-6 -1.7,-2 -6,-6 -8";
	std::string newpoly = "-10 -10,-16 0,-14 2,-2 -2,-10 -10";

	/* Strings with invalid cases*/
	std::string invalidPolygon = "0 0,0 1.5,2 0,0 1";
	std::string singlePoint = "0 0.5";
	std::string invalidPolygonPoints1 = "-1";
	std::string invalidPolygonPoints2 = "-1 3,2";
	std::string stringWithInvalidPointValues1 = "1 1,2 3,$ 2";
	std::string stringWithInvalidPointValues2 = "";
	std::string stringWithInvalidPointValues3 = "a 1,2 b";

	std::cout << "polygonAlpha and polygonBravo are: ";
	try
	{ /* Overlapping */
		if (Intersect::overlap(polygonAlpha, polygonBravo))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	// Alpha and Charlie are not overlapping, so if our function says there exists an overlap
	// then this is clearly not OK
	std::cout << "polygonAlpha and polygonCharlie are: ";
	try
	{
		if (Intersect::overlap(polygonAlpha, polygonCharlie))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	// Checking Charlie against Alpha must also be Non overlapping
	std::cout << "polygonCharlie and polygonAlpha are: ";
	try
	{
		if (Intersect::overlap(polygonCharlie, polygonAlpha))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* ================================ Additional Test Case Scenarios ( Check the document for the polygon overlapping scenarios) ==================================================== */
	std::cout << "squarePolygon1 and squarePolygon2 are: ";
	try
	{ /* Overlapping */
		if (Intersect::overlap(squarePolygon1, squarePolygon2))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* Non overlapping */
	std::cout << "triangle1 and triangle2 are: ";
	try
	{
		if (Intersect::overlap(triangle1, triangle2))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* Overlapping */
	std::cout << "triangle1 and triangle3 are: ";
	try
	{
		if (Intersect::overlap(triangle1, triangle3))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* Overlapping */
	std::cout << "pentagon and nonConvexPolynAlpha are: ";
	try
	{
		if (Intersect::overlap(pentagon, nonConvexPolyAlpha))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* Overlapping */
	std::cout << "triangle4 and triangle5 are: ";
	try
	{
		if (Intersect::overlap(triangle4, triangle5))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/* Not Overlapping */
	std::cout << "triangleAlpha and triangleAlphaMirror are: ";
	try
	{
		if (Intersect::overlap(triangleAlpha, triangleAlphaMirror))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	/*  Overlapping */
	std::cout << "nonConvexPolyBravo and nonConvexPolyCharlie are: ";
	try
	{ /* Overlapping */
		if (Intersect::overlap(nonConvexPolyBravo, nonConvexPolyCharlie))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	//std::cout << std::endl;

	/*  Overlapping */
	std::cout << "hexagon and newpoly are: ";
	try
	{ /* Overlapping */
		if (Intersect::overlap(hexagon, newpoly))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not Overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}
	std::cout << std::endl;

	/* ================================ Test Case Scenarios for Invalid Error Handling ==================================================== */

	std::cout << "polygonAlpha and invalidPolygon are: ";
	try
	{
		if (Intersect::overlap(polygonAlpha, invalidPolygon))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "polygonAlpha and singlePoint are: ";
	try
	{ /* Invalid Polygon - less than 3 sides */
		if (Intersect::overlap(polygonAlpha, singlePoint))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "polygonAlpha and invalidPolygonPoints1 are: ";
	try
	{ /* Invalid Polygon - With just one co-ordinate value */
		if (Intersect::overlap(polygonAlpha, invalidPolygonPoints1))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "polygonAlpha and invalidPolygonPoints2 are: ";
	try
	{ /* Invalid Polygon - Odd number of values */
		if (Intersect::overlap(polygonAlpha, invalidPolygonPoints2))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "nonConvexPolyAlpha and stringWithInvalidPointValues1 are: ";
	try
	{ /* Invalid Polygon - With invalid polygon point values */
		if (Intersect::overlap(nonConvexPolyAlpha, stringWithInvalidPointValues1))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "nonConvexPolyBravo and stringWithInvalidPointValues2 are: ";
	try
	{
		if (Intersect::overlap(nonConvexPolyBravo, stringWithInvalidPointValues2))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << "nonConvexPolyBravo and stringWithInvalidPointValues3 are: ";
	try
	{ /* Invalid Polygon - With invalid polygon point values */
		if (Intersect::overlap(nonConvexPolyBravo, stringWithInvalidPointValues3))
		{
			std::cout << "Overlapping" << std::endl;
		}
		else
		{
			std::cout << "Not overlapping" << std::endl;
		}
	}
	catch (std::string e)
	{
		std::cout << e << std::endl;
	}

	std::cout << std::endl;

	std::cout << "End of Polygon Overlap Check";

	return 0;
}
