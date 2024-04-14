#define PI 3.1415
#include"header.h"

coord* fibonacci_sphere(int samples) {
    coord* coords = (coord*)malloc(samples * sizeof(coord));
    double phi = PI * (sqrt(5.0) - 1.0);

    for (int i = 0; i < samples; i++) {
        double y = 1.0 - (i / (double)(samples - 1)) * 2.0;
        double radius = sqrt(1 - y * y);

        double theta = phi * i;

        double x = cos(theta) * radius;
        double z = sin(theta) * radius;

        coords[i].x = x;
        coords[i].y = y;
        coords[i].z = z;
    }

    return coords;
}



