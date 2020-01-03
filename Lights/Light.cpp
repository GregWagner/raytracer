#include "Light.h"

#include "../Utilities/Constants.h"

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls) {}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}

// ---------------------------------------------------------------------- L
// returns the radiance

RGBColor								
Light::L(ShadeRec& s) {
	return (black);
}


