#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "../BRDFs/Lambertian.h"

//----------------------------------------------------------------------------- class Matte

class Matte: public Material {	
	public:
			
		Matte();

		Matte(const Matte& m);
		
		Material*
		clone() const override;

		Matte& 
		operator= (const Matte& rhs);							

		~Matte();
		
		void 													
		set_ka(const double k);
		
		void 													
		set_kd(const double k);
		
		void													
		set_cd(const RGBColor c);
		
		void													
		set_cd(const double r, const double g, const double b);
		
		void																						
		set_cd(const double c);
				
		RGBColor
		shade(ShadeRec& sr) override;
		
	private:
		
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Matte::set_ka(const double k) {
	ambient_brdf->set_kd(k);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Matte::set_kd (const double k) {
	diffuse_brdf->set_kd(k);
}


// ---------------------------------------------------------------- set_cd

inline void												
Matte::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
Matte::set_cd(const double r, const double g, const double b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Matte::set_cd(const double c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

#endif