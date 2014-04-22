/* INCLUDES */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include "frustum_demo.h"

/* DEFINICOES */

#define NEAR 0.2f
#define FAR 800.0f

/* PROTOTIPOS */

void Display();
void Reshape(int w, int h);

/* MAIN */

int main(int argc,char** argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "Usage: %s <heightmapfile.raw>\n", argv[0]);
        return 1;
    }

    /* Inicializa GLUT */
    glutInit(&argc,argv);

    /* inicializa rand */
    srand(time(NULL));

    /* Cria Janela GLUT */
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(320,240);
    glutCreateWindow("Frustum Culling Demo");

    /* Chama funcao de inicializacao */
    inicializar(argv[1]);

    /* Seta funcoes CallBack */
    glutDisplayFunc(Display);
    //glutReshapeFunc(Reshape);
    Reshape(640,480);

    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutKeyboardFunc(keyboardKeyDown);
    glutKeyboardUpFunc(keyboardKeyUp);

    //glutIdleFunc(atualizar);
    atualizar(0);

    /* Chama loop principal */
    glutMainLoop();

    /* Finaliza aplicacao */
    finalizar();

    return 0;
}

/* CallBack: Desenha cena */

void Display()
{
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

