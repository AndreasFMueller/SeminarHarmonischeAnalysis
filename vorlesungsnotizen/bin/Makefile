#
# Makefile to build numbering script
#
# (c) 2022 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
#
numberpages:	numberpages.cpp
	c++ -std=c++11 -g -Wall -o numberpages numberpages.cpp

test:	numberpages
	./numberpages --debug --section "Komplexe Funktionentheorie" \
		--force \
		"../MSE/1 - Komplexe Funktionen.pdf" blubb.pdf
