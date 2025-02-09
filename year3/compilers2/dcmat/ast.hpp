#define AST_HPP
#ifdef AST_HPP
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <math.h>
#include <cstdlib>
#include <cmath>

enum Kw {
    VARKW,
    SUBVARKW,
    INTKW,
    FLOATKW,
    MATRIXKW,
    IDKW,
    FUNCKW,
    EXPRKW,
    ADDKW,
    SUBKW,
    MULKW,
    DIVKW,
    POWKW,
    RESTKW,
    SENKW,
    COSKW,
    TANKW,
    ABSKW,
    EXPKW,
    OPKW,
};

struct Matrix {
    std::vector<float> line;
    std::vector<std::vector<float>> matrix;
    int lines;
    int columns;
};

struct Expr {
    Matrix* matrix;
    Expr* left;
    Expr* right;
    Expr* expr;
    std::string id;
    float value;
    int element;
    int type;
    int func;
};

Expr *AST(int func, Expr *termo, Expr *expr);

Expr* createNode(int type, int func, float value, Expr* expr, int element = EXPRKW, std::string name = "nullptr");

Expr *createMatrix(Matrix *matrix);

float var(float x, Expr *expr);

float solveFunc(float x, Expr *expr);

void removeExpr(Expr *expr);

#endif