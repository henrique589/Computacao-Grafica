
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int win_id;

#define MAX_VERTICES 100000
#define MAX_NORMALS  100000
#define MAX_FACES    100000

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    int v[3];   // índices dos vértices
    int vn[3];  // índices das normais 
} Face;

Vec3 vertices[MAX_VERTICES];
Vec3 normals[MAX_NORMALS];
Face faces[MAX_FACES];
int vertex_count = 0, normal_count = 0, face_count = 0;

Vec3 min_bounds = {1e9, 1e9, 1e9};
Vec3 max_bounds = {-1e9, -1e9, -1e9};

void carregarOBJ(const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, "v ", 2) == 0) {
            Vec3 v;
            sscanf(linha + 2, "%f %f %f", &v.x, &v.y, &v.z);
            vertices[vertex_count++] = v;
            if (v.x < min_bounds.x) min_bounds.x = v.x;
            if (v.y < min_bounds.y) min_bounds.y = v.y;
            if (v.z < min_bounds.z) min_bounds.z = v.z;
            if (v.x > max_bounds.x) max_bounds.x = v.x;
            if (v.y > max_bounds.y) max_bounds.y = v.y;
            if (v.z > max_bounds.z) max_bounds.z = v.z;
        } else if (strncmp(linha, "vn ", 3) == 0) {
            Vec3 n;
            sscanf(linha + 3, "%f %f %f", &n.x, &n.y, &n.z);
            normals[normal_count++] = n;
        } else if (strncmp(linha, "f ", 2) == 0) {
            Face f;
            int v[3], vt[3], vn[3];
            for (int i = 0; i < 3; i++) { vt[i] = -1; vn[i] = -1; }

            int campos = sscanf(linha + 2, "%d/%d/%d %d/%d/%d %d/%d/%d",
                &v[0], &vt[0], &vn[0],
                &v[1], &vt[1], &vn[1],
                &v[2], &vt[2], &vn[2]);

            if (campos != 9) {
                campos = sscanf(linha + 2, "%d//%d %d//%d %d//%d",
                    &v[0], &vn[0],
                    &v[1], &vn[1],
                    &v[2], &vn[2]);

                if (campos != 6) {
                    campos = sscanf(linha + 2, "%d %d %d", &v[0], &v[1], &v[2]);
                    vn[0] = vn[1] = vn[2] = -1;
                }
            }

            for (int i = 0; i < 3; i++) {
                f.v[i] = v[i] - 1;
                f.vn[i] = vn[i] - 1;
            }
            faces[face_count++] = f;
        }
    }
    fclose(file);
    printf("Carregado: %d vértices, %d normais, %d faces\n", vertex_count, normal_count, face_count);
}

void desenhaModelo() {
    Vec3 centro = {
        (min_bounds.x + max_bounds.x) / 2,
        (min_bounds.y + max_bounds.y) / 2,
        (min_bounds.z + max_bounds.z) / 2
    };

    float tamX = max_bounds.x - min_bounds.x;
    float tamY = max_bounds.y - min_bounds.y;
    float tamZ = max_bounds.z - min_bounds.z;
    float maxTam = fmax(fmax(tamX, tamY), tamZ);
    float escala = 2.0f / maxTam;

    glPushMatrix();
    glScalef(escala, escala, escala);
    glTranslatef(-centro.x, -centro.y, -centro.z);

    glColor3f(1.0f, 0.6f, 0.0f); 

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < face_count; i++) {
        for (int j = 0; j < 3; j++) {
            if (faces[i].vn[j] >= 0) {
                Vec3 n = normals[faces[i].vn[j]];
                glNormal3f(n.x, n.y, n.z);
            }
            Vec3 v = vertices[faces[i].v[j]];
            glVertex3f(v.x, v.y, v.z);
        }
    }
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0,   // olho (distância aumentada)
              0.0, 0.0, 0.0,    // centro
              0.0, 1.0, 0.0);   // cima

    desenhaModelo();
    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {3.0f, 3.0f, 3.0f, 1.0f}; 
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    carregarOBJ("modelo.obj"); 
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Visualizador OBJ");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}