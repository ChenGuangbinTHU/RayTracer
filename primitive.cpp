#include "primitive.h"

Primitive* Sphere::CopyPrimitive()
{
    Sphere* ret = new Sphere(*this);
    return ret;
}

//bool Sphere::Collide(vector3 ray_O,vector3 ray_V)
//{
//    vector3 ray_origin = ray_O;
//    vector3 ray_dir = ray_V;
//    ray_V.Normalize();
//    vector3 Loc = O - ray_origin;
//    double sq_radius = R*R;
//    Result r;
//    int intersect_result = 0;
//    double sq_Loc = DOT(Loc,Loc);
//    double Tca = Loc.Dot(ray_dir);
//    double sq_Thc = sq_radius - sq_Loc + Tca*Tca;
//    if(sq_Loc < sq_radius)
//        intersect_result = -1;
//    else
//    {
//        if(Tca < 0)
//            intersect_result = 0;
//        else
//        {

//            if(sq_Thc < 0)
//                intersect_result = 0;
//            else
//            {
//                intersect_result = 1;
//            }
//        }
//    }
//    if(intersect_result == 0)
//    {
//        return false;
//    }
//    else
//    {
//        double t;
//        if(intersect_result == -1)
//            t = Tca + sqrt(sq_Thc);
//        else if(intersect_result == 1)
//            t = Tca + sqrt(sq_Thc);

//        r.intersect_point = ray_origin + ray_dir*t;
//        vector3 k = r.intersect_point-O;
//        k.Normalize();
//        r.normal = k;
//        vector3 l = r.intersect_point-O;
//        r.distance_to_origin = l.Length();
//        return true;
//    }
//}


bool Sphere::Collide( vector3 ray_O , vector3 ray_V ) {
    ray_V.Normalize();
    vector3 P = ray_O - O;
    double b = -P.Dot( ray_V );
    double det = b * b - P.SqrLength() + R * R;

    if ( det > EPS ) {
        det = sqrt( det );
        double x1 = b - det  , x2 = b + det;

        if ( x2 < EPS ) return false;
        if ( x1 > EPS ) {
            r.distance_to_origin = x1;
            r.front = true;
        } else {
            r.distance_to_origin = x2;
            r.front = false;
        }
    } else
        return false;

    r.intersect_point = ray_O + ray_V * r.distance_to_origin;
    r.normal = ( r.intersect_point - O );
    if(r.front == false) r.normal = -r.normal;
    r.normal.Normalize();
    return true;
}

bool Plane::Collide(vector3 ray_O, vector3 ray_V)
{

    ray_V.Normalize();
    N.Normalize();

    double t = -1*(D + N.Dot(ray_O))/(N.Dot(ray_V));
    if(t < EPS) return false;
    r.distance_to_origin = t;
    r.normal = N;
    r.intersect_point = ray_O + t*ray_V;
    return true;
    /*
    ray_V.Normalize();
    N.Normalize();
    double d = N.Dot( ray_V );
    if ( fabs( d ) < EPS ) return false;
    double l = ( N * D - ray_O ).Dot( N ) / d;
    if ( l < EPS ) return false;

    r.distance_to_origin = l;
    r.front = (d<0);
    r.intersect_point = ray_O + ray_V * l;
    r.normal = N;
    return true;
    */
}

Primitive* Plane::CopyPrimitive()
{
    Plane* ret = new Plane(*this);
    return ret;
}
