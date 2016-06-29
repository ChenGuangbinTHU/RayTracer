#include "camera.h"
#include <stdlib.h>
#include <iostream>
#include <QColor>

using namespace std;

Camera::Camera()
{
    O=vector3(0,-10000,0);
    N = vector3(0,1,0);
    lens_W = STD_LENS_WIDTH;
    lens_H = STD_LENS_HEIGHT;
    W = STD_IMAGE_WIDTH;
    H = STD_IMAGE_HEIGHT;
    data = NULL;
}

Camera::~Camera()
{
    //if(data == NULL)
    //{
        for(int i = 0;i < H;i++)
            delete[] data[i];
        delete[] data;
        //qDebug()<<'.';
    //}
}

void Camera::init()
{
    N.Normalize();
    Dx = N.get_vertical_vector();
    Dy = Dx*N;
    Dx = Dx*lens_W*0.5f;
    Dy = Dy*lens_H*0.5f;

    data = new Color*[H];
    for(int i = 0;i < H;i++)
        data[i] = new Color[W];
}

vector3 Camera::Emit(double i, double j)
{
    //return N + Dy * ( 2 * i / H - 1 ) + Dx * ( 2 * j / W - 1 );

}

void Camera::output(QImage *img)
{
    for(int i = 0;i < H;i++)
    {
        for(int j = 0;j < W;j++)
        {
            vector3 v = data[i][j];
            //v.output();
            //cout<<v.x<<endl;
            int x_color = v.x * 255;
            cout<<x_color<<endl;
            QColor rgb = QColor(min(x_color,255),min(int(v.y*255),255),min(int(v.z*255),255));
            QRgb q = qRgb(min(x_color,255),min(int(v.y*255),255),min(int(v.z*255),255));

            img->setPixel(i,j,q);
        }
    }
}

void Camera::print_data()
{
    //freopen("q.txt","w",stdout);
    for(int i = 0;i < W;i++)
    {
        for(int j = 0;j < H;j++)
        {
            cout<<data[i][j].x<<" "<<data[i][j].y<<" "<<data[i][j].z<<endl;
        }
    }
}
