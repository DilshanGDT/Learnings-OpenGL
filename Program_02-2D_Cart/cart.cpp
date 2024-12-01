//#include<iostream>
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
#include <GL\glut.h>
#include <math.h>
#include <Windows.h>					//optional

constexpr auto PI = 3.14159265358979323846;

//void init() {
//	glClearColor(0.2, 0.95, 0.6, 1.0);
//	glClear(GL_COLOR_BUFFER_BIT);		// Clearing color buffer
//}

void drawDisk(double radius, int n) {
	double angle = 0;

	glBegin(GL_POLYGON);
	for (int c = 0; c <= n; c++) {
		double x = radius * cos(angle);
		double y = radius * sin(angle);

		glVertex2d(x, y);
		angle = angle + ((2 * PI) / n);
	}
	glEnd();
}

void drawWheel() {
	glColor3f(0.0, 0.0, 0.0);
	drawDisk(2.0, 32);					// Middle Bearing
	glColor3f(0.0, 0.0, 0.0);
	drawDisk(1.8, 32);					// Inner tire circle
	glColor3f(0.0, 0.0, 0.0);
	drawDisk(0.5, 32);					// Outer tire circle
}

int main(int argc, char** argv) {

	drawWheel();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);

	glMatrixMode(GL_MODELVIEW);

	// Set it to the identity matrix

}

void drawCart() {

	// Wheel-1
	drawWheel();

	// Wheel-2
	// Translate the wheel along with the x axisby 7 and redraw
	// We update te model-view matrx by pushing a new matrix 
	glPushMatrix();
	glTranslatef(7.0, 0.0, 0.0);
	drawWheel();
	glPopMatrix();		// Finally pop matrix out

	// Cart-body

}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);

	// Calculate the aspect ratio
}