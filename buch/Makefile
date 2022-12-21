#
# Makefile zum Skript ueber Harmonische Analysis
#
# (c) 2022 Prof Dr Andreas Mueller, OST Ostschweizer Fachhochschule
#
all:	buch.pdf

buch:	SeminarHarmonischeAnalysis.pdf

papers/common/Makefile.inc:	papers/common/paperlist

include common/Makefile.inc
include chapters/Makefile.inc
include papers/common/Makefile.inc
include papers/common/includes.inc

ALLTEXFILES = $(TEXFILES) $(CHAPTERFILES)

#
# Buchblock für Druckerei
#
buch.pdf:	buch.tex $(TEXFILES) buch.ind $(BLXFILES)
	$(pdflatex) buch.tex
	$(bibtex) buch

buch.idx:	buch.tex $(TEXFILES) images
	$(touch) buch.ind
	$(pdflatex) buch.tex

buch.ind:	buch.idx
	$(makeindex) buch.idx

#
# Papers in einzelne PDF-Files separieren für digitales Feedback
#
separate:	buch.aux buch.pdf
	bash splitpapers

#
# Version mit Buchdeckeln für Release/Website
#
SeminarHarmonischeAnalysis.pdf:	SeminarHarmonischeAnalysis.tex $(TEXFILES) \
	SeminarHarmonischeAnalysis.ind $(SBLXFILES)
	$(pdflatex) SeminarHarmonischeAnalysis.tex
	$(bibtex) SeminarHarmonischeAnalysis

SeminarHarmonischeAnalysis.idx:	SeminarHarmonischeAnalysis.tex $(TEXFILES) \
	images
	$(touch) SeminarHarmonischeAnalysis.ind
	$(pdflatex) SeminarHarmonischeAnalysis.tex

SeminarHarmonischeAnalysis.ind:	SeminarHarmonischeAnalysis.idx
	$(makeindex) SeminarHarmonischeAnalysis

#
# This Makefile can also construct the short tests
#
include test/Makefile.inc

#
# Errata
#
errata.pdf:	errata.tex
	$(pdflatex) errata.tex

#
# publish
#
publish:	SeminarHarmonischeAnalysis.pdf
	bash publish
