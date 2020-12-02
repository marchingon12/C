/*
Compile: make volume
Run: ./volume
make volume && ./volume
*/
#define _USE_MATH_DEFINES
#define _GNU_SOURCE
#include "base.h"

enum Tag { TCylinder, TSphere, TCuboid };
typedef enum Tag Tag;

struct Cylinder {
    double r, h; // V = pi * r^2 * h
};

struct Sphere {
    double r; // V = 4 / 3 * pi * r^3
};

struct Cuboid {
    double a, b, c; // V = a * b *c
};

struct GeomObject {
	enum Tag tag;
	union {
		struct Cylinder TCylinder;
		struct Sphere TSphere;
		struct Cuboid TCuboid;
	};
};

typedef struct Cylinder Cylinder;
typedef struct Sphere Sphere;
typedef struct Cuboid Cuboid;
typedef struct GeomObject GeomObject;

GeomObject make_cylinder(double r, double h) {
    // todo: implement
	GeomObject o;
	o.tag = TCylinder;
	o.TCylinder.r = r;
	o.TCylinder.h = h;
    return o;
}

GeomObject make_sphere(double r) {
    // todo: implement
    GeomObject o = {};
	o.tag = TSphere;
	o.TSphere.r = r;
    return o;
}

GeomObject make_cuboid(double a, double b, double c) {
    // todo: implement
    GeomObject o = {};
	o.tag = TCuboid;
	o.TCuboid.a = a;
	o.TCuboid.b = b;
	o.TCuboid.c = c;
    return o;
}

double volume(GeomObject o);

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}

// GeomObject -> double
// Computes the surface area of the given object.
double volume(GeomObject o) {
	int n = o.tag;
	switch(n){
		case 0 : return M_PI * pow(o.TCylinder.r,2) * o.TCylinder.h ;
		case 1 : return 4 / 3.0 * M_PI * pow(o.TSphere.r,3);
		default : return o.TCuboid.a * o.TCuboid.b * o.TCuboid.c ;
	}
	return 0.0;
}

int main(void) {
    volume_test();
    return 0;
}

//todo: d)
/*
Tag ist dafür da

In Zeile 10 is Tag als
 */
