#include "raytracer.h"
#include <QImage>
#include <stdlib.h>
#include <iostream>
#include "QDebug"
#include <QRgb>
using namespace std;

const int MAX_DEPTH = 3;
const int MAX_RAYTRACING_DEPTH = 15;


Color Raytracer::cal_diff(Primitive *primitive)
{
    Color color = primitive->material->get_color();
    color.output();
    //primitive->getO().output();
    Color ret = color * primitive->material->get_diff() * scene.background;

    for(Light* light = scene.light_head;light != NULL;light = light->next)
    {

        double shade = light->cal_shade(primitive->r.intersect_point,scene.primitive_head);
        if(shade < EPS)
        {
            return ret;
        }
        vector3 L = light->getO()-primitive->r.intersect_point;

        L.Normalize();
        vector3 N = primitive->r.normal;
        double dot = L.Dot(N);
        if(dot > EPS)
        {
            if(primitive->material->get_diff() > EPS)
            {
                double diff = dot * primitive->material->get_diff() ;
                ret =ret + light->color * diff;
            }

            if(primitive->material->get_spec() > EPS)
            {
                vector3 R = 2*N*dot-L;
                double spec = pow(R.Dot(V),20)*primitive->material->get_spec();
                ret = ret + light->color * spec;
            }
        }
    }
    return ret;
}

Color Raytracer::cal_refl(Primitive *primitive, vector3 ray_V,int dep)
{
    Color ret;
    ray_V.Normalize();
    vector3 I = ray_V;
    vector3 N = primitive->r.normal;
    vector3 R = I - 2*(I.Dot(N))*N;
    ret = ret + Raytracing(primitive->r.intersect_point,R,dep+1,-1,-1);
    ret = ret * primitive->material->get_refl() * primitive->material->get_color();
    return ret;
}

Color Raytracer::cal_refr(Primitive *primitive, vector3 ray_V, int dep)
{
    Color ret;
    vector3 In = ray_V;
    In.Normalize();
    vector3 N = primitive->r.normal;
    double rri = 1/primitive->material->get_rindex();
    if(In.Dot(N) < EPS) rri = primitive->material->get_rindex();

    double cosi = In.Dot(N);
    if(cosi < EPS) cosi = -cosi;

    double temp = 1 - (rri * rri * (1-cosi * cosi));

    if(temp > EPS)
    {
        double cosT = sqrt(temp);
        vector3 T = -1 * rri * In + (rri * cosi - cosT) *  N;
        if(In.Dot(N) < EPS) T = -1 * rri * In + (rri * cosi - cosT) *  N * -1;

        ret = ret + Raytracing(primitive->r.intersect_point,T,dep+1,-1,-1);
        ret = ret * primitive->material->get_refr() * primitive->material->get_color();
    }
    else
    {
        //ret = ret + cal_refl(primitive,I,dep);
        //ret = ret * primitive->material->get_refr() * primitive->material->get_color();
        //N = -1 * N;
        //Primitive* p = scene.find_nearest_primitive()
//        if(primitive->r.front == false)
//            N =-N;
        vector3 R = In - 2*(In.Dot(N))*N;
        ret = ret + Raytracing(primitive->r.intersect_point,R,dep,-1,-1);
        ret = ret * primitive->material->get_refr() * primitive->material->get_color();
    }

    return ret;

//    Color ret;

//    double rri = primitive->material->get_rindex();
//    if(primitive->r.front == false) rri = 1/rri;

//    vector3 N = primitive->r.normal;
//    vector3 I = ray_V;

//    double cosi = I.Dot(N);

//    double temp = 1-(rri * rri * (1-cosi*cosi));

//    if(temp > EPS)
//    {
//        double cosT = sqrt(temp);
//        vector3 T = -rri * I + (rri * (cosi) - cosT) * N;
//        ret = ret + Raytracing(primitive->r.intersect_point + T*EPS,T,dep+1,-1,-1);
//        ret = ret * primitive->material->get_refr() * primitive->material->get_color();
//    }
//    else
//    {
//        //ret = ret + cal_refl(primitive,I,dep);
//        //ret = ret * primitive->material->get_refr() * primitive->material->get_color();
//        //N = -1 * N;
//        //Primitive* p = scene.find_nearest_primitive()
//        if(primitive->r.front == false)
//            N =-N;
//        vector3 R = I - 2*(I.Dot(N))*N;
//        ret = ret + Raytracing(primitive->r.intersect_point,R,dep,-1,-1);
//        ret = ret * primitive->material->get_refr() * primitive->material->get_color();
//    }
//    cout<<"fuck: ";
//    ret.output();
//    return ret;

}

Color Raytracer::Raytracing(vector3 ray_O, vector3 ray_V,int dep,int i,int j)
{
    //qDebug()<<dep;
    if(dep > MAX_RAYTRACING_DEPTH) return Color(0,0,0);
    if(i == 0 && j == 0)
    {
        for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
            pri->material->get_color().display();
    }
    Color ret;
    V = ray_V;
    Primitive* nearest_primitive = scene.find_nearest_primitive(ray_O,ray_V);

    Light* nearest_light = scene.find_nearest_light(ray_O,ray_V);

    //nearest_light->getO().display();
//    if(nearest_light != NULL &&(nearest_primitive == NULL || nearest_light->crash_dist < nearest_primitive->r.distance_to_origin))
//    {
//        //ret = ret + nearest_light->color;
//        //ret.output();
//        return ret;
//    }
//    double shade = nearest_light->cal_shade(nearest_primitive->r.intersect_point,scene.primitive_head);
//    if(shade < EPS)
//    {
//        cout<<"ret:";
//        ret.output();
//        return ret;
//    }
    if(nearest_primitive != NULL)
    {
        //nearest_primitive->getO().output();

        Primitive* primitive = nearest_primitive->CopyPrimitive();

        primitive->material->get_color().output();

        if(primitive->material->get_diff() > EPS || primitive->material->get_specular() > EPS)
        {
            ret = ret + cal_diff(primitive);
        }
        if(primitive->material->get_refl() > EPS)
            ret = ret + cal_refl(primitive,ray_V,dep);
        if(primitive->material->get_refr() > EPS)
            ret = ret + cal_refr(primitive,ray_V,dep);


        delete primitive;
        //primitive = NULL;

    }

    //scene.primitive_head->material->m_color = Color(1,0,0);
    //ret.display();
    return ret;
}

void Raytracer::Run()
{
    Camera* camera = scene.camera;
    scene.initScene1();
//    for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
//        pri->material->get_color().display();
    vector3 ray_O = camera->O;
    int W = camera->W;
    int H = camera->H;
    //qDebug()<<1;
    QImage img = QImage(W,H,QImage::Format_RGB888);

    for(int i = 0;i < W;i++)
    {
        for(int j = 0;j < H;j++)
        {
//            if(i == 0 && j == 0)
//            {
//                for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
//                    pri->material->get_color().display();
//            }

            vector3 ray_V = vector3(i,0,j)-ray_O;
            ray_V.Normalize();

            Color c = Raytracing(ray_O,ray_V,0,i,j);

//            if(i == 0 && j == 0)
//            {
//                for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
//                    pri->material->get_color().display();
//            }
            //camera->data[i][j] = c;
            int r = min(255,int(c.x*255));
            cout<<"r:"<<r<<endl;
            int g = min(255,int(c.y*255));
            int b = min(255,int(c.z*255));
            img.setPixel(i,j,qRgb(r,g,b));

            if(i == 1 && j == 1)
            {
                for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
                    pri->material->get_color().display();
            }
        }
    }
//    for(Primitive* pri = scene.primitive_head;pri!=NULL;pri = pri->next)
//        pri->material->get_color().display();
    img.save("3.jpg");
//    QImage* img = new QImage(W,H,QImage::Format_RGB888);
//    camera->output(img);

    qDebug()<<3;
    //img->save("1.png");
    //Raytracing(ray_O,vector3(300,0,300)-ray_O,0,-1,-1);
}





