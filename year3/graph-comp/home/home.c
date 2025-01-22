#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


void desenha() {
    // Casa (quadrado cinza)
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glBegin(GL_QUADS);
        glVertex2f(200, 200); // Inferior esquerdo
        glVertex2f(400, 200); // Inferior direito
        glVertex2f(400, 350); // Superior direito
        glVertex2f(200, 350); // Superior esquerdo
    glEnd();

	// Chaminé (retângulo marrom atrás do telhado)
    glColor3f(0.6f, 0.3f, 0.2f); // Marrom
    glBegin(GL_QUADS);
        glVertex2f(220, 360); // Inferior esquerdo
        glVertex2f(250, 360); // Inferior direito
        glVertex2f(250, 460); // Superior direito
        glVertex2f(220, 460); // Superior esquerdo
    glEnd();

    // Telhado (triângulo laranja)
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja
    glBegin(GL_TRIANGLES);
        glVertex2f(200, 350); // Esquerda
        glVertex2f(400, 350); // Direita
        glVertex2f(300, 450); // Topo
    glEnd();

    // Porta (retângulo azul à esquerda)
    glColor3f(0.0f, 1.0f, 1.0f); // Azul
    glBegin(GL_QUADS);
        glVertex2f(250, 200); // Inferior esquerdo
        glVertex2f(300, 200); // Inferior direito
        glVertex2f(300, 295); // Superior direito
        glVertex2f(250, 295); // Superior esquerdo
    glEnd();

    // Janela (quadrado azul à direita)
    glColor3f(0.0f, 1.0f, 1.0f); // Azul
    glBegin(GL_QUADS);
        glVertex2f(320, 265); // Inferior esquerdo
        glVertex2f(380, 265); // Inferior direito
        glVertex2f(380, 325); // Superior direito
        glVertex2f(320, 325); // Superior esquerdo
    glEnd();
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    /* Cria uma nova janela de 640x480 */
    /* O NULL passado como parâmetros indica que a janela não terá uma janela
    de compartilhamento de contexto e que não é criada com um monitor específico. */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Definição do Contexto Atual:
    Torna o contexto OpenGL da janela criada como sendo o contexto atual.
    Quer dizer que qualquer chamada seguinte ao OpenGL irá afetar esta janela. */
    glfwMakeContextCurrent(window);

    /* Configura o viewport e a projeção ortográfica */
    glViewport(0, 0, 640, 480);               // Ajusta o viewport para o tamanho da janela
    glMatrixMode(GL_PROJECTION);              // Muda para a matriz de projeção
    glLoadIdentity();                         // Reseta a matriz de projeção para identidade
    glOrtho(0, 640, 0, 480, -1, 1);           // Define uma projeção ortográfica 2D

    /* Loop de execução da janela enquanto não for fechada */
    while (!glfwWindowShouldClose(window))
    {
        /* Limpeza da tela */
        glClear(GL_COLOR_BUFFER_BIT);

        desenha();

        /* Troca os buffers (Mas veremos mais adiante a importância desta parte) */
        glfwSwapBuffers(window);

        /* Chamada para verificar e processar todos os eventos que ocorreram,
        como entradas do teclado, mouse, ... Isso mantém a janela responsiva. */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}