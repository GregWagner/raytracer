#ifndef __REGULAR__
#define __REGULAR__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Sampler.h"

class Regular : public Sampler
{
public:
    explicit Regular(int num = 1);

    virtual ~Regular() = default;

    Regular(const Regular &u);

    Regular &
    operator=(const Regular &rhs);

    Regular *
    clone() const override;

    void
    generate_samples() override;
};

#endif

