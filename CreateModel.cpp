//
// Created by Rchi Lugtu on 28/03/20.
//

//  ========================================================================
//  COSC363: Computer Graphics (2020);  University of Canterbury.
//
//  FILE NAME: Humanoid.cpp
//  See Lab02.pdf for details
//  ========================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include "loadTGA.h"


using namespace std;

//--Globals ---------------------------------------------------------------
int cam_hgt = 4; //Camera height
float angle = 10.0;  //Rotation angle for viewing
float theta = 20; // Rotation angle for left leg and right arm
int downwards = 1;
float batonTheta = 20;
float batonDirection = 1;

GLUquadric *q;

GLuint txId[1];


//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
    glColor3f(0., 0.5, 0.);			//Floor colour
    for(float i = -50; i <= 50; i++)
    {
        glBegin(GL_LINES);			//A set of grid lines on the xz-plane
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }
}

void loadTextures()
{
    glGenTextures(2, txId); 		// Create texture ids
//    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture name for the following OpenGL texture
//    loadTGA("chains.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void myTimer(int value)
{
    if (downwards == 1) {
        theta-=1;
        if (theta < -30) {
            downwards = 0;
        }
    } else {
        theta+=1;
        if (theta > 30) {
            downwards = 1;
        }
    }

    if (batonDirection == 1){
        batonTheta-=1;
        if (batonTheta < -30) {
            batonDirection = 0;
        }
    } else {
        batonTheta+=1;
        if (batonTheta > 30) {
            batonDirection = 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, myTimer, 0);
}


//-------------------------- Draws a Dessert Guard model constructed using GLUT objects --------------------------------
void drawGuard()
{
    glColor3f(1., 0.85, 0.67);		//Head
    glPushMatrix();
    glTranslatef(0, 7.7, 0);
    glRotatef(theta/2, 0, 1, 0);
    glTranslatef(0, -7.7, 0);
    glTranslatef(0, 7.7, 0);
    glutSolidCube(1.4);
    glPopMatrix();

    glColor3f(1., 0., 0.);			//Torso
    glPushMatrix();
    glTranslatef(0, 5.5, 0);
    glScalef(3, 3, 1.4);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 0.);			//Right leg
    glPushMatrix();
    glTranslatef(-0.8, 4, 0);
    glRotatef(-theta, 1, 0, 0);
    glTranslatef(0.8, -4, 0);
    glTranslatef(-0.8, 2.2, 0);
    glScalef(1, 4.4, 1);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0., 0., 0.);          //Left leg
    glPushMatrix();
    glTranslatef(0.8, 4, 0);
    glRotatef(theta, 1, 0, 0);
    glTranslatef(-0.8, -4, 0);
    glTranslatef(0.8, 2.2, 0);
    glScalef(1, 4.4, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1., 0., 0.);			//Right arm
    glPushMatrix();
    glTranslatef(-2, 5, 0);
    glRotatef(theta, 1, 0, 0);
    glTranslatef(2, -5, 0);
    glTranslatef(-2, 5, 0);
    glScalef(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0,0,0);               // Long baton
    glPushMatrix();
    glTranslatef(-2,6.6,0.25);
    glRotatef(batonTheta, 1,0,0);
    glTranslatef(0,-3,0);
    gluCylinder(q, 0.2,0.1, 7,30, 30);
    glPopMatrix();
    glPopMatrix();

    glColor3f(1., 0., 0.);			//Left arm
    glPushMatrix();
    glTranslatef(2, 5, 0);
    glRotatef(-theta, 1, 0, 0);
    glTranslatef(-2, -5, 0);
    glTranslatef(2, 5, 0);
    glScalef(1, 4, 1);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0,0,0);               // GUARD HAT
    glPushMatrix();
    glRotatef(theta/2, 0, 1, 0);
    glTranslatef(0,8,0);
    glRotatef(-90, 1,0,0);
    gluCylinder(q, 1.2,0.9, 3,30, 30);
    glPopMatrix();

}


//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display()
{
    float lpos[4] = {10., 10., 10., 1.0};  //light's position


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, cam_hgt, 20, 0, 4, 0, 0, 1, 0);
    glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glRotatef(angle, 0.0, 1.0, 0.0);  //Rotate the scene about the y-axis

    glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.
//    drawFloor();
    glEnable(GL_LIGHTING);
    //Enable lighting when drawing the model
    glPushMatrix();
    glScalef(2,2,2);
    drawGuard();
    glPopMatrix();
    glutSwapBuffers();
}

//------- Initialize OpenGL parameters -----------------------------------
void initialize()
{
    loadTextures();
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//Background colour

    q = gluNewQuadric();
    gluQuadricTexture (q, GL_TRUE);
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);


    glEnable(GL_LIGHTING);					//Enable OpenGL states
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);


    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 1000.0);   //Camera Frustum

}

//------------ Special key event callback ---------------------------------
// To enable the use of left and right arrow keys to rotate the scene
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) angle-=5;
    else if(key == GLUT_KEY_RIGHT) angle+=5;
    else if (key == GLUT_KEY_UP) cam_hgt+=3;
    else if (key == GLUT_KEY_DOWN) cam_hgt-=3;

    glutPostRedisplay();
}

//  ------- Main: Initialize glut window and register call backs -----------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize (1024, 1024);
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Model Creation");
    initialize();
    glutTimerFunc(10, myTimer, 0);
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}