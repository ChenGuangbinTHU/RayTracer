#include "light.h"

Light::Light()
{
    color = vector3(1,1,1);
    next = NULL;
}

bool PointLight::Collide(vector3 ray_O, vector3 ray_V)
{
    return true;
}

int PointLight::cal_shade(vector3 C, Primitive *primitive_head)
{
    //C.output();
    vector3 v = O - C;
    double dist = v.Length();
    for(Primitive* now = primitive_head;now != NULL;now = now->next)
    {
        if(now->Collide(C,v) && (now->r.distance_to_origin < dist))
        {
            //now->getO().output();
            return 0;
        }
    }
    return 1;
}

bool PointLight::is_pointLight()
{
    return true;
}
