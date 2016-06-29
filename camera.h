#ifndef CAMERA
#define CAMERA

#include <QImage>
#include <QRgb>
#include "common.h"

const double STD_LENS_WIDTH = 0.88;
const double STD_LENS_HEIGHT = 0.88;
const int STD_IMAGE_WIDTH = 400;
const int STD_IMAGE_HEIGHT = 400;

class Camera
{
public:
    Camera();
    ~Camera();
    vector3 O,N,Dx,Dy;
    double lens_W,lens_H;
    int W,H;
    Color** data;

    void set_data(int i,int j,Color color){data[i][j] = color;}
    void set_camera(vector3 pos){O = pos;}
    void init();
    vector3 Emit(double i,double j);
    void output(QImage* img);
    void print_data();
};

#endif // CAMERA

