#
# points.m -- compute randomized points on sin curve
#
N = 50;
sigma = 0.2;
t = 3 * pi * (0:N) / N;
x = zeros(10,N+1);
x(1,:) = t;
x(2,:) = 2 * sin(2*t);
x(3,:) = 2 * cos(2*t);
x(4,:) = 0.8*x(2,:) + sigma * randn(1,N+1);
x(5,:) = 0.8*x(3,:) + sigma * randn(1,N+1);
x(6,:) = randn(1,N+1);
x(7,:) = sqrt(2) * sign(x(2,:));
x(8,:) = x(7,:) + sigma * randn(1,N+1);
x(9,:) = sqrt(2) * sign(x(3,:));
x(10,:) = x(9,:) + sigma * randn(1,N+1);
x(11,:) = randn(1,N+1);

#
# Output random sin points
#
f = fopen("sinpoints.tex", "w");
fprintf(f, "\\def\\punkteA{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(2,i+1), x(4,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphA{\n");
fprintf(f, "\\draw[line width=0.5pt,color=blue] (%.3f,%.3f)\n", x(1,1), x(3,1));
for i = (1:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(4,i));
end
fprintf(f, ";\n}\n");
fclose(f);

#
# Output random cos points
#
f = fopen("cospoints.tex", "w");
fprintf(f, "\\def\\punkteA{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(2,i+1), x(5,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphA{\n");
fprintf(f, "\\draw[line width=0.5pt,color=blue] (%.3f,%.3f)\n", x(1,1), x(3,1));
for i = (1:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(5,i));
end
fprintf(f, ";\n}\n");
fclose(f);

#
# Output random rand points
#
f = fopen("randpoints.tex", "w");
fprintf(f, "\\def\\punkteA{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(2,i+1), x(6,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphA{\n");
fprintf(f, "\\draw[line width=0.5pt,color=blue] (%.3f,%.3f)\n", x(1,1), x(6,1));
for i = (1:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(6,i));
end
fprintf(f, ";\n}\n");
fprintf(f, "\\def\\punkteB{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(11,i+1), x(6,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphB{\n");
fprintf(f, "\\draw[line width=0.5pt,color=red] (%.3f,%.3f)\n", x(1,1), x(6,1));
for i = (1:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(11,i));
end
fprintf(f, ";\n}\n");
fclose(f);

#
# Output rectangular points
#
f = fopen("rectpoints.tex", "w");
fprintf(f, "\\def\\punkteA{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(2,i+1), x(8,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphA{\n");
fprintf(f, "\\draw[line width=0.5pt,color=blue] (%.3f,%.3f)", x(1,1), x(8,1));
for i = (2:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(8,i));
end
fprintf(f, ";\n}\n");
fclose(f);

#
# Output rectangular points
#
f = fopen("rcospoints.tex", "w");
fprintf(f, "\\def\\punkteA{\n");
for i = (0:N)
	fprintf(f, "\\punkt{%.3f}{%.3f}{%.3f}\n", x(1,i+1), x(2,i+1), x(10,i+1));
end
fprintf(f, "}\n");
fprintf(f, "\\def\\graphA{\n");
fprintf(f, "\\draw[line width=0.5pt,color=blue] (%.3f,%.3f)", x(1,1), x(10,1));
for i = (2:N+1)
	fprintf(f, "\n--(%.3f,%.3f)", x(1,i), x(10,i));
end
fprintf(f, ";\n}\n");
fclose(f);
