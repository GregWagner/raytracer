
#ifndef __NORMAL__
#define __NORMAL__

// This file contains the declaration of the class Normal

#include "Matrix.h"
#include "Vector3D.h"
#include "Point3D.h"

class Normal 
{	
	public:
	
		double	x, y, z;
				
	public:
	
		constexpr Normal(): x(0.0), y(0.0), z(0.0) {};	    // default constructor
		explicit constexpr Normal(double a): x(a), y(a), z(a) {}; // constructor
		constexpr Normal(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}; // constructor
		constexpr Normal(const Normal& n): x(n.x), y(n.y), z(n.z) {}; // copy constructor
		explicit Normal(const Vector3D& v);					// constructs a normal from vector

		Normal& 											// assignment of a vector to a normal
		operator= (const Vector3D& rhs);

		Normal& 											// assignment of a point to a normal
		operator= (const Point3D& rhs);
		
		constexpr Normal									// unary minus
		operator- () const {
            return (Normal(-x, -y, -z));
		}
		
		constexpr Normal 												// addition
		operator+ (const Normal& n) const {
            return (Normal(x + n.x, y + n.y, z + n.z));
        }
		
		Normal& 											// compound addition
		operator+= (const Normal& n);
		
		constexpr double                                    // dot product with a vector on the right
		operator* (const Vector3D& v) const {
            return (x * v.x + y * v.y + z * v.z);
        }
		
		constexpr Normal 			    					// multiplication by a double on the right
		operator* (const double a) const {
            return (Normal(x * a, y * a, z * a));
        }

		void 												// convert normal to a unit normal
		normalize();
};





// inlined member functions

// ----------------------------------------------------------------------- addition
// compound addition of two normals

inline Normal& 
Normal::operator+= (const Normal& n) {
	x += n.x; y += n.y; z += n.z;
    return (*this);
}

// inlined non-member functions

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

constexpr inline Normal
operator*(const double f, const Normal& n) {
    return n * f;
}

// ----------------------------------------------------------------------- operator+
// addition of a vector on the left to return a vector 

constexpr Vector3D
operator+ (const Vector3D& v, const Normal& n) {	
	return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}	

// ----------------------------------------------------------------------- operator-
// subtraction of a normal from a vector to return a vector

constexpr Vector3D
operator- (const Vector3D& v, const Normal& n) {
	return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}


// ----------------------------------------------------------------------- operator*
// dot product of a vector on the left and a normal on the right

constexpr double
operator* (const Vector3D& v, const Normal& n) {
	return (v.x * n.x + v.y * n.y + v.z * n.z);     
}



// non-inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left

constexpr Normal
operator* (const Matrix& mat, const Normal& n) {
    return (Normal(	mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
                       mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
                       mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));
}


#endif


