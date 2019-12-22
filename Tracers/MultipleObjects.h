#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

class MultipleObjects: public Tracer {
	public:
		
		MultipleObjects();
		
		explicit MultipleObjects(World* _world_ptr);

		RGBColor
		trace_ray(const Ray& ray) const override;
};

#endif
