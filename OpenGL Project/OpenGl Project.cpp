#include <GL/glut.h>
#include <cmath>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float angleX = 0, zoom = 10.0f;
float personY = 0.0f, personJump = 0.0f;
bool jumping = false;
float sunY = 4.0f;
float personX = 0.0f;  // Person's X position
float personZ = 1.5f;  // Person's Z position

void updateSunLight() {
    GLfloat ambient[] = { sunY > 4.0f ? 0.7f : 0.2f, sunY > 4.0f ? 0.6f : 0.2f, sunY > 4.0f ? 0.8f : 0.3f, 1.0f };
    GLfloat diffuse[] = { 1.0f, 0.6f, 0.3f, 1.0f };
    GLfloat position[] = { -2.0f, sunY, -2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glClearColor(sunY > 4.0f ? 0.7f : 0.1f, sunY > 4.0f ? 0.9f : 0.1f, sunY > 4.0f ? 1.0f : 0.2f, 1.0f);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    updateSunLight();
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void drawSun() {
    glPushMatrix();
    glColor3f(1.0f, 0.6f, 0.0f);
    glTranslatef(0.0f, sunY, -6.0f);
    glutSolidSphere(0.6, 20, 20);
    glPopMatrix();
}

void drawMountain(float x, float z, float scale, float height, bool withSnow, bool isFront) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glScalef(scale, height, scale);
    glColor3f(isFront ? 0.6f : 0.1f, isFront ? 0.6f : 0.1f, isFront ? 0.6f : 0.1f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i <= 6; ++i) {
        float angle = i * 2.0f * M_PI / 6;
        glVertex3f(cos(angle), 0.0f, sin(angle));
    }
    glEnd();
    if (withSnow) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glutSolidCone(0.3, 0.5, 8, 8);
    }
    glPopMatrix();
}

void drawLand() {
    glPushMatrix();
    glColor3f(0.4f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, -6); glVertex3f(10, 0, -6);
    glVertex3f(10, 0, 10); glVertex3f(-10, 0, 10);
    glEnd();
    glPopMatrix();
}

void drawPineTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glColor3f(0.4f, 0.2f, 0.1f);
    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.1, 1.0, 10, 10);
    glPopMatrix();
    gluDeleteQuadric(quad);
    glColor3f(0.0f, 0.4f, 0.1f);
    for (float i = 0; i < 3; ++i) {
        glPushMatrix();
        glTranslatef(0, 1.0 + i * 0.3, 0);
        glutSolidCone(0.4 - 0.1 * i, 0.4, 8, 8);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawYogaMat() {
    glPushMatrix();
    glTranslatef(personX, 0.01f, personZ);  // Position beneath person
    glColor3f(0.5f, 0.1f, 0.6f);  // Purple color
    glScalef(0.8f, 0.02f, 0.4f);  // Mat dimensions
    glutSolidCube(1);
    glPopMatrix();
}

void drawPerson() {
    glPushMatrix();
    glTranslatef(personX, personY, personZ);
    glColor3f(1.0f, 0.8f, 0.6f);
    glPushMatrix(); glTranslatef(0, 0.7, 0); glutSolidSphere(0.1, 10, 10); glPopMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix(); glTranslatef(0, 0.5, 0); glScalef(0.15, 0.3, 0.1); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.1, 0.5, 0); glScalef(0.05, 0.2, 0.05); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(0.1, 0.5, 0); glScalef(0.05, 0.2, 0.05); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.05, 0.3, 0); glScalef(0.05, 0.15, 0.05); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(0.05, 0.3, 0); glScalef(0.05, 0.15, 0.05); glutSolidCube(1); glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); glTranslatef(-0.05, 0.15, 0); glScalef(0.05, 0.05, 0.05); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(0.05, 0.15, 0); glScalef(0.05, 0.05, 0.05); glutSolidCube(1); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.05, 0.05, 0); glScalef(0.06, 0.05, 0.1); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(0.05, 0.05, 0); glScalef(0.06, 0.05, 0.1); glutSolidCube(1); glPopMatrix();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(zoom * sin(angleX), 4.0, zoom * cos(angleX), 0, 1, 0, 0, 1, 0);

    drawSun();
    drawMountain(-3, -5, 2, 1.5, false, true);
    drawMountain(3, -5, 2, 1.5, false, true);
    drawMountain(-2, -6, 2.5, 2.0, true, false);
    drawMountain(2, -6, 2.5, 2.0, true, false);
    drawLand();
    drawPineTree(-3.5, 2.0);
    drawPineTree(3.5, 2.0);

    drawYogaMat();  // Draw mat first so person appears on top
    drawPerson();

    glutSwapBuffers();
}

void animate(int value) {
    if (jumping) {
        personJump += 0.1f;
        personY = 0.4f * sin(personJump);
        if (personJump > M_PI) {
            jumping = false;
            personJump = 0;
            personY = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, animate, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: angleX -= 0.1f; break;
    case GLUT_KEY_RIGHT: angleX += 0.1f; break;
    case GLUT_KEY_UP: zoom -= 0.5f; if (zoom < 2) zoom = 2; break;
    case GLUT_KEY_DOWN: zoom += 0.5f; break;
    }
    glutPostRedisplay();
}

void normalKey(unsigned char key, int x, int y) {
    if (key == ' ') {
        if (!jumping) jumping = true;
    }
    else if (key == 'w') {
        sunY += 0.2f; if (sunY > 6.0f) sunY = 6.0f;
        updateSunLight();
    }
    else if (key == 's') {
        sunY -= 0.2f; if (sunY < 1.0f) sunY = 1.0f;
        updateSunLight();
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Yoga Scene with Person on Mat");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normalKey);
    glutTimerFunc(0, animate, 0);
    glutMainLoop();
    return 0;
}
