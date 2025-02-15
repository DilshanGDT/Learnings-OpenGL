#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL2.h>

constexpr float PI = 3.14159265358979323846;

int width;
int height;

//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

//To on/off grids and axes
int gridOn = 1;
int axesOn = 1;

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
	glClearColor(0.0, 0.8, 0.8, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	//Enabling texture
	glEnable(GL_TEXTURE_2D); // inform openGL that texture mapping is done

	//loadTexture();
}

void drawColoredCube() {
	// Front face (Red)
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);  // Red
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, 1.0); // Bottom left
	glVertex3f(1.0, -1.0, 1.0); // Bottom right
	glVertex3f(1.0, 1.0, 1.0); // Top right
	glVertex3f(-1.0, 1.0, 1.0); // Top left
	glEnd();
	glPopMatrix();

	// Back face (Green)
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);  // Green
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, -1.0); // Bottom left
	glVertex3f(1.0, -1.0, -1.0); // Bottom right
	glVertex3f(1.0, 1.0, -1.0); // Top right
	glVertex3f(-1.0, 1.0, -1.0); // Top left
	glEnd();
	glPopMatrix();

	// Left face (Blue)
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);  // Blue
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, -1.0); // Bottom left
	glVertex3f(-1.0, -1.0, 1.0); // Bottom right
	glVertex3f(-1.0, 1.0, 1.0); // Top right
	glVertex3f(-1.0, 1.0, -1.0); // Top left
	glEnd();
	glPopMatrix();

	// Right face (Yellow)
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);  // Yellow
	glBegin(GL_QUADS);
	glVertex3f(1.0, -1.0, -1.0); // Bottom left
	glVertex3f(1.0, -1.0, 1.0); // Bottom right
	glVertex3f(1.0, 1.0, 1.0); // Top right
	glVertex3f(1.0, 1.0, -1.0); // Top left
	glEnd();
	glPopMatrix();

	// Top face (Cyan)
	glPushMatrix();
	glColor3f(0.5, 0.5, 1.0);  // Cyan
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0, -1.0); // Bottom left
	glVertex3f(1.0, 1.0, -1.0); // Bottom right
	glVertex3f(1.0, 1.0, 1.0); // Top right
	glVertex3f(-1.0, 1.0, 1.0); // Top left
	glEnd();
	glPopMatrix();

	// Bottom face (Magenta)
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);  // Magenta
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, -1.0); // Bottom left
	glVertex3f(1.0, -1.0, -1.0); // Bottom right
	glVertex3f(1.0, -1.0, 1.0); // Top right
	glVertex3f(-1.0, -1.0, 1.0); // Top left
	glEnd();
	glPopMatrix();
}

void rubicCube() {

	// middle set
	// middle - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	drawColoredCube();
	glPopMatrix();

	// right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 0, 0);
	drawColoredCube();
	glPopMatrix();

	// left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 0, 0);
	drawColoredCube();
	glPopMatrix();

	// top - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, 2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// top right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// top left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// bottom - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, -2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// bottom right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, -2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// bottom left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, -2.25, 0);
	drawColoredCube();
	glPopMatrix();

	// front
	// middle - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, 0, 2.25);
	drawColoredCube();
	glPopMatrix();

	// right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 0, 2.25);
	drawColoredCube();
	glPopMatrix();

	// left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 0, 2.25);
	drawColoredCube();
	glPopMatrix();

	// top - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, 2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// top right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// top left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, -2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, -2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, -2.25, 2.25);
	drawColoredCube();
	glPopMatrix();

	// back
	// middle - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, 0, -2.25);
	drawColoredCube();
	glPopMatrix();

	// right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 0, -2.25);
	drawColoredCube();
	glPopMatrix();

	// left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 0, -2.25);
	drawColoredCube();
	glPopMatrix();

	// top - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, 2.25, -2.25);
	drawColoredCube();
	glPopMatrix();

	// top right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, 2.25, -2.25);
	drawColoredCube();
	glPopMatrix();

	// top left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, 2.25, -2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0, -2.25, -2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom right - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(2.25, -2.25, -2.25);
	drawColoredCube();
	glPopMatrix();

	// bottom left - center
	glPushMatrix();
	glScaled(0.5, 0.5, 0.5);
	glTranslated(-2.25, -2.25, -2.25);
	drawColoredCube();
	glPopMatrix();
}

void rubicCubeWithForLoop() {
	const float cubeSize = 0.5;       // Size of each small cube
	const float spacing = 2.25;      // Spacing between cubes

	for (int x = -1; x <= 1; ++x) {
		for (int y = -1; y <= 1; ++y) {
			for (int z = -1; z <= 1; ++z) {
				// Skip the central cube (if needed)
				// if (x == 0 && y == 0 && z == 0) continue;

				glPushMatrix();
				glScaled(cubeSize, cubeSize, cubeSize);
				glTranslated(x * spacing, y * spacing, z * spacing);
				drawColoredCube();
				glPopMatrix();
			}
		}
	}
}

void setLighting() {

	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	// Set lighting intensity and color - light 0
	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position - light 0
	GLfloat qaLightPosition[] = { -10.0, 1.0, -.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	// Set lighting intensity and color - light 1
	GLfloat qaAmbientLight1[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight1[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);

	// Set the light position - light 1
	GLfloat qaLightPosition1[] = { 10.0, 1.0, 0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

	GLfloat SpecRef[] = { 0.7,0.7,0.7,1.0 };
	GLint Shine = 128;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//Set material to follow
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);//Set specular reflectivity and shine
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 0.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	setLighting();

	//Draw a grid on the xz plane
	glColor3f(0.1, 0.1, 0.1);
	if (gridOn == 1)
		drawGrid();
	//draw the three axes
	if (axesOn == 1)
		drawAxes();

	//drawColoredCube();
	//rubicCube();
	rubicCubeWithForLoop();

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
	if (key == 'l')
		objRY += 1;

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

	if (key == '!')
		glDisable(GL_LIGHT0); // Light at -x

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '@')
		glDisable(GL_LIGHT1); // Light at +x

	if (key == '2')
		glEnable(GL_LIGHT1);

	//Grids and axes
	if (key == 'G')
		gridOn = 1;
	if (key == 'g')
		gridOn = 0;
	if (key == 'A')
		axesOn = 1;
	if (key == 'a')
		axesOn = 0;


	glutPostRedisplay();
}

int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D Doll - End 202021");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}