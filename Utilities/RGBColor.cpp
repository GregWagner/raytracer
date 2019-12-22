// This file contains the definition of the class RGBColor

#include <cmath>

#include "RGBColor.h"

// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{}

// --------------------------------------------------------assignment operator

RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}
 

// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor
RGBColor::powc(float p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

