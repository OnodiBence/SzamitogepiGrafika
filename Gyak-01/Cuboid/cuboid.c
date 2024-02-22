#include "cuboid.h"

void set_size(Cuboid* cuboid, double x, double y, double z){
    if (x>0.0){
        cuboid->x=x;
    }
    if (y>0.0){
        cuboid->y=y;
    }
    if (z>0.0){
        cuboid->z=z;
    }
}

double calc_volume(const Cuboid* cuboid){
    double volume = cuboid->x * cuboid->y * cuboid->z;
    return volume;
}

double calc_surface(const Cuboid* cuboid){
    double surface = 2* (cuboid->x + cuboid->y + cuboid->z);
    return surface;
}

void has_square(const Cuboid* cuboid){
    if(cuboid->x == cuboid->y ||  cuboid->x == cuboid->z){
        printf("It has a square side.");
    }else if(cuboid->y == cuboid->x ||  cuboid->y == cuboid->z){
        printf("It has a square side.");
    }else if(cuboid->z == cuboid->x || cuboid->z == cuboid->y) {
        printf("It has a square side.");
    }else{
        printf("It does not have a square side.");
    }
}