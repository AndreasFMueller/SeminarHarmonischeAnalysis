#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	ksi.pdf sy.pdf

ksi.pdf:	ksi.tex ksi.jpg
	pdflatex ksi.tex

ksi.png:	ksi.pov
	povray +A0.1 -Oksi.png -W1920 -H1080 ksi.pov

ksi.jpg:	ksi.png
	convert -extract 1920x760+0+200 ksi.png ksi.jpg

sy.pdf:	sy.tex
	pdflatex sy.tex

