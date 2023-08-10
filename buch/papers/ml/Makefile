#
# Makefile -- make file for the paper ml
#
# (c) 2020 Prof Dr Andreas Mueller
#

pdflatex = pdflatex

all: images
images: images/ann_simple.pdf images/ann_simple_1D.pdf

%.pdf: %.tex
	$(pdflatex) $?
	
.PHONY: clean
clean:
	rm -f images/*.pdf

