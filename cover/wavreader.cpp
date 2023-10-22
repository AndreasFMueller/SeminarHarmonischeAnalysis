/*
 * wavreader.cpp
 *
 * (c) 2023 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <getopt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fcntl.h>
#include <fitsio.h>
#include "wav.h"
#include "spec.h"

namespace wavreader {

int	wav_debug = 0;

static void	usage(const char *progname) {
	std::cout << "usage:" << std::endl << std::endl;
	std::cout << "    " << progname;
	std::cout << " [ options ] [ -f <image.fits> ] sound.wav";
	std::cout << std::endl << std::endl;
	std::cout << "options:" << std::endl;
	std::cout << "  -d,--debug             run in debug mode" << std::endl;
	std::cout << "  -n,--length            block length for FFT" << std::endl;
	std::cout << "  -h,-?,--help           display some help" << std::endl;
	std::cout << "  -f,--fits=image.fits   write image to file image.fits";
	std::cout << "  -l,--limit=<lim>       limit samples to this value"
		<< std::endl;
	std::cout << "  -L,--log               take logarithm values" << std::endl;
	std::cout << "  -o,--octaves           logarithmically map the frequency scale" << std::endl;
	std::cout << "  -s,--step=<s>          use steps of size s instead of N" << std::endl;
	std::cout << std::endl;
}

static struct option	options[] = {
{ "color",		no_argument,			NULL,	'c' },
{ "debug",		no_argument,			NULL,	'd' },
{ "fits",		required_argument,		NULL,	'f' },
{ "help",		no_argument,			NULL,	'h' },
{ "limit",		required_argument,		NULL,	'l' },
{ "log",		no_argument,			NULL,	'L' },
{ "length",		required_argument,		NULL,	'n' },
{ "octaves",		no_argument,			NULL,	'o' },
{ "step",		required_argument,		NULL,	's' },
{ NULL,			0,				NULL,	 0  }
};

class color {
public:
	float	rgb[3];
	color() {
		rgb[0] = rgb[1] = rgb[2] = 0;
	}
	color(float r, float g, float b) {
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
	}
	color(const color& other) {
		for (int i = 0; i < 3; i++) {
			rgb[i] = other.rgb[i];
		}
	}
	color	operator*(float t) {
		return color(t * rgb[0], t * rgb[1], t * rgb[2]);
	}
	color	operator+(const color& other) {
		return color(	rgb[0] + other.rgb[0],
				rgb[1] + other.rgb[1],
				rgb[2] + other.rgb[2]);
	}
	float	R() const { return rgb[0]; }
	float	G() const { return rgb[1]; }
	float	B() const { return rgb[2]; }
};

typedef struct { float top; color farbe; } colorpoint;

class colormap {
	static int	n;
	static colorpoint	points[6];
public:
	static color	get(double value) {
		if (value <= points[0].top) {
			return points[0].farbe;
		}
		for (int i = 0; i < n; i++) {
			if ((value > points[i].top)
				&& (value <= points[i+1].top)) {
				float	d = points[i+1].top - points[i].top;
				float	t = (value - points[i].top) / d;
				return (points[i].farbe * (1-t))
					+ (points[i+1].farbe * t);
			}
		}
		if (value > points[n-1].top) {
			return points[n-1].farbe;
		}
		throw std::runtime_error("color not found");
	}
};

int 	colormap::n = 6;
colorpoint	colormap::points[6] = {
#if 0
	{ 0.0, color(0.0, 0.0, 0.8) },
	{ 0.1, color(0.6, 0.0, 0.6) },
	{ 0.2, color(0.8, 0.0, 0.8) },
	{ 0.3, color(1.0, 0.0, 0.2) },
	{ 0.4, color(1.0, 0.8, 0.0) },
	{ 1.0, color(1.0, 1.0, 1.0) }
#endif
	{ 0.0, color(0.0, 0.0, 1.0) },
	{ 0.1, color(0.6, 0.2, 1.0) },
	{ 0.2, color(0.8, 0.0, 0.4) },
	{ 0.3, color(0.8, 0.0, 0.0) },
	{ 0.4, color(1.0, 0.2, 0.0) },
	{ 1.0, color(1.0, 0.8, 0.0) }
};

/**
 * \brief Main function for the wavreader
 */
int	main(int argc, char *argv[]) {
	std::string	fitsfilename;
	std::string	wavfilename;
	double	limit = 0;
	int	N = 8192;
	int	stepsize = 512;
	bool	logarithmic = false;
	bool	octaves = false;
	bool	use_color = false;

	// parse the command line
	int	c;
	int	longindex;
	while (EOF != (c = getopt_long(argc, argv, "cf:dh?l:Los:",
			options, &longindex)))
		switch (c) {
		case 'f':
			fitsfilename = std::string(optarg);
			break;
		case 'd':
			wav_debug = 1;
			break;
		case 'h':
		case '?':
			usage(argv[0]);
			return EXIT_SUCCESS;
			break;
		case 'l':
			limit = std::stod(optarg);
			break;
		case 'L':
			logarithmic = true;
			break;
		case 'n':
			N = std::stoi(optarg);
			break;
		case 's':
			stepsize = std::stoi(optarg);
			break;
		case 'o':
			octaves = true;
			break;
		case 'c':
			use_color = true;
			break;
		}
	
	// get the wav file name, must be next argument
	if (optind >= argc) {
		std::cerr << "no wav file specified" << std::endl;
		return EXIT_FAILURE;
	}
	wavfilename = std::string(argv[optind++]);

	// open the file
	wav	w(wavfilename);
	chunk_ptr	cp = w.current();

	// create a FITS data structure
	int	blocksize = N;
	int	spectrumsize = blocksize / 2 + 1;
	std::cout << "spectrum size: " << spectrumsize << std::endl;
	int	nblocks = cp->length() / (4 * stepsize);
	std::cout << "blocks: " << nblocks << std::endl;
	long	fpixel = 1;
	long	naxis = (use_color) ? 3 : 2;
	long	naxes[3] = { nblocks, spectrumsize, 3 };
	long	pixels = nblocks * spectrumsize;
	long	nelements = pixels * ((use_color) ? 3 : 1);
	std::cout << "creating buffer with " << nelements << " elements";
	std::cout << std::endl;
	float	*imagedata = new float[nelements];
	fitsfile	*fitsptr;
	std::cout << "creating fits file" << std::endl;

	int	status = 0;
	fits_create_file(&fitsptr, fitsfilename.c_str(), &status);
	fits_report_error(stderr, status);
	fits_create_img(fitsptr, FLOAT_IMG, naxis, naxes, &status);
	fits_report_error(stderr, status);

	std::cout << "writing image data" << std::endl;
	for (int block = 0; block < nblocks - 100; block++) {
		int	offset = block * stepsize;
		spec_ptr	s = spec_base::get(cp, N, offset, 2, 0);
		// process the spectrum
		double	v;
		for (int i = 0; i < spectrumsize; i++) {
			if (octaves) {
				v = fabs(s->f(i));
			} else {
				v = fabs(s->operator()(i));
			}
			//std::cout << v << std::endl;
			//std::cout << block * spectrumsize + i << std::endl;
			if (limit > 0) {
				v = (v > limit) ? limit : v;
			}
			if (logarithmic) {
				if (v > 1) {
					v = log(v);
				} else {
					v = 0;
				}
			}
			if (use_color) {
				color	c = colormap::get(v / limit);
				int	offset = block + nblocks * i;
				imagedata[offset] = c.R();
				imagedata[offset + pixels] = c.G();
				imagedata[offset + 2 * pixels] = c.B();
			} else {
				imagedata[block + nblocks * i] = v;
			}
		}
		offset += stepsize;
	}
	fits_write_img(fitsptr, TFLOAT, fpixel, nelements, imagedata, &status);
	fits_report_error(stderr, status);
	fits_close_file(fitsptr, &status);
	fits_report_error(stderr, status);

	delete[] imagedata;
	
	return EXIT_SUCCESS;
}

} // namespace wavreader

int	main(int argc, char *argv[]) {
	try {
		return wavreader::main(argc, argv);
	} catch (const std::exception& ex) {
		std::cerr << "exception: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
