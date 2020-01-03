#ifndef __PURE_RANDOM__
#define __PURE_RANDOM__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"

class PureRandom : public Sampler
{
public:
    PureRandom();

    virtual ~PureRandom() = default;

    PureRandom(int num);

    PureRandom(const PureRandom &r);

    PureRandom &
    operator=(const PureRandom &rhs);

    PureRandom *
    clone() const override;

private:

    void
    generate_samples() override;
};

#endif

