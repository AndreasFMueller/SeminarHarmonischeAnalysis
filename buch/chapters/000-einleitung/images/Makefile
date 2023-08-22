#
# Makeifle -- build images for chapter 1
#
# (c) 2019 Prof Dr Andreas Müller, Hochschule Rapperswil
#
all:	sinsin.pdf	\
	sincos.pdf	\
	sinrect.pdf	\
	cosrect.pdf	\
	sinrand.pdf	\
	randrand.pdf

sinsin.pdf:	sinsin.tex sinpoints.tex
	pdflatex sinsin.tex

sincos.pdf:	sincos.tex cospoints.tex
	pdflatex sincos.tex

sinrect.pdf:	sinrect.tex rectpoints.tex
	pdflatex sinrect.tex

cosrect.pdf:	cosrect.tex rcospoints.tex
	pdflatex cosrect.tex

sinrand.pdf:	sinrand.tex randpoints.tex
	pdflatex sinrand.tex

randrand.pdf:	randrand.tex randpoints.tex
	pdflatex randrand.tex

pointfiles = 		\
	sinpoints.tex	\
	cospoints.tex	\
	randpoints.tex	\
	rectpoints.tex	\
	rcospoints.tex

$(pointfiles):	points.m
	octave points.m

