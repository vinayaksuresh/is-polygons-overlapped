#include <iostream>
#include <string>
#include <vector>

class Intersect
{
public:
	static bool overlap(std::string polygonA, std::string polygonB);

private:
	struct Point
	{
		float x;
		float y;
	};
	static std::vector<float> removeSpacesCommas(std::string polygon);
	static void split(const std::string &txt, std::vector<float> &strs, char ch);
	static std::vector<Point> toVectorPointStructure(std::vector<float> vect);
	static bool checkIntersecting(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_c, Intersect::Point pt_d, Intersect::Point *intersect);
	static bool checkIfPointIsInsideLineSeg(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_check);
	static bool isValidPolygon(std::vector<Point> polygon);
};

/* ============================================================================================================================
 * Function:isValidPolygon
 * Description:The functions determines the polygon passed is valid or not
 * Parameters:Polygon vector
 * Return Type:bool
 * =============================================================================================================================
*/

bool Intersect::isValidPolygon(std::vector<Point> polygon)
{
	const int MIN_SIZE = 3;
	Point start = polygon.front();
	Point end = polygon.back();
	return (polygon.size() > MIN_SIZE && start.x == end.x && start.y == end.y);
}

/* ============================================================================================================================
 * Function:split
 * Description: This function converts all contents of the string to a vector of floats.
 * 				It throws an error if invalid float value is present in the string.
 * Parameters: string - Polygon string, floats - resultant vector, ch - space
 * Return Type:None
 * =============================================================================================================================
*/

void Intersect::split(const std::string &string, std::vector<float> &floats, char ch)
{
	size_t pos = string.find(ch);
	size_t initialPos = 0;
	floats.clear();
	try
	{
		while (pos != std::string::npos)
		{
			floats.push_back(std::stof(string.substr(initialPos, pos - initialPos)));

			initialPos = pos + 1;
			pos = string.find(ch, initialPos);
		}

		// Add the last one
		floats.push_back(std::stof(string.substr(initialPos, std::min(pos, string.size()) - initialPos + 1))); // stof throws an execption
	}
	catch (std::invalid_argument e)
	{
		throw std::string("ERROR!! Input string contains invalid values for a point.");
	}
}

/* ============================================================================================================================
 * Function:removeSpacesCommas
 * Description:This function replaces all the commas with space and splits the string based on space.
 * Parameters: Polygon string
 * Return Type: float vector
 * =============================================================================================================================
*/

std::vector<float> Intersect::removeSpacesCommas(std::string polygon)
{
	std::vector<float> temp;
	std::string space = " ";

	for (int index = 0; index < polygon.size(); index = index + 1)
	{
		if (polygon[index] == ',')
			polygon.replace(index, 1, space);
	}
	split(polygon, temp, ' ');
	return temp;
}

/* ============================================================================================================================
 * Function:checkIntersecting
 * Description: This function checks if two line segments are interesting or not. If they are intersecting the intersection
 * 				points are updated to the intersect point
 * Parameters:	pt_a,pt_b,pt_c,pt_d - The 4 points which forms two line segments a1x + b1y = c1 and a2x + b2y = c2 respectively.
 * 				intersect - structure pointer to store intersect point
 * Return Type:bool
 * =============================================================================================================================
*/
bool Intersect::checkIntersecting(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_c, Intersect::Point pt_d, Intersect::Point *intersect)
{
	// creating line segments a1x + b1y = c1
	float a1 = pt_b.y - pt_a.y;
	float b1 = pt_a.x - pt_b.x;
	float c1 = a1 * (pt_a.x) + b1 * (pt_a.y);

	// creating line segments a2x + b2y = c2
	float a2 = pt_d.y - pt_c.y;
	float b2 = pt_c.x - pt_d.x;
	float c2 = a2 * (pt_c.x) + b2 * (pt_c.y);

	float determinant = (a1 * b2 - a2 * b1); // Calculating determinant of two lines

	if (determinant == 0) // The lines are parallel.
	{
		return false;
	}
	else
	{
		intersect->x = (b2 * c1 - b1 * c2) / determinant;
		intersect->y = (a1 * c2 - a2 * c1) / determinant;
		return true;
	}
}

/* ============================================================================================================================
 * Function: toVectorPointStructure
 * Description: The co-ordinates extracted from the vector are stored in structure called Points
 * Parameters: Vector with all the polygon points
 * Return Type: Polygon vector with Point structure
 * =============================================================================================================================
*/
std::vector<Intersect::Point> Intersect::toVectorPointStructure(std::vector<float> vect)
{
	std::vector<Point> poly;

	for (int index = 0; index < vect.size(); index = index + 2)
	{
		Point p;
		p.x = vect.at(index);
		p.y = vect.at(index + 1);
		poly.push_back(p);
	}

	return poly;
}

/* ============================================================================================================================
 * Function: checkIfPointIsInsideLineSeg
 * Description: The function checks if intersection point lies inside the line segment formed by two points pt_a and pt_b
 * Parameters: pt_a, pt_b - Points of a line segment, pt_check - Intersection point to be checked
 * Return Type: bool
 * =============================================================================================================================
*/

bool Intersect::checkIfPointIsInsideLineSeg(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_check)
{
	float lowx = pt_a.x < pt_b.x ? pt_a.x : pt_b.x; // Gets the lowest value of x component comparing with pointA and pointB x components
	float lowy = pt_a.y < pt_b.y ? pt_a.y : pt_b.y; // Gets the lowest value of y component comparing with pointA and pointB y components

	float highx = pt_a.x > pt_b.x ? pt_a.x : pt_b.x; // Gets the highest value of x component comparing with pointA and pointB x components
	float highy = pt_a.y > pt_b.y ? pt_a.y : pt_b.y; // Gets the highest value of y component comparing with pointA and pointB y components

	// Checking if the x component of interference point lies between the x component of Point A and Point B
	bool check_xcomponent = ((pt_check.x >= lowx) && (highx >= pt_check.x));
	// Checking if the y component of interference Point lies between the y component of Point A and Point B
	bool check_ycomponent = ((pt_check.y >= lowy) && (highy >= pt_check.y));

	/* Returns true if the intersecting point lies inside the line segment, otherwise returns false */
	return (check_xcomponent && check_ycomponent);
}

/* ======================================================================================================================================
 * Function: overlap
 * Description:This function checks overlapping of two polygons
 * Parameter: PolygonA points string and PolygonB points string
 * Return Type: bool
 * =======================================================================================================================================
*/

bool Intersect::overlap(std::string polygonA, std::string polygonB)
{
	/* The comma and spaces in string of polygonA and polygonB are removed and stored in respective vectors */
	std::vector<float> vectA = removeSpacesCommas(polygonA);
	std::vector<float> vectB = removeSpacesCommas(polygonB);

	/* As a point consist of two co-ordinates, we check if points are having two co-ordinates, else we throw an error*/
	if ((vectA.size() % 2 != 0) || (vectB.size() % 2 != 0))
		throw std::string("ERROR!! Input contains invalid no:of polygon co-ordinates.");

	/* The polygon point values in vector are stored in a Point structure. The structure has two members which represents x component and y component of a point */
	std::vector<Point> polyA = toVectorPointStructure(vectA);
	std::vector<Point> polyB = toVectorPointStructure(vectB);

	/* Freeing the memory used by vectors*/
	vectA.clear();
	vectB.clear();

	/* Check if the points received form vector is a valid polygon. If not, throws an error*/
	if (!Intersect::isValidPolygon(polyA) || !Intersect::isValidPolygon(polyB))
		throw std::string("ERROR!! Inputs are not valid Polygons.");

	/* Checks overlapping of two polygons. Returns true if overlapped else false*/
	for (int polyA_index = 0; polyA_index < polyA.size() - 1; polyA_index++)
	{
		for (int polyB_index = 0; polyB_index < polyB.size() - 1; polyB_index++)
		{
			Point intersect;
			bool isIntersecting = checkIntersecting(polyA.at(polyA_index), polyA.at(polyA_index + 1), polyB.at(polyB_index), polyB.at(polyB_index + 1), &intersect);
			if (isIntersecting)
			{
				if ((checkIfPointIsInsideLineSeg(polyA.at(polyA_index), polyA.at(polyA_index + 1), intersect)) && (checkIfPointIsInsideLineSeg(polyB.at(polyB_index), polyB.at(polyB_index + 1), intersect)))
					return true;
			}
		}
	}
	return false;
}
