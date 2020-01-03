#ifndef __RGB_COLOR__
#define __RGB_COLOR__

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {
	
	public:
	
		double	r, g, b;
				
	public:
	
		constexpr RGBColor(): r(0.0), g(0.0), b(0.0) {};										// default constructor
        constexpr RGBColor(double c): r(c), g(c), b(c) {};									// constructor
        constexpr RGBColor(double _r, double _g, double _b): r(_r), g(_g), b(_b) {};				// constructor
		constexpr RGBColor(const RGBColor& c)			    // copy constructor
		    : r(c.r), g(c.g), b(c.b) {}

		RGBColor& 											// assignment operator
		operator= (const RGBColor& rhs); 

		constexpr RGBColor 									// addition
		operator+ (const RGBColor& c) const;	

		RGBColor& 											// compound addition
		operator+= (const RGBColor& c);
		
		constexpr RGBColor 											// multiplication by a float on the right
		operator* (const double a) const;
		
		RGBColor& 											// compound multiplication by a float on the right
		operator*= (const double a);
				
		constexpr RGBColor 											// division by a float
		operator/ (const double a) const;
		
		RGBColor& 											// compound division by a float
		operator/= (const double a);
				
		constexpr RGBColor 									// component-wise multiplication
		operator* (const RGBColor& c) const;

		constexpr bool										// are two RGBColours the same?
		operator== (const RGBColor& c) const;				

		RGBColor											// raise components to a power
		powc(double p) const;
		
		constexpr double									// the average of the components
		average() const;
};



// inlined member functions

// ----------------------------------------------------------------------- operator+
// addition of two colors

constexpr RGBColor
RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) {
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

constexpr RGBColor
RGBColor::operator* (const double a) const {
	return (RGBColor (r * a, g * a, b * a));	
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline RGBColor& 
RGBColor::operator*= (const double a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

constexpr RGBColor
RGBColor::operator/ (const double a) const {
	return (RGBColor (r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline RGBColor& 
RGBColor::operator/= (const double a) {
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

constexpr RGBColor
RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor (r * c.r, g * c.g, b * c.b));
} 


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

constexpr bool
RGBColor::operator== (const RGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}


// ----------------------------------------------------------------------- average
// the average of the three components

constexpr double
RGBColor::average() const {
	return (0.333333333333 * (r + g + b));
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

constexpr RGBColor
operator* (const double a, const RGBColor& c) {
	return (RGBColor (a * c.r, a * c.g, a * c.b));	
}


#endif
