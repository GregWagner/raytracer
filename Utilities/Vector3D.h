#ifndef __VECTOR_3D__
#define __VECTOR_3D__

// This file contains the defintion of the class Vector3D

#include "Matrix.h"

class Normal;
class Point3D;

//----------------------------------------- class Vector3D

class Vector3D {
	public:
	
		double	x, y, z;

	public:
	
		constexpr Vector3D(): x(0.0), y(0.0), z(0.0) {};    	// default constructor
		explicit constexpr Vector3D(double a): x(a), y(a), z(a) {};		// constructor
		constexpr Vector3D(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}; // constructor
		constexpr Vector3D(const Vector3D& v): x(v.x), y(v.y), z(v.z) {}; // copy constructor
        explicit Vector3D(const Normal& n);						// constructs a vector from a Normal
        explicit Vector3D(const Point3D& p);					// constructs a vector from a point

		Vector3D& 												// assign a Normal to a vector
		operator= (const Normal& rhs); 
		
		Vector3D& 												// assign a Point3D to a vector
		operator= (const Point3D& rhs); 
		
		constexpr Vector3D										// unary minus
		operator- () const {
            return (Vector3D(-x, -y, -z));
        };
				
		double													// length
		length();
		
		constexpr double	    								// square of the length
		len_squared() const {
            return (x * x + y * y + z * z);
        };
		
		constexpr Vector3D										// multiplication by a double on the right
		operator* (const double a) const {
            return (Vector3D(x * a, y * a, z * a));
        };
				
		constexpr Vector3D										// division by a double
		operator/ (const double a) const {
            return (Vector3D(x / a, y / a, z / a));
        };

        constexpr Vector3D										// addition
		operator+ (const Vector3D& v) const {
            return (Vector3D(x + v.x, y + v.y, z + v.z));
        };
		
		Vector3D& 												// compound addition
		operator+= (const Vector3D& v);

        constexpr Vector3D										// subtraction
		operator- (const Vector3D& v) const {
            return (Vector3D(x - v.x, y - v.y, z - v.z));
        };
		
		constexpr double 										// dot product
		operator* (const Vector3D& b) const {
            return (x * b.x + y * b.y + z * b.z);
        };
		
		constexpr Vector3D 										// cross product
		operator^ (const Vector3D& v) const {
            return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
		};
		
		void 													// convert vector to a unit vector
		normalize();
		
		Vector3D& 												// return a unit vector, and normalize the vector												
		hat();
};


// inlined member functions

// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector3D& 
Vector3D::operator+= (const Vector3D& v) {
	x += v.x; y += v.y; z += v.z;
	return (*this);
}

// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

constexpr inline Vector3D
operator* (const double a, const Vector3D& v) {
	return (Vector3D(a * v.x, a * v.y, a * v.z));	
}

// non-inlined non-member function

// ----------------------------------------------------------------------- operator* 
// multiplication by a matrix on the left

constexpr Vector3D
operator* (const Matrix& mat, const Vector3D& v) {
    return (Vector3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
                    mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
                    mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}

#endif


