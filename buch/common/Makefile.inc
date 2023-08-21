#
# Makefile.inc -- gemeinsame Teile des Makefiles für das Buchprojekt
#
# (c) 2021 Prof Dr Andreas Mueller, OST Ostschweizer Fachhochschule
#

SUBDIRECTORIES = chapters 

topdir := ${PWD}
workdir := build

# change the following variables to suit your environment

pdflatex = pdflatex --output-directory=$(workdir)
bibtex = bibtex
makeindex = makeindex
touch = touch

.PHONY:	images

images:
	for d in $(SUBDIRECTORIES); 					\
	do 								\
		(cd $${d}; make images); 				\
	done

BUCHFILES =								\
	common/content.tex						\
	common/macros.tex						\
	common/lststyles.tex						\
	common/packages.tex						\
	common/titlepage.tex						\
	common/teilnehmer.tex						\
	$(CHAPTERS) 							\
	chapters/references.bib 					\
	papers/common/addpackages.tex					\
	papers/common/addpapers.tex					\
	$(PAPERFILES)

THEMA_FILES = 

TEXFILES = $(BUCHFILES) $(THEMA_FILES)

# References des ersten Teils

$(workdir)/buch.bbl:		build/buch.aux
	cd build; bibtex buch

clean:	cleansubdir
	rm -f *.bbl *.aux *.log *.out *.run.xml *.pdf *.blg *.idx *.ind \
		*.ilg *.toc *.synctex.gz *.auxlock *.bak *-blx.bib *.dvi

cleansubdir:
	for d in $(SUBDIRECTORIES);					\
	do								\
		if [ -f $${d}/Makefile ];				\
		then 							\
			cd $${d}; make clean; cd ..;			\
		fi;							\
	done

farbseiten.csv:	farbseiten.txt
	awk '{ printf("%d,", $$1) } END {printf("\n")}' farbseiten.txt \
		> farbseiten.csv
