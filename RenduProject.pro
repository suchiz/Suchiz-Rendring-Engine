#-------------------------------------------------
#
# Project created by QtCreator 2019-10-21T13:54:55
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -ldl

QMAKE_CXXFLAGS += -std=c++11

QT += widgets

TARGET = Suchiz-Rendering-Project
TEMPLATE = app

SOURCES += Scene/main.cpp\
        Scene/mainwindow.cpp \
    External/glad.c \
    Objects/cube.cpp \
    Scene/scene.cpp \
    Scene/light.cpp \
    Objects/plane.cpp \
    Objects/sphere.cpp \
    Scene/depthmap.cpp \
    Scene/openglwindow.cpp \
    Surfaces/bspline.cpp \
    Surfaces/tensorproduct.cpp \
    Objects/capsule.cpp \
    UI/adddialog.cpp

HEADERS  += Scene/mainwindow.h \
    Scene/shader.h \
    External/glm/common.hpp \
    External/glm/exponential.hpp \
    External/glm/ext.hpp \
    External/glm/fwd.hpp \
    External/glm/geometric.hpp \
    External/glm/glm.hpp \
    External/glm/integer.hpp \
    External/glm/mat2x2.hpp \
    External/glm/mat2x3.hpp \
    External/glm/mat2x4.hpp \
    External/glm/mat3x2.hpp \
    External/glm/mat3x3.hpp \
    External/glm/mat3x4.hpp \
    External/glm/mat4x2.hpp \
    External/glm/mat4x3.hpp \
    External/glm/mat4x4.hpp \
    External/glm/matrix.hpp \
    External/glm/packing.hpp \
    External/glm/trigonometric.hpp \
    External/glm/vec2.hpp \
    External/glm/vec3.hpp \
    External/glm/vec4.hpp \
    External/glm/vector_relational.hpp \
    Objects/cube.h \
    Scene/camera.h \
    Scene/scene.h \
    Scene/light.h \
    Objects/plane.h \
    Objects/sphere.h \
    Scene/depthmap.h \
    Scene/openglwindow.h \
    Objects/drawableobject.h \
    Surfaces/bspline.h \
    Surfaces/tensorproduct.h \
    Objects/capsule.h \
    UI/adddialog.h

FORMS    += UI/mainwindow.ui \
    UI/adddialog.ui

DISTFILES += \
    Shaders/blinnphong.vs \
    Shaders/lightshader.vs \
    Shaders/lightshader.fs \
    Shaders/depthmapshader.vs \
    Shaders/depthmapshader.fs \
    Shaders/blinnphong.fs
