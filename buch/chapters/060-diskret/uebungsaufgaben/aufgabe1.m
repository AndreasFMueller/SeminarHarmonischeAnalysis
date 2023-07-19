%
% aufgabe1.m -- direkte Loesung der Aufgabe 1
%
% (c) 2018 Prof Dr Andreas Müller, Hochschule Rapperswil
%
global N;
N = 12;
n = 6;

y = [
   -3.2, -13.6, -12.3, -3.9, 3.1, 2.0, -4.1, -6.1, 0.5, 10.7, 16.3, 10.6
];

function ret = ak(k, y)
	global N;
	ret = 0;
	t = 2 * pi / N;
	for j = (0:N-1)
		ret = ret + y(1,j+1) * cos(k * j * t);
	end
endfunction

function ret = bk(k, y)
	global N;
	ret = 0;
	t = 2 * pi / N;
	for j = (0:N-1)
		ret = ret + y(1,j+1) * sin(k * j * t);
	end
endfunction

printf("a0 = %.8f\n", ak(0, y) / 12);
printf("a1 = %.8f\n", ak(1, y) / 6);
printf("a2 = %.8f\n", ak(2, y) / 6);
printf("a3 = %.8f\n", ak(3, y) / 6);
printf("a4 = %.8f\n", ak(4, y) / 6);
printf("a5 = %.8f\n", ak(5, y) / 6);
printf("a6 = %.8f\n", ak(6, y) / 12);

printf("b1 = %.8f\n", bk(1,y) / 6);
printf("b2 = %.8f\n", bk(2,y) / 6);
printf("b3 = %.8f\n", bk(3,y) / 6);
printf("b4 = %.8f\n", bk(4,y) / 6);
printf("b5 = %.8f\n", bk(5,y) / 6);
