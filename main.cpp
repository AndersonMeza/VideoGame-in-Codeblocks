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
double objeto1x=0,objeto1z=-7,objetoy=0.55;
double objeto2x=0,objeto2z=-53;
double angulogiro1=0;
double angulogiro2=0;
double distancia=5;
double velocidad_camara=0.45;
double velocidad_movimiento=0.05;
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
            camara1_izq=false;
            camara1_der=true;
            break;

        case 'a' :
        case 'A' :
            camara1_der=false;
            camara1_izq=true;
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
            camara1_der=false;
            break;

        case 'a' :
        case 'A' :
            camara1_izq=false;
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
