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
	
$(workdir)/buch1-blx.bbl:	$(workdir)/buch1-blx.aux
	cd $(workdir); bibtex buch1-blx

$(workdir)/buch2-blx.bbl:	$(workdir)/buch2-blx.aux
	cd $(workdir); bibtex buch2-blx

$(workdir)/buch3-blx.bbl:	$(workdir)/buch3-blx.aux
	cd $(workdir); bibtex buch3-blx

$(workdir)/buch4-blx.bbl:	$(workdir)/buch4-blx.aux
	cd $(workdir); bibtex buch4-blx

$(workdir)/buch5-blx.bbl:	$(workdir)/buch5-blx.aux
	cd $(workdir); bibtex buch5-blx

$(workdir)/buch6-blx.bbl:	$(workdir)/buch6-blx.aux
	cd $(workdir); bibtex buch6-blx

$(workdir)/buch7-blx.bbl:	$(workdir)/buch7-blx.aux
	cd $(workdir); bibtex buch7-blx

$(workdir)/buch8-blx.bbl:	$(workdir)/buch8-blx.aux
	cd $(workdir); bibtex buch8-blx

$(workdir)/buch9-blx.bbl:	$(workdir)/buch9-blx.aux
	cd $(workdir); bibtex buch9-blx

$(workdir)/buch10-blx.bbl:	$(workdir)/buch10-blx.aux
	cd $(workdir); bibtex buch10-blx

$(workdir)/buch11-blx.bbl:	$(workdir)/buch11-blx.aux
	cd $(workdir); bibtex buch11-blx

$(workdir)/buch12-blx.bbl:	$(workdir)/buch12-blx.aux
	cd $(workdir); bibtex buch12-blx

$(workdir)/buch13-blx.bbl:	$(workdir)/buch13-blx.aux
	cd $(workdir); bibtex buch13-blx

BLXFILES = $(workdir)/buch.bbl \
	$(workdir)/buch1-blx.bbl \
	$(workdir)/buch2-blx.bbl \
	$(workdir)/buch3-blx.bbl \
	$(workdir)/buch4-blx.bbl \
	$(workdir)/buch5-blx.bbl \
	$(workdir)/buch6-blx.bbl \
	$(workdir)/buch7-blx.bbl \
	$(workdir)/buch8-blx.bbl \
	$(workdir)/buch9-blx.bbl \
	$(workdir)/buch10-blx.bbl \
	$(workdir)/buch11-blx.bbl \
	$(workdir)/buch12-blx.bbl \
	$(workdir)/buch13-blx.bbl \

$(workdir)/SeminarHarmonischeAnalysis1-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis1-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis1-blx

$(workdir)/SeminarHarmonischeAnalysis2-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis2-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis2-blx

$(workdir)/SeminarHarmonischeAnalysis3-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis3-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis3-blx

$(workdir)/SeminarHarmonischeAnalysis4-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis4-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis4-blx

$(workdir)/SeminarHarmonischeAnalysis5-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis5-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis5-blx

$(workdir)/SeminarHarmonischeAnalysis6-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis6-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis6-blx

$(workdir)/SeminarHarmonischeAnalysis7-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis7-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis7-blx

$(workdir)/SeminarHarmonischeAnalysis8-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis8-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis8-blx

$(workdir)/SeminarHarmonischeAnalysis9-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis9-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis9-blx

$(workdir)/SeminarHarmonischeAnalysis10-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis10-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis10-blx

$(workdir)/SeminarHarmonischeAnalysis11-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis11-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis11-blx

$(workdir)/SeminarHarmonischeAnalysis12-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis12-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis12-blx

$(workdir)/SeminarHarmonischeAnalysis13-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis13-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis13-blx

$(workdir)/SeminarHarmonischeAnalysis14-blx.bbl:	$(workdir)/SeminarHarmonischeAnalysis14-blx.aux
	cd $(workdir); bibtex SeminarHarmonischeAnalysis14-blx

SBLXFILES = \
	$(workdir)/SeminarHarmonischeAnalysis1-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis2-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis3-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis4-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis5-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis6-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis7-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis8-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis9-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis10-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis11-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis12-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis13-blx.bbl \
	$(workdir)/SeminarHarmonischeAnalysis14-blx.bbl \

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
	
