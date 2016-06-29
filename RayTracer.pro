#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T16:47:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    raytracer.cpp \
    primitive.cpp \
    result.cpp \
    light.cpp \
    camera.cpp

HEADERS  += mainwindow.h \
    raytracer.h \
    common.h \
    scene.h \
    light.h \
    result.h \
    primitive.h \
    ray.h \
    camera.h

FORMS    += mainwindow.ui
