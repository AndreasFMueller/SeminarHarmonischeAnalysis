#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	ksi.pdf

ksi.pdf:	ksi.tex ksi.jpg
	pdflatex ksi.tex

ksi.png:	ksi.pov Makefile
	povray +A0.1 -Oksi.png -W1920 -H1080 ksi.pov

ksi.jpg:	ksi.png
	convert ksi.png ksi.jpg
