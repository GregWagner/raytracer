#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"

class MultiJittered : public Sampler
{
public:
    explicit MultiJittered(const int num_samples = 1, const int m = kDefaultSets);

    MultiJittered(const MultiJittered &mjs);

    MultiJittered &
    operator=(const MultiJittered &rhs);

    MultiJittered *
    clone() const override;

private:
    void
    generate_samples() override;
};

#endif

