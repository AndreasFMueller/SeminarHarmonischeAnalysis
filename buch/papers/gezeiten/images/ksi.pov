//
// ksi.pov
//
// (c) 2023 Prof Dr Andreas Müller
//
#version 3.7;
#include "colors.inc"

global_settings {
	assumed_gamma 1
}

#declare imagescale = 0.053;

camera {
	location <-28, 30, -40>
	look_at <0, 0.1, 0>
	right (16/9) * x * imagescale
	up y * imagescale
}

light_source {
	<-30, 40, -40> color White
	area_light <1,0,0> <0,0,1>, 10, 10
	adaptive 1
	jitter
}

sky_sphere {
	pigment {
		color rgb<1,1,1>
	}
}

union {
	cylinder { <0,-1,0>, <0,0,0>, 0.05 }
	cylinder { <0,-0.1,0>, <0,0,0>, 1 }
	pigment {
		color White
	}
	finish {
		metallic
		specular 0.99
	}
}

#declare spherecolor = rgb<1,0.8,0.2>;
#declare rollercolor = rgb<1,0.8,0.2>;
#declare pointercolor = rgb<0.6,0.2,0.6>;

#declare curvecolor = rgb<0.4,0.6,0.8>;
#declare integralcolor = rgb<0.2,0.6,0.2>;

#declare r = 0.01;
#declare f = function(X) { 0.25 * (0.8*sin(3 * X) + 0.7 * cos(5*X) + 0.1 * sin(20*X)) }
#macro punkt(T)
	< -1.5 + f(T), 0, T >
#end
#declare F = function(X) { -0.00125*cos(20*X) + 0.035*sin(5*X) - 0.06666666666666667*cos(3*X) }
#macro Punkt(T)
	< 1.5 + T, -0.2, 2*(F(T)-F(-1))-1 >
#end
#declare sphereradius = 0.2;
#declare sphereoffset = f(0);
#declare rollerradius = 0.10;

union {
	cylinder { <-1.8, sphereradius, 0>, <1.1, sphereradius, 0>, 0.02 }
	pigment {
		color spherecolor
	}
	finish {
		metallic
		specular 0.99
	}
}

union {
	sphere { < f(0), sphereradius, 0>, sphereradius }
	cylinder { <-1.5+f(0), sphereradius, 0>, < f(0), sphereradius, 0>, 0.05 }
	pigment {
		color pointercolor
	}
	finish {
		metallic
		specular 0.99
	}
}

union {
	cylinder {
		< -1.5+f(0), sphereradius, 0 >, 
		< -1.5+f(0), 0, 0 >, 
		r
	}
	pigment {
		color pointercolor
	}
	finish {
		metallic
		specular 0.99
	}
}

mesh {
	triangle { < -1.9, 0, -1 >, < -1.1, 0, -1 >, < -1.1, 0, 2 > }
	triangle { < -1.9, 0, -1 >, < -1.1, 0,  2 >, < -1.9, 0, 2 > }
	pigment {
		color White
	}
}

union {
	cylinder { < -1.5, 0, -1 >, < -1.5,0, 2>, r }
	pigment {
		color White
	}
}

union {
	#declare Y = -1;
	#declare Yh = 0.02;
	sphere { punkt(Y), r }
	#while (Y < 2)
		cylinder { punkt(Y), punkt(Y+Yh), r }
		#declare Y = Y + Yh;
		sphere { punkt(Y), r }
	#end
	pigment {
		color curvecolor
	}
}

union {
	cylinder {
		< -1, sphereradius, -(sphereradius+rollerradius) >, 
		<  1, sphereradius, -(sphereradius+rollerradius) >,
		rollerradius
	}
	cylinder {
		< 0, sphereradius, -(sphereradius+rollerradius) >, 
		< 1.32, sphereradius, -(sphereradius+rollerradius) >,
		0.5 * rollerradius
	}
	cylinder {
		< 1.3,  sphereradius, -(sphereradius+rollerradius) >,
		< 1.35, sphereradius, -(sphereradius+rollerradius) >,
		sphereradius
	}
	pigment {
		color rollercolor
	}
	finish {
		metallic
		specular 0.99
	}
}

mesh {
	triangle {
		< 0.5, -0.2, -1.5 >,
		< 3.5, -0.2, -1.5 >,
		< 3.5, -0.2, -0.5 >
	}
	triangle {
		< 0.5, -0.2, -1.5 >,
		< 3.5, -0.2, -0.5 >,
		< 0.5, -0.2, -0.5 >
	}
	pigment {
		color White
	}
}

union {
	cylinder { <0.5, -0.2, -1>, <3.5, -0.2, -1>, r }
	pigment {
		color White
	}
}

union {
	box { < 1.3, -0.05, -1.5 >, < 1.35, 0, 1.5 > }
	pigment {
		color rollercolor
	}
	finish {
		metallic
		specular 0.99
	}
}


union {
	#declare Y = -1;
	#declare Yh = 0.02;
	sphere { Punkt(Y), r }
	#while (Y < 2)
		cylinder { Punkt(Y), Punkt(Y+Yh), r }
		#declare Y = Y + Yh;
		sphere { Punkt(Y), r }
	#end
	pigment {
		color integralcolor
	}
	finish {
		metallic
		specular 0.99
	}
}

union {
	cylinder {
		< 1.325,  0.05, 2*(F(2.325-0.5)-F(-1))-1 >,
		< 1.325, -0.2,  2*(F(2.325-0.5)-F(-1))-1 >,
		r
	}
	pigment {
		color integralcolor
	}
	finish {
		metallic
		specular 0.99
	}
}

//union {
//	cylinder { <-2,  0,  0>, < 2, 0, 0 >, 0.01 }
//	cylinder { < 0, -2,  0>, < 0, 2, 0 >, 0.01 }
//	cylinder { < 0,  0, -2>, < 0, 0, 2 >, 0.01 }
//	pigment {
//		color White
//	}
//	finish {
//		metallic
//		specular 0.99
//	}
//}
