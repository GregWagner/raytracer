#ifndef __POINT3D__
#define __POINT3D__

// This file contains the defintion of the class Point3D

#include "Matrix.h"
#include "Vector3D.h"

class Point3D {
	public:
	
		double x, y, z;

        constexpr Point3D(): x(0.0), y(0.0), z(0.0) {};							// default constructor
		constexpr explicit Point3D(double a): x(a), y(a), z(a) {};						// constructor
		constexpr Point3D(double a, double b, double c): x(a), y(b), z(c) {};	// constructor
		constexpr Point3D(const Point3D& p): x(p.x), y(p.y), z(p.z) {};									// copy constructor

        constexpr Point3D 													// unary minus
		operator- () const {
            return (Point3D(-x, -y, -z));
        }
	
		constexpr Vector3D 													// vector joining two points
		operator- (const Point3D& p) const {
            return (Vector3D(x - p.x,y - p.y,z - p.z));
        };
		
		constexpr Point3D 													// addition of a vector
		operator+ (const Vector3D& v) const {
            return (Point3D(x + v.x, y + v.y, z + v.z));
        };
		
		constexpr Point3D 													// subtraction of a vector
		operator- (const Vector3D& v) const {
            return (Point3D(x - v.x, y - v.y, z - v.z));
        };
				
		constexpr Point3D 													// multiplication by a double on the right
		operator* (const double a) const {
            return (Point3D(x * a,y * a,z * a));
        };
		
		constexpr double														// square of distance bertween two points
		d_squared(const Point3D& p) const {
            return (	(x - p.x) * (x - p.x)
                        + 	(y - p.y) * (y - p.y)
                        +	(z - p.z) * (z - p.z) );
        };
		
		double														// distance bewteen two points
		distance(const Point3D& p) const;
};

// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a double on the left

constexpr inline Point3D
operator* (double a, const Point3D& p) {
    return p * a;
}

// non-inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a matrix on the left

constexpr Point3D
operator* (const Matrix& mat, const Point3D& p) {
    return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
                    mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
                    mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}

#endif
