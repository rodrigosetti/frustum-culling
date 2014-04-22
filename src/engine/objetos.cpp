#include <OpenGL/gl.h>
#include <math.h>
#include <stdlib.h>
#include "objetos.h"

void EsferaLesada(int aneis, int gomos, float raiox, float raioy, float raioz, float perturbacao,
        float r, float gr, float b, float fr, float fgr, float fb)
{
    float *m = new float[aneis * gomos];

    for (int a = 0; a < aneis; a++) //gera matriz de deformação
    {
        for (int g = 0; g < gomos-1; g ++)
        {
            m[(a*gomos)+g] = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
        }
        m[(a*gomos)+(gomos-1)] = m[(a*gomos)+0];
    }

    for (int a = 0; a< aneis-1; a++) //desenha esfera com matrix de deformação
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int g = 0; g< gomos; g++)
        {
            glColor3f(r + (m[(a*gomos)+g]*fr),gr + (m[(a*gomos)+g]*fgr),b + (m[(a*gomos)+g]*fb));
            glVertex3f( cos(a*PI/(aneis-1)) * (raiox + m[(a*gomos)+g]),  sin(g*DPI/(gomos-1)) * sin(a*PI/(aneis-1)) * (raioy + m[(a*gomos)+g]),cos(g*DPI/(gomos-1)) * sin(a*PI/(aneis-1)) * (raioz + m[(a*gomos)+g]));

            glColor3f(r + (m[((a+1)*gomos)+g]*fr),gr + (m[((a+1)*gomos)+g]*fgr),b + (m[((a+1)*gomos)+g]*fb));
            glVertex3f( cos((a+1)*PI/(aneis-1)) * (raiox + m[((a+1)*gomos)+g]),  sin(g*DPI/(gomos-1)) * sin((a+1)*PI/(aneis-1)) * (raioy + m[((a+1)*gomos)+g]),cos(g*DPI/(gomos-1)) * sin((a+1)*PI/(aneis-1)) * (raioz + m[((a+1)*gomos)+g]));
        }
        glEnd();
    }

    delete m; //libera memoria
}

/****************************************************************/

void Tronco(int aneis, int gomos, float raiomin, float raiomax, float altura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   )
{
    gomos ++;
    altura /= aneis;
    float incr = (raiomax - raiomin) /aneis;
    float raio = raiomax;
    float py= 0;
    float *m = new float[aneis * gomos];

    for (int x = 0; x < aneis; x++) //gera matriz de deformação
        for (int y = 0; y < gomos; y ++)
        {
            m[(x*gomos)+y] = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
            m[(x*gomos)+0] = m[(x*gomos)+(gomos-1)];
        }

    glPushMatrix();
    glTranslatef(0.0f, altura * aneis, 0.0f);

    for (int x = 0; x< aneis; x++)     //desenha cilindro com deformação
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int y = 0; y< gomos; y++)
        {
            glColor3f(r + (m[(x*gomos)+y]*fr),g + (m[(x*gomos)+y]*fg),b + (m[(x*gomos)+y]*fb));
            glVertex3f(cos(y * (DPI/aneis))*(raio+m[(x*gomos)+y]), py, sin(y * (DPI/aneis))*(raio+m[(x*gomos)+y]));

            if (x < aneis-1)
            {
                glColor3f(r + (m[((x+1)*gomos)+y]*fr),g + (m[((x+1)*gomos)+y]*fg),b + (m[((x+1)*gomos)+y]*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+m[((x+1)*gomos)+y]), py-altura,sin(y * (DPI/aneis))*((raio-incr)+m[((x+1)*gomos)+y]));
            }
            else
            {
                glColor3f(r + (m[(0*gomos)+y]*fr),g + (m[(0*gomos)+y]*fg),b + (m[(0*gomos)+y]*fb));
                glVertex3f(cos(y * (DPI/aneis))*((raio-incr)+m[(0*gomos)+y]), py-altura,sin(y * (DPI/aneis))*((raio-incr)+m[(0*gomos)+y]));
            }
        }
        glEnd();

        raio -= incr;
        py -= altura;
    }

    glPopMatrix();

    delete m; //libera memoria
}

/****************************************************************/


void Mato(int ramos, float altura, float grossura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb)
{
    float *angz = new float[ramos];
    float *my = new float[ramos];
    float *angy = new float[ramos];

    for (int c =0; c < ramos; c++)
    {
        my[c] = altura + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1))));
        angy[c] = (rand() % 3600) / 10.0f;
        angz[c] = (rand() % 600) / 10.0f;
    }

    for (int c =0; c < ramos; c++) //desenha triangulos com deformação
    {
        glPushMatrix();
        glRotatef(angy[c],0.0f, 1.0f, 0.0f);
        glRotatef(angz[c],0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);

        glColor3f(r,g,b);    glVertex3f(-(grossura/2), 0.0f, 0.0f);
        glColor3f(r,g,b);    glVertex3f(  grossura/2 , 0.0f, 0.0f);
        glColor3f(fr,fg,fb); glVertex3f(0.0f, my[c], 0.0f);

        glEnd();
        glPopMatrix();
    }

    delete my; //libera memoria
    delete angy;
}

/****************************************************************/

void Superficie(float amplitude, int tamx, int tamy,
        float r, float g, float b, float fr, float fg, float fb)
{
    float *m = new float[tamx*tamy];

    for (int x = 0; x < tamx-1; x++)
    {
        for (int y = 0; y < tamy-1 ; y++)
        {
            m[(x * tamy) + y] = amplitude * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
            m[((tamx-1) * tamy) + y] =  m[(0 * tamy) + y];
        }
        m[(x * tamy) + (tamy-1)] = m[(x * tamy) + 0];
    }

    for (int x = 0; x < tamx-1; x++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int y = 0; y < tamy ; y++)
        {
            glColor3f(r + (fr*m[(x * tamy) + y]), g + (fg*m[(x * tamy) + y]),b + (fb*m[(x * tamy) + y]));
            glVertex3f(x-(tamx/2), m[(x * tamy) + y], y-(tamy/2));

            glColor3f(r + (fr*m[((x+1) * tamy) + y]), g + (fg*m[((x+1) * tamy) + y]),b + (fb*m[((x+1) * tamy) + y]));
            glVertex3f(x-(tamx/2)+1, m[((x+1) * tamy) + y], y-(tamy/2));
        }
        glEnd();
    }

    delete m; //libera memoria
}

/****************************************************************/

void CopaCoqueiro(int ramos, int gomos, float comprimento, float grossura, float angulacao, float decaimento, float perturbacao,
        float rd, float gr, float b, float fr, float fg, float fb)
{
    comprimento /= gomos;
    decaimento /= gomos;

    glPushMatrix();
    for (int r = 0; r < ramos; r++)
    {
        float pz = 0.0f, py = perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) );
        float dec = decaimento + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) ))/(float)gomos;
        float ang = angulacao + (perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) ));

        glRotatef((r*360.0f/(float)ramos)+(perturbacao * fabs( ((float)rand()) / ((float)(RAND_MAX+1)) )), 0.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLE_STRIP);
        for (int g =0; g < gomos; g++)
        {
            glColor3f(rd + ((float)(g/(float)(gomos))*fr), gr + ((float)(g/(float)(gomos))*fg), b + ((float)(g/(float)(gomos))*fb));
            glVertex3f(-sin((0.2f*PI)+(g*(PI*0.8f)/(float)(gomos)))*(grossura/2.0f), py, pz);
            glVertex3f( sin((0.2f*PI)+(g*(PI*0.8f)/(float)(gomos)))*(grossura/2.0f), py, pz);
            py += sin(ang) * comprimento;
            pz -= cos(ang) * comprimento;
            ang -= dec;
        }
        glEnd();
    }
    glPopMatrix();
}

/****************************************************************/

void TroncoCoqueiro(int aneis, int gomos, float raiomin, float raiomax, float altura, float curvatura, float perturbacao,
        float r, float g, float b, float fr, float fg, float fb   )
{
    gomos ++;
    altura /= aneis;
    float incr = (raiomax - raiomin) /aneis;
    float raio = raiomax;
    float py= 0.0f;

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
}

