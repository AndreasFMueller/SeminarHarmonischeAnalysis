#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	sinc.pdf kugelschnitt.pdf kugelkarten.pdf

sinc.pdf:	sinc.tex
	pdflatex sinc.tex

#dimensions = -W216 -H216
dimensions = -W1080 -H1080

kugeln:		kugel1.png kugel2.png kugel3.png kugelschnitt.png

kugel1.png:	kugel1.pov
	povray +A0.1 $(dimensions) -Okugel1.png kugel1.pov
kugel1.jpg:	kugel1.png
	convert kugel1.png kugel1.jpg

kugel2.png:	kugel2.pov
	povray +A0.1 $(dimensions) -Okugel2.png kugel2.pov
kugel2.jpg:	kugel2.png
	convert kugel2.png kugel2.jpg

kugel3.png:	kugel3.pov
	povray +A0.1 $(dimensions) -Okugel3.png kugel3.pov
kugel3.jpg:	kugel3.png
	convert kugel3.png kugel3.jpg

kugelschnitt.png:	kugelschnitt.pov kugel-common.inc
	povray +A0.1 $(dimensions) -Okugelschnitt.png kugelschnitt.pov
kugelschnitt.jpg:	kugelschnitt.png
	convert kugelschnitt.png kugelschnitt.jpg

kugelkarten.pdf:	kugelkarten.tex kugel1.jpg kugel2.jpg kugel3.jpg
	pdflatex kugelkarten.tex

kugelschnitt.pdf:	kugelschnitt.tex kugelschnitt.jpg
	pdflatex kugelschnitt.tex

