# Suchiz-Rendring-Engine

Requires at least OpenGL 3.3, Qt 4.7 and C++11
This is a small 3D Engine made for a university project purpose.

![alt text](./Resources/Demo.png?raw=true "Suchiz 3D Engine")

This contains a Blinn-Phong lightning and shadowmaps for the rendering part, nurbs/b-splines for the geometry part, and finally Linear Blending Skinning on GPU for the animation part.
You have the possibility to create your own scene.

Compile:
1) git clone https://github.com/suchiz/Suchiz-Rendring-Engine.git
2) cd ~/Suchiz-Rendring-Engine
3) Generate your own glad.c at https://glad.dav1d.de/ replace it in External directory, and move glad.h into your includes directory
4) qmake RenduProject.pro
5) make -j4
6) make clean
7) open Scene/shader.h, change the absolute path, or use the relative path by adding the variable "path" I've created
7) ./Suchiz-Rendring-Engine

Usage:
Draw a cube, draw a plane, draw a sphere, draw a nurbs surface while playing with the color, and the position.
You can modify nurbs surfaces, and move the light.

Z/Q/S/D to move the camera, and click and rotate to change the view and increase the height and the distance of the light
Z/Q/S/D/T/B for nurbs editing and animation
If you let a blank, the default values are: 
Size = (1,1,1), color = (255,255,255), position = (0,0,0), rotation = (0,0,0) for objects
height =2, width = 2, color = (255,255,255), position = (0,0,0) for nurbs

You can find demos at: 
https://drive.google.com/file/d/1tCMC7BInzmJ8H0W1BcLmhXj2yWSW2y4c/view?usp=sharing
https://drive.google.com/file/d/1gMGxQxszM15c775RfD36k2QyhtkJzoPh/view?usp=sharing


