#include "cuboid.h"
#include <stdio.h>

int main() {
    Cuboid cuboid;
    set_size(&cuboid,5,7,5);
    double volume;
    volume = calc_volume(&cuboid);
    double surface;
    surface = calc_surface(&cuboid);
    printf("Volume: %lf\n", volume);
    printf("Surface %lf\n", surface);
    has_square(&cuboid);
    return 0;
}