#ifndef __LIGHT__
#define __LIGHT__

#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeRec;


//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light() = default;
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light* 						
		clone() const = 0;
		
		virtual 							
		~Light() = default;
						
		virtual Vector3D								
		get_direction(ShadeRec& sr) = 0;				
																
		virtual RGBColor														
		L(ShadeRec& sr);								
};

#endif