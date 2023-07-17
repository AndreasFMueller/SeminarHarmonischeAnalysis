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
$(workdir):
	mkdir -p $(workdir)
buch.pdf:	$(workdir)/buch.pdf
	cp $(workdir)/buch.pdf buch.pdf

$(workdir)/buch.pdf:	$(workdir) buch.tex $(TEXFILES) $(workdir)/buch.ind
	$(pdflatex) buch.tex
	cd $(workdir); $(bibtex) buch

$(workdir)/buch.ind:	$(workdir) $(workdir)/buch.idx
	cd $(workdir); $(makeindex) buch.idx

$(workdir)/buch.idx:	$(workdir) buch.tex $(TEXFILES) images
	$(touch) build/buch.ind
	$(pdflatex) buch.tex

#
# Papers in einzelne PDF-Files separieren für digitales Feedback
#
separate:	build/buch.aux buch.pdf
	bash splitpapers

#
# Version mit Buchdeckeln für Release/Website
#
SeminarHarmonischeAnalysis.pdf:	SeminarHarmonischeAnalysis.tex $(TEXFILES) \
	SeminarHarmonischeAnalysis.ind $(SBLXFILES)
	$(pdflatex) SeminarHarmonischeAnalysis.tex
	cd build; $(bibtex) SeminarHarmonischeAnalysis

SeminarHarmonischeAnalysis.idx:	SeminarHarmonischeAnalysis.tex $(TEXFILES) \
	images
	$(touch) build/SeminarHarmonischeAnalysis.ind
	$(pdflatex) SeminarHarmonischeAnalysis.tex

SeminarHarmonischeAnalysis.ind:	SeminarHarmonischeAnalysis.idx
	cd build; $(makeindex) SeminarHarmonischeAnalysis

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
