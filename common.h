#ifndef COMMON
#define COMMON

#include "math.h"
#include <QDebug>
#include <iostream>
using namespace std;

#define DOT(A,B)		(A.x*B.x+A.y*B.y+A.z*B.z)
const double EPS = 1e-6;

class vector3
{
public:
    double x,y,z;
    vector3() : x( 0.0 ), y( 0.0 ), z( 0.0 ) {}
    vector3( double a_X, double a_Y, double a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {}
    void Set( double a_X, double a_Y, double a_Z ) { x = a_X; y = a_Y; z = a_Z; }
    void Normalize() { double l = 1.0f / Length(); x *= l; y *= l; z *= l; }
    double Length() { return (double)sqrt( x * x + y * y + z * z ); }
    double SqrLength() { return x * x + y * y + z * z; }
    double Dot( vector3 a_V ) { return x * a_V.x + y * a_V.y + z * a_V.z; }
    vector3 Cross( vector3 b ) { return vector3( y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x ); }
    void operator += ( vector3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
    void operator += ( vector3* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
    void operator -= ( vector3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
    void operator -= ( vector3* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
    void operator *= ( double f ) { x *= f; y *= f; z *= f; }
    void operator *= ( vector3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
    void operator *= ( vector3* a_V ) { x *= a_V->x; y *= a_V->y; z *= a_V->z; }
    vector3 operator- () const { return vector3( -x, -y, -z ); }
    friend vector3 operator + ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
    friend vector3 operator - ( const vector3& v1, const vector3& v2 ) { return vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
    friend vector3 operator + ( const vector3& v1, vector3* v2 ) { return vector3( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
    friend vector3 operator - ( const vector3& v1, vector3* v2 ) { return vector3( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
    friend vector3 operator * ( const vector3& v, double f ) { return vector3( v.x * f, v.y * f, v.z * f ); }
    friend vector3 operator * ( const vector3& v1,const vector3& v2 ) { return vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
    friend vector3 operator * ( double f, const vector3& v ) { return vector3( v.x * f, v.y * f, v.z * f ); }
    void display(){qDebug()<<"x:"<<x<<" y:"<<y<<" z:"<<z;}
    void output(){cout<<"x:"<<x<<" y:"<<y<<" z:"<<z<<endl;}
    bool is_zero_vector(){return fabs(x) < EPS && fabs(y) < EPS &&fabs(z) < EPS;}
    vector3 get_vertical_vector()
    {
         vector3 ret = *this * vector3(0,0,1);
         if(ret.is_zero_vector()) ret = vector3(1,0,0);
         else ret.Normalize();
         return ret;
    }
};

typedef vector3 Color;


#endif // COMMON

