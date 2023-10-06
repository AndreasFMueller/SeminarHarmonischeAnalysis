#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	f23.pdf f32.pdf f30.pdf traeger.pdf etraeger.pdf permutation.pdf f16.pdf f4.pdf f8.pdf log.pdf zeitgl.pdf faktoren.pdf

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

f16.pdf:	f16.tex f8common.tex
	pdflatex f16.tex

f4.pdf:	f4.tex
	pdflatex f4.tex

f8.pdf:	f8.tex f8common.tex
	pdflatex f8.tex

log.pdf:	log.tex
	pdflatex log.tex

zeitgl.pdf:	zeitgl.tex
	pdflatex zeitgl.tex

faktoren.pdf:	faktoren.tex
	pdflatex faktoren.tex

