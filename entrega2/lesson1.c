#include <GL/glut.h>
#include <math.h>

GLfloat windowWidth;
GLfloat windowHeight;

//Desenha um quadrado de lado 1 centrado na origem
void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

//Desenha um triângulo equilátero de lado 1 centrado na origem
void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
    glEnd();
}

//Desenha um círculo de raio 1 centrado na origem
void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

//Faz o cisalhamento de um objeto em relação ao eixo X
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewX(GLfloat angle) {
    GLfloat m[16] = {
        1, 0, 0, 0,
        tan(angle), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0 ,1
    };
    glMultMatrixf(m);
}

//Faz o cisalhamento de um objeto em relação ao eixo Y
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewY(GLfloat angle) {
    GLfloat m[16] = {
        1, tan(angle), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(m);
}

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Define a escala da casa com base no menor lado da janela
    GLfloat escala = fmin(windowWidth, windowHeight) / 500.0f;

    //Centraliza a casa e aplica escala
    glTranslatef(windowWidth / 2.0f, windowHeight / 2.0f, 0.0f);
    glScalef(escala, escala, 1.0f);

    //Parede da frente
    glPushMatrix();
        glTranslatef(-30.0f, -30.0f, 0.0f);
        glPushMatrix();
            glScalef(60.0f, 60.0f, 1.0f);
            glColor3f(0.70f, 0.50f, 0.35f);
            desenhaQuadrado();
        glPopMatrix();  

        //Porta
        glPushMatrix();
            glTranslatef(+10.0f, -15.0f, 0.0f);
            glPushMatrix();
                glScalef(15.0f, 30.0f, 1.0f);
                glColor3f(0.5f, 0.25f, 0.0f);
                desenhaQuadrado();
            glPopMatrix();    

            //Maçaneta
            glPushMatrix();
                glTranslatef(3.0f, -2.0f, 0.0f);
                glScalef(2.0f, 2.0f, 1.0f);
                glColor3f(1.0f, 1.0f, 0.0f);
                desenhaCirculo();
            glPopMatrix();  

            //Olho mágico
            glPushMatrix();
                glTranslatef(0.0f, +5.5f, 0.0f);
                glScalef(1.0f, 1.0f, 1.0f);
                glColor3f(0.7f, 0.85f, 1.0f);
                desenhaCirculo();
            glPopMatrix();  
        glPopMatrix();

        //Telhado triângulo
        glPushMatrix();
            glTranslatef(0.0f, 60.0f, 0.0f);
            glPushMatrix();
                glScalef(60.0f, 60.0f, 1.0f);
                glColor3f(0.5f, 0.2f, 0.15f);
                desenhaTriangulo();
            glPopMatrix();

            //Círculo central no triângulo
            glPushMatrix();
                glTranslatef(0.0f, -5.0f, 0.0f);
                glScalef(10.0f, 10.0f, 1.0f);    
                glColor3f(0.9f, 0.95f, 1.0f);
                desenhaCirculo();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Parede lateral, janelas e telhado
    glPushMatrix();
        glTranslatef(60.0f, -30.0f, 0.0f);
        glPushMatrix();
            glScalef(120.0f, 60.0f, 1.0f);
            glColor3f(0.9f, 0.7f, 0.50f);
            desenhaQuadrado();
        glPopMatrix();

        //Janela1
        glPushMatrix();
            glTranslatef(-30.0f, 0.0f, 0.0f);
            glScalef(20.0f, 15.0f, 1.0f);
            glColor3f(0.9f, 0.95f, 1.0f);
            desenhaQuadrado();
        glPopMatrix();

        //Janela2
        glPushMatrix();
            glTranslatef(+30.0f, 0.0f, 0.1f);
            glScalef(20.0f, 15.0f, 1.0f);
            glColor3f(0.9f, 0.95f, 1.0f);
            desenhaQuadrado();
        glPopMatrix();

		// Telhado lateral
		glPushMatrix();
			glTranslatef(0.0f, 60.0f, 0.0f); 
			glScalef(120.0f, 60.0f, 1.0f);      
			glColor3f(0.5f, 0.2f, 0.15f);       
			skewX(atan(-0.5));                   
			desenhaQuadrado();
		glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    windowWidth = w;
    windowHeight = h;

    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Minha Casa");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}
