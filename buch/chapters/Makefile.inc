#
# Makefile.inc
#
# (c) 2022 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
#

CHAPTERFILES = 								\
	chapters/part1.tex						\
	chapters/vorwort.tex

include chapters/000-einleitung/Makefile.inc
include chapters/010-skalarprodukt/Makefile.inc
include chapters/020-orthofkt/Makefile.inc
include chapters/030-gruppen/Makefile.inc
include chapters/040-operatoren/Makefile.inc
include chapters/050-radon/Makefile.inc
include chapters/060-diskret/Makefile.inc
include chapters/070-nichtkomm/Makefile.inc
