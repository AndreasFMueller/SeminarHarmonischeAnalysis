#
# Makefile -- ad
#
# (c) 2017 Prof Dr Andreas Müller, Hochschule Rapperswil
#
all:	ad-handout.pdf MathSem-00-ad.pdf

include ../slides/Makefile.inc

SOURCES = common.tex slides.tex $(slides)

MathSem-00-ad.pdf:	MathSem-00-ad.tex $(SOURCES)
	pdflatex MathSem-00-ad.tex

ad-handout.pdf:	ad-handout.tex $(SOURCES)
	pdflatex ad-handout.tex

thumbnail:	thumbnail.jpg # fix1.jpg

thumbnail.pdf:	MathSem-00-ad.pdf
	pdfjam --outfile thumbnail.pdf --papersize '{16cm,9cm}' \
		MathSem-00-ad.pdf 1
thumbnail.jpg:	thumbnail.pdf
	convert -density 300 thumbnail.pdf \
                -resize 1920x1080 -units PixelsPerInch thumbnail.jpg

fix1.pdf:	MathSem-00-ad.pdf
	pdfjam --outfile fix1.pdf --papersize '{16cm,9cm}' \
		MathSem-00-ad.pdf 1
fix1.jpg:	fix1.pdf
	convert -density 300 fix1.pdf \
                -resize 1920x1080 -units PixelsPerInch fix1.jpg

pages:
	mkdir pages
	for i in `seq 1 1 30`; \
	do \
		n=`printf %02d $${i}`; \
		pdfjam --papersize '{19.2cm,10.8cm}' --outfile pages/p-$${n}.pdf MathSem-00-ad.pdf $${n}; \
		convert -density 600 pages/p-$${n}.pdf -geometry 1920x1080 pages/p-$${n}.jpg; \
	done
