#
# Makefile fuer die Bilder des Kapitels Optische Fouriertransformation <opt>
#
# (c) 2023 Marco Niederberger, Yanick Schoch; OST Ostschweizer Fachhochschule
#
# Compile each .tex file within the current directory with pdflatex
# Save the compiled pdf inside the same directory

# Compiler settings
LATEX_COMPILER = pdflatex

# Source files and PDF files
SRCS = $(filter-out opt_common.tex,$(wildcard *.tex))
PDFS = $(patsubst %.tex,%.pdf,$(SRCS))

# Default rule
all: $(PDFS)

# Rule to build PDF files
%.pdf: %.tex opt_common.tex
	$(LATEX_COMPILER) $<

# Clean rule
clean:
	rm -f *.pdf *.aux *.log

# Phony targets
.PHONY: all clean
