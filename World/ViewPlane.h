#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

//-------------------------------------------------------------------------------------- class ViewPlane

class Sampler;

class ViewPlane {
	public:
		int 			hres;   					// horizontal image resolution 
		int 			vres;   					// vertical image resolution
		double			s;							// pixel size
		int				num_samples;				// number of samples per pixel
		
		double			gamma;						// gamma correction factor
		double			inv_gamma;					// the inverse of the gamma correction factor
		bool			show_out_of_gamut;			// display red if RGBColor out of gamut

		Sampler *       sampler_ptr;
									
	
	public:
	
		ViewPlane();   								// default Constructor
				
		ViewPlane(const ViewPlane& vp);				// copy constructor

		ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator
		
		~ViewPlane();   							// destructor
						
		void 													
		set_hres(const int h_res);
		
		void 													
		set_vres(const int v_res);
				
		void
		set_pixel_size(const double size);
		
		void
		set_gamma(const double g);
		
		void
		set_gamut_display(const bool show);	
		
		void
		set_samples(const int n);

		void
		set_sampler(Sampler* sp);
};




// ------------------------------------------------------------------------------ set_hres

inline void 													
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}


// ------------------------------------------------------------------------------ set_vres

inline void 													
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}


// ------------------------------------------------------------------------------ set_pixel_size

inline void 													
ViewPlane::set_pixel_size(const double size) {
	s = size;
}


// ------------------------------------------------------------------------------ set_gamma

inline void
ViewPlane::set_gamma(const double g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}


// ------------------------------------------------------------------------------ set_gamut_display

inline void
ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}



#endif