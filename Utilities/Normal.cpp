// This file contains the defintion of the class Normal

#include <cmath>

#include "Normal.h"

// ---------------------------------------------------------- constructor
// construct a normal from a vector

Normal::Normal(const Vector3D& v)	 
	: x(v.x), y(v.y), z(v.z)  
{}

// ------------------------------------------------------------ operator=
// assignment of a vector to a normal

Normal& 
Normal::operator= (const Vector3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}

// ------------------------------------------------------------ operator=
// assignment of a point to a normal

Normal& 
Normal::operator= (const Point3D& rhs) {		
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// ------------------------------------------------------------ normalize

void 													
Normal::normalize(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}
