#ifndef RAYTRACER
#define RAYTRACER

#include "scene.h"

class Raytracer
{
public:
    Scene scene;
    Color cal_diff(Primitive* primitive);
    Color cal_refl(Primitive* pri, vector3 ray_V, int dep);
    Color cal_refr(Primitive* pri, vector3 ray_V, int dep);

    Raytracer(){}
    ~Raytracer(){}

    vector3 V;

    Color Raytracing(vector3 ray_O,vector3 ray_V,int dep,int i,int j);
    void Run();
};

#endif // RAYTRACER

