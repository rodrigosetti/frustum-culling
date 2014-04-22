# Frustum Culling

## Programs

### Frustum

The aim of frustum is to demonstrate the Frustum Culling technique used in most
3D rendering software and games where several object exists in a scene but few
of them have to be rendered in the view-port. To do so this technique uses some
calculation to find out which objects can be seen by the camera and which can
not, thus saving processing time.

![Screen Shot](screenshots/frustum-screen-1.png?raw=true)

To achieve a interesting demonstration the program simulates a virtual camera,
it is a third person camera in which you can observe objects being rendered
inside the view-port normally and wire-frame outside. User can move its real
camera and the virtual camera using the commands:

 * W: Move the user's camera forward
 * S: Move the user's camera backward
 * Arrow keys: Turn user's camera

 * E: Move the virtual camera forward
 * D: Move the virtual camera backward
 * J, K, L, and I: Turn virtual camera

 * 1:  Move the user's camera into virtual camera position
 * 2:  Move the virtual camera into user's camera position

The program accepts one of several height maps(located in `hmaps` directory) to
generate the scene. The scene uses the map and put several procedure generated
objects like trees, rocks, grass and water.

Usage:

    frustum heightmap.raw

### Woods

A non ending woods with several procedure generated objects like threes, rocks,
grass and clouds. The scene never ends because when user reaches a block end
another block is put in front of him to continue path.  Use arrow keys to move.

![Screen Shot](screenshots/woods-screen-1.png?raw=true)

## Building

The dependencies are:

 * OpenGL and GLUT.
 * Cmake.
 * C++ compiler.

To build, just run `cmake` to build the Makefile, and then `make`. The executables will
be placed inside `bin` folder.

