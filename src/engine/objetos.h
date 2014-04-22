#ifndef __OBJETOS_H__
#define __OBJETOS_H__

/*
OBJETOS:

Possui uma colecao de funcoes que desenham varios objetos gerados
proceduralmente.
*/

/****************************************************************/
/* DEFINICOES */

#define PI 3.1415926535897932384626433832795f
#define DPI 6.283185307179586476925286766559f

/****************************************************************/

extern void EsferaLesada(int aneis, int gomos, float raiox, float raioy, float raioz, float perturbacao,
        float r, float gr, float b, float fr, float fgr, float fb);

/****************************************************************/

extern void Tronco(int aneis, int gomos, float raiomin, float raiomax, float altura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   );

/****************************************************************/

extern void Mato(int ramos, float altura, float grossura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb);

/****************************************************************/

extern void Superficie(float amplitude, int tamx, int tamy,
        float r, float g, float b, float fr, float fg, float fb);

/****************************************************************/

extern void CopaCoqueiro(int ramos, int gomos, float comprimento, float grossura, float angulacao, float decaimento, float perturbacao,
        float rd, float gr, float b, float fr, float fg, float fb);

/****************************************************************/

extern void TroncoCoqueiro(int aneis, int gomos, float raiomin, float raiomax, float altura, float curvatura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   );

/****************************************************************/

#endif /* #ifndef __OBJETOS_H__ */
