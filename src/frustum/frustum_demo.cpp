#include "frustum_demo.h"

#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../engine/camera.h"
#include "../engine/frustum.h"

#include "objetos2.h"

//*****************************************************

#define MAXX      100
#define MAXZ      100
#define ESCALA    3.0f
#define AMPLITUDE 50.0f

int *m;
float *n;

#define NIVELAGUA  80
#define NIVELNEVE  200
#define NIVELAREIA 90

#define GLPERSPECTIVA 45.0f
#define PERSPECH      25.0f
#define PERSPECW      30.0f
#define GLNEAR        0.1f
#define GLFAR         300.0f

//*****************************************************************************

float frustum1[6][4];
float frustum2[6][4];

//*****************************************************************************

int random( int numVal )
{
    return rand() % (numVal + 1);
}

//*****************************************************************************

class ESTRELA
{
    private:
        float posx, posy, posz;

    public:

        ESTRELA()
        {
#define eRAIO (GLFAR/ESCALA-10.0f);
            int a = random(MAXX);
            int g = -(random(MAXZ)/2) + (MAXZ/4);

            posx = cos(a*PI/(MAXX-1)) * eRAIO;
            posz = sin(g*DPI/(MAXZ-1)) * sin(a*PI/(MAXX-1)) * eRAIO;
            posy = cos(g*DPI/(MAXZ-1)) * sin(a*PI/(MAXX-1)) * eRAIO;

        }

        void Desenhar()
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_POINTS);
            glVertex3f(posx*ESCALA, posy*ESCALA, posz*ESCALA);
            glEnd();
        }
};


//*****************************************************************************

class PEDRA
{
    private:
        float posx, posz, posy;
        GLuint ListaPedra1;
        GLuint ListaPedra2;

    public:

        PEDRA()
        {
            float fcor;

            do
            {
                posx = random(MAXX) - (MAXX/2);
                posz = random(MAXZ) - (MAXZ/2);
            }
            while (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] <= NIVELAGUA);

            posy = m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] * (AMPLITUDE/255.0f);
            fcor = random(50)/100.0f;

            EsferaLesada2(ListaPedra1, ListaPedra2, 0.2f + (random(20)/10.0f),0.1f + (random(10)/10.0f), 0.2f + (random(20)/10.0f), random(1000)/1000.0f ,
                    0.2f+fcor,0.2f+fcor,0.2f+fcor, 0.7f+fcor, 0.7f+fcor, 0.7f+fcor);
        }

        float GetPosX()
        {
            return posx * ESCALA;
        }
        float GetPosZ()
        {
            return posz * ESCALA;
        }
        float GetPosY()
        {
            return posy* ESCALA;
        }

        void Desenhar(bool wire)
        {
            glPushMatrix();
            glTranslatef(posx*ESCALA, posy*ESCALA, posz*ESCALA);
            glCallList((wire)? ListaPedra2 : ListaPedra1);
            glPopMatrix();
        }
};
//*****************************************************************************
class GRAMA
{
    private:
        float posx, posz, posy;
        GLuint ListaGrama1;
        GLuint ListaGrama2;

    public:

        GRAMA()
        {
            float fcor;

            do
            {
                posx = random(MAXX) - (MAXX/2);
                posz = random(MAXZ) - (MAXZ/2);
            }
            while (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] <= NIVELAGUA);

            posy = m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] * (AMPLITUDE/255.0f);
            fcor = random(50)/100.0f;

            Mato2(&ListaGrama1, &ListaGrama2, 3.0f, 0.5f, 0.1f+(random(100)/100.0f),
                    0.0f, 0.3+fcor, 0.0f, fcor, 0.5+fcor, 0.5f);

        }

        float GetPosX()
        {
            return posx * ESCALA;
        }
        float GetPosZ()
        {
            return posz * ESCALA;
        }
        float GetPosY()
        {
            return posy* ESCALA;
        }

        void Desenhar(bool wire)
        {
            glPushMatrix();
            glTranslatef(posx*ESCALA, posy*ESCALA, posz*ESCALA);
            glCallList((wire)? ListaGrama2 : ListaGrama1);
            glPopMatrix();
        }
};

//*****************************************************************************
//*****************************************************************************

class ARVORE
{
    private:

        float posx, posz, posy, ang, altura;

        GLuint Listatronco1;
        GLuint Listatronco2;

        GLuint Listacopa1;
        GLuint Listacopa2;

    public:

        ARVORE()
        {
            float fatorcor;
            float cor1 = 0.0f,
                  cor2 = 0.5f,
                  cor3 = 0.0f;

            altura = 5+(random(70)/10.0f);

            do
            {
                posx = random(MAXX) - (MAXX/2);
                posz = random(MAXZ) - (MAXZ/2);
            }
            while (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] <= NIVELAGUA);

            posy = m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] * (AMPLITUDE/255.0f);
            fatorcor = random(2000)/10000.0f;
            ang = random(361);


            if (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))]+3 >= NIVELNEVE)
            {
                cor1 = 1.0f;
                cor2 = 1.0f;
                cor3 = 1.0f;
            }

            if (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] <= 100)
            {
                TroncoCoqueiro2(Listatronco1, Listatronco2, 10, 10,0.3f ,0.3f, altura, 0.5f+(random(1000)/1000.0f), 0.1f,
                        0.5f + fatorcor, 0.5f+ fatorcor, 0.0f+ fatorcor, 1.0f, 1.0f, 0.0f);
                CopaCoqueiro2(Listacopa1, Listacopa2, 5.0f+(random(50)/10.0f), 0.5f+(random(100)/100.0f),(random(100)/100.0f)*(PI*0.4f), PI*(3.0f/4.0f),0.5f,
                        0.0f+fatorcor, 0.4f+fatorcor, 0.0f, -0.6, 0.2f, -0.5f);
            }
            else
            {
                Tronco2(Listatronco1, Listatronco2, 1.0+(random(100)/100.0f) ,0.5f+(random(100)/100.0f), altura, 0.2f,
                        0.3f + fatorcor, 0.2f+ fatorcor, 0.0f+ fatorcor, 1.0f, 0.5f, 0.0f);
                glTranslatef(0.0f, altura, 0.0f);
                if (m[(((int)posx + (MAXX/2)) * MAXX) + ((int)posz + (MAXZ/2))] >= 150)
                    Tronco2(Listacopa1, Listacopa2, 4.0f+(random(200)/100.0f), 0.0f ,5+(random(70)/10.0f), 1.0f+(random(100)/100.0f),
                            0.0f+ fatorcor, 0.1f+ fatorcor, 0.0f+ fatorcor, cor1, cor2, cor3);
                else
                    EsferaLesada2(Listacopa1, Listacopa2, 4.0f+(random(200)/100.0f), 1.5 + (random(100)/100.0f),4.0f+(random(200)/100.0f), 0.5f+(random(100)/100.0f),
                            0.2f+ fatorcor, 0.3f+ fatorcor, 0.0f+ fatorcor, 0.0f, 0.8f, 0.0f);
            }

        }

        float GetPosX()
        {
            return posx * ESCALA;
        }
        float GetPosZ()
        {
            return posz * ESCALA;
        }
        float GetPosY()
        {
            return posy* ESCALA;
        }

        void Desenhar(bool wire)
        {
            glPushMatrix();
            glTranslatef(posx*ESCALA, (posy*ESCALA), posz*ESCALA);
            glRotatef(ang, 0.0f, 1.0f, 0.0f);

            if (wire)
            {
                glCallList(Listatronco2);
                glTranslatef(0.0f, altura, 0.0f);
                glCallList(Listacopa2);
            }
            else
            {
                glCallList(Listatronco1);
                glTranslatef(0.0f, altura, 0.0f);
                glCallList(Listacopa1);
            }
            glPopMatrix();
        }

};

//***********************************************************

//*****************************************************************************

class PISO
{
    private:

        int posx, posz;

    public:

        PISO()
        {
            posx = posz = 0;
        }

        PISO(int px, int pz)
        {
            posx = px;
            posz = pz;
        }

#define amp  (AMPLITUDE / 255.0f)

        bool noFrustum(float frustum [6][4])
        {
            bool r = false;

            r = r || SphereInFrustum((posx - (MAXX/2.0f))*ESCALA,m[(posx * MAXZ) + posz]*amp*ESCALA,(posz-(MAXZ/2.0f))*ESCALA, ESCALA, frustum);
            r = r || SphereInFrustum((posx+1 - (MAXX/2.0f))*ESCALA,m[((posx+1) * MAXZ) + posz]*amp*ESCALA,(posz-(MAXZ/2.0f))*ESCALA, ESCALA, frustum);
            r = r || SphereInFrustum((posx - (MAXX/2.0f))*ESCALA,m[(posx * MAXZ) + posz+1]*amp*ESCALA,(posz+1-(MAXZ/2.0f))*ESCALA, ESCALA, frustum);
            r = r || SphereInFrustum((posx+1 - (MAXX/2.0f))*ESCALA,m[((posx+1) * MAXZ) + posz+1]*amp*ESCALA,(posz+1-(MAXZ/2.0f))*ESCALA, ESCALA, frustum);

            return r;
        }

        void Desenhar(GLbyte modo, float fr, float fg, float fb)
        {

#define FATOR 3.0f
#define AM1 0.8f
#define AM2 0.7f
#define AM3 0.2f

            glBegin(modo);

            if (m[(posx * MAXZ) + posz] >= NIVELNEVE)
                glColor3b(0.5f*m[(posx * MAXZ) + posz],0.5f*m[(posx * MAXZ) + posz],0.5f*m[(posx * MAXZ) + posz]);
            else if (m[(posx * MAXZ) + posz] >= NIVELAREIA)
                glColor3b(fr*m[(posx * MAXZ) + posz],fg*m[(posx * MAXZ) + posz],fb*m[(posx * MAXZ) + posz]);
            else if (m[(posx * MAXZ) + posz] > NIVELAGUA)
                glColor3b(AM1*m[(posx * MAXZ) + posz],AM2*m[(posx * MAXZ) + posz],AM3*m[(posx * MAXZ) + posz]);
            else
                glColor3b(0,sin(n[(posx*MAXZ)+posz])*m[(posx * MAXZ) + posz],m[(posx * MAXZ) + posz]);

            glVertex3f(posx-(MAXX/2), ((float)m[(posx * MAXZ) + posz]*amp)+(sin(n[(posx*MAXZ)+posz])/FATOR), posz-(MAXZ/2));

            if (m[((posx+1) * MAXZ) + posz] >= NIVELNEVE)
                glColor3b(0.5f*m[((posx+1) * MAXZ) + posz],0.5f*m[((posx+1) * MAXZ) + posz],0.5f*m[((posx+1) * MAXZ) + posz]);
            else if (m[((posx+1) * MAXZ) + posz] >= NIVELAREIA)
                glColor3b(fr*m[((posx+1) * MAXZ) + posz],fg*m[((posx+1) * MAXZ) + posz],fb*m[((posx+1) * MAXZ) + posz]);
            else if (m[((posx+1) * MAXZ) + posz] > NIVELAGUA)
                glColor3b(AM1*m[((posx+1) * MAXZ) + posz],AM2*m[((posx+1) * MAXZ) + posz],AM3*m[((posx+1) * MAXZ) + posz]);
            else
                glColor3b(0,sin(n[((posx+1)*MAXZ)+posz])*m[((posx+1) * MAXZ) + posz],m[((posx+1) * MAXZ) + posz]);

            glVertex3f(posx-(MAXX/2)+1, ((float)m[((posx+1) * MAXZ) + posz]*amp)+(sin(n[((posx+1)*MAXZ)+posz])/FATOR), posz-(MAXZ/2));

            if (m[(posx * MAXZ) + posz+1] >= NIVELNEVE)
                glColor3b(0.5f*m[(posx * MAXZ) + posz+1],0.5f*m[(posx * MAXZ) + posz+1],0.5f*m[(posx * MAXZ) + posz+1]);
            else if (m[(posx * MAXZ) + posz + 1] >= NIVELAREIA)
                glColor3b(fr*m[(posx * MAXZ) + posz + 1],fg*m[(posx * MAXZ) + posz + 1],fb*m[(posx * MAXZ) + posz + 1]);
            else if (m[(posx * MAXZ) + posz+1] > NIVELAGUA)
                glColor3b(AM1*m[(posx * MAXZ) + posz+1],AM2*m[(posx * MAXZ) + posz+1],AM3*m[(posx * MAXZ) + posz+1]);
            else
                glColor3b(0,sin(n[(posx*MAXZ)+posz+1])*m[(posx * MAXZ) + posz + 1],m[(posx * MAXZ) + posz + 1]);
            glVertex3f(posx-(MAXX/2), ((float)m[(posx * MAXZ) + posz + 1]*amp)+(sin(n[(posx*MAXZ)+posz+1])/FATOR), posz-(MAXZ/2)+1);

            if (m[((posx+1) * MAXZ) + posz+1] >= NIVELNEVE)
                glColor3b(0.5f*m[((posx+1) * MAXZ) + posz+1],0.5f*m[((posx+1) * MAXZ) + posz+1],0.5f*m[((posx+1) * MAXZ) + posz+1]);
            else if (m[((posx+1) * MAXZ) + posz + 1] >= NIVELAREIA)
                glColor3b(fr*m[((posx+1) * MAXZ) + posz + 1],fg*m[((posx+1) * MAXZ) + posz + 1],fb*m[((posx+1) * MAXZ) + posz + 1]);
            else if (m[((posx+1) * MAXZ) + posz+1] > NIVELAGUA)
                glColor3b(AM1*m[((posx+1) * MAXZ) + posz+1],AM2*m[((posx+1) * MAXZ) + posz+1],AM3*m[((posx+1) * MAXZ) + posz+1]);
            else
                glColor3b(0,sin(n[((posx+1)*MAXZ)+posz + 1])*m[((posx+1) * MAXZ) + posz + 1],m[((posx+1) * MAXZ) + posz + 1]);

            glVertex3f(posx-(MAXX/2)+1, ((float)m[((posx+1) * MAXZ) + posz +1]*amp)+(sin(n[((posx+1)*MAXZ)+posz + 1])/FATOR), posz-(MAXZ/2)+1);

            glEnd();
        }

};

//*****************************************************************************

/*
   Abre matriz salva no disco dado o nome do arquivo em W.
   */
void AbrirTerreno(char *nome, int *m, int nLinhas,int nColunas)
{
    FILE *arq;
    char k;

    if ((arq = fopen(nome, "r")) == NULL)
    {
        fprintf(stderr, "\nERRO: ABERTURA DO ARQUIVO.\n");
        exit(0);
    }

    for (int p = 0; p < nLinhas*nColunas; p++)
        m[p] = fgetc(arq);

    fclose(arq);
}

//*****************************************************

CAMERA camera1;
CAMERA camera2;

//teclas
bool keys[256+256];

PISO *pisos;

#define PI 3.1415926535897932384626433832795f
#define PARA_RADIANOS (PI/180.0f)

#define NARVORES 38
#define NGRAMAS 25
#define NPEDRAS 20

void DesenharObjetos()
{
    static GRAMA gramas[NGRAMAS];
    static PEDRA pedras[NGRAMAS];
    static ARVORE arvores[NARVORES];

    //Desenha terreno
    glPushMatrix();
    glScalef(ESCALA, ESCALA, ESCALA);

    for (int x = 0; x < MAXX-1; x ++)
        for (int z = 0; z < MAXZ-1; z ++)
            if (pisos[(x*MAXZ)+z].noFrustum(frustum1))
            {
                if (pisos[(x*MAXZ)+z].noFrustum(frustum2))
                    pisos[(x*MAXZ)+z].Desenhar(GL_TRIANGLE_STRIP, 0.0f, 0.5f, 0.0f);
                else
                    pisos[(x*MAXZ)+z].Desenhar(GL_LINE_STRIP, 0.0f, 0.5f, 0.0f);
            }

    glPopMatrix();

    //desenha objetos

    for(int i = 0; i < NARVORES; i++)
        if (SphereInFrustum(arvores[i].GetPosX(), arvores[i].GetPosY()+3.0f, arvores[i].GetPosZ(), 7.5f, frustum1))
            arvores[i].Desenhar(!SphereInFrustum(arvores[i].GetPosX(), arvores[i].GetPosY()+3.0f, arvores[i].GetPosZ(), 7.5f, frustum2));

    for(int i = 0; i < NGRAMAS; i++)
        if (SphereInFrustum(gramas[i].GetPosX(), gramas[i].GetPosY(), gramas[i].GetPosZ(), 2.5f, frustum1))
            gramas[i].Desenhar(!SphereInFrustum(gramas[i].GetPosX(), gramas[i].GetPosY(), gramas[i].GetPosZ(), 2.5f, frustum2));

    for(int i = 0; i < NPEDRAS; i++)
        if (SphereInFrustum(pedras[i].GetPosX(), pedras[i].GetPosY(), pedras[i].GetPosZ(), 2.5f, frustum1))
            pedras[i].Desenhar(!SphereInFrustum(pedras[i].GetPosX(), pedras[i].GetPosY(), pedras[i].GetPosZ(), 2.5f, frustum2));

    //Desenha Frustum
    glPushMatrix();

    glEnable(GL_BLEND);  // Turn Blending On
    // glDisable(GL_DEPTH_TEST); // Turn Depth Testing Off

    glTranslatef(0.0f, AMPLITUDE * ESCALA , 60.0f);
    camera2.BackwardsPosicionar();

    glColor4f(0.0f, 1.0f, 1.0f, 1.0f); //cor
    glBegin(GL_LINE_LOOP);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glEnd();
    glBegin(GL_QUADS);
    glColor4f(0.0f, 1.0f, 1.0f, 0.2f); //cor
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR,- GLNEAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);

    glColor4f(0.0f, 0.8f, 0.8f, 0.2f); //cor
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);

    glColor4f(0.0f, 1.0f, 1.0f, 0.2f); //cor
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f( tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);

    glColor4f(0.0f, 0.8f, 0.8f, 0.2f); //cor
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR, tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR, tan(PERSPECH * PARA_RADIANOS) * GLNEAR, -GLNEAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLNEAR,-tan(PERSPECH * PARA_RADIANOS) * GLNEAR,- GLNEAR);
    glVertex3f(-tan(PERSPECW * PARA_RADIANOS) * GLFAR,-tan(PERSPECH * PARA_RADIANOS) * GLFAR, -GLFAR);
    glEnd();

    //   glEnable(GL_DEPTH_TEST); // Turn Depth Testing On
    glDisable(GL_BLEND);  // Turn Blending On
    glPopMatrix();

}


void inicializar(char *hmap)
{
    glShadeModel(GL_SMOOTH);       // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.2f, 0.5f);    // Black Background
    glClearDepth(1.0f);         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);       // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);        // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);  // Blending Function For Translucency Based On Source Alpha Value ( NEW )

    for (int i = 0; i < 256+256; i++)
        keys[i] = false;

    m = new int[MAXX*MAXZ];
    n = new float[MAXX*MAXZ];
    AbrirTerreno(hmap, m, MAXX, MAXZ);

    //pisos = new PISO[(MAXX-1)*(MAXZ-1)];
    pisos = new PISO[MAXX*(MAXZ-1)];

    for (int x = 0; x < MAXX-1; x ++)
        for (int z = 0; z < MAXZ-1; z ++)
        {
            pisos[(x*MAXZ)+z] = PISO(x, z);
            if (m[(x*MAXZ)+z] <= NIVELAGUA)
            {
                n[(x*MAXZ)+z] = random((int)(DPI * 1000)) / 1000.0f;
                m[(x*MAXZ)+z] = NIVELAGUA;
            }
            else if (m[(x*MAXZ)+z] > NIVELAREIA && m[(x*MAXZ)+z] < NIVELNEVE)
            {
                n[(x*MAXZ)+z] = random((int)(DPI * 1000)) / 1000.0f;
            }
            else
            {
                n[(x*MAXZ)+z] = 0;
            }
        }

}

void specialKeyUp(int key, int x, int y)
{
    keys[256+key] = false;
}

void specialKeyDown(int key, int x, int y)
{
    keys[256+key] = true;
}

void keyboardKeyUp(unsigned char key, int x, int y)
{
    keys[key] = false;
}

void keyboardKeyDown(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void atualizar(int val)
{
    static float GIRO = 1.0f;
    static float VELOC = 1.0f;

    if (keys[256+GLUT_KEY_LEFT])
    {
        camera1.GirarLado(-GIRO);
    }
    if (keys[256+GLUT_KEY_RIGHT])
    {
        camera1.GirarLado(GIRO);
    }
    if (keys[256+GLUT_KEY_UP])
    {
        camera1.GirarFrente(GIRO);
    }
    if (keys[256+GLUT_KEY_DOWN])
    {
        camera1.GirarFrente(-GIRO);
    }
    if (keys['W'] || keys['w'])
    {
        camera1.MoverFrente(VELOC);
    }
    if (keys['S'] || keys['s'])
    {
        camera1.MoverFrente(-VELOC);
    }

    //***************************

    if (keys['J'] || keys['j'])
    {
        camera2.GirarLado(-GIRO);
    }
    if (keys['L'] || keys['l'])
    {
        camera2.GirarLado(GIRO);
    }
    if (keys['I'] || keys['i'])
    {
        camera2.GirarFrente(GIRO);
    }
    if (keys['K'] || keys['k'])
    {
        camera2.GirarFrente(-GIRO);
    }
    if (keys['E'] || keys['e'])
    {
        camera2.MoverFrente(VELOC);
    }
    if (keys['D'] || keys['d'])
    {
        camera2.MoverFrente(-VELOC);
    }

    //***************************

    if (keys['1'])
    {
        camera1 = camera2;
    }
    if (keys['2'])
    {
        camera2 = camera1;
    }

    //***************************

    if (keys['Z'] || keys['z'])
    {
        GIRO += 0.1f;
        VELOC += 0.1f;
    }
    if ((keys['X'] || keys['x']) && GIRO > 0.0f)
    {
        GIRO -= 0.1f;
        VELOC -= 0.1f;
    }


    //atualiza agua
    for (int x = 0; x < MAXX-1; x ++)
        for (int z = 0; z < MAXZ-1; z ++)
            if (m[(x*MAXZ)+z] <= NIVELAGUA)
            {
                n[(x*MAXZ)+z] += 0.08f;
            }
            else if (m[(x*MAXZ)+z] > NIVELAREIA && m[(x*MAXZ)+z] < NIVELNEVE)
            {
                n[(x*MAXZ)+z] += 0.01f;
            }


    glutPostRedisplay();
    glutTimerFunc(10,atualizar,1);
}

#define NESTRELAS 100

void desenhar()
{
    static ESTRELA estrelas[NESTRELAS];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();         // Reset The Current Modelview Matrix
    camera2.Posicionar();
    glTranslatef(0.0f, -AMPLITUDE * ESCALA , -60.0f);

    ExtractFrustum(frustum2);

    glLoadIdentity();         // Reset The Current Modelview Matrix
    glRotatef(camera1.GetAngX(), 1.0f, 0.0f, 0.0f);
    glRotatef(camera1.GetAngY(), 0.0f, 1.0f, 0.0f);
    glRotatef(camera1.GetAngZ(), 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -AMPLITUDE * ESCALA , 0.0f);

    //desenhar as estrelas
    for (int c= 0; c < NESTRELAS; c++)
        estrelas[c].Desenhar();

    glLoadIdentity();         // Reset The Current Modelview Matrix
    camera1.Posicionar();
    glTranslatef(0.0f, -AMPLITUDE * ESCALA , -60.0f);

    ExtractFrustum(frustum1);

    DesenharObjetos();
}

void finalizar()
{
    delete m;
    delete n;
    delete pisos;
}

