#ifndef LIGHT
#define LIGHT
//#include "result.h"
//#include "common.h"
#include "ray.h"
#include "primitive.h"

class Light
{
public:
    Color color;
    Light* next;
    double crash_dist;

    Light();
    virtual bool is_pointLight() = 0;
    void set_next(Light* light) {next = light;}
    virtual bool Collide(vector3 ray_O,vector3 ray_V) = 0;
    virtual int cal_shade(vector3 C,Primitive* primitive_head) = 0;
    virtual vector3 getO() = 0;
};

class PointLight : public Light
{
public:
    PointLight(vector3 o){O=o;}
    vector3 O;
    //PointLight();

    vector3 getO(){return O;}
    bool is_pointLight();
    bool Collide(vector3 ray_O,vector3 ray_V);
    int cal_shade(vector3 C, Primitive *primitive_head);
};

#endif // LIGHT

