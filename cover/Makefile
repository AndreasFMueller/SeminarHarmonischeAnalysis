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
