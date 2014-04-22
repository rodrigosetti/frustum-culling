#ifndef __FRUSTUM_DEMO_H__
#define __FRUSTUM_DEMO_H__

extern void inicializar(char *);

extern void atualizar(int val);

extern void desenhar();

extern void specialKeyUp(int tecla, int x, int y);

extern void specialKeyDown(int tecla, int x, int y);

extern void keyboardKeyUp(unsigned char tecla, int x, int y);

extern void keyboardKeyDown(unsigned char tecla, int x, int y);

extern void finalizar();

#endif /* #ifndef __FRUSTUM_DEMO_H__ */

