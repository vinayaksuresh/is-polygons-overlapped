#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Intersect {
public:
	static bool overlap(std::string polygonA, std::string polygonB);
	static bool overlap(std::string polygonA, std::string polygonB, std::string polygonC);

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
	static std::vector<Point> parsePolygon(std::string polygon);
	static bool polygonsOverlap(const std::vector<Point> &polygonA, const std::vector<Point> &polygonB);
	static bool polygonsOverlapAllThree(const std::vector<Point> &polygonA, const std::vector<Point> &polygonB, const std::vector<Point> &polygonC);
	static bool nearlyEqual(float left, float right);
	static bool samePoint(Point left, Point right);
	static float cross(Point pt_a, Point pt_b, Point pt_c);
	static bool pointOnSegment(Point pt_a, Point pt_b, Point pt_check);
	static bool pointInPolygon(Point point, const std::vector<Point> &polygon);
	static std::vector<Point> edgeIntersectionCandidates(Point pt_a, Point pt_b, Point pt_c, Point pt_d);
	static void addUniquePoint(std::vector<Point> &points, Point point);
};

float Intersect::cross(Point pt_a, Point pt_b, Point pt_c)
{
	return ((pt_b.x - pt_a.x) * (pt_c.y - pt_a.y)) - ((pt_b.y - pt_a.y) * (pt_c.x - pt_a.x));
}

bool Intersect::nearlyEqual(float left, float right)
{
	const float EPSILON = 0.00001f;
	return std::fabs(left - right) <= EPSILON;
}

bool Intersect::samePoint(Point left, Point right)
{
	return nearlyEqual(left.x, right.x) && nearlyEqual(left.y, right.y);
}

void Intersect::addUniquePoint(std::vector<Point> &points, Point point)
{
	for (std::vector<Point>::const_iterator pointIterator = points.begin(); pointIterator != points.end(); ++pointIterator)
	{
		if (samePoint(*pointIterator, point))
			return;
	}
	points.push_back(point);
}

bool Intersect::isValidPolygon(std::vector<Point> polygon)
{
	const int MIN_SIZE = 3;
	if (polygon.empty())
		return false;
	Point start = polygon.front();
	Point end = polygon.back();
	return (polygon.size() > MIN_SIZE && samePoint(start, end));
}

void Intersect::split(const std::string &string, std::vector<float> &floats, char ch)
{
	(void)ch;
	std::stringstream stream(string);
	std::string token;
	floats.clear();
	try
	{
		while (stream >> token)
		{
			size_t parsedCharacters = 0;
			float value = std::stof(token, &parsedCharacters);
			if (parsedCharacters != token.size())
				throw std::invalid_argument("invalid float token");
			floats.push_back(value);
		}
	}
	catch (std::invalid_argument &e)
	{
		throw std::string("ERROR!! Input string contains invalid values for a point.");
	}
	catch (std::out_of_range &e)
	{
		throw std::string("ERROR!! Input string contains invalid values for a point.");
	}

	if (floats.empty())
		throw std::string("ERROR!! Input string contains invalid values for a point.");
}

std::vector<float> Intersect::removeSpacesCommas(std::string polygon)
{
	std::vector<float> temp;
	std::string space = " ";

	for (std::string::size_type index = 0; index < polygon.size(); index = index + 1)
	{
		if (polygon[index] == ',')
			polygon.replace(index, 1, space);
	}
	split(polygon, temp, ' ');
	return temp;
}

bool Intersect::checkIntersecting(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_c, Intersect::Point pt_d, Intersect::Point *intersect)
{
	float a1 = pt_b.y - pt_a.y;
	float b1 = pt_a.x - pt_b.x;
	float c1 = a1 * (pt_a.x) + b1 * (pt_a.y);

	float a2 = pt_d.y - pt_c.y;
	float b2 = pt_c.x - pt_d.x;
	float c2 = a2 * (pt_c.x) + b2 * (pt_c.y);

	float determinant = (a1 * b2 - a2 * b1);

	if (nearlyEqual(determinant, 0.0f))
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

std::vector<Intersect::Point> Intersect::toVectorPointStructure(std::vector<float> vect)
{
	std::vector<Point> poly;

	for (std::vector<float>::size_type index = 0; index < vect.size(); index = index + 2)
	{
		Point p;
		p.x = vect.at(index);
		p.y = vect.at(index + 1);
		poly.push_back(p);
	}

	return poly;
}

bool Intersect::checkIfPointIsInsideLineSeg(Intersect::Point pt_a, Intersect::Point pt_b, Intersect::Point pt_check)
{
	return pointOnSegment(pt_a, pt_b, pt_check);
}

bool Intersect::pointOnSegment(Point pt_a, Point pt_b, Point pt_check)
{
	const float EPSILON = 0.00001f;
	if (!nearlyEqual(cross(pt_a, pt_b, pt_check), 0.0f))
		return false;

	float lowx = std::min(pt_a.x, pt_b.x) - EPSILON;
	float lowy = std::min(pt_a.y, pt_b.y) - EPSILON;
	float highx = std::max(pt_a.x, pt_b.x) + EPSILON;
	float highy = std::max(pt_a.y, pt_b.y) + EPSILON;

	return (pt_check.x >= lowx && pt_check.x <= highx && pt_check.y >= lowy && pt_check.y <= highy);
}

bool Intersect::pointInPolygon(Point point, const std::vector<Point> &polygon)
{
	bool inside = false;
	for (std::vector<Point>::size_type current = 0, previous = polygon.size() - 2; current < polygon.size() - 1; previous = current++)
	{
		Point start = polygon.at(previous);
		Point end = polygon.at(current);
		if (pointOnSegment(start, end, point))
			return true;

		bool crossesRay = ((start.y > point.y) != (end.y > point.y));
		if (crossesRay)
		{
			float xIntersection = ((end.x - start.x) * (point.y - start.y) / (end.y - start.y)) + start.x;
			if (point.x < xIntersection)
				inside = !inside;
		}
	}
	return inside;
}

std::vector<Intersect::Point> Intersect::edgeIntersectionCandidates(Point pt_a, Point pt_b, Point pt_c, Point pt_d)
{
	std::vector<Point> candidates;
	Point intersect;
	if (checkIntersecting(pt_a, pt_b, pt_c, pt_d, &intersect))
	{
		if (pointOnSegment(pt_a, pt_b, intersect) && pointOnSegment(pt_c, pt_d, intersect))
			addUniquePoint(candidates, intersect);
		return candidates;
	}

	if (nearlyEqual(cross(pt_a, pt_b, pt_c), 0.0f) && nearlyEqual(cross(pt_a, pt_b, pt_d), 0.0f))
	{
		if (pointOnSegment(pt_c, pt_d, pt_a))
			addUniquePoint(candidates, pt_a);
		if (pointOnSegment(pt_c, pt_d, pt_b))
			addUniquePoint(candidates, pt_b);
		if (pointOnSegment(pt_a, pt_b, pt_c))
			addUniquePoint(candidates, pt_c);
		if (pointOnSegment(pt_a, pt_b, pt_d))
			addUniquePoint(candidates, pt_d);
	}
	return candidates;
}

std::vector<Intersect::Point> Intersect::parsePolygon(std::string polygon)
{
	std::vector<float> vect = removeSpacesCommas(polygon);

	if (vect.size() % 2 != 0)
		throw std::string("ERROR!! Input contains invalid no:of polygon co-ordinates.");

	std::vector<Point> poly = toVectorPointStructure(vect);

	if (!Intersect::isValidPolygon(poly))
		throw std::string("ERROR!! Inputs are not valid Polygons.");

	return poly;
}

bool Intersect::polygonsOverlap(const std::vector<Point> &polygonA, const std::vector<Point> &polygonB)
{
	for (std::vector<Point>::size_type polyA_index = 0; polyA_index < polygonA.size() - 1; polyA_index++)
	{
		for (std::vector<Point>::size_type polyB_index = 0; polyB_index < polygonB.size() - 1; polyB_index++)
		{
			if (!edgeIntersectionCandidates(polygonA.at(polyA_index), polygonA.at(polyA_index + 1), polygonB.at(polyB_index), polygonB.at(polyB_index + 1)).empty())
				return true;
		}
	}

	for (std::vector<Point>::size_type index = 0; index < polygonA.size() - 1; index++)
	{
		if (pointInPolygon(polygonA.at(index), polygonB))
			return true;
	}
	for (std::vector<Point>::size_type index = 0; index < polygonB.size() - 1; index++)
	{
		if (pointInPolygon(polygonB.at(index), polygonA))
			return true;
	}

	return false;
}

bool Intersect::polygonsOverlapAllThree(const std::vector<Point> &polygonA, const std::vector<Point> &polygonB, const std::vector<Point> &polygonC)
{
	for (std::vector<Point>::size_type index = 0; index < polygonA.size() - 1; index++)
	{
		if (pointInPolygon(polygonA.at(index), polygonB) && pointInPolygon(polygonA.at(index), polygonC))
			return true;
	}
	for (std::vector<Point>::size_type index = 0; index < polygonB.size() - 1; index++)
	{
		if (pointInPolygon(polygonB.at(index), polygonA) && pointInPolygon(polygonB.at(index), polygonC))
			return true;
	}
	for (std::vector<Point>::size_type index = 0; index < polygonC.size() - 1; index++)
	{
		if (pointInPolygon(polygonC.at(index), polygonA) && pointInPolygon(polygonC.at(index), polygonB))
			return true;
	}

	for (std::vector<Point>::size_type polyA_index = 0; polyA_index < polygonA.size() - 1; polyA_index++)
	{
		for (std::vector<Point>::size_type polyB_index = 0; polyB_index < polygonB.size() - 1; polyB_index++)
		{
			std::vector<Point> candidates = edgeIntersectionCandidates(polygonA.at(polyA_index), polygonA.at(polyA_index + 1), polygonB.at(polyB_index), polygonB.at(polyB_index + 1));
			for (std::vector<Point>::const_iterator candidate = candidates.begin(); candidate != candidates.end(); ++candidate)
			{
				if (pointInPolygon(*candidate, polygonC))
					return true;
			}
		}
	}
	for (std::vector<Point>::size_type polyA_index = 0; polyA_index < polygonA.size() - 1; polyA_index++)
	{
		for (std::vector<Point>::size_type polyC_index = 0; polyC_index < polygonC.size() - 1; polyC_index++)
		{
			std::vector<Point> candidates = edgeIntersectionCandidates(polygonA.at(polyA_index), polygonA.at(polyA_index + 1), polygonC.at(polyC_index), polygonC.at(polyC_index + 1));
			for (std::vector<Point>::const_iterator candidate = candidates.begin(); candidate != candidates.end(); ++candidate)
			{
				if (pointInPolygon(*candidate, polygonB))
					return true;
			}
		}
	}
	for (std::vector<Point>::size_type polyB_index = 0; polyB_index < polygonB.size() - 1; polyB_index++)
	{
		for (std::vector<Point>::size_type polyC_index = 0; polyC_index < polygonC.size() - 1; polyC_index++)
		{
			std::vector<Point> candidates = edgeIntersectionCandidates(polygonB.at(polyB_index), polygonB.at(polyB_index + 1), polygonC.at(polyC_index), polygonC.at(polyC_index + 1));
			for (std::vector<Point>::const_iterator candidate = candidates.begin(); candidate != candidates.end(); ++candidate)
			{
				if (pointInPolygon(*candidate, polygonA))
					return true;
			}
		}
	}

	return false;
}

bool Intersect::overlap(std::string polygonA, std::string polygonB)
{
	std::vector<Point> polyA = parsePolygon(polygonA);
	std::vector<Point> polyB = parsePolygon(polygonB);

	return polygonsOverlap(polyA, polyB);
}

bool Intersect::overlap(std::string polygonA, std::string polygonB, std::string polygonC)
{
	std::vector<Point> polyA = parsePolygon(polygonA);
	std::vector<Point> polyB = parsePolygon(polygonB);
	std::vector<Point> polyC = parsePolygon(polygonC);

	return polygonsOverlapAllThree(polyA, polyB, polyC);
}
