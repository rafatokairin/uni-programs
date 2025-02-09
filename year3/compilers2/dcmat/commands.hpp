#ifndef DCMAT_HPP
#define DCMAT_HPP
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
#include "hash.hpp"

Matrix* setMatrix(Matrix* matrixLine, Matrix* matrixColum);

Matrix* setMatrixColum(Matrix* matrixColum, Matrix* matrixLine);

Matrix* setMatrixLine(int limit, Matrix* matrixValue);

Matrix* setMatrixValue(Matrix* matrixValue, int limit);

Expr* handleIdentifier(char* id);

Expr* unaryOperation(Expr* expr, int opType);

Expr* negateMatrix(Expr* expr);

Expr* negateTerm(Expr* expr);

std::string getKwName(int opType);

void showSettings();

void resetSettings();

void plotAxis(Expr *expr);

void showMatrix(Matrix *matrix);

void solveLinearSystem(Matrix *matrix);

void integrate(float superior, float inferior, Expr *expr);

void sum(float inferior, float superior, Expr *expr);

void solveRPN(Expr *expr);

void showAbout();

void setFloatPrecision(int value);

void setHView(float lo, float hi);

void setVView(float lo, float hi);

void setIntegralSteps(int steps);

void clearMemory();

void handleShowMatrix();

void identifier(char* identifier);

void assignmentExpr(char* identifier, Expr* expr);

void assignmentMatrix(char* identifier, Matrix* matrix);

void matrixEqual(Matrix* newMatrix);

void handleSolveDeterminant();

void handleSolveLinearSystem();

void handleExpr(Expr* expr);

void plotExpr(Expr* expr);

void handlePlot();

void handleIntegrate(float lower, float upper, Expr* expr);

void handleSum(char* identifier, float lower, float upper, Expr* expr);

void handleRPN(Expr* expr);

void undefinedSymbol();

float determinantAux(std::vector<std::vector<float>> matrix);

float solveDeterminant(Matrix *matrix);

int lengthValue(int number);

#endif