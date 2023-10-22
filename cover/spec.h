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
#include <cstdio>

namespace wavreader {

class spec_base;

typedef std::shared_ptr<spec_base>	spec_ptr;

class spec_base {
public:
	virtual double	operator()(unsigned int i) const = 0;
	virtual double	f(unsigned int i) const = 0;
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
	int	spectrumsize = n/2 + 1;
	double	values[n/2 + 1];
	double	lb;
public:
	spec(chunk_ptr cp, int initialoffset, int channels, int channel) {
		lb = log2(n/2);
		// read sound data
		for (int i = 0; i < n; i++) {
			frame f = cp->getFrame(initialoffset + i, channels);
			data[i] = f[channel];
			//std::cout << "[" << i << "] " << data[i] << std::endl;
		}

		// perform spectral analysis
		{
			double	in[n];
			fftw_plan	p = fftw_plan_r2r_1d(n, in, spectrum,
						FFTW_R2HC, FFTW_MEASURE);
			memcpy(in, data, sizeof(double) * n);
			fftw_execute(p);
			fftw_destroy_plan(p);
			//std::cout << "FFT complete" << std::endl;
		}

		// compute values
		values[0] = fabs(spectrum[0]);
		for (unsigned int i = 0; i < n / 2; i++) {
			values[i] = hypot(spectrum[i], spectrum[n-i]);
		}
		values[n/2] = fabs(spectrum[n / 2 + 1]);
	}
	virtual ~spec() { }

	double	operator()(unsigned int i) const {
		return values[i];
	}

	static double	expindex(unsigned int i) {
		return (n/2) * exp(5 * ((i / (double)(n/2 + 1)) - 1));
	}

	double	f(unsigned int i) const {
		if (i == 0) {
			return values[0];
		}
		//int	j = floor((n/2) * log2(i) / lb);
		double	t = expindex(i);
		int	j = floor(t);
//printf("%d,%d\n", i, j);
		if (t >= n/2+1) {
printf("%d,%f\n", i, t);
		//	throw std::runtime_error("j exceeds bounds");
		}
		if (t < 0) {
			return 0;
		} 
		double	T = t - floor(t);
		
		return (1-T) * values[j] + T * values[j+1];
	}
};

} // namespace wavreader

#endif /* _spec_h */
