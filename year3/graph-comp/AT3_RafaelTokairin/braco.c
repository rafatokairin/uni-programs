#include <GLFW/glfw3.h>
#include <cmath>

// Função para desenhar um retângulo colorido
void drawRectangle(float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(-width / 2, 0.0f);
    glVertex2f(width / 2, 0.0f);
    glVertex2f(width / 2, height);
    glVertex2f(-width / 2, height);
    glEnd();
}

int main() {
    // Inicialização do GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Criação da janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Braco Mecanico", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Configuração do sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        // Limpa a tela
        glClear(GL_COLOR_BUFFER_BIT);

        // Obtém o tempo atual para animação
        float time = glfwGetTime();

        // Ângulos de rotação animados usando seno
        float lowerArmAngle = sin(time) * 45.0f; // Ângulo do braço inferior
        float upperArmAngle = sin(time * 1.5f) * 30.0f; // Ângulo do braço superior

        // Desenhar a base fixa
        glPushMatrix();
        drawRectangle(-50.0f, -110.0f, 0.5f, 0.5f, 0.5f);
        glPopMatrix();

        // Desenhar o braço inferior
        glPushMatrix();
        glTranslatef(0.0f, 20.0f, 0.0f); // Move para a posição da base
        glRotatef(lowerArmAngle, 0.0f, 0.0f, 1.0f); // Aplica a rotação animada
        drawRectangle(25.0f, 100.0f, 1.0f, 0.0f, 0.0f); // Retângulo azul

        // Desenhar o braço superior (dependente do braço inferior)
        glTranslatef(0.0f, 140.0f, 0.0f); // Move para o topo do braço inferior
        glRotatef(upperArmAngle, 0.0f, 0.0f, 1.0f); // Aplica a rotação animada
        drawRectangle(25.0f, 100.0f, 0.0f, 0.0f, 1.0f); // Retângulo vermelho

        glPopMatrix();

        // Atualiza o buffer da janela
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finaliza o GLFW
    glfwTerminate();
    return 0;
}
