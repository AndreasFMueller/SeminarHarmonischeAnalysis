%
% permutation matrix
%
%
P = zeros(20, 20);
P(1,1) = 1;
P(2,6) = 1;
P(3,11) = 1;
P(4,16) = 1;
P(5,2) = 1;
P(6,7) = 1;
P(7,12) = 1;
P(8,17) = 1;
P(9,3) = 1;
P(10,8) = 1;
P(11,13) = 1;
P(12,18) = 1;
P(13,4) = 1;
P(14,9) = 1;
P(15,14) = 1;
P(16,19) = 1;
P(17,5) = 1;
P(18,10) = 1;
P(19,15) = 1;
P(20,20) = 1;

function retval = Pmatrix(p, q)
	n = p * q
	A = zeros(n, n);
	for i = (1:q)
		for j = (1:p)
			% Block i,j
			A((i-1) * p + j, (j-1) * q + i) = 1;
		end
	end
	retval = A;
end


P - Pmatrix(4,5)
