//
// common.inc
//
// (c) 2023 Prof Dr Andreas Müller
//
#version 3.7;

#include "colors.inc"
#include "math.inc"

global_settings {
	assumed_gamma 1
}

sky_sphere {
	pigment {
		color rgb<1,1,1>
	}
}

#declare e1 = <1, 0, 0>;
#declare e2 = <0, 1, 0>;
#declare e3 = <0, 0, 1>;
#declare O = <0, 0, 0>;

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

//
// Macro to create the camera
//
// from		where the camera is
// to		where to camara is pointed to
// aspectratio	the aspect ratio 
// imagescale	how large the image is to be
//
#macro place_camera(from, to, aspectratio, imagescale)
	camera {
		location from
		look_at to
		right x * aspectratio * imagescale
		up y * imagescale
	}
#end

//
// Macro to create a light source 
//
// from		the place where the light source is placed
// l		the extension of the light source (for smooth shadows)
//
#macro lightsource(from,l)
#declare d1 = l*vnormalize(vcross(e2, from));
#declare d2 = l*vnormalize(vcross(d1, from));
light_source {
	from color White
	area_light d1 d2, 10, 10
	adaptive 1
	jitter
}
#end
