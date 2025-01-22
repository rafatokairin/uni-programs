#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

void bresenham_circle(int cx, int cy, int r) {
    int x = r;
    int y = 0;
    int p = 1 - r; // Valor inicial da variável p

    while (x >= y) {
        glBegin(GL_POINTS);
        glVertex2i(cx + x, cy + y);
        glVertex2i(cx + y, cy + x);
        glVertex2i(cx - y, cy + x);
        glVertex2i(cx - x, cy + y);
        glVertex2i(cx - x, cy - y);
        glVertex2i(cx - y, cy - x);
        glVertex2i(cx + y, cy - x);
        glVertex2i(cx + x, cy - y);
        glEnd();

        y++;

        // Testa o valor de p para decidir o próximo ponto
        if (p <= 0) {
            p += 2 * y + 1;
        } else {
            x--;
            p += 2 * (y - x) + 1;
        }
    }
}

void desenha() {
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    bresenham_circle(320, 240, 100); // Centro da circunferência e raio
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Bresenham Circle Algorithm", NULL, NULL);
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
