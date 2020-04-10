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



double ancho=1500, alto=800;
double objeto1x=0,objeto1z=-7,objetoy=0.55;
double objeto2x=0,objeto2z=-53;
double angulogiro1=0;
double angulogiro2=0;
double distancia=5;
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

void esfera1()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(objeto1x,objetoy,objeto1z);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(1,1,1);
    glutSolidSphere(0.5,50,50);
    glPopMatrix();


    glPopMatrix();

}

void esfera2()
{
    glPushMatrix();
    glColor3d(0,0,0);
    glTranslated(objeto2x,objetoy,objeto2z);
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
    double distancia_camarax1=sin(angulogiro1)*distancia;
    double distancia_camaraz1=cos(angulogiro1)*distancia;
    double distancia_camarax2=sin(angulogiro2)*distancia;
    double distancia_camaraz2=cos(angulogiro2)*distancia;


    glViewport(0,0,ancho,alto/2);
    glPushMatrix();
    gluLookAt(objeto1x+distancia_camarax1,objetoy+0.45,objeto1z+distancia_camaraz1, objeto1x,objetoy,objeto1z,0,1,0);
    esfera1();
    esfera2();
    piso();
    paredes();
    glPopMatrix();

    glViewport(0,alto/2,ancho,alto/2);
    glPushMatrix();
    gluLookAt(objeto2x+distancia_camarax2,objetoy+0.45,objeto2z-distancia_camaraz2, objeto2x,objetoy,objeto2z,0,1,0);
    esfera1();
    esfera2();
    piso();
    paredes();
    glPopMatrix();


    glLoadIdentity();
    glFlush();
}

void teclasCamara(unsigned char key, int x, int y)
{
    switch (key) {
        case 'd' :
        case 'D' :
            angulogiro1-=15*(PI/180);
            break;
        case 'a' :
        case 'A' :
            angulogiro1+=15*(PI/180);
            break;
        case 'q' :
        case 'Q' :
            angulogiro2-=15*(PI/180);
            break;
        case 'e' :
        case 'E' :
            angulogiro2+=15*(PI/180);
            break;
        case '8' :
            objeto2z+=cos(angulogiro2)*0.5;
            objeto2x-=sin(angulogiro2)*0.5;
            break;
        case '5' :
            objeto2z-=cos(angulogiro2)*0.5;
            objeto2x+=sin(angulogiro2)*0.5;
            break;
        case '4' :
            objeto2x+=cos(angulogiro2)*0.5;
            objeto2z+=sin(angulogiro2)*0.5;
            break;
        case '6' :
            objeto2x-=cos(angulogiro2)*0.5;
            objeto2z-=sin(angulogiro2)*0.5;
            break;
    }
    display();
}

void teclasEspeciales(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            objeto1z-=cos(angulogiro1)*0.5;
            objeto1x-=sin(angulogiro1)*0.5;
            break;
        case GLUT_KEY_DOWN :
            objeto1z+=cos(angulogiro1)*0.5;
            objeto1x+=sin(angulogiro1)*0.5;
            break;
        case GLUT_KEY_LEFT :
            objeto1x-=cos(angulogiro1)*0.5;
            objeto1z+=sin(angulogiro1)*0.5;
            break;
        case GLUT_KEY_RIGHT :
            objeto1x+=cos(angulogiro1)*0.5;
            objeto1z-=sin(angulogiro1)*0.5;
            break;
    }
    display();
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
    glutKeyboardFunc(teclasCamara);
    //glutIdleFunc();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
