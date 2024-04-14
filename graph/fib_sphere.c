#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
    double z;
} Point;

Point* fibonacci_sphere(int samples) {
    Point* points = (Point*)malloc(samples * sizeof(Point));
    double phi = PI * (sqrt(5.0) - 1.0);

    for (int i = 0; i < samples; i++) {
        double y = 1.0 - (i / (double)(samples - 1)) * 2.0;
        double radius = sqrt(1 - y * y);

        double theta = phi * i;

        double x = cos(theta) * radius;
        double z = sin(theta) * radius;

        points[i].x = x;
        points[i].y = y;
        points[i].z = z;
    }

    return points;
}

int main() {
    int samples = 1000;
    Point* points = fibonacci_sphere(samples);

    printf("x\t\ty\t\tz\n");
    for (int i = 0; i < samples; i++) {
        printf("%f\t%f\t%f\n", points[i].x, points[i].y, points[i].z);
    }

    free(points);
    return 0;
}

