#ifndef RAY
#define RAY

#include "common.h"

class Ray
{
public:
    Ray():m_Origin(vector3(0,0,0)),m_Direction(vector3(0,0,0)){}
    Ray(vector3 a_Origin,vector3 a_dir){m_Origin = a_Origin;m_Direction = a_dir;m_Direction.Normalize();}
    void set_origin(vector3 origin){m_Origin = origin;}
    //void set_dir(vector3 dir){m_Direction = dir;}
    vector3 get_origin(){return m_Origin;}
    vector3 get_dir(){return m_Direction;}
    vector3 m_Origin;
    vector3 m_Direction;
};

#endif // RAY

