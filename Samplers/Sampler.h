#ifndef __SAMPLER__
#define __SAMPLER__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <vector>
#include <random>
#include <cmath>
#include <climits>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"

class Sampler
{
public:
    static const unsigned int kDefaultSets = 83;

    explicit Sampler(unsigned int samples = 1, unsigned int sets = kDefaultSets);

    virtual ~Sampler() = default;

    Sampler(const Sampler &s);

    Sampler &
    operator=(const Sampler &rhs);

    virtual Sampler *
    clone() const = 0;

    void
    set_num_sets(unsigned int np);

    virtual void                            // generate sample patterns in a unit square
    generate_samples() = 0;

    int
    get_num_samples();

    void
    shuffle_x_coordinates();

    void
    shuffle_y_coordinates();

    void
    setup_shuffled_indices();

    void
    map_samples_to_unit_disk();

    void
    map_samples_to_hemisphere(float p);

    void
    map_samples_to_sphere();


    // the following functions are not const because they change count and jump

    Point2D                                            // get next sample on unit square
    sample_unit_square();

    Point2D                                            // get next sample on unit disk
    sample_unit_disk();

    Point3D                                            // get next sample on unit hemisphere
    sample_hemisphere();

    Point3D                                            // get next sample on unit sphere
    sample_sphere();

    Point2D                                            // only used to set up a vector noise table
    sample_one_set();                            // this is not discussed in the book, but see the
    // file LatticeNoise.cpp in Chapter 31


protected:
    // --- RNG Utility Functions ---


    float                                           // for multi-jittered sampling
    rand_float(float l, float h)
    {
        std::uniform_real_distribution<float> dist(l, h);
        return dist(_rng);
    }

    int                                                     // for multi-jittered sampling
    rand_int(int l, int h)
    {
        std::uniform_int_distribution<int> dist(l, h);
        return dist(_rng);
    }

    int rand_int()
    {
        return rand_int(0, RAND_MAX);
    }

    float rand_float()
    {
        return rand_float(0.0f, 1.0f);
    }

    unsigned int num_samples;            // the number of sample points in a set
    unsigned int num_sets;                // the number of sample sets
    std::vector<Point2D> samples;                // sample points on a unit square
    std::vector<int> shuffled_indices;        // shuffled samples array indices
    std::vector<Point2D> disk_samples;            // sample points on a unit disk
    std::vector<Point3D> hemisphere_samples;        // sample points on a unit hemisphere
    std::vector<Point3D> sphere_samples;            // sample points on a unit sphere
    unsigned long count;                    // the current number of sample points used
    unsigned int jump;                    // random index jump

private:
    static std::random_device _rd;
    std::mt19937 _rng;
};

#endif

