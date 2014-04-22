#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

/****************************************************************/
/* DEFINICOES */

/* Significado dos indices da primeira dimensao da matriz frustum */
#define PRIGHT  0
#define PLEFT   1
#define PBOTTON 2
#define PTOP    3
#define PFAR    4
#define PNEAR   5

/****************************************************************/
/* PROTOTIPOS */

/* Captura matriz PROJECTION que representa o solido de visao (frustum) */
extern void ExtractFrustum(float frustum[6][4]);

/* Verifica se o ponto esta contido no frustum */
extern bool PointInFrustum( float x, float y, float z,float frustum[6][4] );

/* Verifica se algum ponto da esfera esta contido no frustum */
extern bool SphereInFrustum( float x, float y, float z, float radius,float frustum[6][4]  );

/* Verifica se algum ponto do cubo esta contido no frustum */
extern bool CubeInFrustum( float x, float y, float z, float size,float frustum[6][4]  );

/****************************************************************/

#endif /* #ifndef __FRUSTUM_H__ */

