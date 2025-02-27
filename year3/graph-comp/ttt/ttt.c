#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Declaração das funções
void initOpenGL();
void drawScene();
void drawBoard();
void drawPieces();
void draw3DX(float centerX, float centerZ);
void draw3DO(float centerX, float centerZ);
void drawBox(float w, float h, float d);
void drawTorus(float R, float r, int numMajor, int numMinor);
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods);
int checkWin();
void drawWinningBar(int row, int col, int direction);

// Variáveis para animação da vitória
int winningRow = -1, winningCol = -1, winningDirection = -1;
float winningProgress = 0.0f; // varia de 0.0 a 1.0
int animatingWin = 0;         // flag para saber se a animação está em andamento

// definições do tabuleiro
#define BOARD_SIZE 3
#define CELL_SIZE 1.0f
#define BOARD_EXTENT ((BOARD_SIZE * CELL_SIZE) / 2.0f)

// estados do tabuleiro: 0 = vazio, 1 = X, 2 = O
int board[BOARD_SIZE][BOARD_SIZE] = {{0}};
int currentTurn = 1; // 1 = X (vermelho), 2 = O (azul)
int gameOver = 0;    // flag para indicar se o jogo terminou

void initOpenGL() {
  // ativa teste de profundidade
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);

  // cor de fundo (azul opaco)
  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

  // ativa iluminação e normalização
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  // parâmetros da luz
  GLfloat lightPos[] = {0.0f, 10.0f, 10.0f, 1.0f};
  GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

  // permite controle de cor dos materiais via glColor()
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // configura a projeção
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 800.0 / 600.0, 1.0, 50.0);
  glMatrixMode(GL_MODELVIEW);
}

void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0.0, 5.0, 5.0,  // posição da câmera
            0.0, 0.0, 0.0,  // para onde a câmera aponta
            0.0, 1.0, 0.0); // vetor "up"

  drawBoard();
  drawPieces();

  if (gameOver && winningDirection != -1) {
    drawWinningBar(winningRow, winningCol, winningDirection);
  }
}

void drawBoard() {
  // fundo do tabuleiro (cinza)
  glColor3f(0.7f, 0.7f, 0.7f);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-BOARD_EXTENT, 0.0f, -BOARD_EXTENT);
  glVertex3f(BOARD_EXTENT, 0.0f, -BOARD_EXTENT);
  glVertex3f(BOARD_EXTENT, 0.0f, BOARD_EXTENT);
  glVertex3f(-BOARD_EXTENT, 0.0f, BOARD_EXTENT);
  glEnd();

  // linhas da grade (preto)
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  // linhas verticais
  for (int i = 1; i < BOARD_SIZE; i++) {
    float x = -BOARD_EXTENT + i * CELL_SIZE;
    glVertex3f(x, 0.01f, -BOARD_EXTENT);
    glVertex3f(x, 0.01f, BOARD_EXTENT);
  }
  // linhas horizontais
  for (int i = 1; i < BOARD_SIZE; i++) {
    float z = -BOARD_EXTENT + i * CELL_SIZE;
    glVertex3f(-BOARD_EXTENT, 0.01f, z);
    glVertex3f(BOARD_EXTENT, 0.01f, z);
  }
  glEnd();
}

void drawPieces() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      // calcula o centro da célula
      float centerX = -BOARD_EXTENT + (j + 0.5f) * CELL_SIZE;
      float centerZ = BOARD_EXTENT - (i + 0.5f) * CELL_SIZE;

      if (board[i][j] == 1) {
        // desenha X (vermelho)
        glColor3f(1.0f, 0.0f, 0.0f);
        draw3DX(centerX, centerZ);
      } else if (board[i][j] == 2) {
        // desenha O (azul)
        glColor3f(0.0f, 0.0f, 1.0f);
        draw3DO(centerX, centerZ);
      }
    }
  }
}

void drawBox(float w, float h, float d) {
  float hw = w / 2.0f;
  float hh = h / 2.0f;
  float hd = d / 2.0f;

  glBegin(GL_QUADS);
  // face frontal
  glNormal3f(0.0f, 0.0f, 1.0f);
  glVertex3f(-hw, -hh, hd);
  glVertex3f(hw, -hh, hd);
  glVertex3f(hw, hh, hd);
  glVertex3f(-hw, hh, hd);

  // face traseira
  glNormal3f(0.0f, 0.0f, -1.0f);
  glVertex3f(-hw, -hh, -hd);
  glVertex3f(-hw, hh, -hd);
  glVertex3f(hw, hh, -hd);
  glVertex3f(hw, -hh, -hd);

  // face esquerda
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(-hw, -hh, -hd);
  glVertex3f(-hw, -hh, hd);
  glVertex3f(-hw, hh, hd);
  glVertex3f(-hw, hh, -hd);

  // face direita
  glNormal3f(1.0f, 0.0f, 0.0f);
  glVertex3f(hw, -hh, -hd);
  glVertex3f(hw, hh, -hd);
  glVertex3f(hw, hh, hd);
  glVertex3f(hw, -hh, hd);

  // face superior
  glNormal3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-hw, hh, -hd);
  glVertex3f(-hw, hh, hd);
  glVertex3f(hw, hh, hd);
  glVertex3f(hw, hh, -hd);

  // face inferior
  glNormal3f(0.0f, -1.0f, 0.0f);
  glVertex3f(-hw, -hh, -hd);
  glVertex3f(hw, -hh, -hd);
  glVertex3f(hw, -hh, hd);
  glVertex3f(-hw, -hh, hd);
  glEnd();
}

void drawTorus(float R, float r, int numMajor, int numMinor) {
  float uStep = 2.0f * M_PI / numMajor;
  float vStep = 2.0f * M_PI / numMinor;
  for (int i = 0; i < numMajor; i++) {
    float u0 = i * uStep;
    float u1 = (i + 1) * uStep;
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= numMinor; j++) {
      float v = j * vStep;
      float cosV = cosf(v);
      float sinV = sinf(v);
      // vértice com ângulo u0
      float cosU0 = cosf(u0);
      float sinU0 = sinf(u0);
      float x = (R + r * cosV) * cosU0;
      float y = r * sinV;
      float z = (R + r * cosV) * sinU0;
      glNormal3f(cosU0 * cosV, sinV, sinU0 * cosV);
      glVertex3f(x, y, z);

      // vértice com ângulo u1
      float cosU1 = cosf(u1);
      float sinU1 = sinf(u1);
      x = (R + r * cosV) * cosU1;
      y = r * sinV;
      z = (R + r * cosV) * sinU1;
      glNormal3f(cosU1 * cosV, sinV, sinU1 * cosV);
      glVertex3f(x, y, z);
    }
    glEnd();
  }
}

void draw3DX(float centerX, float centerZ) {
  float barLength = 1.2f;
  float barWidth = 0.2f;
  float barHeight = 0.2f;
  float yOffset = barHeight / 2.0f;

  glPushMatrix();
  glTranslatef(centerX, yOffset, centerZ);

  // primeira barra (rotacionada 45°)
  glPushMatrix();
  glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
  drawBox(barLength, barHeight, barWidth);
  glPopMatrix();

  // segunda barra (rotacionada -45°)
  glPushMatrix();
  glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
  drawBox(barLength, barHeight, barWidth);
  glPopMatrix();
  glPopMatrix();
}

void draw3DO(float centerX, float centerZ) {
  float R = 0.35f; // raio maior
  float r = 0.1f;  // raio do tubo
  int numMajor = 30;
  int numMinor = 20;
  glPushMatrix();
  // desloca o toro para ficar sobre o tabuleiro
  glTranslatef(centerX, r, centerZ);
  drawTorus(R, r, numMajor, numMinor);
  glPopMatrix();
}

void drawWinningBar(int row, int col, int direction) {
  glColor3f(0.0f, 1.0f, 0.0f); // verde

  // Parâmetros da barra
  float thickness = 0.1f; // Largura da barra (pode ajustar)
  float yTop = 0.1f;      // Altura superior
  float yBottom = 0.3f;   // Altura inferior

  // Calcula o início e fim da reta central, de acordo com a direção
  float startX, startZ, endX, endZ;
  switch (direction) {
  case 0: // Linha horizontal
    startX = -BOARD_EXTENT + col * CELL_SIZE;
    startZ = BOARD_EXTENT - row * CELL_SIZE - CELL_SIZE / 2;
    endX = startX + 3 * CELL_SIZE * winningProgress;
    endZ = startZ; // mesma linha horizontal
    break;
  case 1: // Coluna vertical
    startX = -BOARD_EXTENT + col * CELL_SIZE + CELL_SIZE / 2;
    startZ = BOARD_EXTENT - row * CELL_SIZE;
    endX = startX; // mesma coluna
    endZ = startZ - 3 * CELL_SIZE * winningProgress;
    break;
  case 2: // Diagonal principal
    startX = -BOARD_EXTENT;
    startZ = BOARD_EXTENT;
    endX = startX + 3 * CELL_SIZE * winningProgress;
    endZ = startZ - 3 * CELL_SIZE * winningProgress;
    break;
  case 3: // Diagonal secundária
    startX = -BOARD_EXTENT + 3 * CELL_SIZE;
    startZ = BOARD_EXTENT;
    endX = startX - 3 * CELL_SIZE * winningProgress;
    endZ = startZ - 3 * CELL_SIZE * winningProgress;
    break;
  }

  // Calcula o vetor da reta vencedora e seu perpendicular (no plano XZ)
  float dx = endX - startX;
  float dz = endZ - startZ;
  float len = sqrt(dx * dx + dz * dz);
  float offsetX = 0.0f, offsetZ = 0.0f;
  if (len > 0.0001f) {
    // Vetor perpendicular normalizado:
    offsetX = -dz / len * (thickness / 2.0f);
    offsetZ = dx / len * (thickness / 2.0f);
  }

  // Define os 8 vértices do paralelepípedo (barra vencedora)
  // Vértices do topo
  float v0[3] = {startX + offsetX, yTop, startZ + offsetZ};
  float v1[3] = {startX - offsetX, yTop, startZ - offsetZ};
  float v2[3] = {endX - offsetX, yTop, endZ - offsetZ};
  float v3[3] = {endX + offsetX, yTop, endZ + offsetZ};

  // Vértices da base
  float v4[3] = {startX + offsetX, yBottom, startZ + offsetZ};
  float v5[3] = {startX - offsetX, yBottom, startZ - offsetZ};
  float v6[3] = {endX - offsetX, yBottom, endZ - offsetZ};
  float v7[3] = {endX + offsetX, yBottom, endZ + offsetZ};

  glBegin(GL_QUADS);
  // Face superior (topo)
  glVertex3f(v0[0], yTop, v0[2]);
  glVertex3f(v1[0], yTop, v1[2]);
  glVertex3f(v2[0], yTop, v2[2]);
  glVertex3f(v3[0], yTop, v3[2]);

  // Face inferior (base)
  glVertex3f(v4[0], yBottom, v4[2]);
  glVertex3f(v5[0], yBottom, v5[2]);
  glVertex3f(v6[0], yBottom, v6[2]);
  glVertex3f(v7[0], yBottom, v7[2]);

  // Lado 1
  glVertex3f(v0[0], yTop, v0[2]);
  glVertex3f(v3[0], yTop, v3[2]);
  glVertex3f(v7[0], yBottom, v7[2]);
  glVertex3f(v4[0], yBottom, v4[2]);

  // Lado 2
  glVertex3f(v1[0], yTop, v1[2]);
  glVertex3f(v0[0], yTop, v0[2]);
  glVertex3f(v4[0], yBottom, v4[2]);
  glVertex3f(v5[0], yBottom, v5[2]);

  // Lado 3
  glVertex3f(v2[0], yTop, v2[2]);
  glVertex3f(v1[0], yTop, v1[2]);
  glVertex3f(v5[0], yBottom, v5[2]);
  glVertex3f(v6[0], yBottom, v6[2]);

  // Lado 4
  glVertex3f(v3[0], yTop, v3[2]);
  glVertex3f(v2[0], yTop, v2[2]);
  glVertex3f(v6[0], yBottom, v6[2]);
  glVertex3f(v7[0], yBottom, v7[2]);
  glEnd();
}

void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods) {
  if (gameOver)
    return;

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double modelview[16], projection[16];
    int viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    double winX = mouseX;
    double winY = viewport[3] - mouseY;

    double nearPoint[3], farPoint[3];
    gluUnProject(winX, winY, 0.0, modelview, projection, viewport,
                 &nearPoint[0], &nearPoint[1], &nearPoint[2]);
    gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &farPoint[0],
                 &farPoint[1], &farPoint[2]);

    double dir[3] = {farPoint[0] - nearPoint[0], farPoint[1] - nearPoint[1],
                     farPoint[2] - nearPoint[2]};

    if (fabs(dir[1]) < 1e-6)
      return;
    double t = -nearPoint[1] / dir[1];
    if (t < 0)
      return;
    double intersect[3] = {nearPoint[0] + t * dir[0], nearPoint[1] + t * dir[1],
                           nearPoint[2] + t * dir[2]};

    if (intersect[0] < -BOARD_EXTENT || intersect[0] > BOARD_EXTENT ||
        intersect[2] < -BOARD_EXTENT || intersect[2] > BOARD_EXTENT)
      return;

    int col = (int)((intersect[0] + BOARD_EXTENT) / CELL_SIZE);
    int row = (int)((BOARD_EXTENT - intersect[2]) / CELL_SIZE);

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
      if (board[row][col] == 0) {
        board[row][col] = currentTurn; // Registra a jogada

        int winner = checkWin();
        if (winner != 0) {
          printf("Jogador %s venceu!\n", (winner == 1) ? "X" : "O");
          gameOver = 1;
        } else {
          currentTurn = (currentTurn == 1) ? 2 : 1;
        }
      }
    }
  }
}

int checkWin(void) {
  int i;
  for (i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] != 0 && board[i][0] == board[i][1] &&
        board[i][1] == board[i][2]) {
      winningRow = i;
      winningCol = 0;
      winningDirection = 0;
      gameOver = board[i][0];
      winningProgress = 0.0f;
      animatingWin = 1;
      return board[i][0];
    }
  }
  for (i = 0; i < BOARD_SIZE; i++) {
    if (board[0][i] != 0 && board[0][i] == board[1][i] &&
        board[1][i] == board[2][i]) {
      winningRow = 0;
      winningCol = i;
      winningDirection = 1;
      gameOver = board[0][i];
      winningProgress = 0.0f;
      animatingWin = 1;
      return board[0][i];
    }
  }
  if (board[0][0] != 0 && board[0][0] == board[1][1] &&
      board[1][1] == board[2][2]) {
    winningRow = 0;
    winningCol = 0;
    winningDirection = 2;
    gameOver = board[0][0];
    winningProgress = 0.0f;
    animatingWin = 1;
    return board[0][0];
  }
  if (board[0][2] != 0 && board[0][2] == board[1][1] &&
      board[1][1] == board[2][0]) {
    winningRow = 0;
    winningCol = 2;
    winningDirection = 3;
    gameOver = board[0][2];
    winningProgress = 0.0f;
    animatingWin = 1;
    return board[0][2];
  }
  return 0;
}

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "Erro ao inicializar GLFW!\n");
    exit(EXIT_FAILURE);
  }

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Jogo da Velha 3D", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Erro ao criar janela!\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSwapInterval(1);
  initOpenGL();

  // Loop principal
  while (!glfwWindowShouldClose(window)) {
    // Atualiza a animação da vitória, se ativa
    if (animatingWin) {
      winningProgress += 0.01f;
      if (winningProgress > 1.0f) {
        winningProgress = 1.0f;
        animatingWin = 0;
      }
    }

    drawScene();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}