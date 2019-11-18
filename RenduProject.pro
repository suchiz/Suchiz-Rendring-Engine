#-------------------------------------------------
#
# Project created by QtCreator 2019-10-21T13:54:55
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -ldl

QMAKE_CXXFLAGS += -std=c++11

QT += widgets

TARGET = RenduProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glad.c \
    cube.cpp \
    scene.cpp \
    light.cpp \
    plane.cpp \
    sphere.cpp \
    depthmap.cpp \
    openglwindow.cpp \
    drawableobject.cpp \
    bspline.cpp \
    tensorproduct.cpp

HEADERS  += mainwindow.h \
    shader.h \
    glm/common.hpp \
    glm/exponential.hpp \
    glm/ext.hpp \
    glm/fwd.hpp \
    glm/geometric.hpp \
    glm/glm.hpp \
    glm/integer.hpp \
    glm/mat2x2.hpp \
    glm/mat2x3.hpp \
    glm/mat2x4.hpp \
    glm/mat3x2.hpp \
    glm/mat3x3.hpp \
    glm/mat3x4.hpp \
    glm/mat4x2.hpp \
    glm/mat4x3.hpp \
    glm/mat4x4.hpp \
    glm/matrix.hpp \
    glm/packing.hpp \
    glm/trigonometric.hpp \
    glm/vec2.hpp \
    glm/vec3.hpp \
    glm/vec4.hpp \
    glm/vector_relational.hpp \
    cube.h \
    camera.h \
    scene.h \
    light.h \
    plane.h \
    sphere.h \
    depthmap.h \
    openglwindow.h \
    drawableobject.h \
    bspline.h \
    tensorproduct.h

FORMS    += mainwindow.ui

DISTFILES += \
    blinnphong.vs \
    blinnphong.fs \
    lightshader.vs \
    lightshader.fs \
    depthmapshader.vs \
    depthmapshader.fs
