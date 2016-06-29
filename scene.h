#ifndef SCENE
#define SCENE

#include "primitive.h"
#include "camera.h"
#include "light.h"


class Scene
{
public:
    Primitive* primitive_head;
    Light* light_head;
    Camera* camera;
    Color background;
    //Color color_infor[100];


    Scene();
    ~Scene();

    void initScene();
    void initScene1();
    Primitive* find_nearest_primitive(vector3 ray_O,vector3 ray_V);
    Light* find_nearest_light(vector3 ray_O, vector3 ray_V);
};

#endif // SCENE

