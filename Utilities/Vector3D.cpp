// This file contains the definition of the class Vector3D

#include <math.h>

#include "Vector3D.h"
#include "Normal.h"
#include "Point3D.h"

// ---------------------------------------------------------- constructor
// constructs a vector from a normal

Vector3D::Vector3D(const Normal& n)	 
	: x(n.x), y(n.y), z(n.z)
{}

// ---------------------------------------------------------- constructor
// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions

Vector3D::Vector3D(const Point3D& p)	 
	: x(p.x), y(p.y), z(p.z)
{}

// ----------------------------------------------------------- assignment operator
// assign a Normal to a vector

Vector3D& 
Vector3D::operator= (const Normal& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// ---------------------------------------------------------- assignment operator 
// assign a point to a vector

Vector3D& 												
Vector3D::operator= (const Point3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// ----------------------------------------------------------  length
// length of the vector

double													
Vector3D::length() {
	return (sqrt(len_squared()));
}


// ----------------------------------------------------------  normalize
// converts the vector to a unit vector

void 													
Vector3D::normalize() {
	double l = length();
	x /= l; y /= l; z /= l;
}


// ----------------------------------------------------------  hat
// converts the vector to a unit vector and returns the vector

Vector3D& 													
Vector3D::hat() {
    normalize();
	return (*this);
} 
