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

#define N 2048

static void	usage(const char *progname) {
	std::cout << "usage:" << std::endl << std::endl;
	std::cout << "    " << progname;
	std::cout << " [ options ] [ -f <image.fits> ] sound.wav";
	std::cout << std::endl << std::endl;
	std::cout << "options:" << std::endl;
	std::cout << "  -d,--debug             run in debug mode" << std::endl;
	std::cout << "  -h,-?,--help           display some help" << std::endl;
	std::cout << "  -f,--fits=image.fits   write image to file image.fits";
	std::cout << std::endl;
}

static struct option	options[] = {
{ "debug",		no_argument,			NULL,	'd' },
{ "fits",		required_argument,		NULL,	'f' },
{ "help",		no_argument,			NULL,	'h' },
{ NULL,			0,				NULL,	 0  }
};

/**
 * \brief Main function for the wavreader
 */
int	main(int argc, char *argv[]) {
	std::string	fitsfilename;
	std::string	wavfilename;

	// parse the command line
	int	c;
	int	longindex;
	while (EOF != (c = getopt_long(argc, argv, "f:dh?",
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
	double	limit = 10000;
	int	blocksize = N;
	int	stepsize = N / 4;
	int	spectrumsize = blocksize / 2 + 1;
	std::cout << "spectrum size: " << spectrumsize << std::endl;
	int	nblocks = cp->length() / (4 * stepsize);
	std::cout << "blocks: " << nblocks << std::endl;
	long	fpixel = 1;
	long	naxis = 2;
	long	naxes[2] = { nblocks, spectrumsize };
	long	nelements = naxes[0] * naxes[1];
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
	for (int block = 0; block < nblocks; block++) {
		int	offset = block * stepsize;
		spec<N>	s(cp, offset, 2, 0);
		// process the spectrum
		for (int i = 0; i < spectrumsize; i++) {
			double	v = fabs(s(i));
			//std::cout << v << std::endl;
			//std::cout << block * spectrumsize + i << std::endl;
			imagedata[block + nblocks * i]
				= (v > limit) ? limit : v;
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
