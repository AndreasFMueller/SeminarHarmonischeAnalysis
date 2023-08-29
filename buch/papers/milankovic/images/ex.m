%
% ex.m -- Exzentrizitaet und Totalstrahlung
%
% (c) 2023 Prof Dr Andreas Müller
%
global a;
a = 1;

function retval = ExzentrischeAnomalie(M, epsilon)
	Ealt = M;
	delta = 1;
	while (delta > 0.0001)
		Eneu = M + epsilon * sin(Ealt);
		delta = abs(Eneu - Ealt);
		Ealt = Eneu;
	end
	retval = Ealt;
end

function retval = abstand(t, epsilon)
	global	a;
	b = a * sqrt(1 - epsilon^2);
	M = 2 * pi * t;
	E = ExzentrischeAnomalie(M, epsilon);
	x = a * (cos(E) - epsilon);
	y = b * sin(E);
	retval = sqrt(x^2 + y^2);
end

function retval = strahlung(epsilon)
	N = 100;
	s = 0;
	for t =	(0:N-1)
		r = abstand(t / N, epsilon);
		s = s + 1/(r^2);
	end
	retval = s / N;
end

A = zeros(1000, 8);
for e = (0:999)
	epsilon = 0.001 * e;
	amin = (1 - epsilon) * a;
	amax = (1 + epsilon) * a;
	d = amax/amin - 1;
	w = amax^2 / amin^2 - 1;
	A(e+1,:) = [ epsilon, strahlung(epsilon), amin, amax, 100 * d, 1/amax^2, 1/amin^2, 100 * w ];
end

printf("   epsilon strahlung      amin      amax     delta      smin      smax     delta\n");
A

fp = fopen("ex.tex", "w");
fprintf(fp, "\\def\\expfad{ (0,0)");
for i = (1:10:950)
	fprintf(fp, "\n\t-- ({%.3f*\\dx},{%.3f*\\dy})", A(i,1), A(i,2) - 1);
end
fprintf(fp, "\n}\n");
fclose(fp);

