#
# Makefile.inc -- Makefile Targets und Variablen für Papers
#
# Achtung: dieses File wird erzeugt vom Skript scripts/mkmakefile
#
# (c) 2020 Prof Dr Andreas Müller, Hochschule Rapperswil
#
PAPERFILES = \
	papers/part2.tex \
	papers/uebersicht.tex \
	papers/ct/main.tex \
	papers/sonogramm/main.tex \
	papers/jpeg/main.tex \
	papers/mellin/main.tex \
	papers/gezeiten/main.tex \
	papers/ml/main.tex \
	papers/ptolemaeus/main.tex \
	papers/milankovic/main.tex \
	papers/spektral/main.tex \
	papers/autotune/main.tex \
	papers/wavelets/main.tex \
	papers/brown/main.tex \
	papers/opt/main.tex \
	
buch1-blx.bbl:	buch1-blx.aux
	bibtex buch1-blx

buch2-blx.bbl:	buch2-blx.aux
	bibtex buch2-blx

buch3-blx.bbl:	buch3-blx.aux
	bibtex buch3-blx

buch4-blx.bbl:	buch4-blx.aux
	bibtex buch4-blx

buch5-blx.bbl:	buch5-blx.aux
	bibtex buch5-blx

buch6-blx.bbl:	buch6-blx.aux
	bibtex buch6-blx

buch7-blx.bbl:	buch7-blx.aux
	bibtex buch7-blx

buch8-blx.bbl:	buch8-blx.aux
	bibtex buch8-blx

buch9-blx.bbl:	buch9-blx.aux
	bibtex buch9-blx

buch10-blx.bbl:	buch10-blx.aux
	bibtex buch10-blx

buch11-blx.bbl:	buch11-blx.aux
	bibtex buch11-blx

buch12-blx.bbl:	buch12-blx.aux
	bibtex buch12-blx

buch13-blx.bbl:	buch13-blx.aux
	bibtex buch13-blx

buch14-blx.bbl:	buch14-blx.aux
	bibtex buch14-blx

BLXFILES = buch.bbl \
	buch1-blx.bbl \
	buch2-blx.bbl \
	buch3-blx.bbl \
	buch4-blx.bbl \
	buch5-blx.bbl \
	buch6-blx.bbl \
	buch7-blx.bbl \
	buch8-blx.bbl \
	buch9-blx.bbl \
	buch10-blx.bbl \
	buch11-blx.bbl \
	buch12-blx.bbl \
	buch13-blx.bbl \
	buch14-blx.bbl \

PAPER_DIRECTORIES = \
	ct \
	sonogramm \
	jpeg \
	mellin \
	gezeiten \
	ml \
	ptolemaeus \
	milankovic \
	spektral \
	autotune \
	wavelets \
	brown \
	opt \
	
PAPER_MAKEFILEINC = \
	papers/ct/Makefile.inc \
	papers/sonogramm/Makefile.inc \
	papers/jpeg/Makefile.inc \
	papers/mellin/Makefile.inc \
	papers/gezeiten/Makefile.inc \
	papers/ml/Makefile.inc \
	papers/ptolemaeus/Makefile.inc \
	papers/milankovic/Makefile.inc \
	papers/spektral/Makefile.inc \
	papers/autotune/Makefile.inc \
	papers/wavelets/Makefile.inc \
	papers/brown/Makefile.inc \
	papers/opt/Makefile.inc \
	
