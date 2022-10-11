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
		pdfjam --outfile pages/p-$${i}.pdf MathSem-00-ad.pdf $${i}; \
		convert pages/p-$${i}.pdf pages/p-$${i}.png; \
	done
