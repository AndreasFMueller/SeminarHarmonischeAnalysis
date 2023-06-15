%
% etraeger.m
%
% (c) 2023 Prof Dr Andreas Müller
%
N = 120;
a = 1.0;

X = (0:0.1:N/10)';
Y = a * rand(N+1,1)
F = zeros(N+1,0);

xmin = 60;
xmax = 80;
d = 2 * pi / (xmax - xmin);
for i = (xmin+1:xmax+1)
	x = (i-1) * 0.1;
	F(i,1) = 3 * (1 - cos((i-xmin-1) * d));
end

G = F + Y;
G = (6 / max(G)) * G;

l1 = sum(G);
l0 = sum(G(1:xmin,1)) + sum(G(xmax:N+1,1));
epsilon = l0/l1

fn = fopen("etraegerpath.tex", "w");

fprintf(fn, "\\def\\eps{%.4f}\n", epsilon);

fprintf(fn, "\\def\\kurve{");

fprintf(fn, "\n\t({%.4f*\\dx},{%.4f*\\dy})", X(1,1), G(1,1));
for i = (2:N+1)
	fprintf(fn, "\n\t--({%.4f*\\dx},{%.4f*\\dy})", X(i,1), G(i,1));
end
fprintf(fn, "\n}\n");

fclose(fn);
