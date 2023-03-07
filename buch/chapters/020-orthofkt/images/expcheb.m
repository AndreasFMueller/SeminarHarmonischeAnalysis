%
% exp.m -- Entwicklung der Exponentialfunktion als Tschebyscheff-Reihe
%
% (c) 2023 Prof Dr Andreas Müller
%

N = 100;
global n;
n = 10;

function retval = rechteck0(x)
	retval = -1;
	epsilon = 1e-3;
	if (x > epsilon)
		retval = 1;
	elseif (x < -epsilon)
		retval = -1;
	else
		retval = 0;
	end
end

function retval = rechteck(x)
	retval = -1;
	x0 = 0.4;
	if (x > x0)
		retval = -1;
	elseif (x < -x0)
		retval = -1;
	else
		retval = 1;
	end
end

function retval = exponential(x)
	retval = exp(x);
end

function retval = quadrat(x)
	retval = 2 * x^2;
end

global g;

function retval = f(y,z)
	global n;
	global g;
	retval = cos(n*z) * g(cos(z));
end

function retval = coefficients(N, funktion)
	global g;
	g = funktion;
	c = zeros(1,N+1);
	global n;
	for n = (0:N)
		lsode_options("maximum step size", 0.01);
		[Y, istate, msg] = lsode(@f, 0, [0, pi]);
		c(1,n+1) = (2/pi) * Y(2,1);
	end
	c(1,1) = c(1,1) / 2;
	retval = c;
end

function retval = Exp(c,z,n)
	koef = c(1:n+1);
	cosnz = cos((0:n) * z);
	retval = koef * cosnz';
end

function retval = frac(x)
	retval = x - floor(x);
end

function drawcurve(fn, name, n, resolution, c, funktion)
	fprintf(fn, "\\def\\degree%s{%d}\n", name, n);
	fprintf(fn, "\\def\\%s{", name);
	z = linspace(0, pi, resolution);
	err = zeros(1,resolution);
	s = "  ";
	for i = (1:resolution)
		x = cos(z(1,i));
		y = Exp(c,z(1,i), n);
		err(1,i) = y - funktion(x);
		fprintf(fn, "\n\t%s ({%.5f*\\sx},{%.5f*\\sy}) %% %.5f", s,
			x, y, err(1,i));
		s = "--";
	end
	fprintf(fn, "\n}\n");
	m =  max(abs(err));
	fprintf(fn, "\\def\\errscalemant%s{%.2f}\n", name, 10^frac(log10(m)));
	fprintf(fn, "\\def\\errscaleexp%s{%.2g}\n", name, floor(log10(m)));
	fprintf(fn, "\\def\\error%s{", name);
	s = "  ";
	for i = (1:resolution)
		x = cos(z(1,i));
		e = err(1,i);
		fprintf(fn, "\n\t%s ({%.5f*\\sx},{%.5f*\\sy})", s, x, e / m);
		s = "--";
	end
	fprintf(fn, "\n}\n");
end

%
% Exponential function
%
c = coefficients(N, @exponential);
c

fn = fopen("exppaths.tex", "w");
drawcurve(fn, "expa",  1, 201, c, @exponential)
drawcurve(fn, "expb",  2, 201, c, @exponential)
drawcurve(fn, "expc",  3, 201, c, @exponential)
drawcurve(fn, "expd",  4, 201, c, @exponential)
drawcurve(fn, "expe",  5, 201, c, @exponential)
drawcurve(fn, "expf",  6, 201, c, @exponential)
drawcurve(fn, "expg",  7, 201, c, @exponential)
drawcurve(fn, "exph",  8, 201, c, @exponential)
drawcurve(fn, "expi",  9, 201, c, @exponential)
drawcurve(fn, "expj", 10, 201, c, @exponential)
drawcurve(fn, "expk", 11, 201, c, @exponential)
fclose(fn);

%
% rectangular function
%
c = coefficients(N, @rechteck);
c

fn = fopen("rectpaths.tex", "w");
drawcurve(fn, "recta",  1, 201, c, @rechteck)
drawcurve(fn, "rectb",  2, 201, c, @rechteck)
drawcurve(fn, "rectc",  4, 201, c, @rechteck)
drawcurve(fn, "rectd", 20, 201, c, @rechteck)
drawcurve(fn, "recte", 50, 501, c, @rechteck)
fclose(fn);

