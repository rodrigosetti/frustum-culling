#include "objetos2.h"

#include <stdlib.h>
#include <math.h>

//******************************************************************************

void EsferaLesada2(GLuint &lista1, GLuint &lista2, float raiox, float raioy, float raioz, float perturbacao,
        float r, float gr, float b, float fr, float fgr, float fb)
{
#define ANEIS 10
#define GOMOS 10

    float m [ANEIS * GOMOS];

    for (int a = 0; a < ANEIS; a++) //gera matriz de deformação
    {
        for (int g = 0; g < GOMOS-1; g ++)
        {
            m[(a*GOMOS)+g] = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
        }
        m[(a*GOMOS)+(GOMOS-1)] = m[(a*GOMOS)+0];
    }

    lista1 = glGenLists(1);
    glNewList(lista1, GL_COMPILE);
    for (int a = 0; a< ANEIS-1; a++) //desenha esfera com matrix de deformação
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int g = 0; g< GOMOS; g++)
        {
            glColor3f(r + (m[(a*GOMOS)+g]*fr),gr + (m[(a*GOMOS)+g]*fgr),b + (m[(a*GOMOS)+g]*fb));
            glVertex3f( cos(a*PI/(ANEIS-1)) * (raiox + m[(a*GOMOS)+g]),  sin(g*DPI/(GOMOS-1)) * sin(a*PI/(ANEIS-1)) * (raioy + m[(a*GOMOS)+g]),cos(g*DPI/(GOMOS-1)) * sin(a*PI/(ANEIS-1)) * (raioz + m[(a*GOMOS)+g]));

            glColor3f(r + (m[((a+1)*GOMOS)+g]*fr),gr + (m[((a+1)*GOMOS)+g]*fgr),b + (m[((a+1)*GOMOS)+g]*fb));
            glVertex3f( cos((a+1)*PI/(ANEIS-1)) * (raiox + m[((a+1)*GOMOS)+g]),  sin(g*DPI/(GOMOS-1)) * sin((a+1)*PI/(ANEIS-1)) * (raioy + m[((a+1)*GOMOS)+g]),cos(g*DPI/(GOMOS-1)) * sin((a+1)*PI/(ANEIS-1)) * (raioz + m[((a+1)*GOMOS)+g]));
        }
        glEnd();
    }
    glEndList();

    lista2 = glGenLists(1);
    glNewList(lista2, GL_COMPILE);
    for (int a = 0; a< ANEIS-1; a++) //desenha esfera com matrix de deformação
    {
        glBegin(GL_LINE_STRIP);
        for (int g = 0; g< GOMOS; g++)
        {
            glColor3f(r + (m[(a*GOMOS)+g]*fr),gr + (m[(a*GOMOS)+g]*fgr),b + (m[(a*GOMOS)+g]*fb));
            glVertex3f( cos(a*PI/(ANEIS-1)) * (raiox + m[(a*GOMOS)+g]),  sin(g*DPI/(GOMOS-1)) * sin(a*PI/(ANEIS-1)) * (raioy + m[(a*GOMOS)+g]),cos(g*DPI/(GOMOS-1)) * sin(a*PI/(ANEIS-1)) * (raioz + m[(a*GOMOS)+g]));

            glColor3f(r + (m[((a+1)*GOMOS)+g]*fr),gr + (m[((a+1)*GOMOS)+g]*fgr),b + (m[((a+1)*GOMOS)+g]*fb));
            glVertex3f( cos((a+1)*PI/(ANEIS-1)) * (raiox + m[((a+1)*GOMOS)+g]),  sin(g*DPI/(GOMOS-1)) * sin((a+1)*PI/(ANEIS-1)) * (raioy + m[((a+1)*GOMOS)+g]),cos(g*DPI/(GOMOS-1)) * sin((a+1)*PI/(ANEIS-1)) * (raioz + m[((a+1)*GOMOS)+g]));
        }
        glEnd();
    }
    glEndList();
}

//*****************************************************************************

void Tronco2(GLuint &lista1, GLuint &lista2, float raiomin, float raiomax, float altura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   )
{
#define tANEIS 15
#define tGOMOS 16

    //         tGOMOS ++;
    altura /= tANEIS;
    float incr = (raiomax - raiomin) /tANEIS;
    float raio = raiomax;
    float py= 0;
    float m[tANEIS * tGOMOS];

    for (int x = 0; x < tANEIS; x++) //gera matriz de deformação
        for (int y = 0; y < tGOMOS; y ++)
        {
            m[(x*tGOMOS)+y] = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
            m[(x*tGOMOS)+0] = m[(x*tGOMOS)+(tGOMOS-1)];
        }

    lista1 = glGenLists(1);
    glNewList(lista1, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.0f, altura * tANEIS, 0.0f);

    for (int x = 0; x< tANEIS; x++)     //desenha cilindro com deformação
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int y = 0; y< tGOMOS; y++)
        {
            glColor3f(r + (m[(x*tGOMOS)+y]*fr),g + (m[(x*tGOMOS)+y]*fg),b + (m[(x*tGOMOS)+y]*fb));
            glVertex3f(cos(y * (DPI/tANEIS))*(raio+m[(x*tGOMOS)+y]), py, sin(y * (DPI/tANEIS))*(raio+m[(x*tGOMOS)+y]));

            if (x < tANEIS-1)
            {
                glColor3f(r + (m[((x+1)*tGOMOS)+y]*fr),g + (m[((x+1)*tGOMOS)+y]*fg),b + (m[((x+1)*tGOMOS)+y]*fb));
                glVertex3f(cos(y * (DPI/tANEIS))*((raio-incr)+m[((x+1)*tGOMOS)+y]), py-altura,sin(y * (DPI/tANEIS))*((raio-incr)+m[((x+1)*tGOMOS)+y]));
            }
            else
            {
                glColor3f(r + (m[(0*tGOMOS)+y]*fr),g + (m[(0*tGOMOS)+y]*fg),b + (m[(0*tGOMOS)+y]*fb));
                glVertex3f(cos(y * (DPI/tANEIS))*((raio-incr)+m[(0*tGOMOS)+y]), py-altura,sin(y * (DPI/tANEIS))*((raio-incr)+m[(0*tGOMOS)+y]));
            }
        }
        glEnd();

        raio -= incr;
        py -= altura;
    }

    glPopMatrix();
    glEndList();

    //****************

    raio = raiomax;
    py= 0;

    lista2 = glGenLists(1);
    glNewList(lista2, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.0f, altura * tANEIS, 0.0f);

    for (int x = 0; x< tANEIS; x++)     //desenha cilindro com deformação
    {
        glBegin(GL_LINE_STRIP);
        for (int y = 0; y< tGOMOS; y++)
        {
            glColor3f(r + (m[(x*tGOMOS)+y]*fr),g + (m[(x*tGOMOS)+y]*fg),b + (m[(x*tGOMOS)+y]*fb));
            glVertex3f(cos(y * (DPI/tANEIS))*(raio+m[(x*tGOMOS)+y]), py, sin(y * (DPI/tANEIS))*(raio+m[(x*tGOMOS)+y]));

            if (x < tANEIS-1)
            {
                glColor3f(r + (m[((x+1)*tGOMOS)+y]*fr),g + (m[((x+1)*tGOMOS)+y]*fg),b + (m[((x+1)*tGOMOS)+y]*fb));
                glVertex3f(cos(y * (DPI/tANEIS))*((raio-incr)+m[((x+1)*tGOMOS)+y]), py-altura,sin(y * (DPI/tANEIS))*((raio-incr)+m[((x+1)*tGOMOS)+y]));
            }
            else
            {
                glColor3f(r + (m[(0*tGOMOS)+y]*fr),g + (m[(0*tGOMOS)+y]*fg),b + (m[(0*tGOMOS)+y]*fb));
                glVertex3f(cos(y * (DPI/tANEIS))*((raio-incr)+m[(0*tGOMOS)+y]), py-altura,sin(y * (DPI/tANEIS))*((raio-incr)+m[(0*tGOMOS)+y]));
            }
        }
        glEnd();

        raio -= incr;
        py -= altura;
    }

    glPopMatrix();
    glEndList();
}

//*****************************************************************************


void Mato2(GLuint *lista1, GLuint *lista2, float altura, float grossura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb)
{
#define RAMOS 10

    float angz[RAMOS];
    float my[RAMOS];
    float angy[RAMOS];

    for (int c =0; c < RAMOS; c++)
    {
        my[c] = altura + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1))));
        angy[c] = (rand() % 3600)/ 10.0f;
        angz[c] = (rand() % 600)/ 10.0f;
    }

    *lista1 = glGenLists(1);
    glNewList(*lista1, GL_COMPILE);
    for (int c =0; c < RAMOS; c++) //desenha triangulos com deformação
    {
        glPushMatrix();
        glRotatef(angy[c],0.0f, 1.0f, 0.0f);
        glRotatef(angz[c],0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);

        glColor3f(r,g,b);
        glVertex3f(-(grossura/2), 0.0f, 0.0f);
        glColor3f(r,g,b);
        glVertex3f(  grossura/2 , 0.0f, 0.0f);
        glColor3f(fr,fg,fb);
        glVertex3f(0.0f, my[c], 0.0f);

        glEnd();
        glPopMatrix();
    }
    glEndList();

    *lista2 = glGenLists(2);
    glNewList(*lista2, GL_COMPILE);
    for (int c =0; c < RAMOS; c++) //desenha triangulos com deformação
    {
        glPushMatrix();
        glRotatef(angy[c],0.0f, 1.0f, 0.0f);
        glRotatef(angz[c],0.0f, 0.0f, 1.0f);
        glBegin(GL_LINE_LOOP);

        glColor3f(r,g,b);
        glVertex3f(-(grossura/2), 0.0f, 0.0f);
        glColor3f(r,g,b);
        glVertex3f(  grossura/2 , 0.0f, 0.0f);
        glColor3f(fr,fg,fb);
        glVertex3f(0.0f, my[c], 0.0f);

        glEnd();
        glPopMatrix();
    }
    glEndList();

}

//*****************************************************************************

//*****************************************************************************

void CopaCoqueiro2(GLuint &lista1, GLuint &lista2, float comprimento, float grossura, float angulacao, float decaimento, float perturbacao,
        float rd, float gr, float b, float fr, float fg, float fb)
{
#define cGOMOS 20
#define cRAMOS 8

    comprimento /= cGOMOS;
    decaimento /= cGOMOS;

    //gera matriz aleatoria

    float py[cRAMOS];
    float dec[cRAMOS];
    float ang[cRAMOS];
    float giro[cRAMOS];

    for (int r = 0; r < cRAMOS; r++)
    {
        py[r] = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
        dec[r] = decaimento + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) ))/(float)cGOMOS;
        ang[r] = angulacao + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) ));
        giro[r] = (r*360.0f/(float)cRAMOS)+(perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) ));
    }


    //desenha(compila)

    lista1 = glGenLists(1);
    glNewList(lista1, GL_COMPILE);
    glPushMatrix();
    for (int r = 0; r < cRAMOS; r++)
    {
        float py2 = py[r];
        float pz = 0.0f;
        float ang2 = ang[r];

        glRotatef(giro[r], 0.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for (int g =0; g < cGOMOS; g++)
        {
            glColor3f(rd + ((float)(g/(float)(cGOMOS))*fr), gr + ((float)(g/(float)(cGOMOS))*fg), b + ((float)(g/(float)(cGOMOS))*fb));
            glVertex3f(-sin((0.2f*PI)+(g*(PI*0.8f)/(float)(cGOMOS)))*(grossura/2.0f), py2, pz);
            glVertex3f( sin((0.2f*PI)+(g*(PI*0.8f)/(float)(cGOMOS)))*(grossura/2.0f), py2, pz);
            py2 += sin(ang2) * comprimento;
            pz -= cos(ang2) * comprimento;
            ang2 -= dec[r];
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();

    //**********

    lista2 = glGenLists(1);
    glNewList(lista2, GL_COMPILE);
    glPushMatrix();
    for (int r = 0; r < cRAMOS; r++)
    {
        float py2 = py[r];
        float pz = 0.0f;
        float ang2 = ang[r];

        glRotatef(giro[r], 0.0f, 1.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (int g =0; g < cGOMOS; g++)
        {
            glColor3f(rd + ((float)(g/(float)(cGOMOS))*fr), gr + ((float)(g/(float)(cGOMOS))*fg), b + ((float)(g/(float)(cGOMOS))*fb));
            glVertex3f(-sin((0.2f*PI)+(g*(PI*0.8f)/(float)(cGOMOS)))*(grossura/2.0f), py2, pz);
            glVertex3f( sin((0.2f*PI)+(g*(PI*0.8f)/(float)(cGOMOS)))*(grossura/2.0f), py2, pz);
            py2 += sin(ang2) * comprimento;
            pz -= cos(ang2) * comprimento;
            ang2 -= dec[r];
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
}

//*****************************************************************************

void TroncoCoqueiro2(GLuint &lista1, GLuint &lista2, int aneis, int gomos, float raiomin, float raiomax, float altura, float curvatura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   )
{
    gomos ++;
    altura /= aneis;
    float incr = (raiomax - raiomin) /aneis;
    float raio = raiomax;
    float py= 0.0f;

    //desenha

    lista1 = glGenLists(1);
    glNewList(lista1, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.0f, altura * aneis, 0.0f);

    for (int x = 0; x< aneis; x++)     //desenha cilindro com deformação
    {

        glBegin(GL_TRIANGLE_STRIP);
        for (int y = 0; y< gomos; y++)
        {
            glColor3f(r + (((x % 2==0)? perturbacao : 0)*fr),g + (((x % 2==0)? perturbacao : 0)*fg),b + (((x % 2==0)? perturbacao : 0)*fb));
            glVertex3f(cos(y * (DPI/aneis))*(raio+((x % 2==0)? perturbacao : 0)), py, sin(y * (DPI/aneis))*(raio+((x % 2==0)? perturbacao : 0)) + (sin(x*PI/(aneis-1)) * curvatura));

            if (x < aneis-1)
            {
                glColor3f(r + ((((x+1) % 2==0)? perturbacao : 0)*fr),g + ((((x+1) % 2==0)? perturbacao : 0)*fg),b + ((((x+1) % 2==0)? perturbacao : 0)*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+(((x+1) % 2==0)? perturbacao : 0)), py-altura,sin(y * (DPI/aneis))*((raio-incr)+(((x+1) % 2==0)? perturbacao : 0)) + (sin((x+1)*PI/(aneis-1)) * curvatura));
            }
            else
            {
                glColor3f(r + (perturbacao*fr),g + (perturbacao*fg),b + (perturbacao*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+perturbacao), py-altura,sin(y * (DPI/aneis))*((raio-incr)+perturbacao) + (sin(0*PI/(aneis-1)) * curvatura));
            }
        }
        glEnd();

        raio -= incr;
        py -= altura;
    }
    glPopMatrix();
    glEndList();

    //**********

    raio = raiomax;
    py= 0.0f;

    lista2 = glGenLists(1);
    glNewList(lista2, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0.0f, altura * aneis, 0.0f);

    for (int x = 0; x< aneis; x++)     //desenha cilindro com deformação
    {

        glBegin(GL_LINE_STRIP);
        for (int y = 0; y< gomos; y++)
        {
            glColor3f(r + (((x % 2==0)? perturbacao : 0)*fr),g + (((x % 2==0)? perturbacao : 0)*fg),b + (((x % 2==0)? perturbacao : 0)*fb));
            glVertex3f(cos(y * (DPI/aneis))*(raio+((x % 2==0)? perturbacao : 0)), py, sin(y * (DPI/aneis))*(raio+((x % 2==0)? perturbacao : 0)) + (sin(x*PI/(aneis-1)) * curvatura));

            if (x < aneis-1)
            {
                glColor3f(r + ((((x+1) % 2==0)? perturbacao : 0)*fr),g + ((((x+1) % 2==0)? perturbacao : 0)*fg),b + ((((x+1) % 2==0)? perturbacao : 0)*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+(((x+1) % 2==0)? perturbacao : 0)), py-altura,sin(y * (DPI/aneis))*((raio-incr)+(((x+1) % 2==0)? perturbacao : 0)) + (sin((x+1)*PI/(aneis-1)) * curvatura));
            }
            else
            {
                glColor3f(r + (perturbacao*fr),g + (perturbacao*fg),b + (perturbacao*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+perturbacao), py-altura,sin(y * (DPI/aneis))*((raio-incr)+perturbacao) + (sin(0*PI/(aneis-1)) * curvatura));
            }
        }
        glEnd();

        raio -= incr;
        py -= altura;
    }
    glPopMatrix();
    glEndList();

}

//*****************************************************************************

