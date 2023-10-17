
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
orion2images =								\
	orion2.jpg							\
	orion2-radon.jpg						\
	orion2-backprojection.jpg					\
	orion2-filtered.jpg						\
	orion2-filtered-backprojection.jpg

radonimages =								\
	mathman.jpg							\
	mathman-radon.jpg						\
	mathman2-backward-FTL.jpg					\
	mathman2-backward-FTL-polar.jpg					\
	mathman-backward-radon.jpg					\
	mathman-backward-masked.jpg

all:	ebenewellen.pdf 						\
	radonft.pdf							\
	orion2.pdf							\
	radon.pdf							\
	rueckprojektion.pdf						\
	$(radonimages)

ebenewellen.pdf:	ebenewellen.tex
	pdflatex ebenewellen.tex

tools = $(HOME)/Projects/AstroPhotography/control/tools/image

mathman.jpg:	mathman.fits
	convert mathman.fits mathman.jpg

mathman-radon.fits:	mathman.fits
	$(tools)/radon --debug --height=1024 --width=1024 mathman.fits \
		mathman-radon.fits

mathman-backprojection.fits:	mathman-radon.fits
	$(tools)/backprojection --debug \
		mathman-radon.fits mathman-backprojection.fits
mathman-backprojection.jpg:	mathman-backprojection.fits
	convert mathman-backprojection.fits mathman-backprojection.jpg

mathman-filtered-backprojection.fits:	mathman-radon.fits
	$(tools)/backprojection --debug --filter \
		mathman-radon.fits mathman-filtered-backprojection.fits
mathman-filtered-backprojection.jpg:	mathman-filtered-backprojection.fits
	convert mathman-filtered-backprojection.fits \
		mathman-filtered-backprojection.jpg

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

radonft.pdf:	radonft.tex
	pdflatex radonft.tex


orion-radon.fits:	orion.fits
	$(tools)/radon --debug --height=1000 --width=1000 orion.fits \
		orion-radon.fits

orion-backprojection.fits:	orion-radon.fits
	$(tools)/backprojection --debug \
		orion-radon.fits orion-backprojection.fits
orion-backprojection.jpg:	orion-backprojection.fits
	convert orion-backprojection.fits orion-backprojection.jpg

orion-filtered-backprojection.fits:	orion-radon.fits
	$(tools)/backprojection --debug --filter \
		orion-radon.fits orion-filtered-backprojection.fits
orion-filtered-backprojection.jpg:	orion-filtered-backprojection.fits
	convert orion-filtered-backprojection.fits \
		orion-filtered-backprojection.jpg

orion2-radon.fits:	orion2.fits
	$(tools)/radon --debug --height=2000 --width=2000 orion2.fits \
		orion2-radon.fits
orion2.jpg:	orion2.fits
	convert orion2.fits orion2.jpg
orion2-radon.jpg:	orion2-radon.fits
	convert orion2-radon.fits orion2-radon.jpg

orion2-backprojection.fits:	orion2-radon.fits
	$(tools)/backprojection --debug \
		orion2-radon.fits orion2-backprojection.fits
orion2-backprojection.jpg:	orion2-backprojection.fits
	convert orion2-backprojection.fits orion2-backprojection.jpg

orion2-filtered-backprojection.fits orion2-filtered.fits:	orion2-radon.fits
	$(tools)/backprojection --debug --filter \
		--filtered-file=orion2-filtered.fits --log \
		orion2-radon.fits orion2-filtered-backprojection.fits
orion2-filtered-backprojection.jpg:	orion2-filtered-backprojection.fits
	convert -black-point-compensation orion2-filtered-backprojection.fits \
		orion2-filtered-backprojection.jpg
orion2-filtered.jpg: orion2-filtered.fits
	convert orion2-filtered.fits orion2-filtered.jpg
	#convert -equalize orion2-filtered.fits orion2-filtered.jpg


orion2.pdf:	orion2.tex $(orion2images) 
	pdflatex orion2.tex


radon.pdf:	radon.tex mathman.jpg mathman-radon.jpg
	pdflatex radon.tex

rueckprojektion.pdf:	rueckprojektion.tex
	pdflatex rueckprojektion.tex
