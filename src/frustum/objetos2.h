#ifndef __OBJETOS_2_H__
#define __OBJETOS_2_H__

#include <GL/glut.h>

/*
   OBJETOS 2:

   Possui uma colecao de funcoes que desenham varios objetos gerados
   proceduralmente.
   */

#define DPI 6.283185307179586476925286766559f
#define PI 3.1415926535897932384626433832795f

/****************************************************************/

extern void EsferaLesada2(GLuint &lista1, GLuint &lista2, float raiox, float raioy, float raioz, float perturbacao,
        float r, float gr, float b, float fr, float fgr, float fb);

/****************************************************************/

extern void Tronco2(GLuint &lista1, GLuint &lista2, float raiomin, float raiomax, float altura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   );

/****************************************************************/

extern void Mato2(GLuint *lista1, GLuint *lista2, float altura, float grossura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb);


/****************************************************************/

extern void CopaCoqueiro2(GLuint &lista1, GLuint &lista2, float comprimento, float grossura, float angulacao, float decaimento, float perturbacao,
        float rd, float gr, float b, float fr, float fg, float fb);

/****************************************************************/

extern void TroncoCoqueiro2(GLuint &lista1, GLuint &lista2, int aneis, int gomos, float raiomin, float raiomax, float altura, float curvatura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   );

/****************************************************************/

#endif /* #ifndef __OBJETOS_2_H__ */
