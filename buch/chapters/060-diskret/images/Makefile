#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	f23.pdf f32.pdf f30.pdf traeger.pdf etraeger.pdf permutation.pdf

f23.pdf:	f23.tex fcommon.tex
	pdflatex f23.tex

f32.pdf:	f32.tex fcommon.tex
	pdflatex f32.tex

f30.pdf:	f30.tex
	pdflatex f30.tex

traeger.pdf:	traeger.tex
	pdflatex traeger.tex

etraeger.pdf:	etraeger.tex etraegerpath.tex
	pdflatex etraeger.tex

etraegerpath.tex:	etraeger.m
	octave etraeger.m

permutation.pdf:	permutation.tex
	pdflatex permutation.tex

