#ifndef __PINHOLE__
#define __PINHOLE__

// This file contains the declaration of the class Pinhole

#include "../Utilities/Point2D.h"
#include "../World/World.h"    // we can #include "World.h" here

//--------------------------------------------------------------------- class Pinhole

class Pinhole: public Camera {
	public:
	
		Pinhole();   							

		Pinhole(const Pinhole& ph);	
		
		Camera*
		clone() const override;

		Pinhole& 							
		operator= (const Pinhole& rhs);	
		
		virtual
		~Pinhole();   						
			
		void
		set_view_distance(const double vpd);
		
		void
		set_zoom(const double zoom_factor);
		
		Vector3D								
		get_direction(const Point2D& p) const;
		
		void
		render_scene(const World &w, unsigned threadnum, unsigned threadcount) override;

        unsigned int max_render_threads(const World &w) override;

private:
			
		double	d;		// view plane distance
		double	zoom;	// zoom factor
		
};




//-------------------------------------------------------------------------- set_vpd

inline void
Pinhole::set_view_distance(const double vpd) {
	d = vpd;
}	
	


//-------------------------------------------------------------------------- set_zoom

inline void
Pinhole::set_zoom(const double zoom_factor) {
	zoom = zoom_factor;
}

#endif