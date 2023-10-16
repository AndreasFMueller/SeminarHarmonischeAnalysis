#!/usr/bin/env bash
#
# farbseiten.sh -- Formattierung der Farbseiteninfo für die Druckerei
#
# (c) 2020 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
#
awk 'BEGIN {
	result = ""
	counter = 0
} 
/^#/ {
	next
}
{
	if (length(result) == 0) {
		result = $1
	} else {
		result = sprintf("%s,%d", result, $1)
	}
	counter++
}
END {
	printf("%s\n", result)
	printf("Anzahl Farbseiten: %d\n", counter)
}' <<EOF
# Kapitel  0
# Kapitel  1
17
20
# Kapitel  2
35
36
37
38
39
41
# Kapitel  3
48
49
51
62
63
66
68
69
71
75
76
# Kapitel  4
88
91
92
99
101
107
117
119
# Kapitel  5
139
140
161
# Kapitel  6
165
186
# Kapitel  7
198
200
201
204
205
215
236
# Kapitel  8
243
246
249
250
256
258
260
261
264
# Kapitel  9
282
# Kapitel 10
# Kapitel 11
301
306
309
312
313
314
317
319
325
326
327
330
332
334
335
338
341
342
346
# Kapitel 12: Verfolgungskurven
356
361
368
# Kapitel 13: FM
372
373
374
375
381
382
383
384
# Kapitel 14 parzyl
386
390
392
# Kapitel 15 fresnel
396
397
398
399
401
# Kapitel 16 kreismembran
410
417
418
419
# Kapitel 17 sturmliouville
# Kapitel 18 laguerre
437
443
444
445
446
447
448
449
# Kapitel 19 zeta
452
454
455
460
# Kapitel 20 0f1
463
465
467
468
469
470
# Kapitel 21 nav
474
475
476
480
482
483
485
486
487
488
# Kapitel 22 transfer
492
493
494
495
496
498
# Kapitel 23 kra
505
507
# Kapitel 24 kugel
515
517
519
522
532
533
535
543
# Kapitel 25 elliptisch
550
552
553
554
556
557
558
559
560
# Kapitel 26
EOF
