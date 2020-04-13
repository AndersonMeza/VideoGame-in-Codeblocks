#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <iostream>
#endif


bool mueve1_izq=false,mueve1_der=false,mueve1_arr=false,mueve1_baj=false;
bool camara1_izq=false,camara1_der=false;
bool mueve2_izq=false,mueve2_der=false,mueve2_arr=false,mueve2_baj=false;
bool camara2_izq=false,camara2_der=false;


double ancho=1550, alto=800;
double objeto1x=0,objeto1z=-7,objetoy=0.88;
double objeto2x=0,objeto2z=-53;
double angulogiro1=0;
double angulogiro2=0;
double distancia=0.1;
double alcance_bala=50;
double velocidad_camara=0.20;
double velocidad_movimiento=0.05;
double PI = 3.14159265358979323846;


static void muneco2(void)
{
    glPushMatrix();
    glTranslated(objeto2x,objetoy,objeto2z);
    glScaled(1.25,1.25,1.25);
    glRotated((-angulogiro2/(PI/180))-180,0,1,0);

    //Cabeza
    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.0, 0.45, 0.0);
    glScalef(0.8, 0.8, 0.6);
    glutSolidCube(0.4);
    glPopMatrix();


    //Ojos
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.05, 0.45, -0.13);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.05, 0.45, -0.13);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();

    //Cuello
    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glutWireCube(0.1);
    glutSolidCube(0.1);
    glPopMatrix();

    //Cuerpo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.0, 0.06, 0.0);
    glScalef(0.73, 1.0, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo izquierdo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.13, 0.2, -0.2);
    glRotated(-130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();


    //correa
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.0, -0.16, 0.0);
    glScalef(0.73, 0.1, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //pierna izquierda
    glColor3f(0.5, 0.25, 0);
    glPushMatrix();
    glTranslatef(-0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //pierna derecha
    glColor3f(0.5, 0.25, 0);
    glPushMatrix();
    glTranslatef(0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Cabello
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.60, 0.0);
    glScalef(0.8, 0.2, 0.6);
    glutSolidCube(0.4);
    glPopMatrix();

    //PortaPistolas
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.1, -0.30, 0.0);
    glScalef(0.11, 0.05, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Zapatos
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.09, -0.60, 0.0);
    glScalef(1.1, 0.5, 1.7);
    glutSolidCube(0.1);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-0.09, -0.60, 0.0);
    glScalef(1.1, 0.5, 1.7);
    glutSolidCube(0.1);
    glPopMatrix();

    //Boca
    glPushMatrix();
    glTranslated(0,0,-0.13);
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(0.1, 0.36);
        glVertex2d(-0.1, 0.36);
        glEnd();
    glPopMatrix();

    //Cejas
    glPushMatrix();
    glTranslated(0,0,-0.13);
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(0.08, 0.50);
        glVertex2d(0.03, 0.48);
        glEnd();


    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(-0.08, 0.50);
        glVertex2d(-0.03, 0.48);
        glEnd();
    glPopMatrix();

    //pistola
    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.25, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.45, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.2, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.15, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPopMatrix();

}

static void dibujo(void)
{
    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(0, 0.2, 0);
    glBegin(GL_QUADS);
    glVertex3d(-0.03,0.05,-0.39);
    glVertex3d(0.03,0.05,-0.39);
    glVertex3d(alcance_bala/21.74,0.05,-alcance_bala);
    glVertex3d(-alcance_bala/21.74,0.05,-alcance_bala);
    glEnd();
    glPopMatrix();
}

static void muneco1(void)
{
    glPushMatrix();
    glTranslated(objeto1x,objetoy,objeto1z);
    glScaled(1.25,1.25,1.25);
    glRotated(angulogiro1/(PI/180),0,1,0);

    //Cabeza
    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.0, 0.45, 0.0);
    glScalef(0.8, 0.8, 0.6);
    glutSolidCube(0.4);
    glPopMatrix();


    //Ojos
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.05, 0.45, -0.13);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.05, 0.45, -0.13);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();

    //Cuello
    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glutWireCube(0.1);
    glutSolidCube(0.1);
    glPopMatrix();

    //Cuerpo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.0, 0.06, 0.0);
    glScalef(0.73, 1.0, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo izquierdo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.13, 0.2, -0.2);
    glRotated(-130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();


    //correa
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.0, -0.16, 0.0);
    glScalef(0.73, 0.1, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //pierna izquierda
    glColor3f(0.5, 0.25, 0);
    glPushMatrix();
    glTranslatef(-0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //pierna derecha
    glColor3f(0.5, 0.25, 0);
    glPushMatrix();
    glTranslatef(0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Cabello
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.60, 0.0);
    glScalef(0.8, 0.2, 0.6);
    glutSolidCube(0.4);
    glPopMatrix();

    //PortaPistolas
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.1, -0.30, 0.0);
    glScalef(0.11, 0.05, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Zapatos
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(0.09, -0.60, 0.0);
    glScalef(1.1, 0.5, 1.7);
    glutSolidCube(0.1);
    glPopMatrix();

    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(-0.09, -0.60, 0.0);
    glScalef(1.1, 0.5, 1.7);
    glutSolidCube(0.1);
    glPopMatrix();

    //Boca
    glPushMatrix();
    glTranslated(0,0,-0.13);
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(0.1, 0.36);
        glVertex2d(-0.1, 0.36);
        glEnd();
    glPopMatrix();

    //Cejas
    glPushMatrix();
    glTranslated(0,0,-0.13);
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(0.08, 0.50);
        glVertex2d(0.03, 0.48);
        glEnd();


    glBegin(GL_LINES);
        glColor3f(0.0,0.0,0.0);
        glVertex2d(-0.08, 0.50);
        glVertex2d(-0.03, 0.48);
        glEnd();
    glPopMatrix();

    //pistola
    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.25, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.45, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.2, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.15, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    dibujo();

    glPopMatrix();

}
static void brazos1(void)
{
    glPushMatrix();
    glTranslated(objeto1x,objetoy,objeto1z);
    glScaled(1.25,1.25,1.25);
    glRotated(angulogiro1/(PI/180),0,1,0);


    //Brazo izquierdo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.13, 0.2, -0.2);
    glRotated(-130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //pistola
    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.25, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.45, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.2, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.15, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //zona disparo

    dibujo();

    glPopMatrix();

}

static void brazos2(void)
{
    glPushMatrix();
    glTranslated(objeto2x,objetoy,objeto2z);
    glScaled(1.25,1.25,1.25);
    glRotated((-angulogiro2/(PI/180))-180,0,1,0);

    //Brazo izquierdo
    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    glColor3f(0.29, 0.43, 0.13);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.99, 0.86, 0.79);
    glPushMatrix();
    glTranslatef(-0.13, 0.2, -0.2);
    glRotated(-130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //pistola
    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.25, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.45, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0, 0.2, -0.3);
    glRotated(90,0,1,0);
    glScalef(0.15, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glPopMatrix();

}

void arbol1()
{

    glTranslated(0,0.2,0);

    //Tronco del arbol
    glPushMatrix();
    glColor3d(0.53, 0.36, 0.035);
    glTranslated(0,0.2,0);
    for (float i = 0; i<=2.5; i+=0.1)
    {
        glPushMatrix();
        glTranslated(0, i, 0);
        glutSolidSphere(0.5, 50, 50);
        glPopMatrix();
    }
    glPopMatrix();


    //Hojas del arbol
    glPushMatrix();
    glColor3d(0.2, 0.8, 0.5);
    glTranslated(1,3.5,0);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.3, 0.8, 0);
    glTranslated(1,3.5,-1);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0, 1, 0.4);
    glTranslated(-1,3.5,1);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0, 0.6, 0.015);
    glTranslated(-1,3.5,-1);
    glutSolidSphere(1.5, 80, 80);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.06, 0.62, 0.07);
    glTranslated(0,4.8,-0);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();


}


void arbol2()
{
    glTranslated(0,0.1,0);

    glPushMatrix();
    //Tronco del arbol
    glPushMatrix();
    glColor3d(0.33, 0.16, 0.015);
    glTranslated(0,0.2,0);
    for (float i = 0; i<=2.5; i+=0.1)
    {
        glPushMatrix();
        glTranslated(0, i, 0);
        glutSolidSphere(0.5, 50, 50);
        glPopMatrix();
    }
    glPopMatrix();

    double ang = 270;
    //Hojas del arbol
    glPushMatrix();
    glColor3d(0.11, 0.6, 0.13);
    glTranslated(0,2,0);
    glRotated(ang, 1.0, 0.0, 0.0);
    glutSolidCone(2.1, 2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.11, 0.65, 0.13);
    glTranslated(0,3.1,0);
    glRotated(ang, 1.0, 0.0, 0.0);
    glutSolidCone(1.6, 2, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.11, 0.70, 0.13);
    glTranslated(0,4.0,0);
    glRotated(ang, 1.0, 0.0, 0.0);
    glutSolidCone(1.1, 3, 50, 50);
    glPopMatrix();

    glPopMatrix();

}

void piso()
{
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslated(0,0,-30);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(50,0.2,50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.8,0.8,0.8);
    glScaled(50,0.2,50);
    glutWireCube(1);
    glPopMatrix();


    glPopMatrix();

}


void paredes()
{
    for(int i =-10;i>=-50;i-=10)
    {
        for(int j= -20;j<=25;j+=10)
        {
            glPushMatrix();
            glTranslated(j,1.5,i);
            glRotated(0,0,0,0);
            glScaled(1,1,1);
            glColor3d(0,1,0);
            glutSolidCube(3);
            glColor3d(0,0.8,0);
            glutWireCube(3);
            glPopMatrix();
        }
    }


}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50, ancho/alto, 0.1, 100.0);
    double distancia_camarax1=sin(angulogiro1)*distancia;
    double distancia_camaraz1=cos(angulogiro1)*distancia;
    double distancia_camarax2=sin(angulogiro2)*distancia;
    double distancia_camaraz2=cos(angulogiro2)*distancia;


    glViewport(0,0,ancho,alto/2);
    glPushMatrix();
    gluLookAt(objeto1x,objetoy+0.4,objeto1z, objeto1x-distancia_camarax1,objetoy+0.4,objeto1z-distancia_camaraz1,0,1,0);
    brazos1();
    muneco2();
    piso();
    paredes();
    glPopMatrix();

    glViewport(0,alto/2,ancho,alto/2);
    glPushMatrix();
    gluLookAt(objeto2x,objetoy+0.4,objeto2z, objeto2x-distancia_camarax2,objetoy+0.4,objeto2z+distancia_camaraz2,0,1,0);
    brazos2();
    muneco1();
    piso();
    paredes();
    glPopMatrix();


    glLoadIdentity();
    glFlush();
}

void Movimiento()
{
    if(mueve1_arr)
    {
        objeto1z-=cos(angulogiro1)*velocidad_movimiento;
        objeto1x-=sin(angulogiro1)*velocidad_movimiento;
    }
    if(mueve1_baj)
    {
        objeto1z+=cos(angulogiro1)*velocidad_movimiento;
        objeto1x+=sin(angulogiro1)*velocidad_movimiento;
    }
    if(mueve1_izq)
    {
        objeto1x-=cos(angulogiro1)*velocidad_movimiento;
        objeto1z+=sin(angulogiro1)*velocidad_movimiento;
    }
    if(mueve1_der)
    {
        objeto1x+=cos(angulogiro1)*velocidad_movimiento;
        objeto1z-=sin(angulogiro1)*velocidad_movimiento;
    }
    if(mueve2_arr)
    {
        objeto2z+=cos(angulogiro2)*velocidad_movimiento;
        objeto2x-=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_baj)
    {
        objeto2z-=cos(angulogiro2)*velocidad_movimiento;
        objeto2x+=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_izq)
    {
        objeto2x+=cos(angulogiro2)*velocidad_movimiento;
        objeto2z+=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_der)
    {
        objeto2x-=cos(angulogiro2)*velocidad_movimiento;
        objeto2z-=sin(angulogiro2)*velocidad_movimiento;
    }
    if(camara1_der)
    {
        angulogiro1+=velocidad_camara*(PI/180);
    }
    if(camara1_izq)
    {
        angulogiro1-=velocidad_camara*(PI/180);
    }
    if(camara2_der)
    {
        angulogiro2+=velocidad_camara*(PI/180);
    }
    if(camara2_izq)
    {
        angulogiro2-=velocidad_camara*(PI/180);
    }

    display();
}

void teclasCamara(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd' :
        case 'D' :
            camara1_der=false;
            camara1_izq=true;
            break;

        case 'a' :
        case 'A' :
            camara1_izq=false;
            camara1_der=true;
            break;


        case 'q' :
        case 'Q' :
            camara2_der=false;
            camara2_izq=true;
            break;


        case 'e' :
        case 'E' :
            camara2_izq=false;
            camara2_der=true;
            break;


        case '8' :
            mueve2_baj=false;
            mueve2_arr=true;
            break;

        case '5' :
            mueve2_arr=false;
            mueve2_baj=true;
            break;

        case '4' :
            mueve2_der=false;
            mueve2_izq=true;
            break;

        case '6' :
            mueve2_izq=false;
            mueve2_der=true;
            break;
    }
    Movimiento();
}

void teclasEspeciales(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            mueve1_baj=false;
            mueve1_arr=true;
            break;
        case GLUT_KEY_DOWN :
            mueve1_arr=false;
            mueve1_baj=true;
            break;
        case GLUT_KEY_LEFT :
            mueve1_der=false;
            mueve1_izq=true;
            break;
        case GLUT_KEY_RIGHT :
            mueve1_izq=false;
            mueve1_der=true;
            break;
    }
    Movimiento();
}

void teclasCamara2(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd' :
        case 'D' :
            camara1_izq=false;
            break;

        case 'a' :
        case 'A' :
            camara1_der=false;
            break;

        case 'q' :
        case 'Q' :
            camara2_izq=false;
            break;

        case 'e' :
        case 'E' :
            camara2_der=false;
            break;



        case '8' :
            mueve2_arr=false;
            break;

        case '5' :
            mueve2_baj=false;
            break;

        case '4' :
            mueve2_izq=false;
            break;

        case '6' :
            mueve2_der=false;
            break;
    }
    Movimiento();
}

void teclasEspeciales2(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            mueve1_arr=false;
            break;
        case GLUT_KEY_DOWN :
            mueve1_baj=false;
            break;
        case GLUT_KEY_LEFT :
            mueve1_izq=false;
            break;
        case GLUT_KEY_RIGHT :
            mueve1_der=false;
            break;
    }
    Movimiento();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ancho,alto);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Figura 3d");
    glClearColor(0,0.7,1,0);
    glutDisplayFunc(display);

    glutSpecialFunc(teclasEspeciales);
    glutSpecialUpFunc(teclasEspeciales2);
    glutKeyboardFunc(teclasCamara);
    glutKeyboardUpFunc(teclasCamara2);
    glutIdleFunc(Movimiento);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
