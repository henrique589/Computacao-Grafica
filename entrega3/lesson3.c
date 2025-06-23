#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int win_id;

// Variáveis de controle de rotação
float armRotation = 20.0f;
float legRotation = 0.0f;
const float MAX_ARM_ROT = 60.0f;
const float MIN_ARM_ROT = -60.0f;
const float MAX_LEG_ROT = 30.0f;
const float MIN_LEG_ROT = -30.0f;

// Função auxiliar para desenhar um cilindro sólido com tampas
void drawCylinder(float radius, float height, int slices) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluCylinder(quad, radius, radius, height, slices, 1);
    glPushMatrix();
        glRotatef(180, 1, 0, 0);
        gluDisk(quad, 0, radius, slices, 1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, height);
        gluDisk(quad, 0, radius, slices, 1);
    glPopMatrix();
    gluDeleteQuadric(quad);
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            glutDestroyWindow(win_id);
            exit(0);
            break;
        case 'a':
            if (armRotation < MAX_ARM_ROT) armRotation += 5.0f;
            break;
        case 'd':
            if (armRotation > MIN_ARM_ROT) armRotation -= 5.0f;
            break;
        case 'w':
            if (legRotation < MAX_LEG_ROT) legRotation += 5.0f;
            break;
        case 's':
            if (legRotation > MIN_LEG_ROT) legRotation -= 5.0f;
            break;
    }
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 20.0, 30.0, 20.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f, 7.0f, 45.0f,
              0.0f, 5.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    // Calça
    glColor3f(0.35f, 0.16f, 0.14f);
    glPushMatrix();
        glTranslatef(0.0f, 1.25f, 0.0f);
        glScalef(10.1f, 2.5f, 5.1f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Camisa
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, 3.75f, 0.0f);
        glScalef(10.1f, 2.5f, 5.1f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Cabeça
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, 10.0f, 0.0f);
        glScalef(10.0f, 10.0f, 5.0f);
        glutSolidCube(1.0f);
    glPopMatrix();

    // Olhos
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); 
		glTranslatef(-2.5f, 12.0f, 2.6f); 
		glutSolidSphere(1.5, 20, 20); 
	glPopMatrix();
    glPushMatrix(); 
		glTranslatef(2.5f, 12.0f, 2.6f); 
		glutSolidSphere(1.5, 20, 20); 
	glPopMatrix();

    // Pupilas
    glColor3f(0.0f, 0.0f, 0.98f);
    glPushMatrix(); 
		glTranslatef(-2.5f, 12.0f, 3.8f); 
		glutSolidSphere(0.5, 20, 20); 
	glPopMatrix();
    glPushMatrix(); 
		glTranslatef(2.5f, 12.0f, 3.8f); 
		glutSolidSphere(0.5, 20, 20); 
	glPopMatrix();

    // Nariz
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(0.0f, 9.5f, 2.5f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        drawCylinder(0.4f, 1.5f, 10);
    glPopMatrix();

    // Braço esquerdo
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(-5.0f, 7.0f, 0.0f);
        glRotatef(-armRotation, 0.0f, 0.0f, 1.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.4f, 4.0f, 10);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 4.0f);
            glutSolidSphere(0.7, 10, 10);
        glPopMatrix();
    glPopMatrix();

    // Braço direito
    glPushMatrix();
        glTranslatef(5.0f, 7.0f, 0.0f);
        glRotatef(armRotation, 0.0f, 0.0f, 1.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        drawCylinder(0.4f, 4.0f, 10);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 4.0f);
            glutSolidSphere(0.7, 10, 10);
        glPopMatrix();
    glPopMatrix();

    // Gravata 
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0.0f, 3.8f, 2.6f);   
		glScalef(0.5f, 1.6f, 0.3f);       
		glutSolidCube(1.0f);
	glPopMatrix();


	// Perna esquerda 
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-2.0f, -4.0f, 0.0f);
		glRotatef(legRotation, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		drawCylinder(0.4f, 4.0f, 10);

		// Sapato 
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f); 
			glScalef(1.5f, 2.5f, 1.0f);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	// Perna direita 
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(2.0f, -4.0f, 0.0f);
		glRotatef(-legRotation, 1.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		drawCylinder(0.4f, 4.0f, 10);

		// Sapato
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(0.0f, -0.5f, 0.0f); 
			glScalef(1.5f, 2.5f, 1.0f);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    win_id = glutCreateWindow("Bob Esponja - Interativo");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
}
