#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

// Variáveis globais
float quadradoX = 0.0f; 
float quadradoY = 0.0f; 
float corR = 1.0f, corG = 1.0f, corB = 1.0f;

// Tamanho do quadrado
const float tamanho = 0.2f;

// Função para desenhar o quadrado
void desenhaQuadrado() {
    glColor3f(corR, corG, corB); // Define a cor atual
    glBegin(GL_QUADS);           
        glVertex2f(quadradoX - tamanho, quadradoY - tamanho);
        glVertex2f(quadradoX + tamanho, quadradoY - tamanho);
        glVertex2f(quadradoX + tamanho, quadradoY + tamanho);
        glVertex2f(quadradoX - tamanho, quadradoY + tamanho);
    glEnd();
}

// Função para redesenhar a tela
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela
    desenhaQuadrado();            // Desenha o quadrado
    glutSwapBuffers();            // Troca os buffers para exibir o resultado
}

// Função para processar as teclas de movimento
void tecladoEspecial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_UP:
            quadradoY += 0.05f;
            break;
        case GLUT_KEY_DOWN:
            quadradoY -= 0.05f;
            break;
        case GLUT_KEY_LEFT:
            quadradoX -= 0.05f;
            break;
        case GLUT_KEY_RIGHT:
            quadradoX += 0.05f;
            break;
    }
    glutPostRedisplay(); // Redesenha a tela
}

// Função para processar clique
void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        // Gera cor aleatória
        corR = (float)rand() / RAND_MAX;
        corG = (float)rand() / RAND_MAX;
        corB = (float)rand() / RAND_MAX;
        glutPostRedisplay(); // Redesenha a tela
    }
}

// Configura a janela de visualização
void inicializaOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Cor de fundo
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define o sistema de coordenadas
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Quadrado OpenGL");
    inicializaOpenGL();
    glutDisplayFunc(display);
    glutSpecialFunc(tecladoEspecial);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}