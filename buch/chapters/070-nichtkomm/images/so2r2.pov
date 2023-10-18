//
// so2r2.pov
//
// (c) 2019 Prof Dr Andreas Müller, Hochschule Rapperswil
//
#version 3.7;
#include "colors.inc"

global_settings {
	assumed_gamma 1
}

#declare imagescale = 0.4;

camera {
        location <1, 1.3, -8>
        look_at <1, 0.5, 0>
        right (16/9) * x * imagescale
        up y * imagescale
}

light_source {
        <-8, 1.1, -5> color White
        area_light <0.1,0,0> <0,0,0.1>, 10, 10
        adaptive 1
        jitter
}

sky_sphere {
        pigment {
                color rgb<1,1,1>
        }
}

fog {
	color White
	distance 100 
}

//
// draw an arrow from <from> to <to> with thickness <arrowthickness> with
// color <c>
//
#macro arrow(from, to, arrowthickness, c)
	#declare arrowdirection = vnormalize(to - from);
	#declare arrowlength = vlength(to - from);
	union {
		sphere {
			from, 1.1 * arrowthickness
		}
		cylinder {
			from,
			from + (arrowlength - 5 * arrowthickness) * arrowdirection,
			arrowthickness
		}
		cone {
			from + (arrowlength - 5 * arrowthickness) * arrowdirection,
			2 * arrowthickness,
			to,
			0
		}
		pigment {
			color c
		}
		finish {
			specular 0.9
			metallic
		}
	}
#end


#declare r = 0.018;

arrow(<-2,0, 0>, <3.7,0,0>, r, 2 * White)
arrow(<-2,2, 0>, <3.7,2,0>, r, 2 * White)
arrow(< 0,0,-5>, <0.0,0,5>, r, 2 * White)
arrow(< 0,2,-5>, <0.0,2,5>, r, 2 * White)

union {
	#declare X = -9;
	#while (X < 10)
		#declare Y = -3;
		#while (Y < 10)
			#if ((X*X+Y*Y) > 0)
				cylinder { <X,0,Y>, <X,2,Y>, r }
			#end
			#declare Y = Y + 3;
		#end
		#declare X = X + 3;
	#end
	pigment {
		color Red
	}
	finish {
		specular 0.9
		metallic
	}
}

union {
	sphere { <0, 0, 0>, 3 * r }
	sphere { <0, 2, 0>, 3 * r }
	pigment {
		color White
	}
	finish {
		specular 0.9
		metallic
	}
}

arrow(<0,0,0>, <0,2,0>, 1.6 * r, Red)

union {
	#declare X = -20;
	#while (X < 20)
		cylinder { <X, 0, -20>, <X, 0, 220>, 0.3 * r }
		cylinder { <X, 2, -20>, <X, 2, 220>, 0.3 * r }
		#declare X = X + 1;
	#end
	#declare Y = -20;
	#while (Y < 20)
		cylinder { <-20, 0, Y>, <20, 0, Y>, 0.3 * r }
		cylinder { <-20, 2, Y>, <20, 2, Y>, 0.3 * r }
		#declare Y = Y + 1;
	#end
	mesh {
		triangle { <-200, 0, -200>, <200, 0, -200>, < 200, 0, 200> }
		triangle { <-200, 0, -200>, <200, 0,  200>, <-200, 0, 200> }
		triangle { <-200, 2, -200>, <200, 2, -200>, < 200, 2, 200> }
		triangle { <-200, 2, -200>, <200, 2,  200>, <-200, 2, 200> }
	}
	pigment {
		color rgb<0.95,0.97,1.0>
	}
	finish {
		specular 0.9
		metallic
	}
}

#macro orbit(r, phi, p0)
	< r * cos(phi + p0), phi / pi, r * sin(phi + p0) >
#end

#macro spirale(R, p0)
	#declare phisteps = 100;
	#declare phistep = 2 * pi / phisteps;
	#declare phi = 0;
	#declare previous = orbit(R, phi, p0);
	sphere { previous, r }
	#while (phi < 2 * pi - phistep/2)
		#declare phi = phi + phistep;
		#declare current = orbit(R, phi, p0);
		cylinder { previous, current, r }
		sphere { current, r }
		#declare previous = current;
	#end
#end

union {
	spirale(1, 0)
	spirale(1, pi / 2)
	spirale(1, pi)
	spirale(1, 3 * pi / 2)
	spirale(2, 0)
	spirale(3, 0)
	pigment {
		color rgb<0.0,0.4,0.6>
	}
	finish {
		specular 0.9
		metallic
	}
}

