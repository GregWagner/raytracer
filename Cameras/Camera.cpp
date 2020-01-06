// This file contains the definition of the Camera class

#include "Camera.h"

//-------------------------------------------------------------- compute_uvw

// This computes an orthornormal basis given the view point, lookat point, and up vector

void
Camera::compute_uvw() {
	w = eye - lookat;
	w.normalize();
	u = up ^ w; 
	u.normalize();
	v = w ^ u;

	// take care of the singularity by hardwiring in specific camera orientations
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y > lookat.y) { // camera looking vertically down
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}
	
	if (eye.x == lookat.x && eye.z == lookat.z && eye.y < lookat.y) { // camera looking vertically up
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}

unsigned
Camera::max_render_threads(const World &) {
    return 1;
}


