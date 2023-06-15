#
# aufgabe1.m -- direkte Loesung der Aufgabe 1
#
# (c) 2018 Prof Dr Andreas Müller, Hochschule Rapperswil
#
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

ak(0, y) / 12
ak(1, y) / 6
ak(2, y) / 6
ak(3, y) / 6
ak(4, y) / 6
ak(5, y) / 6
ak(6, y) / 6

bk(1,y) / 6
bk(2,y) / 6
bk(3,y) / 6
bk(4,y) / 6
bk(5,y) / 6
