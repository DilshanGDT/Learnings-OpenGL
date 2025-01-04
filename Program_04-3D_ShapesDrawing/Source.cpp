#include <GL/glut.h>  
#include <math.h>

// For animating the rotation of the objects
float teapotRotation = 0.0;

// variables to move outermost Object Frame (to move all the rendered environment)
float moveX = 0.0f;
float moveY = 0.0f;
float moveZ = 0.0f;

GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

//variables to move the camera
float camX = 0.0f;
float camY = 0.0f;
float camZ = 0.0f;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawRectangle() {
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
}

void drawPyramid() {
    glTranslatef(0.0f, 0.0f, 0.0f);  // Move if needed

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid (4 triangular faces)

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);    // Top point
    glVertex3f(-1.0f, 0.0f, 1.0f);   // Bottom left
    glVertex3f(1.0f, 0.0f, 1.0f);    // Bottom right

    // Right face
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(0.0f, 1.0f, 0.0f);    // Top point
    glVertex3f(1.0f, 0.0f, 1.0f);    // Bottom front
    glVertex3f(1.0f, 0.0f, -1.0f);   // Bottom back

    // Back face
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(0.0f, 1.0f, 0.0f);    // Top point
    glVertex3f(1.0f, 0.0f, -1.0f);   // Bottom right
    glVertex3f(-1.0f, 0.0f, -1.0f);  // Bottom left

    // Left face
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(0.0f, 1.0f, 0.0f);    // Top point
    glVertex3f(-1.0f, 0.0f, -1.0f);  // Bottom back
    glVertex3f(-1.0f, 0.0f, 1.0f);   // Bottom front

    glEnd();

    glBegin(GL_QUADS);               // Drawing the base (a square)
    glColor3f(1.0f, 0.0f, 1.0f);     // Pink
    glVertex3f(-1.0f, 0.0f, 1.0f);   // Front left
    glVertex3f(1.0f, 0.0f, 1.0f);    // Front right
    glVertex3f(1.0f, 0.0f, -1.0f);   // Back right
    glVertex3f(-1.0f, 0.0f, -1.0f);  // Back left
    glEnd();
}


void drawCube() {
    glTranslatef(0.0f, 0.0f, 0.0f);  // Move right and into the screen

    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face (y = 1.0f)
    // Define vertices in counter-clockwise (CCW) order with normal pointing out

// back
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // top
    glColor3f(1.0f, 0.0f, 0.0f);     // red
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // front
    glColor3f(0.0f, 0.0f, 1.0f);     // blue
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // bottom
    glColor3f(1.0f, 0.0f, 1.0f);       // pink
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    // right
    glColor3f(0.0f, 1.0f, 1.0f);     // yellow
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    // pyramid
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glVertex3f(1.0f, 0.0f, 3.0f);
    glVertex3f(0.0f, 0.0f, 2.0f);
    glVertex3f(1.0f, 0.0f, 3.0f);

    glEnd();  // End of drawing color-cube
}

void drawPyramid() {
    // pyramid
    glTranslatef(2.0f, 2.0f, 2.0f);  // Move right and into the screen

    glBegin(GL_QUADS);

    // bottom
    glColor3f(1.0f, 0.0f, 1.0f);        // pink
    glVertex3f(2.0f, 0.0f, 0.0f);
    glVertex3f(3.0f, 0.0f, 0.0f);
    glVertex3f(2.0f, 0.0f, 1.0f);
    glVertex3f(3.0f, 0.0f, 1.0f);
}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(1.5);

    glColor3f(1.0, 0.0, 0.0);   // y      // x, y, z coordination lines
    glVertex3f(-20, 0, 0);
    glVertex3f(20, 0, 0);

    glColor3f(0.0, 1.0, 0.0);   // x
    glVertex3f(0, -20, 0);
    glVertex3f(0, 20, 0);

    glColor3f(0.0, 0.0, 1.0);   // z
    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, 20);

    glEnd();
}
void DrawGrid() {
    GLfloat ext = 20.0f;
    GLfloat step = 1.0f;
    GLfloat yGrid = -0.4f;
    GLint line;

    glBegin(GL_LINES);
    for (line = -ext; line <= ext; line += step) {
        glVertex3f(line, yGrid, ext);
        glVertex3f(line, yGrid, -ext);

        glVertex3f(ext, yGrid, line);
        glVertex3f(-ext, yGrid, line);
    }
    glEnd();
}

void drawObject() {
    glColor3f(0.0, 1.0, 0.0);
    //glutWireTeapot(2.0);
    //glutWireTorus(0.5, 1.0, 10, 20);

    //glutWireCone(0.5, 2, 20, 20);

    //glutWireIcosahedron();
}


void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // 

    //Setting the modelview matrix to the identity matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    gluLookAt(0.0 + camX, 2.0 + camY, 5.0 + camZ, 0, 0, 0, 0, 1.0, 0);      // set up the viweing camera position
    glColor3f(1.0, 1.0, 1.0);
    //glTranslatef(0.0, 0.0, -5.0);

    glTranslatef(moveX, moveY, moveZ);      // object translation
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);      // object rotation
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    DrawGrid();

    drawAxes();

    glPushMatrix();
    //glRotatef(teapotRotation, 0.0, 1.0, 0.0);
    //drawObject();

    drawCube();
    drawPyramid();

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        camY += 0.5;
    if (key == GLUT_KEY_DOWN)
        camY -= 0.5;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    if (key == 'z')
        moveZ += 1;

    if (key == 'Z')
        moveZ -= 1;

    if (key == 'l')
        rotY -= 5.0;

    if (key == 'r')
        rotY += 1.0;

    glutPostRedisplay();

}

//Rotating teapot
void Timer(int x) {
    teapotRotation += teapotRotation >= 360.0 ? -teapotRotation : 2;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
}

void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum 
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Rotating Teapot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, Timer, 1);
    init();
    glutMainLoop();


    return 0;
}
