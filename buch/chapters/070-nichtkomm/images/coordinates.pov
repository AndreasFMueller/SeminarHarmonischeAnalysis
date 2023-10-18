//
// coordinates.pov
//
// (c) 2019 Prof Dr Andreas Müller, Hochschule Rapperswil
//
#version 3.7;
#include "colors.inc"

global_settings {
	assumed_gamma 1
}

#declare imagescale = 0.145;

camera {
        location <-3.5, 10.3, -12>
        look_at <0, 0, 0>
        right x * imagescale
        up y * imagescale
}

light_source {
        <-8, 6, -5> color White
        area_light <0.1,0,0> <0,0,0.1>, 10, 10
        adaptive 1
        jitter
}

sky_sphere {
        pigment {
                color rgb<1,1,1>
        }
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

#declare thetax = 0.5;
#declare phix = -2.85;
#declare theta = 0.9;
#declare phi0 = 0.8;
#declare rho = sin(theta);
#declare Z = cos(theta);

#macro kugel(the, phi)
	< sin(the) * cos(phi), cos(the), sin(the) * sin(phi) >
#end

#declare n = <0, 1, 0>;
#declare X = kugel(thetax, phix);
#declare O = <0,0,0>;
#declare C = vnormalize(X) * cos(theta);
#declare r1 = -vnormalize(vcross(n, X));
#declare r2 = -vcross(X, r1);

#macro koordinaten(phi, the)
	C + sin(the) * (r1 * cos(phi) + r2 * sin(phi))
#end

arrow(<0,0,0>, 1.4 * n, r, Orange)
sphere { n, 1.2 * r
		pigment {
			color Orange
		}
		finish {
			specular 0.9
			metallic
		}
}

arrow(C, C+X,  r, rgb<1.0,0.6,1.0>)
arrow(C, C+r1, r, rgb<0.0,0.8,0.4>)
cylinder { C, C - 1 * r1, 0.4 * r
		pigment {
			color rgb<0.0,0.8,0.4>
		}
		finish {
			specular 0.9
			metallic
		}
}
arrow(C, C+r2, r, rgb<0.2,0.6,0.8>)
cylinder { C, C - 1 * r2, 0.4 * r
		pigment {
			color rgb<0.2,0.6,0.8>
		}
		finish {
			specular 0.9
			metallic
		}
}

union {
	#declare phisteps = 50;
	#declare phi = 0;
	#declare phistep = pi / phisteps;
	#declare previous = koordinaten(phi, theta);
	#while (phi < 2 * pi - phistep/2)
		#declare phi = phi + phistep;
		#declare new = koordinaten(phi, theta);
		cylinder { previous, new, 0.5 * r }
		sphere { new, 0.5 * r }
		#declare previous = new;
	#end

	pigment {
		color rgbf<0.4,0.0,0.2,0.0>
	}
	finish {
		specular 0.4
		metallic
	}
}

#declare angleColor = rgb<1.0,0.8,0.0>;

mesh {
	#declare phisteps = 50;
	#declare phi = 0;
	#declare phistep = pi / phisteps;
	#declare previous = koordinaten(phi, theta);
	#while (phi < phi0 - phistep)
		#declare phi = phi + phistep;
		#declare new = koordinaten(phi, theta);
		triangle { C, previous, new }
		#declare previous = new;
	#end
	#declare new = koordinaten(phi0, theta);
	triangle { C, previous, new }

	pigment {
		color angleColor
	}
	finish {
		specular 0.4
		metallic
	}
}

union {
	cylinder { C, koordinaten(phi0, theta), 0.5 * r }
	sphere { koordinaten(phi0, theta), r }
	pigment {
		color angleColor
	}
	finish {
		specular 0.4
		metallic
	}
}

sphere { X, 1.2 * r
	pigment {
		color rgbf<1,1,1,0.0>
	}
	finish {
		specular 0.4
		metallic
	}
}

sphere { X, 1.2 * r
	pigment {
		color rgbf<1,1,1,0.0>
	}
	finish {
		specular 0.4
		metallic
	}
}

intersection {
	difference {
		sphere { O, 1 }
		sphere { O, 0.999 }
	}
	plane { X, Z }
	pigment {
		color rgbf<1,1,1,0.3>
	}
	finish {
		specular 0.4
		metallic
	}
}

arrow(O, -<1.2,0,0>, r, White)
// arrow(O, <0,1.2,0>, r, White)
arrow(O, -<0,0,1.2>, r, White)

cylinder { O, C, 0.5 * r
	pigment {
		color rgb<0.6,0.4,0.2>
	}
	finish {
		specular 0.4
		metallic
	}
}

/*
intersection {
	sphere { <0, 0, 0>, 1 }
	plane { -X, -Z-0.001 }
	pigment {
		color rgbf<1,1,1,0.6>
	}
	finish {
		specular 0.4
		metallic
	}
}
*/

