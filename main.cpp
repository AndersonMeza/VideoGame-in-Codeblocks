#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#endif
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



double ancho=1200, alto=700;
double camarax=0,camaraz=0;



void piso()
{
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslated(0,-1,-25);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(50,1,50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.8,0.8,0.8);
    glScaled(50,1,50);
    glutWireCube(1);
    glPopMatrix();


    glPopMatrix();

}

void esfera()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(0,-1,-25);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(1,1,1);
    glutSolidSphere(1,50,50);
    glPopMatrix();


    glPopMatrix();

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);//limpia la pantalla
    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, ancho/alto, 0.1, 100.0); // 1200/800 = 1.5 (proporcion de tamaño de la ventana)



    gluLookAt(camarax,0,camaraz, camarax,0,camaraz-10,    0.0,    1,  0);

    piso();
    esfera();

    glLoadIdentity();


    glFlush();//refresca el buffer
}

void teclasEspeciales(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP :
            camaraz-=0.1;
            break;
        case GLUT_KEY_DOWN :
            camaraz+=0.1;
            break;
        case GLUT_KEY_LEFT :
            camarax-=0.1;
            break;
        case GLUT_KEY_RIGHT :
            camarax+=0.1;
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


    //glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
