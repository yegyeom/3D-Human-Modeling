#include <GLUT.h>
#include <glut.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cctype>

GLUquadricObj* qobj;

#define SLICES  100
#define STACKS  100
#define PI      3.141592
#define WINDOW_WIDTH    700
#define WINDOW_HEIGHT   500
#define CAMERA_NEAR     1
#define CAMERA_FAR      1000

using namespace std;

typedef struct {
    float x, y, z;
} Coordinate;

float fieldOfVision, aspect;
float cameraX, cameraY, cameraZ;
float lightX, lightY, lightZ;
float cameraRadius = 750.0f;
float theta = 0.0f;
float alpha = 0.0f;

float rightShoulderJointXAxis = 0.0;
float rightShoulderJointZAxis = 0.0;

float* xRotation, * zRotation, * yRotation;

int previousX;
int previousY;

bool firstClick = true;

void drawCloud() {
    glColor3f(1.0, 1.0, 1.0);

    //왼쪽 구름
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-320.0, 130.0, 0.0);
        glutSolidSphere(55.0, SLICES, STACKS);
    glPopMatrix();
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-250.0, 130.0, 0.0);
        glutSolidSphere(65.0, SLICES, STACKS);
    glPopMatrix();
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-180.0, 130.0, 0.0);
        glutSolidSphere(55.0, SLICES, STACKS);
    glPopMatrix();

    //오른쪽 구름
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(320.0, 80.0, 0.0);
        glutSolidSphere(50.0, SLICES, STACKS);
    glPopMatrix();
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(250.0, 80.0, 0.0);
        glutSolidSphere(60.0, SLICES, STACKS);
    glPopMatrix();
        glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(180.0, 80.0, 0.0);
        glutSolidSphere(50.0, SLICES, STACKS);
    glPopMatrix();
}

void drawHead(float headRadius) {
    float noseRadius = 4.0;
    
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glTranslatef(0.0, -30.0, 0.0);
        glScalef(1.9, 1.2, 1.0);
        glutSolidSphere(headRadius, SLICES, STACKS);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(-headRadius * 0.12, 18.0, headRadius - noseRadius - 8.0);
        glutSolidSphere(noseRadius, SLICES, STACKS);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(headRadius * 0.12, 18.0, headRadius - noseRadius - 8.0);
        glutSolidSphere(noseRadius, SLICES, STACKS);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.8, 0.3, 0.23);
        glScalef(0.8, 1.0, 0.5);
        glTranslatef(0.0, -20.0, 95.0);
        glutSolidSphere(30, SLICES, STACKS);
    glPopMatrix();
}

void drawEars() {
    float earRadius = 25.0;

    //left
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glScalef(1.2, 1.9, 1.0);
        glTranslatef(earRadius * 1.8, 10.0, earRadius);
        glutSolidSphere(earRadius, SLICES, STACKS);

        glColor3f(1.0, 1.0, 1.0);
        glScalef(1.9, 2.2, 1.0);
        glTranslatef(earRadius * -1.9, 0.0, earRadius - 5.0);
        glutSolidSphere(7.0, SLICES, STACKS);

        glColor3f(0.0, 0.0, 0.0);
        glScalef(1.9, 1.9, 1.0);
        glTranslatef(-1.0, 0.0, earRadius - 18.0);
        glutSolidSphere(2.8, SLICES, STACKS);
    glPopMatrix();

    //right
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glScalef(1.2, 1.9, 1.0);
        glTranslatef(earRadius * -1.8, 10.0, earRadius);
        glutSolidSphere(earRadius, SLICES, STACKS);

        glColor3f(1.0, 1.0, 1.0);
        glScalef(1.9, 2.2, 1.0);
        glTranslatef(earRadius * 1.9, 0.0, earRadius - 2.0);
        glutSolidSphere(7.0, SLICES, STACKS);

        glColor3f(0.0, 0.0, 0.0);
        glScalef(1.9, 1.9, 1.0);
        glTranslatef(-1.0, 0.0, earRadius - 18.0);
        glutSolidSphere(2.8, SLICES, STACKS);
    glPopMatrix();
}

void drawBody() {
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_SMOOTH);
    
    //몸통
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0, 0.6, 1.0);
        glTranslatef(0.0, 0.0, 70.0);
        gluCylinder(qobj, 70, 70, 80, SLICES, STACKS); 
    glPopMatrix();

    //엉덩이
    glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0, 0.6, 0.6);
        glTranslatef(0.0, 0.0, 240.0);
        glutSolidSphere(70, SLICES, STACKS);
    glPopMatrix();
}

void drawArms() {
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_SMOOTH);

    //left
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(40, 0.0, -1.0, 0.0);
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(10.0, 0.0, 80.0);
        gluCylinder(qobj, 20, 20, 100, SLICES, STACKS);
    glPopMatrix();

    //right
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(-40, 0.0, -1.0, 0.0);
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-10.0, 0.0, 80.0);
        gluCylinder(qobj, 20, 20, 100, SLICES, STACKS);
    glPopMatrix();
}

void drawHands() {
    glColor3f(0.008, 0.6, 0.19);

    //Left
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-105.0, -140.0, 0.0);
        glutSolidSphere(22.0, SLICES, STACKS);
    glPopMatrix();

    //Right
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(105.0, -140.0, 0.0);
        glutSolidSphere(22.0, SLICES, STACKS);
    glPopMatrix();
}

void drawLegs() {
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_SMOOTH);

    //Left
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-41.0, 0.0, 140.0);
        gluCylinder(qobj, 28, 28, 80, SLICES, STACKS);
    glPopMatrix();

    //Right
    glPushMatrix();
        glColor3f(0.008, 0.6, 0.19);
        glRotatef(90, 1.0, 0.0, 0.0);
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(41.0, 0.0, 140.0);
        gluCylinder(qobj, 28, 28, 80, SLICES, STACKS);
    glPopMatrix();
}

void drawFoots() {
    glColor3f(0.008, 0.6, 0.19);

    //Left
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(-42.0, -230.0, 0.0);
        glutSolidSphere(30.0, SLICES, STACKS);
    glPopMatrix();

    //Right
    glPushMatrix();
        glScalef(1.0, 1.0, 1.0);
        glTranslatef(42.0, -230.0, 0.0);
        glutSolidSphere(30.0, SLICES, STACKS);
    glPopMatrix();
}

void updateLightPosition() {
    float proportion = 1.0;

    lightX = cameraX * proportion;
    lightY = cameraY * proportion;
    lightZ = cameraZ * proportion;

    GLfloat lightPosition[4] = { lightX, lightY, lightZ, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void updateCameraPosition() {

    float upX, upY, upZ;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfVision, aspect, CAMERA_NEAR, CAMERA_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraX = sin(alpha) * cos(theta) * cameraRadius;
    cameraY = sin(theta) * cameraRadius;
    cameraZ = cos(alpha) * cos(theta) * cameraRadius;

    upX = 0.0;
    upY = 1.0;
    upZ = 0.0;

    if (theta >= PI / 2.0 && theta < 3.0 * PI / 2.0)
        upY = -1.0;
    else
        upY = 1.0;

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, upX, upY, upZ);

    updateLightPosition();
}

void draw() {
    float headRadius = 55.0;
    float thoraxWidth = 70.0;
    float thoraxHeight = 70.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateCameraPosition();
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, thoraxWidth, 0.0);
    glColor3f(0.008, 0.6, 0.19);
    glPushMatrix();
        
    //구름
    drawCloud();
    //머리
    drawHead(headRadius);
    //귀
    drawEars();
    //몸
    drawBody();
    //팔
    drawArms();
    //손
    drawHands();
    //다리
    drawLegs();
    //발
    drawFoots();

    glPopMatrix();
    glutSwapBuffers();
}

void initializeLighting() {

    GLfloat lightAmbient[4] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat lightDiffuse[4] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat lightSpecular[4] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat lightpos[] = { -600.0, 600.0, 0.0, 1.0 };

    glClearColor(0.74, 0.91, 1.0, 1.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    fieldOfVision = 45.0;

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

void resizeWindow(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    aspect = (GLfloat)w / (GLfloat)h;
    updateCameraPosition();
}

void keyPressed(unsigned char key, int x, int y) {
    key = tolower(key);
    if (xRotation != NULL && yRotation != NULL && zRotation != NULL) {
        switch (key) {
        case 'a':
            cameraRadius -= 10.0f;
            break;
        case 'z':
            cameraRadius += 10.0f;
            break;
        }
        glutPostRedisplay();
    }
}

void mousePressed(int x, int y) {

    if (firstClick) {

        previousX = x;
        previousY = y;

        firstClick = false;

    }
    else {

        if (x > previousX)
            alpha -= 0.1;
        else if (x < previousX)
            alpha += 0.1;

        if (y > previousY)
            theta += 0.1;
        else if (y < previousY)
            theta -= 0.1;

        if (theta > 2 * PI)
            theta = theta - 2 * PI;
        else if (theta < 0.0)
            theta = 2 * PI - theta;

        if (alpha > 2 * PI)
            alpha = alpha - 2 * PI;
        else if (alpha < 0.0)
            alpha = 2 * PI - alpha;

        firstClick = true;

        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    xRotation = &rightShoulderJointXAxis;
    yRotation = &rightShoulderJointZAxis;
    zRotation = &rightShoulderJointZAxis;

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(x, y);
    glutCreateWindow("Leonard");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mousePressed);
    glutReshapeFunc(resizeWindow);
    initializeLighting();

    glutMainLoop();
    return EXIT_SUCCESS;
}