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
6
# Kapitel  1
14
18
23
27
29
31
45
51
# Kapitel  2
90
91
# Kapitel  3
105
106
108
118
130
# Kapitel  4
# Kapitel  5
174
177
180
186
187
# Kapitel  6
196
204
209
210
212
214
218
219
220
231
233
# Kapitel  7
246
252
253
254
255
# Kapitel  8: sonogramm
265
266
267
268
270
271
272
273
# Kapitel  9: autotune
279
281
282
283
285
287
288
# Kapitel 10: brown
292
295
298
299
# Kapitel 11: opt
304
305
309
311
315
316
317
318
# Kapitel 12: jpeg
323
325
328
329
330
331
# Kapitel 13: ct
341
343
344
# Kapitel 14: mellin
348
349
355
359
360
# Kapitel 15: gezeiten
366
368
# Kapitel 16: spektral
375
377
# Kapitel 17: milankovic
380
383
384
# Kapitel 18: ml
398
# Kapitel 19: wavelets
403
404
405
406
407
408
409
410
411
412
413
414
415
416
417
418
419
420
421
422
423
424
EOF
