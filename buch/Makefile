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

$(workdir)/buch.pdf:	$(workdir) buch.tex $(TEXFILES) $(workdir)/buch.ind $(BLXFILES)
	$(pdflatex) buch.tex
	cd $(workdir); $(bibtex) buch

$(workdir)/buch.ind:	$(workdir) $(workdir)/buch.idx
	cd $(workdir); $(makeindex) buch.idx

$(workdir)/buch.idx:	$(workdir) buch.tex $(TEXFILES) images
	$(touch) $(workdir)/buch.ind
	$(pdflatex) buch.tex

#
# Papers in einzelne PDF-Files separieren für digitales Feedback
#
separate:	build/buch.aux buch.pdf
	bash splitpapers

#
# Version mit Buchdeckeln für Release/Website
#
buch = SeminarHarmonischeAnalysis
$(buch).pdf:	$(workdir)/$(buch).pdf
	cp $(workdir)/$(buch).pdf $(buch).pdf

$(workdir)/SeminarHarmonischeAnalysis.pdf:	$(buch).tex $(TEXFILES) $(workdir)/$(buch).ind $(SBLXFILES)
	$(pdflatex) $(buch).tex
	cd $(workdir); $(bibtex) $(buch)

$(workdir)/$(buch).idx:	$(workdir) $(buch).tex $(TEXFILES) images
	$(touch) $(workdir)/$(buch).ind
	$(pdflatex) $(buch).tex

$(workdir)/$(buch).ind:	$(workdir)/$(buch).idx
	cd $(workdir); $(makeindex) $(buch).idx

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
