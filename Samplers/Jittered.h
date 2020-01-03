#ifndef __JITTERED__
#define __JITTERED__


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Sampler.h"

class Jittered: public Sampler {
	public:
		
		Jittered();

		virtual ~Jittered() = default;
		
		explicit Jittered(int num_samples, int m = kDefaultSets);

		Jittered(const Jittered& u);					

		Jittered& 
		operator= (const Jittered& rhs);				

		Jittered*
		clone() const override;

	private:
		
		void
		generate_samples() override;
};

#endif

