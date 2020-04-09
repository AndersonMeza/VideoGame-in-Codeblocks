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



double ancho=1200, alto=700;
double camarax=0,camaraz=0;
double girocamarax = camarax, gorocamaraz=camaraz-10;



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

void esfera()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(camarax,0.55,camaraz-7);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(1,1,1);
    glutSolidSphere(0.5,50,50);
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
    gluLookAt(camarax,1,camaraz, camarax,0,camaraz-10,    0.0,    1,  0);

    esfera();
    piso();
    paredes();

    glLoadIdentity();
    glFlush();
}

void teclasCamara(unsigned char key, int x, int y)
{

}

void teclasEspeciales(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            camaraz-=0.5;
            break;
        case GLUT_KEY_DOWN :
            camaraz+=0.5;
            break;
        case GLUT_KEY_LEFT :
            camarax-=0.5;
            break;
        case GLUT_KEY_RIGHT :
            camarax+=0.5;
            break;
    }
    display();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ancho,alto);//tamaño
    glutInitWindowPosition(0,0);//cordenadas de la pantalla
    glutCreateWindow("Figura 3d");//Titulo de la Ventana
    glClearColor(0,0.7,1,0);
    glutDisplayFunc(display);
    glutSpecialFunc(teclasEspeciales);
    glutKeyboardFunc(teclasCamara);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
