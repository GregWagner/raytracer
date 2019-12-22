#ifndef __RAY_CAST__
#define __RAY_CAST__

#include "Tracer.h"

class RayCast: public Tracer {
	public:
		
		RayCast();
		
		explicit RayCast(World* _worldPtr);
				
    	RGBColor
		trace_ray(const Ray& ray) const override;
};

#endif