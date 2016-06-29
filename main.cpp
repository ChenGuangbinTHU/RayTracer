#include "mainwindow.h"
#include "raytracer.h"
#include <QApplication>
#include <QImage>
#include <QDebug>
#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    freopen("ray.txt","w",stdout);
    vector3 start = vector3(-1.0f,0.0f,0.0f);
    Raytracer raytracer;
    raytracer.Run();
    //MainWindow w;
    //w.show();
    return 0;
}
