#include "bosque.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "../engine/camera.h"
#include "../engine/frustum.h"
#include "../engine/objetos.h"

//*****************************************************************************

#define MAXX 200
#define MAXZ 200

//*****************************************************************************

int random( int numVal )
{
    return rand() % (numVal+1);
}

//*****************************************************************************

class PEDRA
{
    private:
        float posx, posz;
        GLuint ListaPedra;

    public:

        PEDRA()
        {
            float fcor;

            posx = random(MAXX) - (MAXX/2);
            posz = random(MAXZ) - (MAXZ/2);
            fcor = random(50)/100.0f;

            ListaPedra = glGenLists(1);
            glNewList(ListaPedra, GL_COMPILE);
            glPushMatrix();
            glTranslatef(posx, 0.0f, posz);
            EsferaLesada(10, 10, 0.2f + (random(20)/10.0f),0.1f + (random(10)/10.0f), 0.2f + (random(20)/10.0f), random(1000)/1000.0f ,
                    0.2f+fcor,0.2f+fcor,0.2f+fcor, 0.7f+fcor, 0.7f+fcor, 0.7f+fcor);
            glPopMatrix();
            glEndList();
        }

        float GetPosX()
        {
            return posx;
        }
        float GetPosZ()
        {
            return posz;
        }

        void Desenhar()
        {
            glCallList(ListaPedra);
        }
};
//*****************************************************************************
class GRAMA
{
    private:
        float posx, posz;
        GLuint ListaGrama;

    public:

        GRAMA()
        {
            float fcor;

            posx = random(MAXX) - (MAXX/2);
            posz = random(MAXZ) - (MAXZ/2);
            fcor = random(50)/100.0f;

            ListaGrama = glGenLists(1);
            glNewList(ListaGrama, GL_COMPILE);
            glPushMatrix();
            glTranslatef(posx, 0.0f, posz);
            Mato(20, 3.0f, 0.5f, 0.1f+(random(100)/100.0f),
                    0.0f, 0.3+fcor, 0.0f, fcor, 0.5+fcor, 0.5f);
            glPopMatrix();
            glEndList();

        }

        float GetPosX()
        {
            return posx;
        }
        float GetPosZ()
        {
            return posz;
        }

        void Desenhar()
        {
            glCallList(ListaGrama);
        }
};

//*****************************************************************************

void CopaFrutificada(int aneis, int gomos, float raiox, float raioy, float raioz, float perturbacao, float frutificacao,
        float r, float g, float b, float fr, float fg, float fb)
{
    bool *frutas = new bool[aneis * gomos]; //matriz de frutas

    EsferaLesada(aneis, gomos, raiox, raioy, raioz, perturbacao, r, g, b, fr, fg, fb);

    for (int x = 0; x < aneis; x++)
        for (int y = 0; y < gomos; y ++)
            frutas[(x*gomos)+y] = (random(1000) <= (int)(frutificacao * 1000));

    glColor3f(1.0f, 0.1f, 0.0f);

    for (int x = 0; x < aneis; x++) //desenha frutas
        for (int y = 0; y < gomos; y ++)
            if (frutas[(x*gomos)+y])
            {
                glPushMatrix();
                glTranslatef(cos(y * (DPI/aneis))*sin(x * (DPI/gomos))*(raiox+perturbacao),sin(y * (DPI/aneis))*sin(x * (DPI/gomos))*(raioy+perturbacao), cos(x * (DPI/gomos))*(raioz+perturbacao));
                glutSolidSphere(0.3f, 6, 6);
                glPopMatrix();
            }

    delete frutas;
}

//*****************************************************************************

class ARVORE
{
    private:

        float px, pz;
        GLuint ListaArvore;

    public:

        ARVORE()
        {
            float fatorcor;
            float altura = 5+(random(70)/10.0f);

            px = random(MAXX) - (MAXX/2);
            pz = random(MAXZ) - (MAXZ/2);
            fatorcor = random(2000)/10000.0f;

            ListaArvore = glGenLists (1);
            glNewList( ListaArvore, GL_COMPILE);

            glPushMatrix();
            glTranslatef(px, 0.0f, pz);
            glRotatef(random(360), 0.0f, 1.0f, 0.0f);

            if (random(4) == 0)
            {
                TroncoCoqueiro(20, 20,0.3f ,0.3f, altura, 0.5f+(random(1000)/1000.0f), 0.1f,
                        0.5f + fatorcor, 0.5f+ fatorcor, 0.0f+ fatorcor, 1.0f, 1.0f, 0.0f);
                glTranslatef(0.0f, altura, 0.0f);
                CopaCoqueiro(5+random(10), 30, 5.0f+(random(50)/10.0f), 0.5f+(random(100)/100.0f),(random(100)/100.0f)*(PI*0.4f), PI*(3.0f/4.0f),0.5f,
                        0.0f+fatorcor, 0.4f+fatorcor, 0.0f, -0.6, 0.2f, -0.5f);
            }
            else
            {
                Tronco(20, 20,1.0+(random(100)/100.0f) ,0.5f+(random(100)/100.0f), altura, 0.2f,
                        0.3f + fatorcor, 0.2f+ fatorcor, 0.0f+ fatorcor, 1.0f, 0.5f, 0.0f);
                glTranslatef(0.0f, altura, 0.0f);
                if (random(4) == 0)
                    Tronco(20, 20, 4.0f+(random(200)/100.0f), 0.0f ,5+(random(70)/10.0f), 1.0f+(random(100)/100.0f),
                            0.0f+ fatorcor, 0.1f+ fatorcor, 0.0f+ fatorcor, fatorcor, 0.8f, 0.0f);
                else
                    CopaFrutificada(20, 20, 4.0f+(random(200)/100.0f), 1.5 + (random(100)/100.0f),4.0f+(random(200)/100.0f), 0.5f+(random(100)/100.0f), random(10)/1000.0f,
                            0.3f+ fatorcor, 0.3f+ fatorcor, 0.0f+ fatorcor, 0.0f, 0.5f, 0.1f);
            }

            glPopMatrix();

            glEndList();

        }

        float GetPosX()
        {
            return px;
        }
        float GetPosZ()
        {
            return pz;
        }

        void Desenhar()
        {
            glCallList(ListaArvore);
        }

};

//***********************************************************
class NUVEM
{
    private:

        float px, py, pz;
        float vel;

        GLuint ListaNuvem;

    public:

        NUVEM()
        {
            vel = (random(2500)/10000.0f) - 0.125f;

            px = random(MAXX) - (MAXX/2.0f);
            py = 30.0f + (random(300)/10.0f);
            pz = (random(MAXZ) - (MAXZ/2.0f))/ 2.0f;
            ;

            ListaNuvem = glGenLists (1);
            glNewList( ListaNuvem, GL_COMPILE);
            glRotatef(random(360), 0.0f, 1.0f, 0.0f);
            EsferaLesada(50, 50, 3.0f+(random(20000)/1000.0f), 3.0f + (random(4000)/1000.0f),3.0f+(random(20000)/1000.0f), 2.0f+(random(100)/100.0f),
                    0.8f, 0.8f, 0.9f, 1.0f, 1.0f, 1.0f);
            glEndList();
        }

        float GetPosX()
        {
            return px;
        }
        float GetPosY()
        {
            return py;
        }
        float GetPosZ()
        {
            return pz;
        }

        void Desenhar()
        {
            glPushMatrix();
            glTranslatef(px, py, pz);
            glCallList(ListaNuvem);
            glPopMatrix();
        }

        void Atualizar()
        {
            px += vel;
            if (px < -(1.5f*MAXX))
                px = 1.5f*MAXX;
            else if (px > 1.5f*MAXX)
                px = -(1.5f*MAXX);
        }
};
//***********************************************************

#define NARVORES 50
#define NGRAMAS 100
#define NPEDRAS 25
#define NNUVENS 5

#define FATOR_TERRENO 4.0f

float giro = 0.0f;
float veloc = 0.0f;

CAMERA camera1;

bool teclas[256];

//andar, passo
float passo;

//nuvens
NUVEM *nuvens[NNUVENS];
ARVORE *arvores[NARVORES];

//display list
GLuint ListaSol, ListaTerreno;

void DesenhaObjetos()
{
    float frustum[6][4];
    static GRAMA gramas[NGRAMAS];
    static PEDRA pedras[NPEDRAS];

    ExtractFrustum(frustum);

    if (!CubeInFrustum(0.0f, 0.0f, 0.0f, (MAXX > MAXZ)? MAXX : MAXZ, frustum))
        return;

    glCallList(ListaTerreno);

    glColor3f(0.0f, 1.0f, 0.0f);
    for(int i = 0; i < NARVORES; i++)
        if (SphereInFrustum(arvores[i]->GetPosX(), 5.0f, arvores[i]->GetPosZ(), 5.0f, frustum))
            arvores[i]->Desenhar();

    glColor3f(0.0f, 0.6f, 0.0f);
    for(int i = 0; i < NGRAMAS; i++)
        if (SphereInFrustum(gramas[i].GetPosX(), 0.0f, gramas[i].GetPosZ(), 2.0f, frustum))
            gramas[i].Desenhar();

    glColor3f(0.5f, 0.5f, 0.5f);
    for(int i = 0; i < NPEDRAS; i++)
        if (SphereInFrustum(pedras[i].GetPosX(), 0.0f, pedras[i].GetPosZ(), 2.0f, frustum))
            pedras[i].Desenhar();

    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i = 0; i < NNUVENS; i++)
        if (SphereInFrustum(nuvens[i]->GetPosX(), nuvens[i]->GetPosY(), nuvens[i]->GetPosZ(), 23.0f, frustum))
            nuvens[i]->Desenhar();

}


void inicializar()
{
    // glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
    glClearColor(0.5f, 1.0f, 1.0f, 0.5f);    // Black Background
    glClearDepth(1.0f);         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

    glDisable(GL_BLEND);
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);

    giro = 0.0f;
    veloc = 0.0f;

    for (int i = 0; i < 256; i++)
        teclas[i] = false;

    //cria display lists

    ListaSol = glGenLists (1);
    glNewList( ListaSol, GL_COMPILE);
    glTranslatef(0.0f, 40.0f, -250.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(8.0f, 10, 10);
    glEndList();

    ListaTerreno = glGenLists (1);
    glNewList( ListaTerreno, GL_COMPILE);
    glPushMatrix();
    glScalef(FATOR_TERRENO, 1.0f, FATOR_TERRENO);
    Superficie(0.8f, (int)(MAXX/FATOR_TERRENO)+1, (int)(MAXZ/FATOR_TERRENO)+1,
            0.0f, 0.5f, 0.2f, 0.5f, 2.0f, 0.0f);
    glPopMatrix();
    glEndList();

    //inicializa nuvens
    for(int i = 0; i < NNUVENS; i++)
        nuvens[i] = new NUVEM();

    //inicializa arvores
    for(int i = 0; i < NARVORES; i++)
        arvores[i] = new ARVORE();

    passo = 0.0f;
}

void specialKeyUp(int key, int x, int y)
{
    teclas[key] = false;
}

void specialKeyDown(int key, int x, int y)
{
    teclas[key] = true;
}

#define ACELGIRO 1.0f
#define ACELVELOC 1.0f
#define ATRITOGIRO 0.6f
#define ATRITOVELOC 0.8f
#define VELOCMAX 10.5f

void atualizar()
{

    if (teclas[GLUT_KEY_UP])
        veloc += ACELVELOC;
    if (teclas[GLUT_KEY_DOWN])
        veloc -= ACELVELOC;
    if (teclas[GLUT_KEY_LEFT])
        giro -= ACELGIRO;
    if (teclas[GLUT_KEY_RIGHT])
        giro += ACELGIRO;

    if (veloc > VELOCMAX)
        veloc = VELOCMAX;
    if (veloc < -VELOCMAX)
        veloc = -VELOCMAX;

    camera1.GirarLado(giro);
    camera1.MoverFrente(veloc);
    passo += veloc + 0.05f;

    //atualiza nuvens
    for(int i = 0; i < NNUVENS; i++)
        nuvens[i]->Atualizar();

    float cposx = ((floor((camera1.GetPosX()+(MAXX/2.0f))/MAXX) * MAXX) - camera1.GetPosX());
    float cposz = ((floor((camera1.GetPosZ()+(MAXZ/2.0f))/MAXZ) * MAXZ) - camera1.GetPosZ());

    //verifica colisão com alguma arvore
    for(int i = 0; i < NARVORES; i++)
        if (sqrt( ((arvores[i]->GetPosX()-cposx)*(arvores[i]->GetPosX()-cposx)) +
                    ((arvores[i]->GetPosZ()-cposz)*(arvores[i]->GetPosZ()-cposz)) ) <= 2.0f)
        {
            camera1.MoverFrente(-veloc); //desfaz movimento
            camera1.GirarLado(-giro);
            veloc = -veloc; //rebate
            giro = -giro;
        }

    //aplica atrito
    giro *= ATRITOGIRO;
    veloc *= ATRITOVELOC;

    /* Requisita redesenho */
    glutPostRedisplay();
}

void desenhar()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();         // Reset The Current Modelview Matrix
    camera1.Posicionar();

    glTranslatef(0.0f, cos(passo)/5.0f, 0.0f);
    glTranslatef(0.0f, -3.5f, 2.0f);

    //********
    int centrox = (int)floor((camera1.GetPosX()+(MAXX/2.0f))/MAXX) * MAXX;
    int centroz = (int)floor((camera1.GetPosZ()+(MAXZ/2.0f))/MAXZ) * MAXZ;

    glPushMatrix();
    glTranslatef(-centrox, 0.0f, -centroz);

    DesenhaObjetos();
    glTranslatef(-MAXX, 0.0f, 0.0f);
    DesenhaObjetos();
    glTranslatef(2*MAXX, 0.0f, 0.0f);
    DesenhaObjetos();
    glTranslatef(-MAXX, 0.0f, -MAXZ);
    DesenhaObjetos();
    glTranslatef(0.0f, 0.0f, 2*MAXZ);
    DesenhaObjetos();
    glTranslatef(-MAXX, 0.0f, 0.0f);
    DesenhaObjetos();
    glTranslatef(2*MAXX, 0.0f, 0.0f);
    DesenhaObjetos();
    glTranslatef(0.0f, 0.0f, -(2*MAXZ));
    DesenhaObjetos();
    glTranslatef(-(2*MAXX), 0.0f, 0.0f);
    DesenhaObjetos();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glRotatef((camera1.GetAngY()/2)-15.0f, 0.0f, 1.0f, 0.0f);
    glCallList(ListaSol); //desenha sol
    glPopMatrix();
}


void finalizar()
{
    //deleta objetos
    for(int i = 0; i < NNUVENS; i++)
        delete nuvens[i];
    //delete nuvens;

    for(int i = 0; i < NARVORES; i++)
        delete arvores[i];
    //delete arvores;
}

