#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
# 
all:	chebexp.pdf chebrect.pdf

exppaths.tex rectpaths.tex:	expcheb.m
	octave expcheb.m

chebexp.pdf:	chebexp.tex exppaths.tex
	pdflatex chebexp.tex

chebrect.pdf:	chebrect.tex rectpaths.tex
	pdflatex chebrect.tex
