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
#include "ast.hpp"

Expr *createMatrix(Matrix *matrix){
    Expr *new_expr = new Expr();
    new_expr->type = MATRIXKW;
    new_expr->element = EXPRKW; 
    new_expr->func = OPKW;
    new_expr->left = nullptr;
    new_expr->right = nullptr;
    new_expr->expr = nullptr;
    new_expr->matrix = matrix;
    new_expr->id = "F";
    return new_expr;
}

Expr* createNode(int type, int func, float value, Expr* expr, int element, std::string name) {
    Expr* new_expr = new Expr();
    new_expr->func = func;
    new_expr->value = value;
    new_expr->type = type;
    new_expr->expr = expr;
    new_expr->element = element;
    new_expr->id = name;
    new_expr->left = nullptr;
    new_expr->right = nullptr;
    if (type == VARKW || type == SUBVARKW) 
        new_expr->element = FUNCKW;
    return new_expr;
}

void removeExpr(Expr *expr){
    if (expr == nullptr) 
        return;
    if (expr->expr != nullptr)
        removeExpr(expr->expr);
    if (expr->left != nullptr)
        removeExpr(expr->left);
    if (expr->right != nullptr)
        removeExpr(expr->right);
    delete expr;
    expr = nullptr;
}

float var(float x, Expr *expr) {
    if(expr->func == EXPKW || expr->func == SENKW || expr->func == COSKW || expr->func == TANKW || expr->func == ABSKW) {
        return solveFunc(x, expr);
    }
    switch (expr->type) {
        case VARKW:
            return x;
        case SUBVARKW:
            return -x;
        case IDKW:
            return x;
        default:
            return expr->value;
    }
}

float solveFunc(float x, Expr *expr) {
    Expr *aux = expr;
    float result = 0;           
    if(aux->right != nullptr) {
        result = solveFunc(x, aux->right);
    }
    switch (aux->func) {
        case ADDKW:
            result = solveFunc(x, aux->left) + result;
            break;
        case SUBKW:
            result = solveFunc(x, aux->left) - result;
            break;  
        case DIVKW:
            result = solveFunc(x, aux->left) / result;
            break;
        case MULKW:
            result = solveFunc(x, aux->left) * result;
            break;
        case POWKW:
            result = pow(solveFunc(x, aux->left), result);
            break;
        case SENKW:
            result = sin(solveFunc(x, aux->expr));
            break;
        case COSKW:
            result = cos(solveFunc(x, aux->expr));
            break;
        case TANKW:
            result = tan(solveFunc(x, aux->expr));
            break;
        case ABSKW:
            result = abs(solveFunc(x, aux->expr));
            break;
        case EXPKW:
            result = solveFunc(x, aux->expr);
            break;
        case OPKW:
            return var(x, aux);
    }
    return result;
}

Expr *AST(int func, Expr *termo, Expr *expr){
    Expr *new_expr = new Expr(); 
    Matrix *new_matrix = new Matrix();
    
    if (termo->type == MATRIXKW || expr->type ==MATRIXKW)
        new_expr->type = MATRIXKW;
    else if (termo->type == FLOATKW || expr->type ==FLOATKW)
        new_expr->type = FLOATKW; 
    else
        new_expr->type = INTKW;
            
    new_expr->func = func; 
    new_expr->left = termo; 
    new_expr->right = expr;
    new_expr->expr = nullptr;
    if (termo->element == FUNCKW || expr->element == FUNCKW)
        new_expr->element = FUNCKW;
    else
        new_expr->element = EXPRKW;
    if (termo->type == IDKW || expr->type == IDKW) 
        return new_expr;
    if (termo->type == MATRIXKW || expr->type == MATRIXKW) {
        if (termo->type == IDKW || expr->type == IDKW) 
            return nullptr;
        switch (func) {
            case ADDKW:
                if (termo->type == MATRIXKW && (expr->type == INTKW || expr->type == FLOATKW)) {
                    printf("\nIncorrect type for operator ’+’ - have MATRIX and FLOAT\n\n");
                    return nullptr;
                }
                if (expr->type == MATRIXKW && (termo->type == INTKW || termo->type == FLOATKW)) {
                    printf("\nIncorrect type for operator ’+’ - have FLOAT and MATRIX\n\n");
                    return nullptr;
                }
                if (termo->type != MATRIXKW || expr->type != MATRIXKW)
                    return nullptr;
                if (expr->matrix->lines != termo->matrix->lines || expr->matrix->columns != termo->matrix->columns) {
                    std::cout << "\nIncorrect dimensions for operator ’+’ - have MATRIX ["<< termo->matrix->lines <<"][" << termo->matrix->columns <<"] and MATRIX ["<< expr->matrix->lines <<"][" << expr->matrix->columns << "]\n\n";
                    return nullptr;
                }
                for(int i = 0; i < termo->matrix->lines; i++){
                    for(int j = 0; j < termo->matrix->columns; j++)
                        new_matrix->line.push_back(termo->matrix->matrix[i][j] + expr->matrix->matrix[i][j]);
                    new_matrix->matrix.push_back(new_matrix->line);
                    new_matrix->line.clear();
                }
                new_expr->matrix = new_matrix;
                new_expr->matrix->lines = termo->matrix->lines; new_expr->matrix->columns =  termo->matrix->columns;
                break;
            case SUBKW:
                if (termo->type == MATRIXKW && (expr->type == INTKW || expr->type == FLOATKW)) {
                    printf("\nIncorrect type for operator ’-’ - have MATRIX and FLOAT\n\n");
                    return nullptr;
                }
                if (expr->type == MATRIXKW && (termo->type == INTKW || termo->type == FLOATKW)) {
                    printf("\nIncorrect type for operator ’-’ - have FLOAT and MATRIX\n\n");
                    return nullptr;
                }
                if (termo->type != MATRIXKW || expr->type != MATRIXKW) {
                    return nullptr;
                }
                if (expr->matrix->lines != termo->matrix->lines || expr->matrix->columns != termo->matrix->columns) {
                    std::cout << "\nIncorrect dimensions for operator ’-’ - have MATRIX ["<< termo->matrix->lines <<"][" << termo->matrix->columns <<"] and MATRIX ["<< expr->matrix->lines <<"][" << expr->matrix->columns << "]\n\n";
                    return nullptr;
                }
                for(int i = 0; i < termo->matrix->lines; i++) {
                    for(int j = 0; j < termo->matrix->columns; j++)
                        new_matrix->line.push_back(termo->matrix->matrix[i][j] - expr->matrix->matrix[i][j]);
                    new_matrix->matrix.push_back(new_matrix->line);
                    new_matrix->line.clear();
                }
                new_expr->matrix = new_matrix;
                new_expr->matrix->lines = termo->matrix->lines; new_expr->matrix->columns =  termo->matrix->columns;
                break;
            case MULKW:
                if (termo->type == MATRIXKW && (expr->type == INTKW || expr->type == FLOATKW)) {
                    for(int i = 0; i < termo->matrix->lines; i++){
                        Matrix *line = new Matrix();
                        for(int j = 0; j < termo->matrix->columns; j++)
                            line->line.push_back(termo->matrix->matrix[i][j] * expr->value);
                        new_matrix->matrix.push_back(line->line);
                    }
                    new_expr->matrix = new_matrix;
                    new_expr->matrix->lines = termo->matrix->lines; new_expr->matrix->columns = termo->matrix->columns;
                    break;
                }
                else if (expr->type == MATRIXKW && (termo->type == INTKW || termo->type == FLOATKW)){
                    
                    for(int i = 0; i < expr->matrix->lines; i++){
                        Matrix *line = new Matrix();
                        for(int j = 0; j < expr->matrix->columns; j++)
                            line->line.push_back(expr->matrix->matrix[i][j] * termo->value);
                        new_matrix->matrix.push_back(line->line);
                    }
                    new_expr->matrix = new_matrix;
                    new_expr->matrix->lines = expr->matrix->lines; new_expr->matrix->columns = expr->matrix->columns;
                    break;
                }
                else {
                    if(termo->matrix->columns != expr->matrix->lines){
                        std::cout << "\nIncorrect dimensions for operator ’*’ - have MATRIX ["<< termo->matrix->lines <<"][" << termo->matrix->columns <<"] and MATRIX ["<< expr->matrix->lines <<"][" << expr->matrix->columns << "]\n\n";
                        return nullptr;
                    }
                    else {
                        for(int i = 0; i < termo->matrix->lines; i++){
                            Matrix *line = new Matrix();
                            std::vector<float> result(expr->matrix->columns, 0);  
                            for(int j = 0; j < expr->matrix->columns; j++){
                                for(int k = 0; k < termo->matrix->columns; k++)
                                    result[j] += termo->matrix->matrix[i][k] * expr->matrix->matrix[k][j];
                            }
                            line->line = result;
                            new_matrix->matrix.push_back(line->line);
                        }
                        new_expr->matrix = new_matrix;
                        new_expr->matrix->lines = termo->matrix->lines; new_expr->matrix->columns = expr->matrix->columns;
                        break;
                    }
                }
                break;
        }
    }
    else if (termo->type == FLOATKW ||termo->type == INTKW || expr->type == FLOATKW ||expr->type == INTKW ) {
        delete new_matrix;
        switch (func) {
            case ADDKW:
                new_expr->value = termo->value + expr->value;
                break;
            case SUBKW:
                new_expr->value = termo->value - expr->value;
                break;
            case MULKW:
                new_expr->value = termo->value * expr->value;
                break;
            case DIVKW:
                new_expr->value = termo->value / expr->value;
                break;
            case RESTKW:
                new_expr->value = static_cast<int>(termo->value) % static_cast<int>(expr->value);
                break;
            case POWKW:
                new_expr->value = pow(termo->value, expr->value);
                break;
        }
    }
    return new_expr;
}