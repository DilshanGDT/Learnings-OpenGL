#include <gl\glut.h>

//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

//Vertices of the objects
float vertices[][3] = {
	{1,1,-1},{-1,1,-1},{-1,1,1},{1,1,1},		//Cube coordinates
	{1,-1,-1},{1,-1,1},{-1,-1,1},{-1,-1,-1},
	{0,1,0},									//Pyramid apex
	{1,0,-1},{0,1,-1},{-1,0,-1},{0,-1,-1},		//3D octagon coordinates
	{-1,1,0},{-1,0,1},{-1,-1,0},
	{0,-1,1},{1,0,1},{0,1,1},
	{1,1,0},{1,-1,0}
};


void drawGrid() {
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

void drawAxes() {

	glBegin(GL_LINES);

	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);

	glEnd();
}

//Draw a quandrangle surface
void surface4(int v1, int v2, int v3, int v4) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glVertex3fv(vertices[v4]);
	glEnd();
}

//Draw a triangle surface
void surface3(int v1, int v2, int v3) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glEnd();
}

//Draw a wireframe around the quandrangle surface
void frame4(int v1, int v2, int v3, int v4) {
	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glVertex3fv(vertices[v4]);
	glEnd();
}

//Draw a wireframe around the triangle surface
void frame3(int v1, int v2, int v3) {
	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glEnd();
}

//3D Cube
void cube() {
	//Top-Green
	glColor3f(0.0f, 1.0f, 0.0f);
	surface4(0, 1, 2, 3);
	// Bottom-Orange
	glColor3f(1.0f, 0.5f, 0.0f);
	surface4(4, 7, 6, 5);
	// Front-Red
	glColor3f(1.0f, 0.0f, 0.0f);
	surface4(3, 2, 6, 5);
	// Back-Yellow
	glColor3f(1.0f, 1.0f, 0.0f);
	surface4(0, 1, 7, 4);
	// Left-Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	surface4(1, 2, 6, 7);
	// Right-Magenta
	glColor3f(1.0f, 0.0f, 1.0f);
	surface4(0, 3, 5, 4);
}

//Draw a pyramid
void pyramid1() {
	//Base (square)
	glColor3f(0.0, 0.0, 0.0);
	surface4(4, 7, 6, 5);
	//4 sides (triangles)
	glColor3f(0.9569, 0.6431, 0.3765); // front
	surface3(8, 6, 5);
	glColor3f(0.8235, 0.7059, 0.5490); // left
	surface3(8, 6, 7);
	glColor3f(0.8039, 0.5216, 0.2471);
	surface3(8, 7, 4);
	glColor3f(0.6275, 0.3216, 0.1765);// right
	surface3(8, 5, 4);
}

//3D Octagon - each surface contains a wireframe
void octagon3D() {
	//Square surfaces
	glColor3f(1.0, 1.0, 0.0);
	surface4(9, 10, 11, 12); //surface
	frame4(9, 10, 11, 12);//wireframe
	glColor3f(0.0, 1.0, 0.0);
	surface4(11, 13, 14, 15);
	frame4(11, 13, 14, 15);
	glColor3f(1.0f, 0.0f, 1.0f);
	surface4(14, 16, 17, 18);
	frame4(14, 16, 17, 18);
	glColor3f(0.0f, 0.0f, 1.0f);
	surface4(9, 19, 17, 20);
	frame4(9, 19, 17, 20);

	//Top triangular surfaces
	glColor3f(1.0, 1.0, 1.0);
	surface3(9, 10, 19);
	frame3(9, 10, 19);
	glColor3f(1.0, 1.0, 1.0);
	surface3(10, 13, 11);
	frame3(10, 13, 11);
	glColor3f(1.0, 1.0, 1.0);
	surface3(13, 14, 18);
	frame3(13, 14, 18);
	glColor3f(1.0, 1.0, 1.0);
	surface3(18, 17, 19);
	frame3(18, 17, 19);

	//Bottom triangular surfaces
	glColor3f(1.0, 1.0, 1.0);
	surface3(14, 16, 15);
	frame3(14, 16, 15);
	glColor3f(1.0, 1.0, 1.0);
	surface3(17, 16, 20);
	frame3(17, 16, 20);
	glColor3f(1.0, 1.0, 1.0);
	surface3(9, 12, 20);
	frame3(9, 12, 20);
	glColor3f(1.0, 1.0, 1.0);
	surface3(11, 15, 12);
	frame3(11, 15, 12);
}


void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(2.0);
	glEnable(GL_DEPTH_TEST);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 2.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	//Draw a grid on the xz plane
	glColor3f(1, 1, 1);
	drawGrid();
	//draw the three axes
	drawAxes();

	/*glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(objRX, 1.0, 0.0, 0.0);
	glRotatef(objRY, 0.0, 1.0, 0.0);
	glScalef(1.5, 1.5, 1.5);
	octagon3D();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 0.0, -1.0);
	glScalef(1.5, 1.5, 1.5);
	cube();
	glPopMatrix();*/

	//3 big ones
	glPushMatrix();
	glTranslatef(7.0, 0.0, -3.0);
	glScalef(2, 2, 2);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 0.0, 2.5);
	glScalef(1.5, 1.5, 1.5);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, 6.0);
	glScalef(0.8, 0.8, 0.8);
	pyramid1();
	glPopMatrix();

	//3 with small one
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 7.5);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0, 0.0, 7.5);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 7.5);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();

	//3 with big one
	glPushMatrix();
	glTranslatef(9.5, 0.0, -3.0);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.5, 0.0, -2.0);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.5, 0.0, -1.0);
	glScalef(0.25, 0.25, 0.25);
	pyramid1();
	glPopMatrix();


	glPopMatrix();		//gl pop matrix of the camera : camera angle specified in modeling 
	glutSwapBuffers();
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

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 1;

	if (key == GLUT_KEY_DOWN)
		camY -= 1;

	if (key == GLUT_KEY_RIGHT)
		sceTX += 1;

	if (key == GLUT_KEY_LEFT)
		sceTX -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'l')
		objRY += 5;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 1;

	if (key == 'z')
		sceTZ -= 1;

	if (key == 'w')
		sceTX += 1;

	if (key == 's')
		sceTX -= 1;

	if (key == 'y')
		sceRY += 1;

	if (key == 'Y')
		sceRY -= 1;

	glutPostRedisplay();
}


void main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Complex 3D Shapes");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
}