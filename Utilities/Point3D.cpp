// this file contains the definition of the class Point3D

#include <cmath>
#include "Point3D.h"

// --------------------------------------------- distance
// distance between two points

double
Point3D::distance(const Point3D& p) const {
    return (sqrt(d_squared(p)));
}
