#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Variables to move the camera
GLfloat camXInit = 0.0;
GLfloat camYInit = 0.0;
GLfloat camZInit = 0.0;

GLfloat camX = camXInit;
GLfloat camY = camYInit;
GLfloat camZ = camZInit;

// Variables to move the scene
GLfloat sceRXInit = 0.0;
GLfloat sceRYInit = 0.0;
GLfloat sceRZInit = 0.0;
GLfloat sceTXInit = 0.0;
GLfloat sceTYInit = 0.0;
GLfloat sceTZInit = 0.0;

GLfloat sceRX = sceRXInit;
GLfloat sceRY = sceRYInit;
GLfloat sceRZ = sceRZInit;
GLfloat sceTX = sceTXInit;
GLfloat sceTY = sceTYInit;
GLfloat sceTZ = sceTZInit;

// Variables to move the looking position
GLfloat lookX = 0.0;
GLfloat lookY = 0.0;
GLfloat lookZ = 0.0;

// Variables to move the objects
GLfloat objRX = 0.0;
GLfloat objRY = 0.0;
GLfloat objRZ = 0.0;
GLfloat objTX = 0.0;
GLfloat objTY = 0.0;
GLfloat objTZ = 0.0;

GLfloat openDoorAngle = 60;
GLfloat openDoorZ = -0.05;
GLfloat openDoorXInit = -0.4;
GLfloat closeDoorAngle = 0;
GLfloat closeDoorZ = 0;
GLfloat closeDoorXInit = -0.5;

GLfloat doorAngle = closeDoorAngle;
GLfloat doorZ = closeDoorZ;
GLfloat doorXInit = closeDoorXInit;

static float dRot;

// Grid and coordinate axes for better visualization
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

// Intensity of the light source
void light0(GLfloat offset, GLfloat posOffset) {

	// (r, g, b, opacity)
	GLfloat l0amb[] = { 0.2 + offset, 0.2 + offset, 0.2 + offset, 1.0 };
	GLfloat l0diff[] = { 0.8 - offset, 0.8 - offset, 0.8 - offset, 1.0 };
	GLfloat l0spec[] = { 1.0, 1.0, 1.0, 1.0 };

	// Light source position : (x, y, z, type_of_the_light_source)
	GLfloat l0pos[] = { -10 + posOffset, 1.0, -0.5, 1.0 };

	// Set the illumination or intensity (ambiant, diffusion, specular)
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glGetLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);

	// Set the Light source position
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
}

// Set Properties of light sources and materials
void setLightingandShading() {
	// Enable light
	glEnable(GL_LIGHTING); //Tell opengl that we are setting custom lighting

	// Create light
	// Define the illumination or intensity of the light source
	GLfloat l0amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat l0diff[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat l0spec[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat l0pos[] = { -10, 1.0, -0.5, 1.0 };

	// Set the illumination or intensity (ambiant, diffusion, specular)
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glGetLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);

	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

	// Seting surface colors and properties
	// Enable glColor function apply its color
	glEnable(GL_COLOR_MATERIAL);
	// glShadeModel(GL_SMOOTH);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat specRef[] = { 0.7, 0.7,0.7, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);

	GLint shiness = 128;
	glMateriali(GL_FRONT, GL_SHININESS, shiness);
}

// Bicycle

// Tyre, spokes and hub
void tire() {
	glPushMatrix();

	glColor3f(0.1f, 0.1f, 0.1f); // Black color for tire
	glutSolidTorus(0.1f, 1.0f, 30, 30);

	glPopMatrix();
}

void spoke() {
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f); // Light gray for spokes
	glRotated(90.0, 1, 0, 0);

	GLUquadricObj* quad = gluNewQuadric();
	gluCylinder(quad, 0.02f, 0.02f, 1.0f, 10, 1);

	glPopMatrix();
}

void hub() {
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f); // Light gray for axel

	GLUquadricObj* quad = gluNewQuadric();

	// Draw the cylinder
	glTranslated(0, 0, -0.1f);
	gluCylinder(quad, 0.2f, 0.2f, 0.2f, 10, 1);

	// Draw the bottom disk
	glPushMatrix();
	glRotated(180.0, 1, 0, 0); // Rotate to align with bottom
	gluDisk(quad, 0.0, 0.2f, 10, 1);
	glPopMatrix();

	// Draw the top disk
	glPushMatrix();
	glTranslated(0, 0, 0.2f); // Move to the top of the cylinder
	gluDisk(quad, 0.0, 0.2f, 10, 1);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void wheel() {
	tire(); // Draw the tire

	// Draw 8 spokes around the origin
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glRotated(i * 45.0, 0, 0, 1); // Rotate each spoke by 45 degrees around Z-axis
		spoke(); // Draw the spoke in the new orientation
		glPopMatrix();
	}

	hub();	// Draw the axel
}

// Handlebar
void handleBarMiddle() {
	glPushMatrix();
	glColor3f(1.0f, 0, 0); // Light gray for spokes
	//glRotated(90.0, 1, 0, 0);

	glTranslated(0, 0, -0.5f);
	GLUquadricObj* quad = gluNewQuadric();
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);

	glPopMatrix();
}

void handRestRight() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); // Light gray for hand rest

	GLUquadricObj* quad = gluNewQuadric();

	// Draw the cylinder
	glTranslated(0, 0, 0.5f);
	gluCylinder(quad, 0.07f, 0.07f, 0.3f, 10, 1);

	// Draw the bottom cap
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glRotated(180.0, 1, 0, 0); // Rotate to align with the bottom of the cylinder
	gluDisk(quad, 0.0, 0.07f, 10, 1);
	glPopMatrix();

	// Draw the top cap
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslated(0, 0, 0.3f); // Move to the top of the cylinder
	gluDisk(quad, 0.0, 0.07f, 10, 1);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void handRestLeft() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); // Light gray for hand rest

	GLUquadricObj* quad = gluNewQuadric();

	// Draw the cylinder
	glTranslated(0, 0, -0.7f);
	gluCylinder(quad, 0.07f, 0.07f, 0.3f, 10, 1);

	// Draw the bottom cap
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glRotated(180.0, 1, 0, 0); // Rotate to align with the bottom of the cylinder
	gluDisk(quad, 0.0, 0.07f, 10, 1);
	glPopMatrix();

	// Draw the top cap
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslated(0, 0, 0.3f); // Move to the top of the cylinder
	gluDisk(quad, 0.0, 0.07f, 10, 1);
	glPopMatrix();

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void handleBar() {
	handleBarMiddle();
	handRestRight();
	handRestLeft();
}

// Fork 
void fork() {

	// Horizontal bar
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f); // Light gray for spokes
	glScaled(1.2f, 1.2f, 1.2f);
	glTranslated(0, 0, -0.3f);
	GLUquadricObj* quad = gluNewQuadric();
	gluCylinder(quad, 0.04f, 0.04f, 0.6f, 10, 1);
	glPopMatrix();

	// Fork Middle - vertical
	glPushMatrix();
	glScaled(1.2f, 1.2f, 1.2f);
	glRotated(90.0, 1, 0, 0);
	glTranslated(0, 0.0f, -0.6f); 
	gluCylinder(quad, 0.04f, 0.04f, 0.6f, 10, 1);
	glPopMatrix();

	// Shocks
	glPushMatrix();
	glScaled(1.2f, 1.2f, 1.2f);
	glRotated(90.0, 1, 0, 0);
	glTranslated(0.0, -0.28f, 0.0f);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();

	// Shocks
	glPushMatrix();
	glScaled(1.2f, 1.2f, 1.2f);
	glRotated(90.0, 1, 0, 0);
	glTranslated(0.0, 0.28f, 0.0f);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();
}

void frame() {

	glPushMatrix();
	glColor3f(0, 0, 1); // Light gray for spokes
	glRotated(90.0, 0, 1, 0);
	GLUquadricObj* quad = gluNewQuadric();
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1); // Light gray for spokes
	glTranslated(1, 0, 0);
	glRotated(90.0, 0, 1, 0);
	glRotated(-120, 1, 0, 0);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1); // Light gray for spokes
	glRotated(90.0, 0, 1, 0);
	glRotated(-60, 1, 0, 0);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0); // Light gray for spokes
	glTranslated(-0.5, 0.85, 0);
	glRotated(90.0, 0, 1, 0);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 1, 0); // Light gray for spokes
	glTranslated(-0.5, 0.85, 0);
	glRotated(90.0, 0, 1, 0);
	glRotated(60, 1, 0, 0);
	gluCylinder(quad, 0.04f, 0.04f, 1.0f, 10, 1);
	glPopMatrix();
}

// Complete Bicycle
void bicycle() {
	//glPushMatrix();
	//glScaled(0.5f, 0.5f, 0.5f);
	
	//glPopMatrix();
	wheel();

	glRotated(15, 0, 0, -1);
	glScaled(1.2f, 1.2f, 1.2f);
	glTranslated(0.0f, 2.0f, 0.0f);
	handleBar();

	glPushMatrix();
	glTranslated(0.0f, -0.6f, 0.0f);
	fork();
	glPopMatrix();

	glPushMatrix();
	//glTranslated(0.0f, -0.6f, 0.0f);
	frame();
	glPopMatrix();
	

	//wheel();
}



void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// Camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 1.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	// Draw a grid on the xz plane
	glColor3f(1, 1, 1);
	drawGrid();

	// draw the three axes
	drawAxes();

	//setLightingandShading();

	bicycle();
	//frame();

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
		camY += 0.5;

	if (key == GLUT_KEY_DOWN)
		camY -= 0.5;

	if (key == GLUT_KEY_RIGHT)
		sceTX += 1;
	objTX -= 1;

	if (key == GLUT_KEY_LEFT)
		sceTX -= 1;
	objTX += 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	if (key == 'y')
		sceRY += 1;

	if (key == 'Y')
		sceRY -= 1;

	if (key == 'l')
		objRY += 1;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 1;

	if (key == 'z')
		sceTZ -= 1;

	if (key == 'w') {
		sceTZ += 1;
		objTZ -= 1;
	}

	if (key == 's') {
		sceTZ -= 1;
		objTZ += 1;
	}

	if (key == 'a') {
		sceTY += 1;
		objTY -= 1;
	}

	if (key == 'd') {
		sceTY -= 1;
		objTY += 1;
	}

	if (key == '6')
		lookX += 1;

	if (key == '4')
		lookX -= 1;

	if (key == '8')
		lookY += 1;

	if (key == '2')
		lookY -= 1;

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '3')
		glDisable(GL_LIGHT0);

	if (key == '6')
		glShadeModel(GL_FLAT);

	if (key == '7')
		glShadeModel(GL_SMOOTH);

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bicycle");

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();
	glutMainLoop();
	return 0;
}