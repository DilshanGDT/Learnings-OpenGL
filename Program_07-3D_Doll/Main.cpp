#include <GL/glut.h>
#include <math.h>

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

//Defines the properties of light sourse and material
void setLightingAndShading() {
	//Enable lighting
	glEnable(GL_LIGHTING);//tell opengl that we are setting the lighting
	//Create the light souse 0

	//glEnable(GL_LIGHT0);

	//Defining the illumination or intensity of the light sourse
	GLfloat l0amb[] = { 0.2,0.2,0.2,1.0 };
	GLfloat l0diff[] = { 0.8,0.8,0.8,1.0 };
	GLfloat l0spec[] = { 1.0,1.0,1.0,1.0 };

	//define the position
	//(x,y,z,type_of_light_sourse)
	GLfloat l0pos[] = { -10.0,1.0,-0.5,1.0 };

	//set the illlumination (ambient,diffusion,specular) using glGet
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);

	//set the position of the light sourse
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

	//Create the light souse 1

	//glEnable(GL_LIGHT1);

	//Defining the illumination or intensity of the light sourse
	//(r,g,b,opacity) - normalized values
	GLfloat l1amb[] = { 0.5,0.5,0.5,1.0 }; // array
	GLfloat l1diff[] = { 0.8,0.8,0.8,1.0 };
	GLfloat l1spec[] = { 1.0,1.0,1.0,1.0 };

	//define the position
	//(x,y,z,type_of_light_sourse)
	GLfloat l1pos[] = { 10.0,1.0,-0.5,1.0 };

	//set the illlumination (ambient,diffusion,specular) using glGet
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1spec);

	//set the position of the light sourse
	glLightfv(GL_LIGHT1, GL_POSITION, l1pos);

	//setting the surface colors and properties
	//Enable glColor function apply its color
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); // Apply pong shading to apply the aillumination
	//OR FLAT

	//ask opengl spetialy to apply ambient,diffuse and specular

	//set the ambient and diffuse
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//set the specular material properties
	//set the specular intensity
	GLfloat specRef[] = { 0.7,0.7,0.7,1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);

	//set the shineness - glMateriali - i for intiger
	//glMateriali(GL_FRONT, GL_SHININESS, 128);
}

// Doll Creation
void BellyCoat() {
	glPushMatrix();
	glColor3f(1.0, 0.45, 0.09);
	glTranslatef(0, 1, 0);
	glScalef(1, 0.7, 1);
	glRotatef(90.0, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad, 0.6, 0.8, 1, 100, 100);

	glPopMatrix();
}

void Head() {
	glPushMatrix();
	glColor3f(1.0, 0.89, 0.7);
	glTranslatef(0, 1.5, 0);
	glScalef(0.8, 0.8, 0.8);

	GLUquadric* quad = gluNewQuadric();
	gluSphere(quad, 1, 100, 100);

	glPopMatrix();
}

void BellyButtons() {
	// Bottom
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 0.4, 0.76);
	glScalef(0.5, 0.5, 0.5);

	GLUquadric* quad = gluNewQuadric();
	gluSphere(quad, 0.1, 100, 100);

	glPopMatrix();

	// Middle
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 0.6, 0.7);
	glScalef(0.5, 0.5, 0.5);

	GLUquadric* quad2 = gluNewQuadric();
	gluSphere(quad2, 0.1, 100, 100);

	glPopMatrix();

	// Top
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 0.8, 0.65);
	glScalef(0.5, 0.5, 0.5);

	GLUquadric* quad3 = gluNewQuadric();
	gluSphere(quad3, 0.1, 100, 100);

	glPopMatrix();
}

void Legs() {
	//left
	glPushMatrix();
	glColor3f(0.18, 0.09, 0.2);
	glTranslatef(-0.3, 0.5, 0);
	glScalef(0.6, 0.6, 0.6);
	glRotatef(90.0, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad, 0.6, 0.6, 1, 100, 100);

	glPopMatrix();

	//right
	glPushMatrix();
	glColor3f(0.18, 0.09, 0.2);
	glTranslatef(0.3, 0.5, 0);
	glScalef(0.6, 0.6, 0.6);
	glRotatef(90.0, 1, 0, 0);

	GLUquadric* quad1 = gluNewQuadric();
	gluCylinder(quad1, 0.6, 0.6, 1, 100, 100);

	glPopMatrix();
}

void Hands() {
	glPushMatrix();
	glColor3f(1.0, 0.45, 0.09);
	glTranslatef(0, 1, 0);
	glScalef(1, 0.7, 1);
	glRotatef(90.0, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad, 0.6, 0.8, 1, 100, 100);

	glPopMatrix();
}

void Shoes() {

}

void Scarf() {

}

void Eyes() {
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0.3, 1.4, 0.7);
	glScalef(0.5, 0.7, 0.5);
	glRotatef(90, 0, 0, 1);


	GLUquadric* quad = gluNewQuadric();
	gluSphere(quad, 0.3, 100, 100);

	glPopMatrix();
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

	//draw bellyCoat
	BellyCoat();

	//draw coat button
	BellyButtons();
	Head();
	Scarf();
	Legs();
	//Eyes();
	//Shoes();

	//setLightingAndShading();

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
		//glutTimerFunc(200, doFrame, 0);
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

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '!')
		glDisable(GL_LIGHT0);

	if (key == '2')
		glEnable(GL_LIGHT1);

	if (key == '!')
		glDisable(GL_LIGHT1);

	glutPostRedisplay();
}

int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D Doll");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutTimerFunc(200, doFrame, 0);
	init();
	glutMainLoop();
	return 0;
}