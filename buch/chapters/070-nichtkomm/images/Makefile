#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	2dmendez.pdf							\
	MTransformExamples.pdf						\
	MTransformExamples2.pdf						\
	so2r2.pdf							\
	coordinates.pdf

2dmendez.pdf:	2dmendez.tex
	pdflatex 2dmendez.tex

MTransformExamples.pdf:	MTransformExamples.tex common.tex
	pdflatex MTransformExamples.tex

MTransformExamples2.pdf:	MTransformExamples2.tex common.tex
	pdflatex MTransformExamples2.tex

so2r2.png:	so2r2.pov
	povray +A0.1 -W1920 -H1080 -Oso2r2.png so2r2.pov

so2r2.jpg:	so2r2.png Makefile
	convert so2r2.png -density 300 -units PixelsPerInch so2r2.jpg

so2r2.pdf:	so2r2.tex so2r2.jpg common.tex
	pdflatex so2r2.tex

coordinates.png:	coordinates.pov
	povray +A0.1 -W1080 -H1080 -Ocoordinates.png coordinates.pov

coordinates.jpg:	coordinates.png Makefile
	convert -extract 1000x1000+2+5 coordinates.png -density 300 -units PixelsPerInch coordinates.jpg

coordinates.pdf:	coordinates.tex coordinates.jpg common.tex
	pdflatex coordinates.tex

