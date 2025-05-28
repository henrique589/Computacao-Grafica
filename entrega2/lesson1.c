#include <GL/glut.h>
#include <math.h>

// Largura e altura da janela
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

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

    // Aqui entra todo o seu código da casa 2D.
    //Vocês só pode usar as funções de desenho:
        // desenhaQuadrado, desenhaTriangulo, desenhaCirculo
    // as transformações geométricas:
        // glTranslatef, glRotatef, glScalef, skewX, skewY
    // e as funções de cor:
        // glColor3f
    // Não desenhe nenhuma primitiva utilizando glBegin/glEnd diretamente aqui.
    /*glTranslatef(100.0f,100.0f,0.0f);
    glPushMatrix();
      glColor3f(1.0f,0.0f,0.0f);
      glScalef(10.0f,10.0f,1.0f);
      desenhaQuadrado();
    glPopMatrix();
    
    glTranslatef(20.0f, 0.0f,0.0f);
    glPushMatrix();
    glColor3f(0.0f,1.0f,0.0f);
      glScalef(20.0f,20.0f,1.0f);
      desenhaTriangulo();
    glPopMatrix();
    
    glTranslatef(50.0f, 0.0f, 0.0f);
    glScalef(20.0f,30.0f,1.0f);
    glColor3f(0.0f,0.0f,1.0f);
    desenhaCirculo();*/

	//Parede da frente
    glTranslatef(100.0f, 100.0f, 0.0f);
    glPushMatrix();
      glScalef(60.0f, 60.0f, 1.0f);
      glColor3f(0.70f, 0.50f, 0.35f);
      desenhaQuadrado();
    glPopMatrix();  

	//Porta
	glPushMatrix();
		glTranslatef(+10.0f, -15.0f, 0.1f);
		glScalef(15.0f, 30.0f, 1.0f);
		glColor3f(0.5f, 0.25f, 0.0f);
		desenhaQuadrado();
		glPopMatrix();      
    glPopMatrix();
    
	// Telhado triângulo
    glPushMatrix();
      glTranslatef(0.0f, 60.0f, 0.0f);
      glScalef(60.0f, 60.0f, 1.0f);
      glColor3f(0.5f, 0.2f, 0.15f);
      desenhaTriangulo();
    glPopMatrix();
	
	//Parede lateral
    glPushMatrix();
      glTranslatef(90.0f, 0.0f, 0.0f);
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
      
    glPopMatrix();

    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    // Se a largura da janela, em pixels, for menor que a altura, a largura da viewport é fixada em 250 e a altura é escalada para o necessário
    if (w <= h)  {
        windowHeight = 250.0f*h/w;
                windowWidth = 250.0f;
    }
    else  {
    // Se a altura da janela, em pixels, for menor que a largura, a altura da viewport é fixada em 250 e a largura é escalada para o necessário
                windowWidth = 250.0f*w/h;
                windowHeight = 250.0f;
    }

    // As dimensões da janela vão de (0.0, 0.0) até (windowWidth, windowHeight), essas são as coordenadas da tela
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Minha Casa");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}
