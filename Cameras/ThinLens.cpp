//
// Created by chris on 6/01/2020.
//

#include "ThinLens.h"
#include "../Utilities/Constants.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../World/ViewPlane.h"
#include "../World/World.h"

void ThinLens::render_scene(const World &w, unsigned int threadnum, unsigned int threadcount) {
    RGBColor	L;
    Ray			ray;
    ViewPlane	vp(w.vp);
    int 		depth = 0;

    Point2D sp; // sample point in the unit square
    Point2D pp; // sample point on a pixel
    Point2D dp; // unit disc...
    Point2D lp; // on lens.

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

    const Point2D vpSize(vp.hres, vp.vres);

    for (int r = rs; r < re; r++)			// up
        for (int c = 0; c < vp.hres; c++) {		// across
            Point2D cPos(c,r);
            L = black;

            for (int n = 0; n < vp.num_samples; n++) {
                sp = vp.sampler_ptr->sample_unit_square();
                pp = (cPos - vpSize / 2.0 + sp) * vp.s;

                dp = sampler_ptr->sample_unit_disk();
                lp = dp * lens_radius;

                ray.o = eye + lp.x * u + lp.y * v;
                ray.d = ray_direction(pp, lp);
                L += w.tracer_ptr->trace_ray(ray, depth);
            }
            L /= vp.num_samples;
            L *= exposure_time;
            w.display_pixel(r, c, L);
        }

}

unsigned int ThinLens::max_render_threads(const World &w) {
    return w.vp.vres;
}
