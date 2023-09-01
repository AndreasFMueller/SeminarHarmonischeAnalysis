#
# Makefile -- make file for the paper ml
#
# (c) 2020 Prof Dr Andreas Mueller
#

pdflatex = pdflatex

images: images/ann_simple.pdf images/ann_simple_1D.pdf images/ann_dft_linear.pdf

%.pdf: %.tex
	$(pdflatex) $?
	
.PHONY: clean
clean:
	rm -f images/*.pdf

