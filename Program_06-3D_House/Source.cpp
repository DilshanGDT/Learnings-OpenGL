#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

static float dRot;

//Grid and coordinate axes for better visualization
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

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

void wall(double thickness)
{
	glPushMatrix();
	glTranslated(-0.5 - 0.5 * thickness, 0.5, 0.0);
	glScaled(thickness, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawFloor(double thickness)
{
	glPushMatrix();
	//glTranslated(0.5,0.5*thickness,0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1.5);
	glPopMatrix();
}

void frontWallWithDoor(double thickness, double doorWidth, double doorHeight) {
	glPushMatrix();

	// Translate the front wall to the correct position
	glTranslated(0.0, 0.0, 0.75);  // Place the front wall correctly at the 4th side

	// Draw the front wall with a cutout for the door
	glPushMatrix();
	glScaled(thickness, 1.0, 1.0);

	// Left part of the front wall (to the left of the door)
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);  // Yellow for the wall
	glVertex3f(-0.75, 1.0, 0.0);  // Top-left corner of the wall
	glVertex3f(-0.75, 0.0, 0.0);  // Bottom-left corner
	glVertex3f(-doorWidth / 2, 0.0, 0.0);  // Bottom of the door
	glVertex3f(-doorWidth / 2, doorHeight, 0.0);  // Top of the door
	glEnd();

	// Right part of the front wall (to the right of the door)
	glBegin(GL_QUADS);
	glVertex3f(doorWidth / 2, 1.0, 0.0);  // Top-right corner of the wall
	glVertex3f(doorWidth / 2, doorHeight, 0.0);  // Top of the door
	glVertex3f(0.75, doorHeight, 0.0);  // Right above the door
	glVertex3f(0.75, 0.0, 0.0);  // Bottom-right corner
	glEnd();

	// Top part of the front wall (above the door)
	glBegin(GL_QUADS);
	glVertex3f(-doorWidth / 2, 1.0, 0.0);  // Top-left above the door
	glVertex3f(doorWidth / 2, 1.0, 0.0);  // Top-right above the door
	glVertex3f(doorWidth / 2, doorHeight, 0.0);  // Right above the door
	glVertex3f(-doorWidth / 2, doorHeight, 0.0);  // Left above the door
	glEnd();

	glPopMatrix();

	// Draw the door in the cutout, halfway closed (opening inward)
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);  // Red color for the door
	glTranslated(-doorWidth / 2, 0.0, thickness / 10);  // Position the door
	glRotated(-45.0, 0.0, 1.0, 0.0);  // Rotate the door inward (halfway open)

	glBegin(GL_QUADS);  // Draw the door
	glVertex3f(0.0, 0.0, 0.0);  // Bottom-left corner
	glVertex3f(doorWidth, 0.0, 0.0);  // Bottom-right corner
	glVertex3f(doorWidth, doorHeight, 0.0);  // Top-right corner
	glVertex3f(0.0, doorHeight, 0.0);  // Top-left corner
	glEnd();

	glPopMatrix();
	glPopMatrix();
}

void roof() {
	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0);  // Position the roof on top of the house
	glColor3f(1.0, 0.0, 0.0);  // Red color for the roof
	glBegin(GL_TRIANGLES);

	// Pyramid faces
	glVertex3f(-0.75, 0.0, -0.75);  // Base front-left corner
	glVertex3f(0.75, 0.0, -0.75);   // Base front-right corner
	glVertex3f(0.0, 0.75, 0.0);    // Top vertex

	glVertex3f(0.75, 0.0, -0.75);   // Base front-right corner
	glVertex3f(0.75, 0.0, 0.75);    // Base back-right corner
	glVertex3f(0.0, 0.75, 0.0);    // Top vertex

	glVertex3f(0.75, 0.0, 0.75);    // Base back-right corner
	glVertex3f(-0.75, 0.0, 0.75);   // Base back-left corner
	glVertex3f(0.0, 0.75, 0.0);    // Top vertex

	glVertex3f(-0.75, 0.0, 0.75);   // Base back-left corner
	glVertex3f(-0.75, 0.0, -0.75);  // Base front-left corner
	glVertex3f(0.0, 0.75, 0.0);    // Top vertex

	glEnd();
	glPopMatrix();
}

void house()
{
	glColor3f(0.0, 1.0, 0.0);
	drawFloor(0.02);

	/* other walls */
	/* yellow Walls */
	glColor3f(1.0, 1.0, 0.0);
	wall(0.02);

	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);			// Right side wall
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0.0, -0.5);			// Back wall
	glRotated(90.0, 0.0, 1.0, 0.0);
	glTranslated(0.5, 0.0, 0.5);
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0.0, -0.5);			// Back wall
	glRotated(90.0, 0.0, 1.0, 0.0);
	glTranslated(0.5, 5.0, 0.0);
	wall(0.02);
	glPopMatrix();

	// Front wall with door
	frontWallWithDoor(0.02, 0.3, 0.6);  // Door width = 0.3, height = 0.6

	// Roof
	roof();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 1.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	//Draw a grid on the xz plane
	glColor3f(1, 1, 1);
	drawGrid();
	//draw the three axes
	drawAxes();

	glScalef(2.0, 2.0, 2.0);
	house();

	glPopMatrix();
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
	//ifs can be replaced with switch...case
	if (key == 'o')
		if (dRot != 120)
			dRot += 2;
	if (key == 'c')
		if (dRot != 0)
			dRot -= 2;

	if (key == 'l')
		objRY += 1;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 0.2;

	if (key == 'z')
		sceTZ -= 0.2;

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

int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("House - End 201920");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}

