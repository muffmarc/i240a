#ifndef LINE_HH_
#define LINE_HH_
#include "point.hh"
#include <string>

struct Line{
	const Point x, y;

	Line(Point x=Point(), Point y=Point()) : x(x), y(y){}

	double length(const Point& other) const;

	std::string toString() const;

};
#endif
