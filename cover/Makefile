#
# Makefile -- build the book cover
#
# (c) 2018 Prof Dr Andreas Müller, Hochschule Rapperswil
#
all:	buchcover.jpg backcover.jpg front.pdf back.pdf lncover.png

buchcover.pdf:	buchcover.tex 
	pdflatex buchcover.tex

buchcover.png:	buchcover.pdf  Makefile
	convert -density 300 -extract 2054x2900+2630+190 buchcover.pdf \
		buchcover.png
buchcover.jpg:	buchcover.png
	convert buchcover.png buchcover.jpg
buchcover-small.jpg:	buchcover.jpg
	convert buchcover.jpg -scale 50% buchcover-small.jpg
backcover.png:	buchcover.pdf Makefile
	convert -density 300 -extract 2054x2900+192+190 buchcover.pdf \
		backcover.png
backcover.jpg:	backcover.png
	convert backcover.png backcover.jpg

front.pdf:	front.tex buchcover.pdf
	pdflatex front.tex

back.pdf:	back.tex buchcover.pdf
	pdflatex back.tex

lncover.pdf:	lncover.tex
	pdflatex lncover.tex
lncover.png:	lncover.pdf Makefile
	convert -density 300 -extract 2007x2834+0+0 lncover.pdf \
		lncover.png

libwavspec.a:	wav.o spec.o
	ar -r libwavspec.a wav.o
wav.o:	wav.cpp wav.h 
	g++ -std=c++11 -o wav.o -O -Wall -g -c wav.cpp
spec.o:	spec.cpp spec.h wav.h
	g++ -std=c++11 -o spec.o -O -Wall -g -c spec.cpp

wavreader:	wavreader.cpp libwavspec.a spec.h
	g++ -std=c++11 -o wavreader -O -Wall -g wavreader.cpp \
		-L. -lwavspec `pkg-config --libs fftw3` \
		`pkg-config --libs cfitsio`
test:	wavreader
	rm -f brahms.fits
	./wavreader -d -f brahms.fits brahms.wav
