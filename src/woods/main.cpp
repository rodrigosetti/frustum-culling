/* INCLUDES */

#include <GL/glut.h>
#include "bosque.h"
#include <time.h>
#include <stdlib.h>

/* DEFINICOES */

#define NEAR 0.4f
#define FAR 254.0f

/* PROTOTIPOS */

void Display();
void Reshape(int w, int h);

/* MAIN */

int main(int argc,char** argv)
{
    /* Inicializa GLUT */
    glutInit(&argc,argv);

    /* Inicializa random */
    srand(time(NULL));

    /* Cria Janela GLUT */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow("3D Woods");

    /* Seta funcoes CallBack */
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutIdleFunc(atualizar);

    /* Chama funcao de inicializacao */
    inicializar();

    /* Chama loop principal */
    glutMainLoop();

    /* Finaliza aplicacao */
    finalizar();

    return 0;
}

/* CallBack: Desenha cena */

void Display()
{
    /* Limpa buffers: imagem e de profundidade */
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /* Carrega matriz identidade para MODELVIEW:
       reseta transformacoes espaciais */
    glLoadIdentity();

    /* Desenha objetos da cena */
    desenhar();

    /* Coloca buffer de imagem para exibição */
    glutSwapBuffers();
}

/* Funcao CallBack: Redimensiona cena */

void Reshape(int w, int h)
{
    /* Previne e trata excecao de divisao por zero */
    if(w==0)
        h = 1;

    /* Redimensiona janela de visao */
    glViewport(0,0,w,h);

    /* Recalcula matriz de projecao */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)w/h,NEAR,FAR);

    /* Retorna para matriz de transformacoes espaciais e limpa-a */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

