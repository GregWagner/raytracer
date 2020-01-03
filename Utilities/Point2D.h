#ifndef __POINT_2D__
#define __POINT_2D__

class Point2D {	
	public:
		double	x, y;
				
	public:
	
		constexpr Point2D(): x(0.0), y(0.0) {};
		explicit constexpr Point2D(double arg): x(arg), y(arg) {};	// constructor
		constexpr Point2D (double x1, double y1): x(x1), y(y1) {};	// constructor
		constexpr Point2D (const Point2D& p): x(p.x), y(p.y) {};	// copy constructor

		Point2D& 											// assignment operator
		operator= (const Point2D& rhs) {
			if (this == &rhs)
				return (*this);

			x = rhs.x;
			y = rhs.y;

			return (*this);
		};
		
		constexpr Point2D												// multiplication on right by scalar
		operator* (const double a) const;
};


// scales the point by the float a

constexpr Point2D
Point2D::operator* (const double a) const {
	return (Point2D(a * x, a * y));
}


#endif


