#ifndef __HAMMERSLEY__
#define __HAMMERSLEY__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"

class Hammersley : public Sampler {
public:
    Hammersley(unsigned int num = 1, unsigned int sets = kDefaultSets);

    virtual ~Hammersley() = default;

    Hammersley(const Hammersley &r);

    Hammersley &
    operator=(const Hammersley &rhs);

    Hammersley *
    clone() const override;

    double
    phi(int j);

private:

    void
    generate_samples() override;
};

#endif

