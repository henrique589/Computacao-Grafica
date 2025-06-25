#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

int windowWidth = 800, windowHeight = 600;
float rectWidth = 400.0f, rectHeight = 300.0f;

#define INSIDE 0 // 0000
#define LEFT   1 // 0001
#define RIGHT  2 // 0010
#define BOTTOM 4 // 0100
#define TOP    8 // 1000

// Retângulo de recorte
float centerX, centerY;
float left, right, bottom, top;

int computeOutCode(float x, float y) {
    int code = INSIDE;
    if (x < left)   code |= LEFT;
    else if (x > right)  code |= RIGHT;
    if (y < bottom) code |= BOTTOM;
    else if (y > top)    code |= TOP;
    return code;
}

// Cohen-Sutherland
int cohenSutherlandClip(float x0, float y0, float x1, float y1, float* nx0, float* ny0, float* nx1, float* ny1) {
    int outcode0 = computeOutCode(x0, y0);
    int outcode1 = computeOutCode(x1, y1);
    int accept = 0;

    while (1) {
        if (!(outcode0 | outcode1)) {
            accept = 1;
            break;
        } else if (outcode0 & outcode1) {
            break;
        } else {
            float x, y;
            int outcodeOut = outcode0 ? outcode0 : outcode1;

            if (outcodeOut & TOP) {
                x = x0 + (x1 - x0) * (top - y0) / (y1 - y0);
                y = top;
            } else if (outcodeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (bottom - y0) / (y1 - y0);
                y = bottom;
            } else if (outcodeOut & RIGHT) {
                y = y0 + (y1 - y0) * (right - x0) / (x1 - x0);
                x = right;
            } else if (outcodeOut & LEFT) {
                y = y0 + (y1 - y0) * (left - x0) / (x1 - x0);
                x = left;
            }

            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    }

    if (accept) {
        *nx0 = x0; *ny0 = y0;
        *nx1 = x1; *ny1 = y1;
        return 1;
    }

    return 0;
}

void drawClippedLine(float x0, float y0, float x1, float y1) {
    float cx0, cy0, cx1, cy1;
    int accepted = cohenSutherlandClip(x0, y0, x1, y1, &cx0, &cy0, &cx1, &cy1);

    // Parte fora (vermelha)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(cx0, cy0);
        glVertex2f(x1, y1);
        glVertex2f(cx1, cy1);
    glEnd();

    // Parte dentro (azul)
    if (accepted) {
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_LINES);
            glVertex2f(cx0, cy0);
            glVertex2f(cx1, cy1);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    centerX = windowWidth / 2.0f;
    centerY = windowHeight / 2.0f;
    left = centerX - rectWidth / 2.0f;
    right = centerX + rectWidth / 2.0f;
    bottom = centerY - rectHeight / 2.0f;
    top = centerY + rectHeight / 2.0f;

    glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
    glEnd();

    glLineWidth(1.0f);
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        float x0 = rand() % windowWidth;
        float y0 = rand() % windowHeight;
        float x1 = rand() % windowWidth;
        float y1 = rand() % windowHeight;
        drawClippedLine(x0, y0, x1, y1);
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Retângulo base de recorte - Cohen-Sutherland");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
    glutMainLoop();
    return 0;
}
