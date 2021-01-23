//  ========================================================================
//  Assignment1 created by Rchi Lugtu
//
//  FILE NAME: Assignment1.cpp
//  ========================================================================

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include "loadTGA.h"
#define GL_CLAMP_TO_EDGE 0x812F


//--Globals ---------------------------------------------------------------
GLuint texId[13];   //Texture ids
float *x, *y, *z;		//vertex coordinate arrays
int *t1, *t2, *t3;		//triangles
int nvrt, ntri;			//total number of vertices and triangles

// Physics model cannon
bool fire = false;
float v = 0;
float x_ballpos = 38.88;
float y_ballpos = 64;

// Camera Movement
float angle = 0;
float look_x=0, look_z = -1;
float eye_x=0, eye_z = 2250;

// Dessert Museum Animation
float elevateUp = 19;
float openMuseum = false;
// Dessert Museum Ice Cream Movement
float jumpIceCream = 0;
float jumpIncrement = 0.2;
float spinIceCream = 90;


// Dessert Guard Walking
int armSwings = 1;
int moveGuard = 0;
int moveIncrement = 5;
int directionGuard = 0;
float theta = 20;   // Dessert Guard Body Movements
float light1Pos = -100.0f;    // Guard Flash Light

// Candy Cane Swing Movement
float swingDirection = 1;
float swingTheta = 0;

// Candy Carousel Animation
float candyBallDirection = 1;
float candyBallMovement = 0;

float spinObject = 0;    // Responsible for the rotation of candy balls, carousel, and swing, and gingerbread house

// Shadow Object ( Icosahedron )
float spinobjectshadow;

// Ginger Bread House Translation up and down
float oscillate = 200;
float oscillateIncrement = 1;

GLUquadric *q;    //Required for creating cylindrical objects

void loadTextures()
{
    glGenTextures(13, texId);
//    -------------------------------------- FRONT -------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    loadTGA("front.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- BACK -------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    loadTGA("back.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- LEFT -------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    loadTGA("right.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- RIGHT ---------------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    loadTGA("left.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- BOTTOM --------------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[4]);
    loadTGA("bottom.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- TOP -----------------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[5]);
    loadTGA("top.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

//    -------------------------------------- Museum Textures -----------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[6]);
    loadTGA("chocolate.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texId[7]);
    loadTGA("sprinkles.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


    glBindTexture(GL_TEXTURE_2D, texId[8]);  //Use this texture name for the following OpenGL texture
    loadTGA("splatter.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


    glBindTexture(GL_TEXTURE_2D, texId[9]);  //Use this texture name for the following OpenGL texture
    loadTGA("candyHearts.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texId[10]);
    loadTGA("jellyBites.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texId[11]);
    loadTGA("gingerbread.tga");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texId[12]);
    loadTGA("icecreamMelt.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//--------------------------------------  Load OFF Format files (for cannon  -------------------------------------------
void loadMeshFile(const char* fname)
{
    ifstream fp_in;
    int num, ne;

    fp_in.open(fname, ios::in);
    if(!fp_in.is_open())
    {
        cout << "Error opening mesh file" << endl;
        exit(1);
    }

    fp_in.ignore(INT_MAX, '\n');				//ignore first line
    fp_in >> nvrt >> ntri >> ne;			    // read number of vertices, polygons, edges

    x = new float[nvrt];                        //create arrays
    y = new float[nvrt];
    z = new float[nvrt];

    t1 = new int[ntri];
    t2 = new int[ntri];
    t3 = new int[ntri];

    for(int i=0; i < nvrt; i++)                         //read vertex list
        fp_in >> x[i] >> y[i] >> z[i];

    for(int i=0; i < ntri; i++)                         //read polygon list
    {
        fp_in >> num >> t1[i] >> t2[i] >> t3[i];
        if(num != 3)
        {
            cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl;  //not a triangle!!
            exit(1);
        }
    }

    fp_in.close();
    cout << " File successfully read." << endl;
}


//    -------------------------------------- Draws the floor -----------------------------------------------------------
void floor()
{
    glDisable(GL_TEXTURE_2D);
    float white[4] = {1., 1., 1., 1.};
    float black[4] = {0};
//    glColor4f(0.60, 0.81, 0.83, 0.5);
    glColor3f(1,1,1);
    glNormal3f(0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);

    glBegin(GL_QUADS);
    for(int i = -2500; i < 2500; i+=20)
    {
        for(int j = -2500;  j < 2500; j+=20)
        {
            glVertex3f(i, 0, j);
            glVertex3f(i, 0, j+20);
            glVertex3f(i+20, 0, j+20);
            glVertex3f(i+20, 0, j);
        }
    }
    glEnd();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

//    -------------------------------------- Draws the Skybox ----------------------------------------------------------
void skybox()
{
    glEnable(GL_TEXTURE_2D);

    ////////////////////// FRONT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);    glVertex3f(-2500, 0, -2500);
        glTexCoord2f(1.0,0.0);    glVertex3f(2500, 0, -2500);
        glTexCoord2f(1.0,1.0);    glVertex3f(2500, 2500, -2500);
        glTexCoord2f(0.0,1.0);    glVertex3f(-2500, 2500, -2500);
    glEnd();

    ////////////////////// BACK WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0,0.0);    glVertex3f(-2500, 0, 2500);
        glTexCoord2f(0.0,0.0);    glVertex3f(2500, 0, 2500);
        glTexCoord2f(0.0,1.0);    glVertex3f(2500, 2500, 2500);
        glTexCoord2f(1.0,1.0);    glVertex3f(-2500, 2500, 2500);
    glEnd();

    ////////////////////// LEFT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);    glVertex3f(-2500, 0, 2500);
        glTexCoord2f(1.0,0.0);    glVertex3f(-2500, 0, -2500);
        glTexCoord2f(1.0,1.0);    glVertex3f(-2500, 2500, -2500);
        glTexCoord2f(0.0,1.0);    glVertex3f(-2500, 2500, 2500);
    glEnd();

    ////////////////////// RIGHT WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,0.0);    glVertex3f(2500, 0, -2500);
        glTexCoord2f(1.0,0.0);    glVertex3f(2500, 0, 2500);
        glTexCoord2f(1.0,1.0);    glVertex3f(2500, 2500, 2500);
        glTexCoord2f(0.0,1.0);    glVertex3f(2500, 2500, -2500);
    glEnd();


    // Uncomment this and comment out the code that makes floor() to texture the floor.
//    ////////////////////// FLOOR ///////////////////////
//    glBindTexture(GL_TEXTURE_2D, texId[4]);
//    glBegin(GL_QUADS);
//        glTexCoord2f(0.0,0.0);    glVertex3f(-1250, 0, 1250);
//        glTexCoord2f(1.0,0.0);    glVertex3f(1250, 0, 1250);
//        glTexCoord2f(1.0,1.0);    glVertex3f(1250, 0, -1250);
//        glTexCoord2f(0.0,1.0);    glVertex3f(-1250, 0, -1250);
//    glEnd();

    ////////////////////// TOP WALL ///////////////////////
    glBindTexture(GL_TEXTURE_2D, texId[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0,1.0);    glVertex3f(-2500, 2500, 2500);
        glTexCoord2f(1.0,1.0);    glVertex3f(2500, 2500, 2500);
        glTexCoord2f(1.0,0.0);    glVertex3f(2500, 2500, -2500);
        glTexCoord2f(0.0,0.0);    glVertex3f(-2500, 2500, -2500);
    glEnd();
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
    glTranslatef(-2,3.6,0.25);
    glRotatef(theta, 1,0,0);
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

//    -------------------------------------- Draws the Dessert Swing ---------------------------------------------------

void drawSwing()
{
    glPushMatrix();                             // SMALL RIGHT VERT BAR
    glTranslatef(5.55,14.5,-0.05);
    glScalef(.25,.6,.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();                             // SMALL LEFT VERT BAR
    glTranslatef(2,14.5,-0.05);
    glScalef(.25,.6,.25);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.53,0.81,0.94);

    glPushMatrix();
    glTranslatef(5.55,14.2,-0.05);      // RIGHT CHAIN
    glRotatef(swingTheta, 1,0,0);
    glRotatef(90, 1,0,0);
    gluCylinder(q, 0.1, 0.1,9.25, 30,30);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2,14.2,-0.05);      // LEFT CHAIN
    glRotatef(swingTheta, 1,0,0);
    glRotatef(90, 1,0,0);
    gluCylinder(q, 0.1, 0.1,9.25, 30,30);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();                             // PARABOLIC SEAT OF THE SWING
    glRotatef(180, 0,1,0);
    glTranslatef(-3.8,14,0);
    glRotatef(-swingTheta, 1,0,0);
    glTranslatef(0,-9.769,1);
    glRotatef(-90,1,0,0);
    glScalef(0.1,0.1,0.1);
    glBegin(GL_QUAD_STRIP);
    for (int i = -20; i <= 20; i++) {
        glVertex3f(i, 0, (0.020*i*i));
        glVertex3f(i, 20, (0.020*i*i));
    }
    glEnd();
    glPopMatrix();
}

//    -------------------------------------- Draws the BODY Of the Dessert Swing ---------------------------------------
void drawCandySwing(string girth)
{
    float radius = 0.4;
    if (girth == "thinner") {
        radius = 0.2;
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[7]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    for (int i = 5; i<=15; i+=5) {              // POLE
        glPushMatrix();
        glTranslatef(0, i,0);
        glRotatef(90, 1,0,0);
        gluCylinder(q, radius, radius,5, 30,30);
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.53,0.81,0.94);
    glPushMatrix();                         // TOP HORIZONTAL BAR
    glTranslatef(3,14.75,-0.05);
    glScalef(5.5, .25, .25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    drawSwing();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

//    -------------------------------------- Draws the Ice Cream for the museum ----------------------------------------
void iceCream()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texId[7]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPushMatrix();
    glTranslatef(0, 12, 0);
    glRotatef(90,1,0,0);
    gluSphere(q, 2.5, 50, 40);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1,0.85,0.725);
    glPushMatrix();
    glTranslatef(0, 11, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(1.8, 11, 50,40);
    glPopMatrix();

}

//    ---------------------------- Draws the small walls of the musuem -------------------------------------------------
void smallBlock()
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[12]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.,1.);    glVertex3f(-2.0, 0.0, 1);  // Front side Z+ facing
    glTexCoord2f(2.,1.);    glVertex3f(2.0, 0.0, 1);
    glTexCoord2f(2.,0.);    glVertex3f(2.0, 5.0, 1);
    glTexCoord2f(0,0.);     glVertex3f(-2.0, 5.0, 1);

    glTexCoord2f(0.,1.);    glVertex3f(2.0, 0.0, -1);
    glTexCoord2f(2.,1.);    glVertex3f(-2.0, 0.0,-1);  // Back side Z- facing
    glTexCoord2f(2.,0.);    glVertex3f(-2.0, 5.0,-1);
    glTexCoord2f(0.,0.);    glVertex3f(2.0, 5.0, -1);

    glTexCoord2f(0.,1.);    glVertex3f(-2.0, 0.0, -1);
    glTexCoord2f(1.,1.);    glVertex3f(-2.0, 0.0,1);  // Left side X- facing
    glTexCoord2f(1.,0.);    glVertex3f(-2.0, 5.0,1);
    glTexCoord2f(0.,0.);    glVertex3f(-2.0, 5.0, -1);

    glTexCoord2f(0.,1.);    glVertex3f(2.0, 0.0, 1);
    glTexCoord2f(1.,1.);    glVertex3f(2.0, 0.0,-1);  // Right side X+ facing
    glTexCoord2f(1.,0.);    glVertex3f(2.0, 5.0,-1);
    glTexCoord2f(0.,0.);    glVertex3f(2.0, 5.0, 1);

    glDisable(GL_TEXTURE_2D);
    glColor3f(0.96,0.70,0.86);
    glVertex3f(-2.0, 5.0, 1);
    glVertex3f(2.0, 5.0,  1);                                // Top side Y+ facing
    glVertex3f(2.0, 5.0, -1);
    glVertex3f(-2.0, 5.0, -1);
    glEnd();
    glPopMatrix();
}

//    ---------------------------- Draws the BIG walls of the Museum ---------------------------------------------------
void drawWall()
{
    glBindTexture(GL_TEXTURE_2D, texId[12]);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.,1.);    glVertex3f(-8.0, 0.0, 1.0);  // Front side Z+ facing
    glTexCoord2f(2.,1.);    glVertex3f(8.0, 0.0, 1.0);
    glTexCoord2f(2.,0.);    glVertex3f(8.0, 10.0, 1.0);
    glTexCoord2f(0,0.);     glVertex3f(-8.0, 10.0, 1.0);

    glTexCoord2f(0.,1.);    glVertex3f(8.0, 0.0, -1.0);
    glTexCoord2f(2.,1.);    glVertex3f(-8.0, 0.0,-1.0);  // Back side Z- facing
    glTexCoord2f(2.,0.);    glVertex3f(-8.0, 10.0,-1.0);
    glTexCoord2f(0.,0.);    glVertex3f(8.0, 10.0, -1.0);

    glTexCoord2f(0.,0.);    glVertex3f(-8.0, 10.0, 1.0);
    glTexCoord2f(2.,0.);    glVertex3f(8.0, 10.0,  1.0); // Top side Y+ facing
    glTexCoord2f(2,1.);    glVertex3f(8.0, 10.0, -1.0);
    glTexCoord2f(0.,1.);    glVertex3f(-8.0, 10.0, -1.0);

    glTexCoord2f(0.,1.);    glVertex3f(8.0, 0.0, 1.0);
    glTexCoord2f(2.,1.);    glVertex3f(8.0, 0.0,  -1.0); // Right side X+ facing
    glTexCoord2f(2.,0.);    glVertex3f(8.0, 10.0, -1.0);
    glTexCoord2f(0.,0.);    glVertex3f(8.0, 10.0, 1.0);

    glTexCoord2f(0.,1.);    glVertex3f(-8.0, 0.0, -1.0);
    glTexCoord2f(2.,1.);    glVertex3f(-8.0, 0.0,  1.0); // Left side X- facing
    glTexCoord2f(2.,0.);    glVertex3f(-8.0, 10.0, 1.0);
    glTexCoord2f(0.,0.);    glVertex3f(-8.0, 10.0, -1.0);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 0,0);
    smallBlock();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 0,0);
    smallBlock();
    glPopMatrix();
}

//    ---------------------------- Connects the components of the museum -----------------------------------------------
void drawMuseum()
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glRotatef(90, 0, 1,0);
    // LEFT WALL
    glPushMatrix();
    glTranslatef(0, 0, -13);
    drawWall();
    glPopMatrix();
    // RIGHT WALL
    glPushMatrix();
    glTranslatef(0, 0, 13);
    drawWall();
    glPopMatrix();
    glPopMatrix();

    for (int x = -10; x < -5; x+=4) {           // FRONT WALLS LEFT
        glPushMatrix();
        glTranslatef(x, 0,11);
        smallBlock();
        glPopMatrix();
    }

    for (int x = 10; x > 5; x-=4) {             // FRONT WALLS RIGHT
        glPushMatrix();
        glTranslatef(x, 0,11);
        smallBlock();
        glPopMatrix();
    }

    glPushMatrix();                             // BACK WALL
    glTranslatef(0, 0, -11);
    drawWall();
    glPopMatrix();

    // -------------------------------- DRAWS THE ICE CREAM IN THE 4 CORNERS ---------------------------------------
    glEnable(GL_TEXTURE_2D);
    for (int i = 1; i > -2; i-=2) {                     // CORNER BACK RIGHT AND CORNER BACK LEFT
        glPushMatrix();
        glTranslatef(0,jumpIceCream/2,0);
        glTranslatef(11*i, 3, -10.6);
        glRotatef(spinIceCream, 0, 1, 0);
        iceCream();
        glPopMatrix();
    }

    for (int i = 1; i > -2; i-=2) {                         // FRONT BACK RIGHT AND FRONT BACK LEFT
        glPushMatrix();
        glTranslatef(12.7*i, 2, 10.6);
        glRotatef(-spinIceCream, 0, 1, 0);
        iceCream();
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}

// ------------------------------------------ CANDY Carousel Balls -----------------------------------------------------
void drawCandyBalls()
{
    glPushMatrix();
    glRotatef(-spinObject*4, 0,1,0);
    gluSphere(q, 2, 20,20);
    glPopMatrix();
}

// ------------------------------------------ CANDY Carousel Sticks -----------------------------------------------------
void drawCandySticks()
{
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0,1,0);
    glRotatef(-90, 1,0,0);
    gluCylinder(q, 0.2,0.2,7,20,20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.78, 0.63,0.78);
    glTranslatef(0,8,0);
    glRotatef(-90, 1,0,0);
    gluCylinder(q, 0.2,0.2,7,20,20);
    glPopMatrix();
}

// ---------------------------------- Upper half of Candy Carousel -----------------------------------------------------
void drawTopLayer()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[7]);
    glPushMatrix();                                          //    THE BALL AT THE TOP
    glTranslatef(0,26.5,0);
    gluSphere(q, 1.5, 30,30);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.78, 0.63,0.78);
    glPushMatrix();                                             // THE CONE ROOF
    glTranslatef(0,19,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(10, 7,50,50);
    glPopMatrix();

    glPushMatrix();                                             // 6th LAYER DISK
    glTranslatef(0,19,0);
    glRotatef(-90,1,0,0);
    gluDisk(q, 0,10,50,50);
    glPopMatrix();

    glPushMatrix();                                             // 6th LAYER CYLINDER
    glTranslatef(0,19,0);
    glRotatef(-90,1,0,0);
    gluCylinder(q, 10, 10, 1, 50,50);
    glPopMatrix();

    glPushMatrix();                                             // LONG CENTRE CYLINDER
    glRotatef(-90,1,0,0);
    gluCylinder(q, 2,2,19,30,30);
    glPopMatrix();

    // ----------------------------------------------- CANDY BALLS -----------------------------------------------------
    glPushMatrix();                                            // 1st Candy Stick
    glTranslatef(7,19.2,0);
    glRotatef(candyBallMovement,0,0,1);
    glTranslatef(0,-15,0);
    drawCandySticks();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[6]);
    drawCandyBalls();                                         // 1st Candy Ball
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,19.2,0);
    glRotatef(-candyBallMovement,0,0,1);
    glTranslatef(0,-15,0);
    drawCandySticks();                                        // 2nd Candy Stick
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[7]);
    drawCandyBalls();                                         // 2nd Candy Ball
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,19.2,-7);
    glRotatef(candyBallMovement,1,0,0);
    glTranslatef(0,-15,0);
    drawCandySticks();                                        // 3rd Candy Stick
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[8]);
    drawCandyBalls();                                         // 3rd Candy Ball
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,19.2,7);
    glRotatef(-candyBallMovement,1,0,0);
    glTranslatef(0,-15,0);
    drawCandySticks();                                       // 4th Candy Stick
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[9]);
    drawCandyBalls();                                        // 4th Candy Ball
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawCandyCarousel()
{

    glColor3f(0.78, 0.63,0.78);
    glPushMatrix();                                     // 5TH LAYER CYLINDER
    glRotatef(-90,1,0,0);
    gluCylinder(q, 2.3,2.3,5.5,30,30);
    glPopMatrix();

    glPushMatrix();                                     // 4th LAYER DISK
    glTranslatef(0,3,0);
    glRotatef(-90,1,0,0);
    gluCylinder(q, 3, 2.3,1,30,30);
    glPopMatrix();

    glPushMatrix();                                       // 3rd LAYER CYLINDER
    glRotatef(-90,1,0,0);
    gluCylinder(q, 3,3,3,30,30);
    glPopMatrix();

    drawTopLayer();
    glColor3f(0.78, 0.63,0.78);
    glPushMatrix();                                      // 5TH LAYER DISK
    glTranslatef(0,5.5,0);
    glRotatef(-90,1,0,0);
    gluDisk(q, 0, 2.3,30,30);
    glPopMatrix();

    glPushMatrix();                                     // 2ND LAYER DISK
    glTranslatef(0,1.5,0);
    glRotatef(-90,1,0,0);
    gluDisk(q, 0,9.5,80,50);
    glPopMatrix();
    glPushMatrix();                                     // 2ND LAYER CYLINDER
    glTranslatef(0,0.5,0);
    glRotatef(-90,1,0,0);
    gluCylinder(q, 9.5, 9.5, 1, 80,50);
    glPopMatrix();

    glPushMatrix();                                     // MAIN LAYER DISK
    glTranslatef(0,1,0);
    glRotatef(-90,1,0,0);
    gluDisk(q, 0,10,80,50);
    glPopMatrix();
    glPushMatrix();                                     // MAIN LAYER CYLINDER
    glRotatef(-90,1,0,0);
    gluCylinder(q, 10, 10, 1, 80,50);
    glPopMatrix();
}


// ---------------------------------------- Draws the GINGERBREAD HOUSE ------------------------------------------------
void drawGingerHouse()
{
    glColor3f(0.62,0.33,0.16);
    glPushMatrix();                     // CHIMNEY
    glTranslatef(0.8,6,0);
    glRotatef(-90,1,0,0);
    gluCylinder(q, 0.3,0.3,3,30,30);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[10]);
    // -------------------------------------  small house roof ----------------------------------------
    glPushMatrix();
    glBegin(GL_POLYGON);          // Front Side triangle roof
    glTexCoord2f(0,0);      glVertex3f(-1,2,3);
    glTexCoord2f(1,0);      glVertex3f(1,2,3);
    glTexCoord2f(0.5,1);      glVertex3f(0,3,3);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);          // LEFT Side wall
    glTexCoord2f(1,0);      glVertex3f(-1,2,3);
    glTexCoord2f(1,1);      glVertex3f(0,3,3);
    glTexCoord2f(0,1);      glVertex3f(0,3,2);
    glTexCoord2f(0,0);      glVertex3f(-1,2,2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);          // RIGHT Side wall
    glTexCoord2f(0,0);      glVertex3f(1,2,3);
    glTexCoord2f(1,0);      glVertex3f(1,2,2);
    glTexCoord2f(1,1);      glVertex3f(0,3,2);
    glTexCoord2f(0,1);      glVertex3f(0,3,3);
    glEnd();
    glPopMatrix();

    // -------------------------------------  small cube body house  ---------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[11]);
    glPushMatrix();
    glBegin(GL_POLYGON);              // Left Side wall
    glTexCoord2f(0,0);     glVertex3f(-1,0,2);
    glTexCoord2f(1,0);     glVertex3f(-1,0,3);
    glTexCoord2f(1,1);     glVertex3f(-1,2,3);
    glTexCoord2f(0,1);     glVertex3f(-1,2,2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);          // Right Side wall
    glTexCoord2f(0,0);      glVertex3f(1,0,2);
    glTexCoord2f(1,0);      glVertex3f(1,0,3);
    glTexCoord2f(1,1);      glVertex3f(1,2,3);
    glTexCoord2f(0,1);      glVertex3f(1,2,2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);          // Front Side wall
    glTexCoord2f(0,0);      glVertex3f(-1,0,3);
    glTexCoord2f(1,0);      glVertex3f(1,0,3);
    glTexCoord2f(1,1);      glVertex3f(1,2,3);
    glTexCoord2f(0,1);      glVertex3f(-1,2,3);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texId[11]);

    // -------------------------------------  BIG SQUARE BODY HOUSE ----------------------------------------
    glPushMatrix();
    glBegin(GL_POLYGON);                // FRONT side square
    glTexCoord2f(0,0);      glVertex3f(-2,0,2);
    glTexCoord2f(1,0);      glVertex3f(2, 0,2);
    glTexCoord2f(1,1);      glVertex3f(2, 4,2);
    glTexCoord2f(0,1);      glVertex3f(-2, 4,2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);                // BACK side square
    glTexCoord2f(1,0);      glVertex3f(-2,0,-2);
    glTexCoord2f(0,0);      glVertex3f(2, 0,-2);
    glTexCoord2f(0,1);      glVertex3f(2, 4,-2);
    glTexCoord2f(1,1);      glVertex3f(-2, 4,-2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);                // RIGHT side square
    glTexCoord2f(0,1);      glVertex3f(2, 4,2);
    glTexCoord2f(0,0);      glVertex3f(2, 0,2);
    glTexCoord2f(1,0);      glVertex3f(2, 0,-2);
    glTexCoord2f(1,1);      glVertex3f(2, 4,-2);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_POLYGON);                // LEFT side square
    glTexCoord2f(1,1);      glVertex3f(-2, 4,2);
    glTexCoord2f(1,0);      glVertex3f(-2, 0,2);
    glTexCoord2f(0,0);      glVertex3f(-2, 0,-2);
    glTexCoord2f(0,1);      glVertex3f(-2, 4,-2);
    glEnd();
    glPopMatrix();

    // ---------------------------------------------- MAIN ROOF ----------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texId[10]);
    glPushMatrix();
    glBegin(GL_POLYGON);                // FRONT triangle roof
    glTexCoord2f(0,0);     glVertex3f(-2,4,2);
    glTexCoord2f(1,0);     glVertex3f(2,4,2);
    glTexCoord2f(0.5,1);     glVertex3f(0, 8,2);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_POLYGON);                // BACK triangle roof
    glTexCoord2f(1,0);     glVertex3f(-2,4,-2);
    glTexCoord2f(0,0);     glVertex3f(2,4,-2);
    glTexCoord2f(0.5,1);     glVertex3f(0, 8,-2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);                // RIGHT side rectangle roof
    glTexCoord2f(0,0);      glVertex3f(3,2,2);
    glTexCoord2f(0,1);      glVertex3f(3, 2,-2);
    glTexCoord2f(1,1);      glVertex3f(0, 8,-2);
    glTexCoord2f(0,1);      glVertex3f(0, 8,2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);                // LEFT side rectangle roof
    glTexCoord2f(0,0);      glVertex3f(-3,2,2);
    glTexCoord2f(1,0);      glVertex3f(-3, 2,-2);
    glTexCoord2f(1,1);      glVertex3f(0, 8,-2);
    glTexCoord2f(0,1);      glVertex3f(0, 8,2);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void drawObjectStand()
{
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(0,6,0);
    glRotatef(-90,1,0,0);
    gluDisk(q, 0,1,50,50);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-90,1,0,0);
    gluCylinder(q, 1,1,6,50,50);
    glPopMatrix();
}

void drawMuseumCarpet()
{
    glColor3f(1.0,0.0,0.0);
    glTranslatef(0,1,0);
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-100,1,-400);
    glVertex3f(-100,1,480);
    glVertex3f(100,1,480);
    glVertex3f(100,1,-400);
    glEnd();
    glPopMatrix();
}
//---Function to compute the normal vector of a triangle with index tindx ---------
void normal(int tindx)
{
    float x1 = x[t1[tindx]], x2 = x[t2[tindx]], x3 = x[t3[tindx]];
    float y1 = y[t1[tindx]], y2 = y[t2[tindx]], y3 = y[t3[tindx]];
    float z1 = z[t1[tindx]], z2 = z[t2[tindx]], z3 = z[t3[tindx]];
    float nx, ny, nz;
    nx = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
    ny = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
    nz = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void drawCannon()
{
    glColor3f(0.968, 0.937, 0.69);

    glPushMatrix();
        glTranslatef(-20, 30, 0);
        glRotatef(30, 0, 0, 1);
        glTranslatef(20, -30, 0);
        //Construct the object model here using triangles read from OFF file
        glBegin(GL_TRIANGLES);
        for(int tindx = 0; tindx < ntri; tindx++)
        {
            normal(tindx);
            glVertex3d(x[t1[tindx]], y[t1[tindx]], z[t1[tindx]]);
            glVertex3d(x[t2[tindx]], y[t2[tindx]], z[t2[tindx]]);
            glVertex3d(x[t3[tindx]], y[t3[tindx]], z[t3[tindx]]);
        }
        glEnd();
    glPopMatrix();

    //--start here
    glPushMatrix();
    glTranslatef(-10, 5, 17);
    glScalef(80, 10, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 25, 17);
    glScalef(40, 30, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, 5, -17);
    glScalef(80, 10, 6);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, 25, -17);
    glScalef(40, 30, 6);
    glutSolidCube(1);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[7]);
    glPushMatrix();
    glTranslatef(x_ballpos, y_ballpos, 0);
    gluSphere(q,5, 36, 18);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

//-------------------------------------------------------------------
void display(void)
{
    float light0_pos[] = {0.0f,700.0f,-1000.0f,1.0f};
    float light1_pos[] = {light1Pos, 30.0f, 590.0f, 1.0f};
//    float light2_pos[] = {0.0f,1200.0f,2000.0f,1.0f};

    float spotdir[] = {1.08,-1,0};
    float spotdir2[] = {0,-1,-0.1};


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt (eye_x, 300, eye_z, look_x, 300, look_z, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
//    glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotdir2);

    skybox();
    floor();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    // -----------------------------------------------START ------------------------------------------------------------
    glPushMatrix();
    glScalef(2,2,2);
    // -------------------------------------------------- DRAW MUSEUM --------------------------------------------------
        glPushMatrix();
            glTranslatef(0, 0, -400);
            glScalef(60,50,60);
            drawMuseum();
        glPopMatrix();
    // -------------------------------------------------- CANDY GUARD --------------------------------------------------
        glPushMatrix();
            glTranslatef(moveGuard, 0, 0);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
            glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);   //light position
            glTranslatef(-200, 0, 590);
            glRotatef(directionGuard,0, 1, 0);
            glScalef(20,40,20);
            glRotatef(90,0,1,0);
            drawGuard();
        glPopMatrix();
    // ------------------------------------------------- THE CANDY SWING -----------------------------------------------
        glPushMatrix();
            glTranslatef(-400,elevateUp,-600);
            glScalef(25,25,25);
            glColor3f(0.53,0.81,0.94);
            glPushMatrix();
            glutSolidCube(2);  // SWING CUBE BASE
            glPopMatrix();
            glRotatef(spinObject, 0,1,0);
            glPushMatrix();
                glRotatef(180, 0,1,0);
                drawCandySwing("normal");
            glPopMatrix();
            glPushMatrix();
                drawCandySwing("thinner");
            glPopMatrix();
        glPopMatrix();
    // ---------------------------------------- THE CANDY BALLS CAROUSEL -----------------------------------------------
        glPushMatrix ();
            glTranslatef(400,elevateUp-20,-600);
            glRotatef(spinObject, 0,1,0);
            glScalef(10,14,10);
            drawCandyCarousel();
        glPopMatrix();
    // ---------------------------------------- THE GINGERBREAD HOUSE -------------------------------------------------
        glPushMatrix();
            glTranslatef(0,elevateUp-220,0);
            glTranslatef(0,oscillate,-700);
            glRotatef(spinObject*2, 0, 1, 0);
            glScalef(25,25,25);
            glRotatef(-45,0,1,0);
            drawGingerHouse();
        glPopMatrix();

    // ---------------------------------------- The OBJECT STANDS ------------------------------------------------------
        glPushMatrix();
            glTranslatef(0,elevateUp-200,-700);
            glScalef(80,30,80);
            drawObjectStand();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(400,elevateUp-200,-600);
            glScalef(80,30,80);
            drawObjectStand();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-400,elevateUp-200,-600);
            glScalef(80,30,80);
            drawObjectStand();
        glPopMatrix();

    // ------------------------------------------------ SHADOW OBJECT --------------------------------------------------
        //     Draw the shadow
        glPushMatrix();
            glTranslatef(0,0.1,0);
            float shadowMat[16] = {
                    700,0,0,0,
                    0,0,1000,-1,
                    0,0,700,0,
                    0,0,0,700
            };

            glDisable(GL_LIGHTING);
            glPushMatrix();
                glMultMatrixf(shadowMat);
                glColor4f(0.2,0.2,0.2,1.0);
                glTranslatef(-330, 150, -280);
                glRotatef(spinobjectshadow, 1, 0, 0);
                glRotatef(spinobjectshadow*2, 0, 1, 0);
                glColor3f(0.2, 0.2, 0.2);
                glScalef(40,40,40);
                glutSolidIcosahedron();
            glPopMatrix();
        glPopMatrix();

        //  Draw Object
        glEnable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(-330, 150, -280);
            glRotatef(spinobjectshadow, 1, 0, 0);
            glRotatef(spinobjectshadow*2, 0, 1, 0);
            glColor3f(0.80, 0.945, 0.686);
            glScalef(40,40,40);
            glutSolidIcosahedron();
        glPopMatrix();

    // ------------------------------------------------ MUSEUM CARPET --------------------------------------------------
        drawMuseumCarpet();
    // ------------------------------------------------ CANDY CANNON ---------------------------------------------------
        glPushMatrix();
            glTranslatef(400,0,-200);
            glScalef(1,1,1);
            glRotatef(180,0,1,0);
            drawCannon();
        glPopMatrix();

    // ------------------------------------------------ DONUT DOOR -----------------------------------------------------
        glPushMatrix();
//            glColor3f(0.505, 0.854, 0.988);
            glColor3f(0.623,0.803,0.870);
            glTranslatef(0,190,273);
            glScalef(5,5,5.8);
            glutSolidTorus(20.5,64,50,30);
        glPopMatrix();

    glPopMatrix();
    // ----------------------------------------------- END -------------------------------------------------------------

    glutSwapBuffers();
}


//---------------------------------------------------------------------
void initialize(void)
{
    loadTextures();
    loadMeshFile("Cannon.off");				//Specify mesh file name here

    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    // For the Ice Cream
    q = gluNewQuadric();
    gluQuadricTexture (q, GL_TRUE);
    gluQuadricDrawStyle(q, GLU_FILL);
    gluQuadricNormals(q, GLU_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Museum Spotlight
    glEnable(GL_LIGHT1); // Guard's flash light
    glEnable(GL_LIGHT2); // Guard's flash light


    // Let the colour still be enabled even tho the shadows and shading are enabled
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.01);

    glLightfv(GL_LIGHT2, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT2, GL_SPECULAR, white);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1);




//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0, 1.0, 100.0, 8000.0);   //Perspective projection
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) {
        angle -= 7 * (M_PI/180.0);
    }
    else if(key == GLUT_KEY_RIGHT) {
        angle += 7 * (M_PI/180.0);
    }
    else if(key == GLUT_KEY_DOWN){
        if (eye_x > 2300) eye_x = 2300;
        if (eye_x < -2300) eye_x = -2300;
        if (eye_z > 2300) eye_z = 2300;
        if (eye_z < -2300) eye_z = -2300;

        if (eye_z <= 2300 and eye_z >= -2300 and eye_x >= -2300 and eye_x <= 2300)
            eye_z += 40*cos(angle);
            eye_x -= 40*sin(angle);
    }
    else if(key == GLUT_KEY_UP){
        if (eye_x > 2300) eye_x = 2300;
        if (eye_x < -2300) eye_x = -2300;
        if (eye_z > 2300) eye_z = 2300;
        if (eye_z < -2300) eye_z = -2300;

        if (eye_x >= -2300 and eye_x <= 2300) {
            eye_x += 30 * sin(angle);
        }
        if (eye_z <= 2300 and eye_z >= -2300) {
            eye_z -= 30 * cos(angle);

        }
    }
    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);

    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{
    switch(key) {
        case 'f': fire = true;
            break;
    }
    glutPostRedisplay();
}

void myTimer(int value)
{
    if (fire == true) {
        x_ballpos += 8.66;
        y_ballpos += 5 - v;
        v += 0.098;

        if (elevateUp <= 200) {
            elevateUp++;
        } else {
            openMuseum = true;
        }


        if (openMuseum) {
            spinObject += 1;
            if (swingDirection == 1) {
                swingTheta -= 1;
                if (swingTheta < -25) {
                    swingDirection = 0;
                }
            } else {
                swingTheta += 1;
                if (swingTheta > 25) {
                    swingDirection = 1;
                }
            }


            if (candyBallDirection == 1) {
                candyBallMovement -= 1;
                if (candyBallMovement < 0) {
                    candyBallDirection = 0;
                }
            } else {
                candyBallMovement += 1;
                if (candyBallMovement > 50) {
                    candyBallDirection = 1;
                }
            }

            oscillate += oscillateIncrement;
            if (oscillate > 260) {
                oscillateIncrement = -1;
            }
            if (oscillate < 220) {
                oscillateIncrement = 1;
            }
        }
    }


    jumpIceCream += jumpIncrement;
    if (jumpIceCream > 7) {
        jumpIncrement = -0.2;
    }
    if (jumpIceCream < 0) {
        jumpIncrement = 0.2;
    }

    // Dessert Guard movement
    if (armSwings == 1) {
        theta-=3;
        if (theta < -30) {
            armSwings = 0;
        }
    } else {
        theta+=3;
        if (theta > 30) {
            armSwings = 1;
        }
    }

    moveGuard += moveIncrement;
    if (moveGuard == 740) {
        directionGuard = 180;
        moveIncrement = -5;
        light1Pos -= 800;
    }
    if (moveGuard == -350) {
        directionGuard = 0;
        moveIncrement = 5;
        light1Pos += 800;
    }

    spinIceCream+=1;
    spinobjectshadow+=0.5;

    glutPostRedisplay();
    glutTimerFunc(20, myTimer, 0);
}


//---------------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize (1024, 1024);
    glutInitWindowPosition (50, 50);
    glutCreateWindow ("Rchi\'s Museum");
    initialize();
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    // 500ms delay before we call the myTimer func
    glutTimerFunc(20, myTimer, 0);
    glutMainLoop();
    return 0;
}
