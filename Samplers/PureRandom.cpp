// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "PureRandom.h"

// ---------------------------------------------------------------- default constructor

PureRandom::PureRandom()
    : Sampler()
{}


// ---------------------------------------------------------------- constructor

PureRandom::PureRandom(const int num)
    : Sampler(num)
{
    PureRandom::generate_samples();
}


// ---------------------------------------------------------------- constructor

PureRandom::PureRandom(const PureRandom &r)
    : Sampler(r)
{
    PureRandom::generate_samples();
}

// ---------------------------------------------------------------- assignment operator

PureRandom &
PureRandom::operator=(const PureRandom &rhs)
{
    if (this == &rhs) {
        return (*this);
    }

    Sampler::operator=(rhs);

    return (*this);
}

// ---------------------------------------------------------------- clone

PureRandom *
PureRandom::clone() const
{
    return (new PureRandom(*this));
}

// ---------------------------------------------------------------- generate_samples

void
PureRandom::generate_samples()
{
    for (int p = 0; p < num_sets; p++) {
        for (int q = 0; q < num_samples; q++) {
            samples.emplace_back(rand_float(), rand_float());
        }
    }
}


