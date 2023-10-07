%
% konzertsaal.m
%
% (c) 2023 Prof Dr Andreas Müller
%
N = 1024;
rand("seed", 4711);

delta = zeros(1,N);
delta(1,100) = 1;

g = zeros(1,N);
g(1,200) = 1;

% random echos between 300 and 500
x = rande(1,20) * 200;
x
for i = (1:20)
	if (x(1,i) < 350)
		j = 600 - round(x(1,i));
		g(1,j) = 1 + 0.3 * (rand(1,1) - 0.5);
	end
end

% noise after 500
n = N - 600;
x = (601:601+n-1);
g(1,x) = abs(0.5 * randn(1,n));
g(1,1:N) = g .* exp(-2 * (1:N) / N) / exp(-2 * 100 / N);

fn = fopen("kpath.tex", "w");

fprintf(fn, "\\def\\impuls{\n");
for i = (1:N)
	fprintf(fn, "\\draw[color=deltacolor] ({%d*\\dx},0) -- ({%d*\\dx},{%.4f*\\dy});\n", i, i, delta(1, i));
end
fprintf(fn, "}\n");

fprintf(fn, "\\def\\echo{\n");
for i = (1:N)
	farbe = "echocolor";
	if (i == 200)
		farbe = "deltacolor!70!echocolor";
	elseif (i > 600)
		farbe = "echocolor!40";
	endif
	fprintf(fn, "\\draw[color=%s] ({%d*\\dx},0) -- ({%d*\\dx},{%.4f*\\dy});\n", farbe, i, i, g(1, i));
end
fprintf(fn, "}\n");

hall = zeros(1,4096);
hall(1,1:N) = g;
Fhall = fft(hall);
signal = zeros(1,4096);
omega = 2 * pi / N;
samples = round(N/3)
signal(101:100+samples) = sin((0:samples-1) * 30 * omega);
Fsignal = fft(signal);
normierung = sum(g);
verhallt = ifft(Fhall .* Fsignal) / normierung;

fprintf(fn, "\\def\\signal{\n");
fprintf(fn, "\t\\draw[color=signalcolor] ({%d*\\dx},{%.4f*\\dy})", 1, signal(1,1));
for i = (2:N)
	fprintf(fn, "\n\t\t-- ({%d*\\dx},{%.4f*\\dy})", i, signal(1, i));
end
fprintf(fn, ";\n\t}\n");

fprintf(fn, "\\def\\hall{\n");
fprintf(fn, "\t\\draw[color=verhalltcolor] ({%d*\\dx},{%.4f*\\dy})", 100,
	verhallt(1,100));
for i = (101:N)
	fprintf(fn, "\n\t\t-- ({%d*\\dx},{%.4f*\\dy})", i, verhallt(1, i + 100));
end
fprintf(fn, ";\n\t}\n");

fclose(fn);
