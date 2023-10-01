//
// 3dimage.pov -- -template for 3d images rendered by Povray
//
// (c) 2023 Prof Dr Andreas Müller
//
#include "../../../common/common.inc"

place_camera(<-33, 20, 50>, <0, 0, 0>, 16/9, 0.2)
lightsource(<10, 5, 40>, 1)

arrow(-e1, e1, 0.01, White)
arrow(-e2, e2, 0.01, White)
arrow(-e3, e3, 0.01, White)

