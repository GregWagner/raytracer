// This file contains the definition of the Pinhole class

#include "../Utilities/Constants.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"
#include "Pinhole.h"
#include <cmath>
#include <algorithm>

// ----------------------------------------------------------------------------- default constructor

Pinhole::Pinhole(void)		
	:	Camera(),
		d(500),
		zoom(1.0)
{}


// ----------------------------------------------------------------------------- copy constructor

Pinhole::Pinhole(const Pinhole& c)   		
	: 	Camera(c),
		d(c.d),
		zoom(c.zoom)
{}


// ----------------------------------------------------------------------------- clone

Camera* 
Pinhole::clone(void) const {
	return (new Pinhole(*this));
}



// ----------------------------------------------------------------------------- assignment operator

Pinhole& 
Pinhole::operator= (const Pinhole& rhs) { 	
	if (this == &rhs)
		return (*this);
		
	Camera::operator= (rhs);

	d 		= rhs.d;
	zoom	= rhs.zoom;

	return (*this);
}


// ----------------------------------------------------------------------------- destructor

Pinhole::~Pinhole(void) {}	


// ----------------------------------------------------------------------------- get_direction

Vector3D
Pinhole::get_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	
	return(dir);
}



// ----------------------------------------------------------------------------- render_scene

void 												
Pinhole::render_scene(const World &w, unsigned threadnum, unsigned threadcount) {
	RGBColor	L;
	ViewPlane	vp(w.vp);	 								
	Ray			ray;
	int 		depth = 0;  
	Point2D 	pp;		// sample point on a pixel

	vp.s /= zoom;
	ray.o = eye;

	int rs = 0;
	int re = vp.vres;
	if (threadcount > 1) {
	    re /= static_cast<int>(threadcount);
	    rs = static_cast<int>(threadnum) * re;
	    re += rs;
	    re = std::min<int>(re, vp.vres);
	}

	const Point2D vpres(vp.hres, vp.vres);

	for (int r = rs; r < re; r++)			// up
		for (int c = 0; c < vp.hres; c++) {		// across 					
			L = black;
            const Point2D cp(c,r);
			for (int p = 0; p < vp.num_samples; p++) {
			    const Point2D sp = vp.sampler_ptr->sample_unit_square();
			    pp = (cp - vpres / 2.0 + sp) * vp.s;
                ray.d = get_direction(pp);
                L += w.tracer_ptr->trace_ray(ray, depth);
            }
			L /= vp.num_samples;
			L *= exposure_time;
			w.display_pixel(r, c, L);
		} 
}

unsigned int
Pinhole::max_render_threads(const World &w) {
    return w.vp.vres;
}

