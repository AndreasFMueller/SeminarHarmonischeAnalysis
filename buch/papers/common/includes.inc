include papers/ct/Makefile.inc
include papers/sonogramm/Makefile.inc
include papers/jpeg/Makefile.inc
include papers/mellin/Makefile.inc
include papers/gezeiten/Makefile.inc
include papers/ml/Makefile.inc
include papers/ptolemaeus/Makefile.inc
include papers/milankovic/Makefile.inc
include papers/spektral/Makefile.inc
include papers/autotune/Makefile.inc
include papers/wavelets/Makefile.inc
include papers/brown/Makefile.inc
include papers/opt/Makefile.inc

TEXFILES-DEP = \
	$(dependencies-ct) \
	$(dependencies-sonogramm) \
	$(dependencies-jpeg) \
	$(dependencies-mellin) \
	$(dependencies-gezeiten) \
	$(dependencies-ml) \
	$(dependencies-ptolemaeus) \
	$(dependencies-milankovic) \
	$(dependencies-spektral) \
	$(dependencies-autotune) \
	$(dependencies-wavelets) \
	$(dependencies-brown) \
	$(dependencies-opt) \

