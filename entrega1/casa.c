#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.

/* The number of our GLUT window */
int window; 

void InitGL(int Width, int Height){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
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

void ReSizeGLScene(int Width, int Height){
    if (Height == 0)				// Prevent A Divide By Zero If The Window Is Too Small
        Height = 1;

    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Adjust the orthogonal projection to match the new window size
    glOrtho(-Width / 200.0f, Width / 200.0f, -Height / 200.0f, Height / 200.0f, 0.1f, 100.0f);
    //x de -3.2 até +3.2
    //y de -2.4 até +2.4
    //z de 0.1 até 100.0
    glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
    glLoadIdentity();				// Reset The View

    // Telhado paralelogramo aumentado
    glColor3f(0.3, 0.5, 0.8);
    glBegin(GL_POLYGON);
        glVertex3f(-1.2, 0.4f, -1.0f);
        glVertex3f(2.8, 0.4f, -1.0f);
        glVertex3f(1.8, 2.3f, -1.0f);    
        glVertex3f(-2.2, 2.3f, -1.0f);
    glEnd();

    // Telhado triângulo aumentado
    glColor3f(0.1, 0.5, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(-3.2, 0.4f, -1.0f);   
        glVertex3f(-1.2, 0.4f, -1.0f);   
        glVertex3f(-2.2, 2.3f, -1.0f);   
    glEnd();

    // Parede da frente
    glColor3f(0.7, 0.2, 0.3);
    glBegin(GL_QUADS);
        glVertex3f(-3.2, -1.6f, -1.0f);   
        glVertex3f(-1.2, -1.6f, -1.0f);   
        glVertex3f(-1.2, 0.4f, -1.0f); 
        glVertex3f(-3.2, 0.4f, -1.0f); 
    glEnd();

    // Parede lateral
    glColor3f(0.1, 0.2, 0.3);
    glBegin(GL_QUADS);   
        glVertex3f(-1.2, -1.6f, -1.0f); 
        glVertex3f(2.8, -1.6f, -1.0f);  
        glVertex3f(2.8, 0.4f, -1.0f); 
        glVertex3f(-1.2, 0.4f, -1.0f); 
    glEnd();

    // Quadrado chaminé
    glColor3f(0.4, 0.2, 0.1);
    glBegin(GL_QUADS);   
        glVertex3f(0.0, 2.3f, -1.0f); 
        glVertex3f(0.8, 2.3f, -1.0f);  
        glVertex3f(0.8, 3.1f, -1.0f); 
        glVertex3f(0.0, 3.1f, -1.0f); 
    glEnd();

    // Retângulo chaminé
    glColor3f(0.1, 0.5, 0.2);
    glBegin(GL_QUADS);   
        glVertex3f(-0.3, 3.1f, -1.0f); 
        glVertex3f(1.1, 3.1f, -1.0f);  
        glVertex3f(1.1, 3.5f, -1.0f); 
        glVertex3f(-0.3, 3.5f, -1.0f); 
    glEnd();

    // since this is double buffered, swap the buffers to display what just got drawn.
    glutSwapBuffers();
}

int main(int argc, char **argv){ 
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

    glutInitWindowSize(800, 800);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(100, 100);  

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