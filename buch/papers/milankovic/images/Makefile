#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	exzentrizitaet.pdf strahlung.pdf

exzentrizitaet.pdf:	exzentrizitaet.tex
	pdflatex exzentrizitaet.tex

strahlung.pdf:	strahlung.tex ex.tex
	pdflatex strahlung.tex

ex.tex:	ex.m
	octave ex.m
