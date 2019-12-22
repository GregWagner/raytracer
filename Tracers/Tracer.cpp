#include "Tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer()
	: world_ptr(nullptr)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}



// -------------------------------------------------------------------- destructor

Tracer::~Tracer() {
	if (world_ptr)
		world_ptr = nullptr;
}


// -------------------------------------------------------------------- trace_ray

RGBColor	
Tracer::trace_ray(const Ray& ray) const {
	return (black);
}


// -------------------------------------------------------------------- trace_ray

RGBColor	
Tracer::trace_ray(const Ray& ray, const int depth) const {
	return trace_ray(ray);
}



