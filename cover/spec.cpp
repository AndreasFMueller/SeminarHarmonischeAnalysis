/*
 * spec.cpp -- spectrum analysis component
 *
 * (c) 2023 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#include "spec.h"
#include <fftw3.h>

namespace wavreader {

spec_ptr	spec_base::get(chunk_ptr cp, int size, int initialoffset,
			int channels, int channel) {
	switch (size) {
	case 1024:
		return spec_ptr(new spec<1024>(cp, initialoffset,
			channels, channel));
		break;
	case 2048:
		return spec_ptr(new spec<2048>(cp, initialoffset,
			channels, channel));
		break;
	case 4096:
		return spec_ptr(new spec<4096>(cp, initialoffset,
			channels, channel));
		break;
	case 8192:
		return spec_ptr(new spec<8192>(cp, initialoffset,
			channels, channel));
		break;
	default:
		throw std::runtime_error("cannot create spec of this size");
	}
}

} // namespace wavreader
