#include <GL/glut.h>
#include <math.h>

float PI = 3.14;
int frameNumber = 0;

void drawDisk(double radius, int n)
{
    double angle = 0;
    glBegin(GL_POLYGON);
    for (int c = 0; c <= n; c++)
    {
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        glVertex2d(x, y);
        angle = angle + ((2 * PI) / n);
    }
    glEnd();
}

void drawBearing()
{
    // Outer black part
    glColor3f(0.0, 0.0, 0.0);
    drawDisk(1, 32);

    glColor3f(0.68, 0.85, 0.90);
    drawDisk(0.9, 32);

    // Inner black part
    glColor3f(0.0, 0.0, 0.0);
    drawDisk(0.2, 32);
}

void drawHandles()
{

    // A
    glColor3f(0.68, 0.85, 0.90);
    glBegin(GL_POLYGON);
    glVertex2f(-4.0, -6.0); // BL
    glVertex2f(-2.0, -6.0); // BR
    glVertex2f(-2.0, 0.0);  // TR
    glVertex2f(-4.0, 0.0);  // TL
    glEnd();

    // B
    glColor3f(0.68, 0.85, 0.90);
    glBegin(GL_POLYGON);
    glVertex2f(-4.0, 0.0);
    glVertex2f(-2.0, 0.0);
    glVertex2f(-3.0, 8.0);
    glVertex2f(-3.0, 8.0);
    glEnd();
}

void drawArm()
{

    // Draw arm handles
    drawHandles();

    // Bottom Bearing
    glPushMatrix();
    glTranslatef(-3.0, -6.0, 0.0);
    drawBearing();
    glPopMatrix();

    // Top Bearing
    glPushMatrix();
    glTranslatef(-3.0, 0.0, 0.0);
    drawBearing();
    glPopMatrix();
}

void reshape(GLsizei w, GLsizei h)
{

    glViewport(0, 0, w, h);
    if (h == 0)
        h = 1;
    GLfloat aspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w >= h)
        gluOrtho2D(-10 * aspect, 10 * aspect, -10, 10);
    else
        gluOrtho2D(-10, 10, -10 / aspect, 10 / aspect);
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawArm();

    glFlush();
}

void init()
{

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(720, 480);
    glutCreateWindow("Robot Arm");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}