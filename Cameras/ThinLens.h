//
// Created by chris on 6/01/2020.
//

#ifndef RAYTRACER_THINLENS_H
#define RAYTRACER_THINLENS_H

#include "Camera.h"
#include "../Samplers/Sampler.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Vector3D.h"

class ThinLens : public Camera {
public:
    constexpr ThinLens()
            : Camera(),
              lens_radius(1.0),
              d(500.0),
              f(750.0),
              zoom(1.0),
              sampler_ptr(nullptr) {}
    ThinLens(const ThinLens &cpySource) = default;

    void set_sampler(Sampler *sp) {
        if (sampler_ptr) {
            delete sampler_ptr;
            sampler_ptr = nullptr;
        }
        sampler_ptr = sp;
        if (sampler_ptr) {
            sampler_ptr->map_samples_to_unit_disk();
        }
    }

    Vector3D ray_direction(const Point2D &pixel_point, const Point2D &lens_point) const {
        Point2D p = pixel_point * f / d;
        Point2D lp = p - lens_point;
        Vector3D dir = lp.x * u + lp.y * v - f * w;
        dir.normalize();
        return dir;
    };

    void
    render_scene(const World &w, unsigned int threadnum, unsigned int threadcount) override;

    unsigned int max_render_threads(const World &w) override;

    ThinLens *clone() const override {
        return new ThinLens(*this);
    }

    void
    set_view_distance(const double vpd) {
        d = vpd;
    }

    void
    set_zoom(const double zoom_factor) {
        zoom = zoom_factor;
    }

    void
    set_focal_distance(const double fpd) {
        f = fpd;
    }

    void
    set_lens_radius(const double radius) {
        lens_radius = radius;
    }

protected:
    double lens_radius;
    double d;
    double f;
    double zoom;
    Sampler *sampler_ptr;
};


#endif //RAYTRACER_THINLENS_H
