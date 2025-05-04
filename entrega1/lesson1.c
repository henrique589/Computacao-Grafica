#include <GL/glut.h> 
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <unistd.h>    
#include <math.h> // ADICIONAR -lm no makefile

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int frameCount = 0;
int smokeDirection = 1; // 1: indo pra direita, -1: voltando
float smokeOffset = 0.0f;

int window; 

void InitGL(int Width, int Height){
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f);		// This Will Clear The Background Color To blue
    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
    glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
    glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix

    // Set up an orthogonal projection
    glOrtho(-Width / 200.0f, Width / 200.0f, -Height / 200.0f, Height / 200.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

float orthoLeft, orthoRight, orthoBottom, orthoTop;

void ReSizeGLScene(int Width, int Height){
    if(Height == 0) Height = 1;

    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)Width / (float)Height;

    if(aspect >= 1.0f){
        orthoLeft = -aspect * 5.0f;
        orthoRight = aspect * 5.0f;
        orthoBottom = -5.0f;
        orthoTop = 5.0f;
    }else{
        orthoLeft = -5.0f;
        orthoRight = 5.0f;
        orthoBottom = -5.0f / aspect;
        orthoTop = 5.0f / aspect;
    }

    glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View

    // Telhado paralelogramo 
    glColor3f(0.7f, 0.3f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex3f(-1.2, 0.4f, -1.0f);
        glVertex3f(2.8, 0.4f, -1.0f);
        glVertex3f(1.8, 2.3f, -1.0f);    
        glVertex3f(-2.2, 2.3f, -1.0f);
    glEnd();

    //Círculo do telhado
    float centroX = -2.2f, centroY = 1.2f, raio = 0.4f;
    int numLados = 100;

    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(centroX, centroY, -1.0f);
        for(int i = 0; i <= numLados; i++){
            float angulo = 2.0f * M_PI * i/numLados;
            float x = centroX + raio * cos(angulo);
            float y = centroY + raio * sin(angulo);
            glVertex3f(x, y, 0.3f);
        }
        glEnd();

    // Telhado triângulo 
    glColor3f(0.5f, 0.2f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-3.2, 0.4f, -1.0f);   
        glVertex3f(-1.2, 0.4f, -1.0f);   
        glVertex3f(-2.2, 2.3f, -1.0f);   
    glEnd();

    //Olho mágico
    centroX = -1.90f, centroY = -0.65f, raio = 0.06f;
    numLados = 100;

    glColor3f(0.7f, 0.85f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(centroX, centroY, -1.0f);
        for(int i = 0; i <= numLados; i++){
            float angulo = 2.0f * M_PI * i/numLados;
            float x = centroX + raio * cos(angulo);
            float y = centroY + raio * sin(angulo);
            glVertex3f(x, y, 0.3f);
        }
        glEnd();

    //Maçaneta
    centroX = -1.75f, centroY = -1.0f, raio = 0.085f;
    numLados = 100;

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(centroX, centroY, -1.0f);
        for(int i = 0; i <= numLados; i++){
            float angulo = 2.0f * M_PI * i/numLados;
            float x = centroX + raio * cos(angulo);
            float y = centroY + raio * sin(angulo);
            glVertex3f(x, y, 0.3f);
        }
        glEnd();

    // Porta
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-2.2, -1.6f, -1.0f);   
        glVertex3f(-1.6, -1.6f, -1.0f);   
        glVertex3f(-1.6, -0.3f, -1.0f); 
        glVertex3f(-2.2, -0.3f, -1.0f); 
    glEnd();

    // Janela frente
    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_QUADS);   
        glVertex3f(-3.0, -1.0f, -1.0f); 
        glVertex3f(-2.5, -1.0f, -1.0f);  
        glVertex3f(-2.5, -0.5f, -1.0f); 
        glVertex3f(-3.0, -0.5f, -1.0f); 
    glEnd();

    // Parede da frente
    glColor3f(0.70f, 0.50f, 0.35f);
    glBegin(GL_QUADS);
        glVertex3f(-3.2, -1.6f, -1.0f);   
        glVertex3f(-1.2, -1.6f, -1.0f);   
        glVertex3f(-1.2, 0.4f, -1.0f); 
        glVertex3f(-3.2, 0.4f, -1.0f); 
    glEnd();

    // Janela esquerda
    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_QUADS);   
        glVertex3f(-0.5, -0.9f, -1.0f); 
        glVertex3f(0.2, -0.9f, -1.0f);  
        glVertex3f(0.2, -0.4f, -1.0f); 
        glVertex3f(-0.5, -0.4f, -1.0f); 
    glEnd();

    // Janela direita
    glColor3f(0.9f, 0.95f, 1.0f);
    glBegin(GL_QUADS);   
        glVertex3f(1.5, -0.9f, -1.0f); 
        glVertex3f(2.2, -0.9f, -1.0f);  
        glVertex3f(2.2, -0.4f, -1.0f); 
        glVertex3f(1.5, -0.4f, -1.0f); 
    glEnd();

    // Parede lateral
    glColor3f(0.9f, 0.7f, 0.50f);
    glBegin(GL_QUADS);   
        glVertex3f(-1.2, -1.6f, -1.0f); 
        glVertex3f(2.8, -1.6f, -1.0f);  
        glVertex3f(2.8, 0.4f, -1.0f); 
        glVertex3f(-1.2, 0.4f, -1.0f); 
    glEnd();

    // Quadrado chaminé
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_QUADS);   
        glVertex3f(0.3, 2.3f, -1.0f); 
        glVertex3f(0.9, 2.3f, -1.0f);  
        glVertex3f(0.9, 2.7f, -1.0f); 
        glVertex3f(0.3, 2.7f, -1.0f); 
    glEnd();

    // Retângulo chaminé
    glColor3f(0.8f, 0.5f, 0.3f);
    glBegin(GL_QUADS);   
        glVertex3f(0.045, 2.7f, -1.0f); 
        glVertex3f(1.15, 2.7f, -1.0f);  
        glVertex3f(1.15, 3.0f, -1.0f); 
        glVertex3f(0.045, 3.0f, -1.0f); 
    glEnd();

    // Sol
    centroX = 4.0f, centroY = 4.0f, raio = 1.0f;
    numLados = 100;

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(centroX, centroY, -1.0f);
        for(int i = 0; i <= numLados; i++){
            float angulo = 2.0f * M_PI * i/numLados;
            float x = centroX + raio * cos(angulo);
            float y = centroY + raio * sin(angulo);
            glVertex3f(x, y, 0.3f);
        }
        glEnd();
    
    // Caminho de pedras
    glColor3f(0.6f, 0.6f, 0.6f); 
    float startY = -2.8f;
    float step = 0.3f; 

    for (int i = 0; i < 5; ++i) {
        glBegin(GL_QUADS);
            glVertex3f(-2.1f, startY + i * step, -1.0f);
            glVertex3f(-1.7f, startY + i * step, -1.0f);
            glVertex3f(-1.7f, startY + i * step + 0.2f, -1.0f);
            glVertex3f(-2.1f, startY + i * step + 0.2f, -1.0f);
        glEnd();
    }

    // Caminho até a porta
    glColor3f(0.7f, 0.7f, 0.7f); // cinza claro para o caminho
    glBegin(GL_QUADS);
        glVertex3f(-2.2f, orthoBottom, -1.0f); // canto inferior esquerdo
        glVertex3f(-1.6f, orthoBottom, -1.0f); // canto inferior direito
        glVertex3f(-1.6f, -1.6f, -1.0f); // canto superior direito
        glVertex3f(-2.2f, -1.6f, -1.0f); // canto superior esquerdo
    glEnd();

    // Cor do chão (verde)
    glColor3f(0.5f, 0.8f, 0.3f); 
    glBegin(GL_QUADS);
        glVertex3f(orthoLeft, -0.4f, -1.0f);
        glVertex3f(orthoRight, -0.4f, -1.0f);
        glVertex3f(orthoRight, orthoBottom, -1.0f);
        glVertex3f(orthoLeft, orthoBottom, -1.0f);
    glEnd();

    //Fumaça
    centroX = 0.95f + smokeOffset;
    centroY = 3.45f;
    raio = 0.5f;
    numLados = 100;

    for(int j = 0; j < 3; j++){
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(centroX, centroY, -1.0f);
            for(int i = 0; i <= numLados; i++){
                float angulo = 2.0f * M_PI * i / numLados;
                float x = centroX + raio * cos(angulo);
                float y = centroY + raio * sin(angulo);
                glVertex3f(x, y, 0.3f);
            }
        glEnd();
        centroX += 0.5f;
        centroY += 0.1f;
    }

    // Nuvem
    centroX = -4.0f, centroY = 3.6f, raio = 0.5f;
    numLados = 100;
    
    for(int j = 0; j < 4; j++){
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(centroX, centroY, -1.0f);
            for(int i = 0; i <= numLados; i++){
                float angulo = 2.0f * M_PI * i/numLados;
                float x = centroX + raio * cos(angulo);
                float y = centroY + raio * sin(angulo);
                glVertex3f(x, y, 0.3f);
            }
        glEnd();
        centroX += 0.45f;
        centroY += 0.1f;
    }
    
    centroX = -3.8f, centroY = 3.45f, raio = 0.5f;
    numLados = 100;
    
    for(int j = 0; j < 3; j++){
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(centroX, centroY, -1.0f);
            for(int i = 0; i <= numLados; i++){
                float angulo = 2.0f * M_PI * i/numLados;
                float x = centroX + raio * cos(angulo);
                float y = centroY + raio * sin(angulo);
                glVertex3f(x, y, 0.3f);
            }
        glEnd();
        centroX += 0.45f;
        centroY += 0.1f;
    }

    // Atualiza deslocamento da fumaça
    if (frameCount % 20 == 0) { // ajusta esse valor para controlar a velocidade
        smokeOffset += 0.1f * smokeDirection;

        if (smokeOffset >= 0.4f) { 
            smokeDirection = -1;
        } else if (smokeOffset <= 0.0f) {
            smokeDirection = 1;
        }
    }
    frameCount++;

    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}

int main(int argc, char **argv){ 
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    glutInitWindowSize(800, 800);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(100, 0);  

    /* Open a window */  
    window = glutCreateWindow("Casa");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(&DrawGLScene);  

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(&DrawGLScene);

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Initialize our window. */
    InitGL(640, 600);
    
    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}