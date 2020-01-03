// This file contains the definition of the class RGBColor

#include <cmath>

#include "RGBColor.h"

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
RGBColor::powc(double p) const {
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}

