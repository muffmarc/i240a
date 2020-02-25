#include "line.hh"
#include "point.hh"
#include <cmath>
#include <string>
#include <sstream>

double Line::length() const {
	return x.distance(y);
}

std::string Line::toString() const {
	std::stringstream s;
	s << x.toString() << " -- " << y.toString() << " length = " << length();  
	return s.str(); 
}
