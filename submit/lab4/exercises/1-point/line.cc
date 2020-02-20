#include "line.hh"
#include "point.hh"
#include "point.cc"
#include <cmath>
#include <string>
#include <sstream>

double Line::length(const Point& other) const{
	x.distance(y);
}

std::string Line::toString() const {
	std::stringstream s;
	s << "(" << x.toString() << ", " << y.toString << ")";  
	return s.str(); 
}
