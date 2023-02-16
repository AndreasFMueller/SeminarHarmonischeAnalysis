/*
 * spec.h -- spectrum analysis component
 *
 * (c) 2023 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#ifndef _spec_h
#define _spec_h

#include "wav.h"
#include <fftw3.h>
#include <cmath>

namespace wavreader {

class spec_base;

typedef std::shared_ptr<spec_base>	spec_ptr;

class spec_base {
public:
	virtual double	operator()(int i) const = 0;
	static spec_ptr	get(chunk_ptr cp, int size, int initialoffset,
		int channels, int channel);
	virtual ~spec_base() { }
};

/**
 * \brief spectrum class 
 */
template<int n>
class spec : public spec_base {
	double	data[n];
	double	spectrum[n];
public:
	spec(chunk_ptr cp, int initialoffset, int channels, int channel) {
		// read sound data
		for (int i = 0; i < n; i++) {
			frame f = cp->getFrame(initialoffset + i, channels);
			data[i] = f[channel];
			//std::cout << "[" << i << "] " << data[i] << std::endl;
		}

		// perform spectral analysis
		{
			double	in[n];
			memcpy(in, data, sizeof(double) * n);
			fftw_plan	p = fftw_plan_r2r_1d(n, in, spectrum,
						FFTW_R2HC, FFTW_MEASURE);
			fftw_execute(p);
			fftw_destroy_plan(p);
			//std::cout << "FFT complete" << std::endl;
		}
	}
	virtual ~spec() { }

	double	operator()(int i) const {
		if (i == 0) {
			return spectrum[0];
		}
		return hypot(spectrum[i], spectrum[n-i]);
	}
};

} // namespace wavreader

#endif /* _spec_h */
