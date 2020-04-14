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

bool entra_juego=false;
bool cabello1=false,camiseta1=false,pantalon1=false;
bool cabello2=false,camiseta2=false,pantalon2=false;
bool mueve1_izq=false,mueve1_der=false,mueve1_arr=false,mueve1_baj=false;
bool camara1_izq=false,camara1_der=false;
bool mueve2_izq=false,mueve2_der=false,mueve2_arr=false,mueve2_baj=false;
bool camara2_izq=false,camara2_der=false;
bool herida1=false,herida2=false;
bool dispara1=false,dispara2=false;

int vida1=5,kills1=0;
int vida2=5,kills2=0;
double mousey=0,mousex=0;
double ancho=1550, alto=800;
double objeto1x=0,objeto1z=3,objetoy=0.88;//-7
double objeto2x=0,objeto2z=-63;//-53
double angulogiro1=0;
double angulogiro2=-3.1;
double distancia=0.1;
double alcance_bala=20;
double velocidad_camara=1;
double velocidad_movimiento=0.1;
double PI = 3.14159265358979323846;




void inline drawString(char* s)
{
    unsigned int i;
    for(i = 0; i < strlen(s); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}

void imprimir_vida(int vidas, int kills)
{
    glLoadIdentity();

    static char label[100];
    static char arr[10][50] = {"VIDAS:", "KILLS:", "O","X"};

    //PULSE START
    glPushMatrix();
    glColor3f(1, 0, 0);
    sprintf(label, "%s", arr[0]);
    glRasterPos2f(-0.99, 0.9);
    drawString(label);
    glPopMatrix();
    //START
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[1]);
    glRasterPos2f(-0.99, 0.78);
    drawString(label);
    glPopMatrix();
    //CABELLO 1

    double dis=0;
    for( int i=1;i<=vidas;i++)
    {
        glPushMatrix();
        glColor3f(1, 0, 0);
        sprintf(label, "%s", arr[2]);
        glRasterPos2f(-0.9+dis,0.9);
        drawString(label);
        glPopMatrix();
        dis+=0.03;
    }

    dis=0;
    for( int i=1;i<=kills;i++)
    {
        glPushMatrix();
        glColor3f(0, 0, 0);
        sprintf(label, "%s", arr[3]);
        glRasterPos2f(-0.9+dis,0.78);
        drawString(label);
        glPopMatrix();
        dis+=0.03;
    }

    //CAMISETA1


}

void imprimir(void)
{
    glLoadIdentity();

    static char label[100];
    static char arr[10][50] = {"Pulse boton verde para comenzar", "START", "Color cabello:","Color camiseta:",
                                "Color shorts:","Color cabello:", "Color camiseta:", "Color shorts:",
                              "PLAYER 1", "PLAYER 2"};

    //PULSE START
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[0]);
    glRasterPos2f(-0.17, 0.3);
    drawString(label);
    glPopMatrix();
    //START
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[1]);
    glRasterPos2f(-0.05, -0.02);
    drawString(label);
    glPopMatrix();
    //CABELLO 1
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[2]);
    glRasterPos2f(-0.85,-0.51);
    drawString(label);
    glPopMatrix();
    //CAMISETA1
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[3]);
    glRasterPos2f(-0.85,-0.66);
    drawString(label);
    glPopMatrix();
    //PANTALON1
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[4]);
    glRasterPos2f(-0.85,-0.81);
    drawString(label);
    glPopMatrix();

    //CABELLO2
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[5]);
    glRasterPos2f(0.35,-0.51);
    drawString(label);
    glPopMatrix();
    //CAMISETA2
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[6]);
    glRasterPos2f(0.35,-0.66);
    drawString(label);
    glPopMatrix();
    //PANTALON2
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[7]);
    glRasterPos2f(0.35,-0.81);
    drawString(label);
    glPopMatrix();

    //PLAYER 1
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[8]);
    glRasterPos2f(-0.65,0.8);
    drawString(label);
    glPopMatrix();

    //PLAYER 2
    glPushMatrix();
    glColor3f(0, 0, 0);
    sprintf(label, "%s", arr[9]);
    glRasterPos2f(0.55,0.8);
    drawString(label);
    glPopMatrix();

}

static void prohibir_paso()
{
    ///////////////////////////////////////////////////
    //paredes laterales
    if(objeto1x>=29.5)
        objeto1x=29.5;

    if(objeto1x<=-29.5)
        objeto1x=-29.5;

    //parte fuera casa 1
    if((objeto1z>=-0.4 && objeto1z<=0) &&  !(objeto1x>=-1.75 && objeto1x<=1.75 ) )
    {
        objeto1z=-0.5;
    }

    //parte fuera casa 2
    if((objeto1z<=-59.5 && objeto1z>=-60) &&  !(objeto1x>=-1.75 && objeto1x<=1.75 ) )
    {
        objeto1z=-59.5;
    }

    //parte dentro casa 1
    if((objeto1z<=0.4 && objeto1z>=0) &&  !(objeto1x>=-1.75 && objeto1x<=1.75 ) )
    {
        objeto1z=0.5;
    }

    //parte dentro casa 2
    if((objeto1z>=-60.4 && objeto1z<=-60) &&  !(objeto1x>=-1.75 && objeto1x<=1.75 ) )
    {
        objeto1z=-60.5;
    }

    //parte atras casa 1
    if(objeto1z>=4.5 )
    {
        objeto1z=4.5;
    }

    //parte atras casa 2
    if(objeto1z<=-64.5 )
    {
        objeto1z=-64.5;
    }

    //laterales casa1
        //derecha
    if(objeto1x>=3 && objeto1z>=0)
        objeto1x=3;

      //izquierda
    if(objeto1x<=-3 && objeto1z>=0)
        objeto1x=-3;

    //laterales casa2
        //derecha
    if(objeto1x>=3 && objeto1z<=-60)
        objeto1x=3;

      //izquierda
    if(objeto1x<=-3 && objeto1z<=-60)
        objeto1x=-3;

    //paredes hierro izquierda
    if((objeto1x<=-12 && objeto1x>=-15) && (objeto1z>=-45 && objeto1z<=-15))
        objeto1x=-12;
    if((objeto1x>=-18 && objeto1x<=-15) && (objeto1z>=-45 && objeto1z<=-15))
        objeto1x=-18;
    if((objeto1z<=-14.5 && objeto1z>=-15) && (objeto1x<=-12.5 && objeto1x>=-17.5))
        objeto1z=-14.5;
    if((objeto1z<=-45 && objeto1z>=-45.5) && (objeto1x<=-12.5 && objeto1x>=-17.5))
        objeto1z=-45.5;

    //paredes hierro derecha
    if((objeto1x>=12 && objeto1x<=15) && (objeto1z>=-45 && objeto1z<=-15))
        objeto1x=12;
    if((objeto1x<=18 && objeto1x>=15) && (objeto1z>=-45 && objeto1z<=-15))
        objeto1x=18;
    if((objeto1z<=-14.5 && objeto1z>=-15) && (objeto1x>=12.5 && objeto1x<=17.5))
        objeto1z=-14.5;
    if((objeto1z<=-45 && objeto1z>=-45.5) && (objeto1x>=12.5 && objeto1x<=17.5))
        objeto1z=-45.5;

    //demas bloques
    for(double i=-10;i<=10;i+=5)
    {
        for(double j =-10;j>=-50;j-=10)
        {

            //glTranslated(i,1.5,j);
            //glutSolidCube(1);
            //glScaled(2.5,3,2.5);
            if((objeto1x>=i-1.55 && objeto1x<=i) && (objeto1z>=j-1.25 && objeto1z<=j+1.25))
                objeto1x=i-1.5;

            if((objeto1x<=i+1.55 && objeto1x>=i) && (objeto1z>=j-1.25 && objeto1z<=j+1.25))
                objeto1x=i+1.55;

            if((objeto1z>=j-1.55 && objeto1z<=j) && (objeto1x>=i-1.25 && objeto1x<=i+1.25))
                objeto1z=j-1.55;

            if((objeto1z<=j+1.55 && objeto1z>=j) && (objeto1x>=i-1.25 && objeto1x<=i+1.25))
                objeto1z=j+1.55;


        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //OBJETO2
    //paredes laterales
    if(objeto2x>=29.5)
        objeto2x=29.5;

    if(objeto2x<=-29.5)
        objeto2x=-29.5;

    //parte fuera casa 1
    if((objeto2z>=-0.4 && objeto2z<=0) &&  !(objeto2x>=-1.75 && objeto2x<=1.75 ) )
    {
        objeto2z=-0.5;
    }

    //parte fuera casa 2
    if((objeto2z<=-59.5 && objeto2z>=-60) &&  !(objeto2x>=-1.75 && objeto2x<=1.75 ) )
    {
        objeto2z=-59.5;
    }

    if((objeto2z<=0.4 && objeto2z>=0) &&  !(objeto2x>=-1.75 && objeto2x<=1.75 ) )
    {
        objeto2z=0.5;
    }

    //parte dentro casa 2
    if((objeto2z>=-60.4 && objeto2z<=-60) &&  !(objeto2x>=-1.75 && objeto2x<=1.75 ) )
    {
        objeto1z=-60.5;
    }

    //parte atras casa 1
    if(objeto1z>=4.5 )
    {
        objeto2z=4.5;
    }

    //parte atras casa 2
    if(objeto2z<=-64.5 )
    {
        objeto2z=-64.5;
    }

    //laterales casa1
        //derecha
    if(objeto2x>=3 && objeto2z>=0)
        objeto2x=3;

      //izquierda
    if(objeto2x<=-3 && objeto2z>=0)
        objeto2x=-3;
    //laterales casa2
        //derecha
    if(objeto2x>=3 && objeto2z<=-60)
        objeto2x=3;

      //izquierda
    if(objeto2x<=-3 && objeto2z<=-60)
        objeto2x=-3;

    //paredes hierro izquierda
    if((objeto2x<=-12 && objeto2x>=-15) && (objeto2z>=-45 && objeto2z<=-15))
        objeto2x=-12;
    if((objeto2x>=-18 && objeto2x<=-15) && (objeto2z>=-45 && objeto2z<=-15))
        objeto2x=-18;
    if((objeto2z<=-14.5 && objeto2z>=-15) && (objeto2x<=-12.5 && objeto2x>=-17.5))
        objeto2z=-14.5;
    if((objeto2z<=-45 && objeto2z>=-45.5) && (objeto2x<=-12.5 && objeto2x>=-17.5))
        objeto2z=-45.5;

    //paredes hierro derecha
    if((objeto2x>=12 && objeto2x<=15) && (objeto2z>=-45 && objeto2z<=-15))
        objeto2x=12;
    if((objeto2x<=18 && objeto2x>=15) && (objeto2z>=-45 && objeto2z<=-15))
        objeto2x=18;
    if((objeto2z<=-14.5 && objeto2z>=-15) && (objeto2x>=12.5 && objeto2x<=17.5))
        objeto2z=-14.5;
    if((objeto2z<=-45 && objeto2z>=-45.5) && (objeto2x>=12.5 && objeto2x<=17.5))
        objeto2z=-45.5;

    //demas bloques
    for(double i=-10;i<=10;i+=5)
    {
        for(double j =-10;j>=-50;j-=10)
        {

            //glTranslated(i,1.5,j);
            //glutSolidCube(1);
            //glScaled(2.5,3,2.5);
            if((objeto2x>=i-1.55 && objeto2x<=i) && (objeto2z>=j-1.25 && objeto2z<=j+1.25))
                objeto2x=i-1.5;

            if((objeto2x<=i+1.55 && objeto2x>=i) && (objeto2z>=j-1.25 && objeto2z<=j+1.25))
                objeto2x=i+1.55;

            if((objeto2z>=j-1.55 && objeto2z<=j) && (objeto2x>=i-1.25 && objeto2x<=i+1.25))
                objeto2z=j-1.55;

            if((objeto2z<=j+1.55 && objeto2z>=j) && (objeto2x>=i-1.25 && objeto2x<=i+1.25))
                objeto2z=j+1.55;


        }
    }


}
static void disparo (double posx,double posy,double posz)
{

    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(posx, posy, posz);
    glutSolidCone(0.05,0.05,50,50);
    glPopMatrix();
}

static void herido(double atacantex,double atacantez,double angulo_atacante, double victimax,double victimaz)
{
    bool esta_herido=false;

    double distancia_camarax1=sin(angulo_atacante)*alcance_bala;
    double distancia_camaraz1=cos(angulo_atacante)*alcance_bala;

   /*for(double i=atacantex-0.3;i>atacantez-alcance_bala;i-=0.01)
    {
        for(double j=-i/21.74;j<i/21.74;j+=0.01)
        {
            float xDistance = j - perx;
            float yDistance = i - perz;
            if(sqrt(pow(xDistance, 2) + pow(yDistance, 2)) <0.5)
            {
                esta_herido=true;
                break;
            }
        }
    }*/



    glPushMatrix();
    glColor3f(1,1,0);
    glTranslatef(atacantex, objetoy+0.22, atacantez);
    glRotated((angulo_atacante/(PI/180)),0,1,0);
    glBegin(GL_QUADS);
    glVertex3d(-0.03,0.05,-0.39);
    glVertex3d(+0.03,0.05,-0.39);
    glVertex3d(alcance_bala/21.74,0.05,-alcance_bala);
    glVertex3d(-alcance_bala/21.74,0.05,-alcance_bala);
    glEnd();
    glPopMatrix();

}

static void muneco2(void)
{
    glPushMatrix();
    glTranslated(objeto2x,objetoy,objeto2z);
    glScaled(1.25,1.25,1.25);
    glRotated((angulogiro2/(PI/180)),0,1,0);

    //Cabeza
    glColor3f(0.93, 0.77, 0.51);
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
    glColor3f(0.93, 0.77, 0.51);
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glutWireCube(0.1);
    glutSolidCube(0.1);
    glPopMatrix();

    //Cuerpo
    if(camiseta2)
        glColor3f(0.12, 0.11, 0.11);
    else
        glColor3f(0.2, 0.5, 0.9);

    glPushMatrix();
    glTranslatef(0.0, 0.06, 0.0);
    glScalef(0.73, 1.0, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo izquierdo

    if(camiseta2)
        glColor3f(0.12, 0.11, 0.11);
    else
        glColor3f(0.2, 0.5, 0.9);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    if(camiseta2)
        glColor3f(0.12, 0.11, 0.11);
    else
        glColor3f(0.2, 0.5, 0.9);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
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
    if(pantalon2)
        glColor3f(0.36, 0.32, 0.31);
    else
        glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(-0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
    glPushMatrix();
    glTranslatef(-0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //pierna derecha
    if(pantalon2)
        glColor3f(0.36, 0.32, 0.31);
    else
        glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0.09, -0.28, 0.0);
    glScalef(0.11, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
    glPushMatrix();
    glTranslatef(0.09, -0.48, 0.0);
    glScalef(0.10, 0.2, 0.15);
    glutWireCube(1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    //Cabello
    if(cabello2)
        glColor3f(0.73, 0.14, 00.015);
    else
        glColor3f(0, 0, 0);
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

    if(dispara2)
    {
            disparo(0,0.25,-0.43);
    }

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
    if(camiseta1)
        glColor3f(0.05, 0.34, 0.40);
    else
        glColor3f(0.29, 0.43, 0.13);

    glPushMatrix();
    glTranslatef(0.0, 0.06, 0.0);
    glScalef(0.73, 1.0, 0.4);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo izquierdo
    if(camiseta1)
        glColor3f(0.05, 0.34, 0.40);
    else
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

    if(camiseta1)
        glColor3f(0.05, 0.34, 0.40);
    else
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
    if(pantalon1)
    glColor3f(0.0078, 0.15, 0.18);
    else
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
    if(pantalon1)
    glColor3f(0.0078, 0.15, 0.18);
    else
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
    if(cabello1)
    {
        glColor3f(0.93, 0.89, 0.11);
    }
    else
    {
        glColor3f(0.0, 0.0, 0.0);
    }
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

    if(dispara1)
    {
            disparo(0,0.25,-0.43);
    }


    glPopMatrix();

}

static void brazos1(void)
{
    glPushMatrix();
    glTranslated(objeto1x,objetoy,objeto1z);
    glScaled(1.25,1.25,1.25);
    glRotated(angulogiro1/(PI/180),0,1,0);


    //Brazo izquierdo
    if(camiseta1)
        glColor3f(0.05, 0.34, 0.40);
    else
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

    if(camiseta1)
        glColor3f(0.05, 0.34, 0.40);
    else
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

    if(dispara1)
    {
        disparo(0,0.25,-0.43);
    }

    glPopMatrix();

}

static void brazos2(void)
{
    glPushMatrix();
    glTranslated(objeto2x,objetoy,objeto2z);
    glScaled(1.25,1.25,1.25);
    glRotated((angulogiro2/(PI/180)),0,1,0);

    //Brazo izquierdo
    if(camiseta2)
        glColor3f(0.12, 0.11, 0.11);
    else
        glColor3f(0.2, 0.5, 0.9);
    glPushMatrix();
    glTranslatef(0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
    glPushMatrix();
    glTranslatef(0.13, 0.2, -0.2);
    glRotated(130,0,1,0);
    glScalef(0.85, 0.15, 0.12);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    //Brazo derecho

    if(camiseta2)
        glColor3f(0.12, 0.11, 0.11);
    else
        glColor3f(0.2, 0.5, 0.9);
    glPushMatrix();
    glTranslatef(-0.17, 0.2, 0.0);
    glRotated(90,0,1,0);
    glScalef(0.4, 0.16, 0.1);
    glutWireCube(0.4);
    glutSolidCube(0.4);
    glPopMatrix();

    glColor3f(0.93, 0.77, 0.51);
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

    if(dispara2)
    {
            disparo(0,0.25,-0.43);
    }

    glPopMatrix();

}

void arbol2()
{
    for(double i=-25;i<=-20;i+=5)
    {
        for(double j =-10;j>=-50;j-=10)
        {


    glPushMatrix();
    glTranslated(i,1.3,j);
    //Tronco del arbol
    glPushMatrix();
    glColor3d(0.33, 0.16, 0.015);
    glPushMatrix();
    glScaled(1.5,5,1.5);
    glutSolidCube(0.5);
    glPopMatrix();


    //Hojas del arbol
    glPushMatrix();
    glColor3d(0.11, 0.6, 0.13);
    glTranslated(0,0,0);
    glRotated(270, 1.0, 0.0, 0.0);
    glScaled(0.5,0.5,2);
    glutSolidCone(2.1, 2, 50, 50);
    glPopMatrix();


    glPopMatrix();

        }
    }

    for(double i=20;i<=25;i+=5)
    {
        for(double j =-10;j>=-50;j-=10)
        {


    glPushMatrix();
    glTranslated(i,1.3,j);
    //Tronco del arbol
    glPushMatrix();
    glColor3d(0.33, 0.16, 0.015);
    glPushMatrix();
    glScaled(1.5,5,1.5);
    glutSolidCube(0.5);
    glPopMatrix();


    //Hojas del arbol
    glPushMatrix();
    glColor3d(0.11, 0.6, 0.13);
    glTranslated(0,0,0);
    glRotated(270, 1.0, 0.0, 0.0);
    glScaled(0.5,0.5,2);
    glutSolidCone(2.1, 2, 50, 50);
    glPopMatrix();


    glPopMatrix();

        }
    }
}

void arbol1()
{

    glPushMatrix();
    glScaled(2.5,3,2.5);
    glTranslated(0,1.8,8);
    //Tronco del arbol
    glPushMatrix();
    glColor3d(0.33, 0.16, 0.015);
    glScaled(1,5,1);
    glTranslated(0,0.09,-20);
    glutSolidCube(1);
    glPopMatrix();

    //Hojas del arbol
    glPushMatrix();
    glColor3d(0, 0.20, 0.015);
    glTranslated(1,3,-21);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.06, 0.25, 0.07);
    glTranslated(1,3.5,-19);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.06, 0.20, 0.07);
    glTranslated(-1,3.5,-21);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0, 0.16, 0.015);
    glTranslated(-1,3.5,-19);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glColor3d(0.06, 0.22, 0.07);
    glTranslated(0,4.8,-20);
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();

    glPopMatrix();
}

void piso()
{

    glPushMatrix();
    glColor3d(0.8,0.6,0.4);
    glTranslated(0,0,-30);
    glRotated(0,0,0,0);

    glPushMatrix();
    glScaled(60,0.2,70);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.7,0.5,0.3);
    glScaled(60,0.2,60);
    glutWireCube(1);
    glPopMatrix();


    glPopMatrix();

}

void paredes_hierro()
{
    glPushMatrix();
            glTranslated(-15,1.5,-30);
            glRotated(0,0,0,0);
            glScaled(5,3,30);
            glColor3d(0.6,0.6,0.7);
            glutSolidCube(1);
            glColor3d(0.4,0.4,0.5);
            glutWireCube(1);
            glPopMatrix();

    glPushMatrix();
            glTranslated(15,1.5,-30);
            glRotated(0,0,0,0);
            glScaled(5,3,30);
            glColor3d(0.6,0.6,0.7);
            glutSolidCube(1);
            glColor3d(0.4,0.4,0.5);
            glutWireCube(1);
            glPopMatrix();

    for(double i=-10;i<=10;i+=5)
    {
        for(double j =-10;j>=-50;j-=10)
        {
            if(j!=-30 || i!=0)
            {
            glPushMatrix();
            glTranslated(i,1.5,j);
            glRotated(0,0,0,0);
            glScaled(2.5,3,2.5);
            glColor3d(0.6,0.6,0.7);
            glutSolidCube(1);
            glColor3d(0.4,0.4,0.5);
            glutWireCube(1);
            glPopMatrix();
            }
        }
    }
}

void paredes()
{

            glPushMatrix();
            glTranslated(-30,1.5,-30);
            glRotated(0,0,0,0);
            glScaled(0.1,3,60);
            glColor3d(0.7,0.5,0.3);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();

             glPushMatrix();
            glTranslated(-16.75,1.5,0);
            glRotated(0,0,0,0);
            glScaled(26.5,3,0.1);
            glColor3d(0.75,0.55,0.35);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();

            glPushMatrix();
            glTranslated(16.75,1.5,0);
            glRotated(0,0,0,0);
            glScaled(26.5,3,0.1);
            glColor3d(0.75,0.55,0.35);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();



            glPushMatrix();
            glTranslated(30,1.5,-30);
            glRotated(0,0,0,0);
            glScaled(0.1,3,60);
            glColor3d(0.7,0.5,0.3);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();

              glPushMatrix();
            glTranslated(-16.75,1.5,-60);
            glRotated(0,0,0,0);
            glScaled(26.5,3,0.1);
            glColor3d(0.75,0.55,0.35);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();

            glPushMatrix();
            glTranslated(16.75,1.5,-60);
            glRotated(0,0,0,0);
            glScaled(26.5,3,0.1);
            glColor3d(0.75,0.55,0.35);
            glutSolidCube(1);
            glColor3d(0.7,0.5,0.3);
            glutWireCube(1);
            glPopMatrix();


}

void dibujaCasa()
{


    glPushMatrix();

    glScaled(10,10,10);
    glTranslated(-0.55,-0.1,0.005);
    /* pared frontal */
    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.0);
    glVertex3f(0.4, 0.1, 0.0);
    glVertex3f(0.4, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.0);
    glEnd();

    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.7, 0.1, 0.0);
    glVertex3f(0.9, 0.1, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.7, 0.575, 0.0);
    glEnd();

    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.4, 0.4, 0.0);
    glVertex3f(0.7, 0.4, 0.0);
    glVertex3f(0.7, 0.575, 0.0);
    glVertex3f(0.4, 0.575, 0.0);
    glEnd();

    //pared de atras
    glColor3f(0.7, 0.75, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.5);
    glVertex3f(0.9, 0.1, 0.5);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.2, 0.575, 0.5);
    glEnd();

    //pared izquierda
    glColor3f(0.9, 0.9, .25);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.5);
    glVertex3f(0.2, 0.1, 0.0);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.5);
    glEnd();

    //pared derecha
    glColor3f(0.9, 0.9, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(0.9, 0.1, 0.5);
    glVertex3f(0.9, 0.1, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.5);
    glEnd();

    //lado del techo izquiero
    glColor3f(.5, 0.5, .25);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.9, 0.8, 0.25);
    glEnd();

    //lado del techo derecho
    glColor3f(0.5, 0.5, 0.25);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.5);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //techo frontal
    glColor3f(0.55, 0.35, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.8, 0.25);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //techo de atras
    glColor3f(0.55, 0.35, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.575, 0.5);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.9, 0.8, 0.25);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //ventana 1
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0,0,-0.001);
    glBegin(GL_POLYGON);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.85, 0.25, 0.0);
    glVertex3f(0.85, 0.4, 0.0);
    glVertex3f(0.75, 0.4, 0.0);
    glEnd();
    glPopMatrix();

    //ventana 2
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0,0,-0.001);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.35, 0.25, 0.0);
    glVertex3f(0.35, 0.4, 0.0);
    glVertex3f(0.25, 0.4, 0.0);
    glEnd();
    glPopMatrix();


    glPopMatrix();

    //CASA2

    glPushMatrix();

    glRotated(180,0,1,0);
    glScaled(10,10,10);
    glTranslated(-0.55,-0.1,6.005);
    /* pared frontal */
    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.0);
    glVertex3f(0.4, 0.1, 0.0);
    glVertex3f(0.4, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.0);
    glEnd();

    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.7, 0.1, 0.0);
    glVertex3f(0.9, 0.1, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.7, 0.575, 0.0);
    glEnd();

    glColor3f(01, 1, 0.15);
    glBegin(GL_POLYGON);
    glVertex3f(0.4, 0.4, 0.0);
    glVertex3f(0.7, 0.4, 0.0);
    glVertex3f(0.7, 0.575, 0.0);
    glVertex3f(0.4, 0.575, 0.0);
    glEnd();

    //pared de atras
    glColor3f(0.7, 0.75, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.5);
    glVertex3f(0.9, 0.1, 0.5);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.2, 0.575, 0.5);
    glEnd();

    //pared izquierda
    glColor3f(0.9, 0.9, .25);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.1, 0.5);
    glVertex3f(0.2, 0.1, 0.0);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.5);
    glEnd();

    //pared derecha
    glColor3f(0.9, 0.9, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(0.9, 0.1, 0.5);
    glVertex3f(0.9, 0.1, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.5);
    glEnd();

    //lado del techo izquiero
    glColor3f(.5, 0.5, .25);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.9, 0.8, 0.25);
    glEnd();

    //lado del techo derecho
    glColor3f(0.5, 0.5, 0.25);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.2, 0.575, 0.5);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //techo frontal
    glColor3f(0.55, 0.35, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.575, 0.0);
    glVertex3f(0.9, 0.575, 0.0);
    glVertex3f(0.9, 0.8, 0.25);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //techo de atras
    glColor3f(0.55, 0.35, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(0.2, 0.575, 0.5);
    glVertex3f(0.9, 0.575, 0.5);
    glVertex3f(0.9, 0.8, 0.25);
    glVertex3f(0.2, 0.8, 0.25);
    glEnd();

    //ventana 1
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0,0,-0.001);
    glBegin(GL_POLYGON);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.85, 0.25, 0.0);
    glVertex3f(0.85, 0.4, 0.0);
    glVertex3f(0.75, 0.4, 0.0);
    glEnd();
    glPopMatrix();

    //ventana 2
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0,0,-0.001);
    glBegin(GL_POLYGON);
    glVertex3f(0.25, 0.25, 0.0);
    glVertex3f(0.35, 0.25, 0.0);
    glVertex3f(0.35, 0.4, 0.0);
    glVertex3f(0.25, 0.4, 0.0);
    glEnd();
    glPopMatrix();


    glPopMatrix();


}


static void juego(void)
{


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
    arbol2();
    arbol1();
    piso();
    paredes();
    paredes_hierro();
    dibujaCasa();
    imprimir_vida(vida1,kills1);


    glPopMatrix();

    glViewport(0,alto/2,ancho,alto/2);
    glPushMatrix();
    gluLookAt(objeto2x,objetoy+0.4,objeto2z, objeto2x-distancia_camarax2,objetoy+0.4,objeto2z-distancia_camaraz2,0,1,0);
    brazos2();
    muneco1();
    dibujaCasa();
    arbol2();
    arbol1();
    piso();
    paredes();
    paredes_hierro();
    imprimir_vida(vida2,kills2);
    glPopMatrix();



}

static void menu(void)
{
    glClear(GL_COLOR_BUFFER_BIT);//limpia la pantalla
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //muneco1
    glPushMatrix();
    glScaled(0.5,0.5,1);
    glTranslated(-1.2,-0.4,-3);
    muneco1();
    glPopMatrix();

    //muneco2
    glPushMatrix();

    glRotated(180,0,1,0);
    glScaled(0.5,0.5,1);
    glTranslated(-1.2,-0.4,+63);
    muneco2();
    glPopMatrix();

    //Colores de la ropa muneco1
    //CABELLO
    glPushMatrix();
    glTranslated(-0.6,-0.5,0);
    glColor3f(0.93, 0.89, 0.11);
    glutSolidCube(0.1);
    glPopMatrix();
    //CAMISETA
    glPushMatrix();
    glTranslated(-0.6,-0.65,0);
    glColor3f(0.05, 0.34, 0.40);
    glutSolidCube(0.1);
    glPopMatrix();
    //PANTALON
    glPushMatrix();
    glTranslated(-0.6,-0.80,0);
    glColor3f(0.0078, 0.15, 0.18);
    glutSolidCube(0.1);
    glPopMatrix();

    //Colores de la ropa muneco2
    //CABELLO
    glPushMatrix();
    glTranslated(0.6,-0.5,0);
    glColor3f(0.73, 0.14, 00.015);
    glutSolidCube(0.1);
    glPopMatrix();
    //CAMISETA
    glPushMatrix();
    glTranslated(0.6,-0.65,0);
    glColor3f(0.12, 0.11, 0.11);
    glutSolidCube(0.1);
    glPopMatrix();
    //PANTALON
    glPushMatrix();
    glTranslated(0.6,-0.80,0);
    glColor3f(0.36, 0.32, 0.31);
    glutSolidCube(0.1);
    glPopMatrix();


    imprimir();

    //Boton aceptar
    glPushMatrix();
    glTranslated(0,0,-1.0);
    glColor3f(0.21, 0.91, 0.04);
    glutSolidCube(0.3);
    glPopMatrix();






}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);

    if(entra_juego)
        juego();
    else
    menu();

    glLoadIdentity();
    glFlush();
}

void Movimiento()
{
    prohibir_paso();

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
        objeto2z-=cos(angulogiro2)*velocidad_movimiento;
        objeto2x-=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_baj)
    {
        objeto2z+=cos(angulogiro2)*velocidad_movimiento;
        objeto2x+=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_izq)
    {
        objeto2x-=cos(angulogiro2)*velocidad_movimiento;
        objeto2z+=sin(angulogiro2)*velocidad_movimiento;
    }
    if(mueve2_der)
    {
        objeto2x+=cos(angulogiro2)*velocidad_movimiento;
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
    if(entra_juego)
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
            camara2_izq=false;
            camara2_der=true;
            break;


        case 'e' :
        case 'E' :
            camara2_der=false;
            camara2_izq=true;
            break;

        case 's' :
        case 'S' :
            dispara1=true;
            break;

        case 'W' :
        case 'w' :
            dispara2=true;
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

}

void teclasEspeciales(int key, int x, int y)
{
    if(entra_juego)
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
            camara2_der=false;
            break;

        case 'e' :
        case 'E' :
            camara2_izq=false;

            break;
        case 's' :
        case 'S' :
            dispara1=false;
            break;

        case 'W' :
        case 'w' :
            dispara2=false;
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

void movmouse(int button, int state, int x, int y)
{
    if(!entra_juego)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            mousey=(((-y/alto)+1)*2)-1;
            mousex=((x/ancho)*2)-1;

            if(mousex<0.15 && mousex>-0.15 && mousey<0.15 && mousey>-0.15)
                entra_juego=true;



            if(mousex<-0.55 && mousex>-0.65 && mousey<-0.45 && mousey>-0.55)
                {
                    if(cabello1)
                        cabello1=false;
                    else
                        cabello1=true;
                }

            if(mousex<-0.55 && mousex>-0.65 && mousey<-0.6 && mousey>-0.7)
                {
                    if(camiseta1)
                        camiseta1=false;
                    else
                        camiseta1=true;
                }
            if(mousex<-0.55 && mousex>-0.65 && mousey<-0.75 && mousey>-0.85)
                {
                    if(pantalon1)
                        pantalon1=false;
                    else
                        pantalon1=true;
                }
            if(mousex<0.65 && mousex>0.55 && mousey<-0.45 && mousey>-0.55)
                {
                    if(cabello2)
                        cabello2=false;
                    else
                        cabello2=true;
                }
            if(mousex<0.65 && mousex>0.55 && mousey<-0.6 && mousey>-0.7)
                {
                    if(camiseta2)
                        camiseta2=false;
                    else
                        camiseta2=true;
                }
             if(mousex<0.65 && mousex>0.55 && mousey<-0.75 && mousey>-0.85)
                {
                    if(pantalon2)
                        pantalon2=false;
                    else
                        pantalon2=true;
                }
        }
    }
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
    glutMouseFunc(movmouse);
    glutIdleFunc(Movimiento);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
