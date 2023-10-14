#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
radonimages =								\
	mathman.jpg							\
	mathman-radon.jpg						\
	mathman2-backward-FTL.jpg					\
	mathman2-backward-FTL-polar.jpg					\
	mathman-backward-radon.jpg					\
	mathman-backward-masked.jpg

all:	ebenewellen.pdf $(radonimages)

ebenewellen.pdf:	ebenewellen.tex
	pdflatex ebenewellen.tex

tools = $(HOME)/Projects/AstroPhotography/control/tools/image

mathman.jpg:	mathman.fits
	convert mathman.fits mathman.jpg

mathman-radon.fits:	mathman.fits
	$(tools)/radon --debug --height=1024 --width=1024 mathman.fits \
		mathman-radon.fits

mathman-radon.jpg:	mathman-radon.fits
	convert mathman-radon.fits mathman-radon.jpg

mathman2-radon.fits:	mathman2.fits
	$(tools)/radon --debug --height=2048 --width=2048 mathman2.fits \
		mathman2-radon.fits

mathmanjpg = mathman-backward-radon.jpg mathman-backward-masked.jpg
fr $(mathmanjpg):	mathman-radon.fits
	$(tools)/radoni --debug --log --radius=0.5 mathman
	convert mathman-backward-radon.fits mathman-backward-radon.jpg
	convert mathman-backward-masked.fits mathman-backward-masked.jpg

mathman2jpg = mathman2-backward-FTL.jpg mathman2-backward-FTL-polar.jpg
fr2 $(mathman2jpg):	mathman2-radon.fits
	$(tools)/radoni --debug --log --radius=1.0 mathman2
	convert mathman2-backward-FTL.fits mathman2-backward-FTL.jpg
	convert mathman2-backward-FTL-polar.fits mathman2-backward-FTL-polar.jpg

clean:
	rm -f mathman-F.fits mathman-F2.fits mathman-o.fits mathman-FF.fits
