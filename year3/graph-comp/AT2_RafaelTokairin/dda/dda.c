#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

void DDA(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        glBegin(GL_POINTS);
        glVertex2f(round(x), round(y)); // Desenha o ponto na tela
        glEnd();
        x += xIncrement;
        y += yIncrement;
    }
}

void desenha() {
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    DDA(100, 100, 400, 400); // Ponto inicial e final
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "DDA Line Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        desenha();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
