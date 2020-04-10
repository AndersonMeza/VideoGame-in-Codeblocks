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
double objetox=0,objetoz=-7,objetoy=0.55;
double angulogiro=0;
double distancia=2;
double PI = 3.14159265358979323846;



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
    glTranslated(objetox,objetoy,objetoz);
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
    double distancia_camarax=sin(angulogiro)*distancia;
    double distancia_camaraz=cos(angulogiro)*distancia;
    gluLookAt(objetox+distancia_camarax,objetoy+0.45,objetoz+distancia_camaraz, objetox,objetoy,objetoz,0,1,0);
    esfera();
    piso();
    paredes();


    glLoadIdentity();
    glFlush();
}

void teclasCamara(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd' :
        case 'D' :
            angulogiro-=15*(PI/180);
            break;
        case 'a' :
        case 'A' :
            angulogiro+=15*(PI/180);
            break;
    }
    display();
}

void teclasEspeciales(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            objetoz-=cos(angulogiro)*0.5;
            objetox-=sin(angulogiro)*0.5;
            break;
        case GLUT_KEY_DOWN :
            objetoz+=cos(angulogiro)*0.5;
            objetox+=sin(angulogiro)*0.5;
            break;
        case GLUT_KEY_LEFT :
            objetox-=cos(angulogiro)*0.5;
            objetoz+=sin(angulogiro)*0.5;
            break;
        case GLUT_KEY_RIGHT :
            objetox+=cos(angulogiro)*0.5;
            objetoz-=sin(angulogiro)*0.5;
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
    //glutIdleFunc();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
