#include <GL/glut.h>
#include <math.h>
#include "camera.h"

/****************************************************************/

#define PARA_RADIANOS (PI/180.0f)
#define PI 3.1415926535897932384626433832795f
#define DPI 6.283185307179586476925286766559f

/****************************************************************/

CAMERA::CAMERA()
{
    posx = posy = posz = 0.0f;
    angx = angy = angz = 0.0f;
}

void CAMERA::GirarLado(float delta)
{
    angy += delta;
}

void CAMERA::GirarFrente(float delta)
{
    angx += delta;
}

void CAMERA::Posicionar()
{
    glRotatef(angx, 1.0f, 0.0f, 0.0f);
    glRotatef(angy, 0.0f, 1.0f, 0.0f);
    glRotatef(angz, 0.0f, 0.0f, 1.0f);

    glTranslatef(posx, posy, posz);
}

void CAMERA::BackwardsPosicionar()
{
    glTranslatef(-posx, -posy, -posz);

    glRotatef(angz, 0.0f, 0.0f, -1.0f);
    glRotatef(angy, 0.0f, -1.0f, 0.0f);
    glRotatef(angx, -1.0f, 0.0f, 0.0f);

}

void CAMERA::Reposicionar()
{
    posx = 0;
    posy = 0;
    posz = 0;
}

void CAMERA::Realinhar()
{
    angx = 0;
    angy = 0;
    angz = 0;
}

void CAMERA::MoverFrente(float delta)
{
    posx += sin(angy * PARA_RADIANOS) * -cos(angz * PARA_RADIANOS) * delta;
    posy += cos(angz * PARA_RADIANOS) * sin(angx * PARA_RADIANOS) * delta;
    posz += cos(angx * PARA_RADIANOS) * cos(angy * PARA_RADIANOS) * delta;
}

void CAMERA::MoverLado(float delta)
{
}

/****************************************************************/
