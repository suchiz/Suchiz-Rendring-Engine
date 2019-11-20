# Suchiz-Rendring-Engine

Requires at least OpenGL 3.3, Qt 4.7 and C++11
This is a small 3D Engine made for a university project purpose.

This contains a Blinn-Phong lightning and shadowmaps for the rendering part.
You have the possibility to create your own scene, or use the demo scene.

Compile:
1) git clone https://github.com/suchiz/Suchiz-Rendring-Engine.git
2) cd ~/Suchiz-Rendring-Engine
3) Generate your own glad.c at https://glad.dav1d.de/ replace it in External directory, and move glad.h into your includes directory
4) qmake RenduProject.pro
5) make
6) make clean
7) ./Suchiz-Rendring-Engine


Usage:
Draw a cube, draw a plane, draw a sphere, draw a nurbs surface while playing with the color, and the position.
You can modify nurbs surfaces, and move the light.

Z/Q/S/D to move the camera, and click and rotate to change the view.
If move light is ticked, the light will do some circle, then use Z/Q/S/D to increase the height and the distance.
If you let a blank, the default values are: 
Size = 1, color = (1,1,1), position = (0,0,0), rotation = (0,0,0) for objects
height = 3, width = 3, color = (1,1,1), position = (0,0,0) for nurbs

You can find a full demo at: 
https://drive.google.com/file/d/1LfFDe1iO9OX7FpwCynKNQcrEHGYanHxr/view?fbclid=IwAR2Im6su9RlvRiJp8YjFWXbiTvhFCYRYcNskIArWCs8yjseaPuafxOD5DIg


