/*
August Ho und Benjamin von Behren
Assignment 07
Aufgabe 4: Volumengeometrischer Körper

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
	printf("Expected value: %f\n", 4 /3.0 * M_PI * 2 * 2 * 2);
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
	printf("Expected value: %f\n", 2.0 * 3 * 4);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
	printf("Expected value: %f\n", 4.0 * M_PI * 3 * 3);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}

// GeomObject -> double
// Computes the surface area of the given object.
double volume(GeomObject o) {
	double volume;
	//Precondition
	require("validTag", o.tag == TCylinder || o.tag == TSphere || o.tag == TCuboid);
	switch (o.tag) {
		case TCylinder :
			volume = M_PI * pow(o.TCylinder.r, 2.0) * o.TCylinder.h;
			//printf("%f\n", volume);
			//Postconditions
			ensure("correct result", fabs(o.TCylinder.r - pow(volume / (M_PI * o.TCylinder.h), 1 / 2.0)) < 1e-6);
			ensure("correct result", fabs(o.TCylinder.h - volume / (M_PI * pow(o.TCylinder.r, 2.0))) < 1e-6);
			break;
		case TSphere :
			volume =  4.0 / 3.0 * M_PI * pow(o.TSphere.r, 3.0);
			//printf("%f\n", volume);
			//Postconditions
			ensure("correct result", fabs(o.TSphere.r - pow(3.0 / 4.0 * volume / M_PI, 1 / 3.0)) < 1e-6);
			break;
		case TCuboid :
			volume = o.TCuboid.a * o.TCuboid.b * o.TCuboid.c;
			//printf("%f\n", volume);
			//Postconditions
			ensure("correct result for a", fabs(o.TCuboid.a - volume / (o.TCuboid.b * o.TCuboid.c)) < 1e-6);
			ensure("correct result for b", fabs(o.TCuboid.b - volume / (o.TCuboid.a * o.TCuboid.c)) < 1e-6);
			ensure("correct result for c", fabs(o.TCuboid.c - volume / (o.TCuboid.a * o.TCuboid.b)) < 1e-6);
			break;
	}
	return volume;
}

int main(void) {
    volume_test();
    return 0;
}

//todo: d)
/*
Tag ist dafür da zu wissen, um welche Struktur es sich handelt.

Tag wird benuzt in struct GeomObject, um zu makieren um welche Objekt es sich handelt.
Außerdem wird es in volume benutzt, um zu wissen welche Objekt es sich handelt.

 */
