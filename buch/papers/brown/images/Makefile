#
# Makefile
#
# (c) 2023 Prof Dr Andreas Müller
#
all:	weissesRauscheDurchBrown-timeDomain-crop.png \
	harmonischeOszillatoren-FFT-crop.png \
	weissesRauschen-FFT.h-crop.png

weissesRauscheDurchBrown-timeDomain-crop.png: \
	weissesRauscheDurchBrown-timeDomain.png Makefile
	convert -extract 775x920+50+60 \
		weissesRauscheDurchBrown-timeDomain.png \
		weissesRauscheDurchBrown-timeDomain-crop.png

format = 780x630+35+20

harmonischeOszillatoren-FFT-crop.png: \
	harmonischeOszillatoren-FFT.png Makefile
	convert -extract $(format) harmonischeOszillatoren-FFT.png \
		harmonischeOszillatoren-FFT-crop.png

weissesRauschen-FFT.h-crop.png: \
	weissesRauschen-FFT.png Makefile
	convert -extract $(format) weissesRauschen-FFT.png \
		weissesRauschen-FFT-crop.png
