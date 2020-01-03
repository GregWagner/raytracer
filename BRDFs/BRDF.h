#ifndef __BRDF__
#define __BRDF__

// This file contains the declaration of the base class BRDF

#include <cmath>

#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeRec.h"

class BRDF {
	public:
	
		BRDF();
		
		BRDF(const BRDF& object);
		
		virtual BRDF*
		clone() const = 0;
		
		~BRDF();
								
		virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, double &pdf) const;
		
		virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& wo) const;
		
			
	protected:
	
		BRDF&							
		operator= (const BRDF& rhs);
};

#endif