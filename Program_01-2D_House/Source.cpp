#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <GL\glut.h>

void draw() {
	//House Creation Logic
	glClear(GL_COLOR_BUFFER_BIT); //Clears the Color Buffer

	//Roof
	glBegin(GL_TRIANGLE_FAN);
	//Color for the Roof
	glColor3f(0.0f, 1.0f, 0.0f);

	//Vertices of the Roof Shape
	glVertex2f(0.0f, 0.7f);
	glVertex2f(0.6f, 0.1f);
	glVertex2f(0.5f, 0.1f);
	glVertex2f(-0.6f, 0.1f);
	glEnd();

	/*float i = -0.6;
	while(i<0.6) {
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(i, 0.7);
	i += 0.1;
	glEnd();
	}*/

	//Walls
	glBegin(GL_QUADS);
	//Color for the Walls
	glColor3f(0.0f, 0.0f, 1.0f);

	//Vertices of the Wall Shape
	glVertex2f(-0.55f, 0.1f);
	glVertex2f(0.55f, 0.1f);
	glVertex2f(0.55f, -0.8f);
	glVertex2f(-0.55f, -0.8f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, -0.8f);
	glVertex2f(0.05f, -0.5f);
	glVertex2f(-0.05f, -0.5f);
	glVertex2f(-0.05f, -0.8f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.4f);
	glVertex2f(0.05f, -0.8f);
	glVertex2f(0.05f, -0.95f);
	glVertex2f(-0.05f, -0.95f);
	glVertex2f(-0.05f, -0.8f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.4f);
	glVertex2f(-1.0f, -0.95f);
	glVertex2f(1.0f, -0.95f);
	glVertex2f(1.0f, -0.99f);
	glVertex2f(-1.0f, -0.99f);
	glEnd();

	////Foundation
	//glBegin(GL_QUADS);
	// //Color for the Foundation
	// glColor3f(0.0f, 0.0f, 0.5f);
	// //Vertices of the Foundation Shape
	// glVertex2f(0.55f, -0.8f);
	// glVertex2f(0.57f, -0.85f);
	// glVertex2f(-0.55f, -0.8f);
	// glVertex2f(-0.57f, -0.9f);
	//glEnd();

	//Window_1
	glBegin(GL_QUADS);
	//Color for the Windows
	glColor3f(1.0f, 0.0f, 0.0f);

	//Vertices of the Window Shape
	glVertex2f(-0.4f, -0.1f);
	glVertex2f(-0.2f, -0.1f);
	glVertex2f(-0.2f, -0.4f);
	glVertex2f(-0.4f, -0.4f);
	glEnd();


	//Window_2
	glBegin(GL_QUADS);
	//Color for the Windows
	glColor3f(1.0f, 0.0f, 0.0f);

	//Vertices of the Window Shape
	glVertex2f(0.4f, -0.1f);
	glVertex2f(0.2f, -0.1f);
	glVertex2f(0.2f, -0.4f);
	glVertex2f(0.4f, -0.4f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	float i = -0.1;
	while (i > -1) {
		glVertex2f(i, -0.7);
		glVertex2f(i, -0.85);
		i = i - 0.1;
	}
	glEnd();


	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	float j = 0.1;
	while (j < 1) {
		glVertex2f(j, -0.7);
		glVertex2f(j, -0.85);
		j = j + 0.1;
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	glVertex2f(-1, -0.75);
	glVertex2f(-0.1, -0.75);

	glVertex2f(-1, -0.82);
	glVertex2f(1, -0.82);
	glEnd();
	glFlush(); //Clears all the Buffers
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);

	glutCreateWindow("House 2D");
	glutDisplayFunc(draw);
	glutMainLoop();

	return 0;
}