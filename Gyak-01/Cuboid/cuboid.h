#ifndef CUBOID_H
#define CUBOID_H

/**
 * Data of a cuboid object in Descartes coordinate system
 */
typedef struct Cuboid
{
	double x;
	double y;
    double z;
} Cuboid;

/**
 * Set the data of the Cuboid
 */
void set_size(Cuboid* Cuboid, double x, double y, double z);

/**
 * Calculate the volume of the Cuboid.
 */
double calc_volume(const Cuboid* Cuboid);

/**
 * Calculate the surface of the Cuboid.
 */
double calc_surface(const Cuboid* Cuboid);

#endif // CUBOID_H
