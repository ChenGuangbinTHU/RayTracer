#include "scene.h"

Scene::Scene()
{
    primitive_head = NULL;
    light_head = NULL;
    camera = new Camera();
}

Scene::~Scene()
{
    //之后要删除纹理
    while(primitive_head != NULL)
    {
        Primitive* next = primitive_head->next;
        delete primitive_head;
        primitive_head = next;
    }

    while(light_head != NULL)
    {
        Light* next = light_head->next;
        delete light_head;
        light_head = next;
    }

    delete camera;
}

void Scene::initScene()
{
    //background = Color(0,0.1,0.1);

    Sphere* s1 = new Sphere();
    s1->set_O_R(vector3(200,200,200),100);
    Sphere* s2 = new Sphere();
    Sphere* s3 = new Sphere();
    //s3->set_O_R(vector());
    //Sphere* s4 = new Sphere(vector3(0.6,-1.5,0),0.5);
    //s1->material->set_color();
    s1->material->set_color(Color(0,0,1));
    s1->material->set_diff(0.5);
    s1->material->set_spec(0.6);
    s2->material->set_color(Color(0,1,0));
    s2->material->set_diff(0.4);
    s2->set_O_R(vector3(50,100,200),30);
    s2->material->set_spec(0.6);
    //s2->material->set_color(Color(0,1,0));
    //s3->material->set_color(Color(0.5,0.5,1));
    //s4->material->set_color(Color(1,1,1));
    PointLight* pl = new PointLight(vector3(0,0,0));
    pl->O = vector3(0,0,0);
    primitive_head=s1;
    s1->setNext(s2);
    s2->setNext(NULL);
    //s1->setNext(s2);
    //s2->setNext(s3);
    //s3->setNext(s4);
    //s4->setNext(NULL);

    light_head=pl;
    pl->set_next(NULL);
    camera->init();

}

Primitive* Scene::find_nearest_primitive(vector3 ray_O, vector3 ray_V)
{

    Primitive* ret = NULL;
    for(Primitive* now = primitive_head;now != NULL;now = now->next)
    {
        if(now->Collide(ray_O,ray_V) && (ret == NULL || now->r.distance_to_origin < ret->r.distance_to_origin))
        {
            ret = now;
            //ret->getO().output();
        }

    }
    //if(ret == NULL) qDebug()<<"fuck";
    //ret->getO().display();
    return ret;
}

Light* Scene::find_nearest_light(vector3 ray_O, vector3 ray_V)
{
    Light* ret = NULL;
    for(Light* now = light_head;now != NULL;now = now->next)
        if(now->Collide(ray_O,ray_V) && (ret == NULL || now->crash_dist < ret->crash_dist))
        {
            ret = now;
            //ret->getO().output();
        }

    return ret;
      //return light_head;
}

void Scene::initScene1()
{
    background = Color(0.8,0.8,0.8);

    camera->O = vector3(200,-500,200);

    Plane* p1 = new Plane();//right
    p1->N = vector3(1,0,0);
    p1->D = 0;


    //p1->setNext(NULL);
    p1->material->set_color(Color(0,0.8,0.8));
    p1->material->set_diff(0.3);
    primitive_head = p1;
    //p1->N.display();
    Plane* p2 = new Plane();//left
    p2->N = vector3(-1,0,0);
    p2->D = 400;
    p2->material->set_color(Color(1,0,1));
    p2->material->set_diff(0.3);

    Plane* p3 = new Plane();//left
    p3->N = vector3(0,-1,0);
    p3->D = 400;
    p3->material->set_color(Color(0,1,1));
    p3->material->set_diff(0.3);

    Plane* p4 = new Plane();//left
    p4->N = vector3(0,0,-1);
    p4->D = 400;
    p4->material->set_color(Color(0,0.7,0.2));
    p4->material->set_diff(0.3);
    p4->material->set_refl(0.4);

    Plane* p5 = new Plane();//left
    p5->N = vector3(0,0,1);
    p5->D = 0;
    p5->material->set_color(Color(0,0.4,0.8));
    p5->material->set_diff(0.5);


    p1->setNext(p2);
    p2->setNext(p3);
    p3->setNext(p4);
    p4->setNext(p5);

    Sphere* s1 = new Sphere();
    s1->set_O_R(vector3(250,200,300),100);
    Sphere* s2 = new Sphere();
    s1->material->set_color(Color(0.86,0.86,0.86));
    s1->material->set_diff(0.5);
    s1->material->set_spec(0.6);
    //s1->material->set_refl(0.3);
    s1->material->set_rindex(1.6);
    s1->material->set_refr(0.9);

    p5->setNext(s1);
    s2->material->set_color(Color(0.86,0.86,0.86));
    s2->material->set_diff(0.4);
    s2->set_O_R(vector3(100,40,200),50);
    s2->material->set_spec(0.6);
    s2->material->set_rindex(1.6);
    s2->material->set_refr(0.9);
    s1->setNext(s2);

    Sphere* s3 = new Sphere();
    s3->set_O_R(vector3(200,370,370),30);
    s3->material->set_color(Color(1,0,0));
    s3->material->set_diff(0.8);
    s3->material->set_spec(0.6);
    //s1->material->set_refl(0.6);
    s2->setNext(s3);
//    primitive_head=s1;
//    s1->setNext(s2);
//    s2->setNext(NULL);

    PointLight* pl = new PointLight(vector3(200,200,20));
    //pl->O = vector3(200,200,380);
    light_head=pl;
    pl->set_next(NULL);

//    color_infor[0] = p1->material->get_color();
//    color_infor[1] = p2->material->get_color();
//    color_infor[2] = p4->material->get_color();
//    color_infor[3] = p4->material->get_color();
//    color_infor[4] = p5->material->get_color();

//    color_infor[6] = s1->material->get_color();
//    color_infor[7] = s2->material->get_color();

    camera->init();
    //qDebug()<<"1";
}





