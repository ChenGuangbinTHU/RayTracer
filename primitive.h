#ifndef PRIMITIVE
#define PRIMITIVE

#include "ray.h"
//#include "common.h"



class Material
{
public:
    Material(){m_color = vector3(0,0,0);}
    void set_color(Color color){m_color = color;}
    Color get_color(){return m_color;}
    void set_diff(double diff){m_diff = diff;}
    double get_diff(){return m_diff;}
    void set_refl(double refl){m_refl = refl;}
    double get_refl(){return m_refl;}
    double get_specular(){return 1.0f-m_diff;}
    void set_spec(double spec){m_spec = spec;}
    double get_spec(){return m_spec;}
    void set_refr(double refr){m_refr = refr;}
    double get_refr(){return m_refr;}
    void set_rindex(double rindex){m_rindex = rindex;}
    double get_rindex(){return m_rindex;}
private:
    Color m_color;
    double m_refl;
    double m_diff;
    double m_spec;
    double m_refr;
    double m_rindex;
};

class Result
{
public:
    vector3 normal;
    double distance_to_origin;
    vector3 intersect_point;
    bool front;
    Result() : normal(vector3(-10,-10,-10)),distance_to_origin(-10.0f),intersect_point(vector3(-10,-10,-10)),front(true){}
    void display(int i);
};

class Primitive
{
public:
    Result r;


    Primitive* next;

    Primitive(){material = new Material;next = NULL;}
    Primitive( const Primitive& primitive )
    {
        *this = primitive;
        material = new Material;
        *material = *primitive.material;
    }
    ~Primitive(){delete material;}
    Material* material;
    void setNext(Primitive* primitive){next = primitive;}

    virtual bool Collide(vector3 ray_O,vector3 ray_V) = 0;
    virtual Primitive* CopyPrimitive() = 0;
    virtual vector3 getO() = 0;

};

class Sphere : public Primitive
{
public:
    Sphere():Primitive(){}
    vector3 O;
    double R;
    void set_O_R(vector3 a,double b){O = a;R = b;}
    bool Collide(vector3 ray_O,vector3 ray_V);
    Primitive* CopyPrimitive();
    vector3 getO(){return O;}
};

class Plane : public Primitive
{
public:
    vector3 N,Dx,Dy;
    double D;
    Plane() : Primitive(){}
    ~Plane() {}
    bool Collide(vector3 ray_O, vector3 ray_V);
    Primitive* CopyPrimitive();
    vector3 getO(){return N;}
};


#endif // PRIMITIVE

