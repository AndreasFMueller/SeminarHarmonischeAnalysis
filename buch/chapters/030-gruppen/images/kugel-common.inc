//
// 3dimage.pov -- -template for 3d images rendered by Povray
//
// (c) 2023 Prof Dr Andreas Müller
//
#include "../../../common/common.inc"

place_camera(<33, 20, 50>, <0, 0, 0>, 1, 0.038)
lightsource(<20, 5, 4>, 1)

#declare al = 1.25;
arrow(-al*e1, al*e1, 0.02, White)
arrow(-al*e2, al*e2, 0.02, White)
arrow(-al*e3, al*e3, 0.02, White)

sphere {
	O, 1
	pigment {
		color Gray
	}
	finish {
		metallic
		specular 0.9
	}
}

#declare e1farbe = rgb<0.8,0.4,0.6>;
#declare e2farbe = rgb<0.6,0.8,0.4>;
#declare e3farbe = rgb<0.4,0.6,0.8>;
#declare r = 0.95;

#macro c1()
	cylinder { O, 1.1 * e1, r }
#end
#macro c2()
	cylinder { O, 1.1 * e2, r }
#end
#macro c3()
	cylinder { O, 1.1 * e3, r }
#end

#macro umgebung(richtung, farbe)
intersection {
	sphere { O, 1.001 }
	cylinder { O, 1.1 * richtung, r }
	pigment {
		color farbe
	}
	finish {
		metallic
		specular 0.99
	}
}
#end

#macro koordinatensystem(r1, r2, farbe)
#declare r3 = vnormalize(vcross(r1, r2));
intersection {
	cone { O, 0, 1.1 * r3, 1.1 * tan(asin(r)) }
	union {
		#declare y1step = 0.02;
		#declare x1step = 0.2;
		#declare x1 = -0.8;
		#while (x1 < 0.95)
			#declare y0 = sqrt(r*r - x1*x1);
			#declare y1max = y1step * (ceil(y0 / y1step) + 1);
			#declare y1min = -y1max;
			#declare y1 = y1min;
			#declare z1 = sqrt(1 - x1*x1 - y1*y1);
			#declare p = x1 * r1 + y1 * r2 + z1 * r3;
			#while (y1 < y1max)
				sphere { p, 0.01 }
				#declare y1 = y1 + y1step;
				#declare z1 = sqrt(1 - x1*x1 - y1*y1);
				#declare pneu = x1 * r1 + y1 * r2 + z1 * r3;
				cylinder { p, pneu, 0.01 }
				#declare p = pneu;
			#end
			sphere { p, 0.01 }
			#declare x1 = x1 + x1step;
		#end
		#declare x1step = 0.02;
		#declare y1step = 0.2;
		#declare y1 = -0.8;
		#while (y1 < 0.95)
			#declare x0 = sqrt(r*r - y1*y1);
			#declare x1may = x1step * (ceil(x0 / x1step) + 1);
			#declare x1min = -x1may;
			#declare x1 = x1min;
			#declare z1 = sqrt(1 - x1*x1 - y1*y1);
			#declare p = x1 * r1 + y1 * r2 + z1 * r3;
			#while (x1 < x1may)
				sphere { p, 0.01 }
				#declare x1 = x1 + x1step;
				#declare z1 = sqrt(1 - x1*x1 - y1*y1);
				#declare pneu = x1 * r1 + y1 * r2 + z1 * r3;
				cylinder { p, pneu, 0.01 }
				#declare p = pneu;
			#end
			sphere { p, 0.01 }
			#declare y1 = y1 + y1step;
		#end
		pigment {
			color farbe
		}
		finish {
			metallic
			specular 0.99
		}
	}
}
#end

#macro umgebungen2(richtung1, farbe1, richtung2, farbe2)
intersection {
	sphere { O, 1.002 }
	cylinder { O, 1.1 * richtung1, r }
	cylinder { O, 1.1 * richtung2, r }
	pigment {
		color 0.5 * (farbe1 + farbe2)
	}
	finish {
		metallic
		specular 0.99
	}
}
#end

#macro umgebungen3(richtung1, farbe1, richtung2, farbe2, richtung3, farbe3)
intersection {
	sphere { 0, 1.003 }
	cylinder { O, 1.1 * richtung1, r }
	cylinder { O, 1.1 * richtung2, r }
	cylinder { O, 1.1 * richtung3, r }
	pigment {
		color 0.3333 * (farbe1 + farbe2 + farbe3)
	}
	finish {
		metallic
		specular 0.99
	}
}
#end

