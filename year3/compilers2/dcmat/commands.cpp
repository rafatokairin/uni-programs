#include "commands.hpp"
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

float h_view_lo = -6.5;
float h_view_hi = 6.5;
float v_view_lo = -3.5;
float v_view_hi = 3.5;
int precision = 6;
int integral_steps = 1000;
bool axis = true;
bool erase_matrix = true;
bool def = false;
std::vector<std::string> undef;
Expr *matrix = nullptr;
bool quit_prog = false;
Expr *function = nullptr; 
std::string axis_matrix[25][80];

void resetSettings() {
    h_view_lo = -6.5;
    h_view_hi = 6.5;
    v_view_lo = -3.5;
    v_view_hi = 3.5;
    precision = 6;
    integral_steps = 1000;
    axis = true;
    erase_matrix = true;
};

void showSettings() {
    std::cout << "\nh_view_lo: " << std::fixed << std::setprecision(6) << h_view_lo << "\nh_view_hi: " << h_view_hi;
    std::cout << "\nv_view_lo: " << v_view_lo << "\nv_view_hi: "  << v_view_hi;
    std::cout << "\nfloat precision: " << precision << "\nintegral_steps: " << integral_steps;
    axis?std::cout << "\n\nDraw Axis: " << "ON":std::cout << "\n\nDraw Axis: " << "OFF";
    erase_matrix?std::cout << "\nErase Plot: " << "ON":std::cout << "\nErase Plot: " << "OFF";
    std::cout << "\n\n";
};

Matrix* setMatrix(Matrix* matrixLine, Matrix* matrixColum) {
    if (!matrixLine) 
        return nullptr;
    matrixLine->matrix.push_back(matrixLine->line);
    if (matrixColum) 
        for (size_t i = 0; i < matrixColum->matrix.size(); ++i) 
            matrixLine->matrix.push_back(matrixColum->matrix[i]);
    matrixLine->lines = matrixLine->matrix.size();
    matrixLine->columns = matrixLine->matrix[0].size();
    for (size_t i = 0; i < matrixLine->matrix.size(); ++i) 
        if (matrixLine->columns < matrixLine->matrix[i].size()) 
            matrixLine->columns = matrixLine->matrix[i].size();
    for (size_t i = 0; i < matrixLine->lines; ++i) 
        if (matrixLine->columns > matrixLine->matrix[i].size()) 
            for (size_t j = matrixLine->matrix[i].size(); j < matrixLine->columns; ++j) 
                matrixLine->matrix[i].push_back(0);
    return matrixLine;
}

Matrix* setMatrixColum(Matrix* matrixColum, Matrix* matrixLine) {
    if (matrixColum) {
        matrixColum->matrix.push_back(matrixLine->line);
        return matrixColum;
    } 
    else {
        Matrix* newColum = new Matrix();
        newColum->matrix.push_back(matrixLine->line);
        return newColum;
    }
}

Matrix* setMatrixLine(int limit, Matrix* matrixValue) {
    Matrix* line = new Matrix();
    line->line.push_back(limit);
    if (matrixValue)
        for (size_t i = 0; i < matrixValue->line.size(); ++i)
            line->line.push_back(matrixValue->line[i]);
    return line;
}

Matrix* setMatrixValue(Matrix* matrixValue, int limit) {
    if (matrixValue) {
        matrixValue->line.push_back(limit);
        return matrixValue;
    } 
    else {
        Matrix* newValue = new Matrix();
        newValue->line.push_back(limit);
        return newValue;
    }
}

void setFloatPrecision(int value) {
    if (value >= 0 && value <= 8)
        precision = value;
    else
        printf("\nERROR: float precision must be from 0 to 8\n\n");
}

void setHView(float lo, float hi) {
    if (lo < hi) {
        h_view_lo = lo;
        h_view_hi = hi;
    } 
    else 
        printf("\nERROR: h_view_lo must be smaller than h_view_hi\n\n");
}

void setVView(float lo, float hi) {
    if (lo < hi) {
        v_view_lo = lo;
        v_view_hi = hi;
    } 
    else
        printf("\nERROR: v_view_lo must be smaller than v_view_hi\n\n");
}

void setIntegralSteps(int steps) {
    if (steps > 0) {
        integral_steps = steps;
    } 
    else
        printf("\nERROR: integral_steps must be a positive non-zero integer\n\n");
}

void showAbout() {
    printf(
        "\n+----------------------------------------------+\n"
        "|                                              |\n"
        "|                202200560447                  |\n"
        "|            Rafael Palheta Tokairin           |\n"
        "|                                              |\n"
        "+----------------------------------------------+\n\n"
    );
}

void plotAxis(Expr *expr) {
    float h = (h_view_hi - h_view_lo) / 80.0;
    if (erase_matrix) 
        for (int i = 0; i < 25; i++) 
            for (int j = 0; j < 80; j++) 
                axis_matrix[i][j] = " ";
    int xAxisRow = (v_view_lo <= 0 && v_view_hi >= 0) ? 24 - (int)((0 - v_view_lo) * 25 / (v_view_hi - v_view_lo)) : -1;
    int yAxisCol = (h_view_lo <= 0 && h_view_hi >= 0) ? (int)((0 - h_view_lo) * 80 / (h_view_hi - h_view_lo)) : -1;

    if (axis) {
        if (xAxisRow >= 0 && xAxisRow < 25) 
            for (int i = 0; i < 80; i++) 
                axis_matrix[xAxisRow][i] = "-";
        if (yAxisCol >= 0 && yAxisCol < 80) 
            for (int j = 0; j < 25; j++) 
                axis_matrix[j][yAxisCol] = "|";
        if (xAxisRow >= 0 && xAxisRow < 25 && yAxisCol >= 0 && yAxisCol < 80) 
            axis_matrix[xAxisRow][yAxisCol] = "+"; 
    }

    for (int i = 0; i < 80; i++) {
        float x = i * h + h_view_lo;
        float y = solveFunc(x, expr);
        int row = 24 - (int)((y - v_view_lo) * 25 / (v_view_hi - v_view_lo));
        if (row >= 0 && row < 25) 
            axis_matrix[row][i] = "*";
    }

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) 
            std::cout << axis_matrix[i][j];
        std::cout << std::endl;
    }
}

int lengthValue(int number) {
    std::string numeroString = std::to_string(number);
    return numeroString.length();
}

void showMatrix(Matrix *matrix){
    int lineSize = 0;
    bool isNegative[matrix->columns];
    
    for (int k = 0; k < matrix->columns; k++)
        isNegative[k] = false;

    for (int i = 0; i < matrix->lines; i++) {
        int result = 0;
        for (int j = 0; j < matrix->columns; j++) {
            if (matrix->matrix[i][j] >= 0) {
                result += lengthValue((int)matrix->matrix[i][j]) + precision;
                if(precision > 0)
                    result += 1;
            }
            else {
                result += lengthValue((int)matrix->matrix[i][j]) + precision;
                if(precision > 0)
                    result += 1;
                isNegative[j] = true;
                result +=1;
            }
            if (j < matrix->columns-1) 
                result+=1;
        }
        if(lineSize < result) 
            lineSize = result;
    }
    printf("\n+-");
    for(int k = 0; k < lineSize; k++)
        printf(" ");
    printf("-+\n");
    for(int i = 0; i < matrix->lines; i++){
        printf("| ");
        for(int j = 0; j < matrix->columns; j++){
            if(matrix->matrix[i][j]) {
                if(matrix->matrix[i][j] >= 0 && isNegative[j])
                    printf(" ");
                std::cout << std::fixed << std::setprecision(precision) << matrix->matrix[i][j] << " ";
            }
            else {
                if(isNegative[j])
                    printf(" ");
                std::cout << std::fixed << std::setprecision(precision) << (float)0 << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    printf("+-");
    for(int k = 0; k < lineSize; k++) 
        printf(" ");
    printf("-+\n\n");
};

float determinantAux(std::vector<std::vector<float>> matrix){
    float det = 0;
    if(matrix.size() == 1)
        det = matrix[0][0];
    else if(matrix.size() == 2)
         det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else {
          for (int i = 0; i < matrix.size(); ++i) {
            std::vector<std::vector<float>> submatrix(matrix.size() - 1, std::vector<float>(matrix.size() - 1));

            for (int j = 1; j < submatrix.size() ; ++j) {
                int k = 0;
                for (int l = 0; l < matrix.size(); ++l) {
                    if (l != i) {
                       submatrix[j - 1][k] = submatrix[j][l];
                        ++k;
                    }
                }
            }
            det += submatrix[0][i] * determinantAux(submatrix) * ((i % 2 == 0) ? 1 : -1);
        }
    }
    return det;
};

float solveDeterminant(Matrix *matrix){
    float det = 0;
    if(matrix->columns == 1)
        det = matrix->matrix[0][0];
    else if(matrix->columns == 2)
         det = matrix->matrix[0][0] * matrix->matrix[1][1] - matrix->matrix[0][1] * matrix->matrix[1][0];
    else {
          for (int i = 0; i < matrix->columns; ++i) {
            std::vector<std::vector<float>> submatrix(matrix->columns - 1, std::vector<float>(matrix->columns - 1));
            for (int j = 1; j < matrix->columns; ++j) {
                int k = 0;
                for (int l = 0; l < matrix->columns; ++l) {
                    if (l != i) {
                        submatrix[j - 1][k] = matrix->matrix[j][l];
                        ++k;
                    }
                }
            }
            det += matrix->matrix[0][i] * determinantAux(submatrix) * ((i % 2 == 0) ? 1 : -1);
        }
    }
    return det;
};

void solveLinearSystem(Matrix *matrix) {
    std::vector<std::vector<float>> L(matrix->lines, std::vector<float>(matrix->lines, 0)), U;
    U = matrix->matrix;
    float aux[matrix->lines] = {0};

    for (int i = 0; i < matrix->lines; ++i) {
        L[i][i] = 1;
        for (int j = i + 1; j < matrix->lines; ++j) {
            float ratio = U[j][i] / U[i][i];
            L[j][i] = ratio;
            for (int k = i; k < matrix->lines+1; ++k) {
                U[j][k] -= ratio * U[i][k];
            }
        }
    }

    for(int i=0; i < matrix->lines; i++) {
        for(int j=i+1; j < matrix->lines; j++) {
            for(int k= 0; k < matrix->lines; k++) {
                if(fmod(matrix->matrix[i][k], matrix->matrix[j][k]) != 0 && fmod(matrix->matrix[j][k], matrix->matrix[i][k]) != 0) 
                    break;
                aux[k] = matrix->matrix[i][k] > matrix->matrix[j][k]?matrix->matrix[i][k]/matrix->matrix[j][k]:
                 matrix->matrix[j][k]/matrix->matrix[i][k];
            }

            for(int k= 0; k < matrix->lines; k++) {
                if(aux[k] != aux[0]) break;
                if(k == matrix->lines-1 && (matrix->matrix[i][matrix->lines]/aux[0] == matrix->matrix[j][matrix->lines] || matrix->matrix[j][matrix->lines]/aux[0] == matrix->matrix[i][matrix->lines])) {
                    printf("\nSPI - The Linear System has infinitely many solutions\n\n");
                    return;
                } 
                else if(k == matrix->lines-1 && ( matrix->matrix[i][matrix->lines]/aux[0] !=  matrix->matrix[j][matrix->lines] && matrix->matrix[j][matrix->lines]/aux[0] !=  matrix->matrix[i][matrix->lines])) {
                    printf("\nSI - The Linear System has no solution\n\n");
                    return;
                }
            }
        }
    }

    std::vector<float> y(matrix->lines);
    for (int i = 0; i < matrix->lines; ++i) {
        float sum = 0;
        for (int j = 0; j < i; ++j) 
            sum += L[i][j] * y[j];
        y[i] = (matrix->matrix[i][matrix->columns-1] - sum) / L[i][i];
    }
    std::vector<float> result(matrix->lines);
    for (int i = matrix->lines - 1; i >= 0; --i) {
        float sum = 0;
        for (int j = i + 1; j < matrix->lines; ++j) 
            sum += U[i][j] * result[j];
        result[i] = (y[i] - sum) / U[i][i];
    }

    int verify = 0;
    for (int i = 0; i < matrix->lines; ++i)
        if (U[i][i] != 0) 
            verify++;
    if(verify == matrix->lines) {
        printf("\nMatrix x:\n\n");
        for(int i = 0; i < matrix->lines; i++) 
            std::cout << std::fixed << std::setprecision(precision) << result[i] << std::endl;
        std::cout << std::endl;
    }
};

void integrate(float inferior, float superior, Expr *expr) {
    float subInterval = (inferior - superior) / integral_steps;
    float result = 0;
    for(int i = 0; i < integral_steps; i++)
        result += subInterval * solveFunc(superior + subInterval * i, expr);
    std::cout << "\n" << std::fixed << std::setprecision(precision) << result << "\n\n";
    removeExpr(expr);
};

void sum(float inferior, float superior, Expr *expr) {
    float result = 0;
    for(int i = inferior; i <= superior; i++)
        result += solveFunc(i, expr);
    std::cout << "\n" << std::fixed << std::setprecision(precision) << result << "\n\n";
    removeExpr(expr);
};

void solveRPN(Expr *expr) {
    if(expr->type != OPKW) {
        if(expr->left != nullptr) solveRPN(expr->left);
        if(expr->right != nullptr) solveRPN(expr->right);
    }
    switch (expr->func) {
        case SUBKW:
            printf("- ");
            break;  
        case ADDKW:
            printf("+ ");
            break;  
        case DIVKW:
            printf("/ ");
            break;  
        case MULKW:
            printf("* ");
            break;  
        case POWKW:
            printf("^ ");
            break;  
        case SENKW:
            solveRPN(expr->expr);
            printf("SEN ");
            break;  
        case COSKW:
            solveRPN(expr->expr);
            printf("COS ");
            break;  
        case TANKW:
            solveRPN(expr->expr); 
            printf("TAN ");
            break;  
        case ABSKW:
            solveRPN(expr->expr);
            printf("ABS ");
            break;  
        case EXPKW:
            solveRPN(expr->expr); 
            break;
        case OPKW:
            switch (expr->type){
                case VARKW:
                    printf("x ");
                    break;  
                case SUBVARKW:
                    printf("x - ");
                    break;
                case FLOATKW: case INTKW:
                    if(expr->id.compare("F")) {
                        std::cout << expr->id  << " "; 
                        break; 
                    }
                    else {
                        std::cout << std::fixed << std::setprecision(precision) << expr->value << " ";
                        break;
                    } 
                case IDKW: case MATRIXKW:
                    std::cout << expr->id << " "; 
                }
    }
};

void clearMemory() {
    if(matrix != nullptr) 
        delete matrix;
    delete function;
    removeHash();
}

Expr* handleIdentifier(char* id) {
    auto result = searchHash(id);
    if (result.exists) {
        result.value->id = id;
        if (result.value->type != MATRIXKW)
            return createNode(result.value->type, OPKW, result.value->value, result.value->expr, EXPRKW, id);
        else 
            return createMatrix(result.value->matrix);
    } 
    else {
        Expr* expr = createNode(IDKW, OPKW, 0, nullptr, EXPRKW, id);
        def = true;
        bool alreadyAdded = false;
        for (const auto& undeclaredId : undef) {
            if (undeclaredId == id) {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded)
            undef.push_back(id);
        return expr;
    }
}

Expr* unaryOperation(Expr* expr, int opType) {
    if (expr->type == MATRIXKW) {
        std::cerr << "\nIncorrect type for operator '" << getKwName(opType) << "' - have MATRIX\n\n";
        return nullptr;
    }
    
    float value = 0;
    int element = expr->element;

    if (expr->element != FUNCKW) {
        switch (opType) {
            case SENKW: 
                value = sin(expr->value); 
                break;
            case COSKW: 
                value = cos(expr->value); 
                break;
            case TANKW: 
                value = tan(expr->value); 
                break;
            case ABSKW: 
                value = fabs(expr->value); 
                break;
            default: 
                break;
        }
    }
    return createNode(expr->type, opType, value, expr, element);
}

Expr* negateMatrix(Expr* expr) {
    Expr* negExpr = createMatrix(expr->matrix);
    for (int i = 0; i < negExpr->matrix->lines; i++) 
        for (int j = 0; j < negExpr->matrix->columns; j++) 
            negExpr->matrix->matrix[i][j] *= -1;
    return negExpr;
}

Expr* negateTerm(Expr* expr) {
    if (expr->type == MATRIXKW) 
        return negateMatrix(expr);
    else {
        switch (expr->type) {
            case VARKW:
                expr->type = SUBVARKW;
                break;
            default:
                if (expr->element != FUNCKW && expr->type != IDKW) {
                    expr->value = -expr->value;
                }
                break;
        }
        return expr;
    }
}

void handleShowMatrix() {
    if (matrix != nullptr)
        showMatrix(matrix->matrix);
    else
        printf("\nNo Matrix defined!\n\n");
}

void identifier(char* identifier) {
    auto result = searchHash(identifier);
    if (result.exists) {
        if (result.type == MATRIXKW)
            showMatrix(result.value->matrix);
        else if (result.type == INTKW)
            std::cout << "\n" << identifier << " = " << result.value->value << "\n\n";
        else if (result.type == FLOATKW)
            std::cout << "\n" << std::fixed << std::setprecision(precision) << identifier << " = " << result.value->value << "\n\n";
    } 
    else
        printf("\nUndefined symbol\n\n");
}

void assignmentExpr(char* identifier, Expr* expr) {
    if (def)
        undefinedSymbol();
    else if (expr != nullptr && expr->element != FUNCKW) {
        createHash(identifier, expr, expr->type);
        if (expr->type == FLOATKW || expr->type == INTKW)
            std::cout << "\n" << std::fixed << std::setprecision(precision) << (float)expr->value << "\n\n";
        else if (expr->type == MATRIXKW)
            showMatrix(expr->matrix);
    }
}

void assignmentMatrix(char* identifier, Matrix* matrix) {
    if (matrix != nullptr) {
        if (matrix->lines > 10 || matrix->columns > 10)
            std::cout << "\nERROR: Matrix limits out of boundaries.\n" << std::endl;
        else {
            auto expr = createMatrix(matrix);
            createHash(identifier, expr, MATRIXKW);
            showMatrix(matrix);
        }
    }
}

void matrixEqual(Matrix* newMatrix) {
    if (newMatrix->lines > 10 || newMatrix->columns > 10) 
        std::cout << "\nERROR: Matrix limits out of boundaries.\n" << std::endl;
    else {
        if (matrix)
            matrix->matrix = newMatrix;
        else {
            auto expr = createMatrix(newMatrix);
            matrix = expr;
        }
    }
}

void handleSolveDeterminant() {
    if (matrix) {
        if (matrix->matrix->lines != matrix->matrix->columns)
            printf("\nMatrix format incorrect!\n\n");
        else {
            float det = solveDeterminant(matrix->matrix);
            std::cout << "\n" << std::fixed << std::setprecision(precision) << det << "\n\n";
        }
    } 
    else
        printf("\nNo Function defined!\n\n");
}

void handleSolveLinearSystem() {
    if (matrix) {
        if (matrix->matrix->lines != matrix->matrix->columns - 1)
            printf("\nMatrix format incorrect!\n\n");
        else
            solveLinearSystem(matrix->matrix);
    } 
    else
        printf("\nNo Function defined!\n\n");
}

void handleExpr(Expr* expr) {
    if (expr != nullptr) {
        if (def)
            undefinedSymbol();
        else if (expr->element != FUNCKW) {
            if (expr->type == MATRIXKW)
                showMatrix(expr->matrix);
            else
                std::cout << "\n" << std::fixed << std::setprecision(precision) << expr->value << "\n\n";
        } 
        else
            std::cout << "\nThe x variable cannot be present on expressions.\n" << std::endl;
    }
}

void plotExpr(Expr* expr) {
    if (!quit_prog) {
        if (def)
            undefinedSymbol();
        else {
            function = expr;
            plotAxis(function);
        }
    }
}

void handlePlot() {
    if (function)
        plotAxis(function);
    else
        printf("\nNo Function defined!\n\n");
}

void handleIntegrate(float lower, float upper, Expr* expr) {
    if (def)
        undefinedSymbol();
    else if (lower >= upper)
        printf("\nERROR: lower limit must be smaller than upper limit\n\n");
    else 
        integrate(upper, lower, expr);
}

void handleSum(char* identifier, float lower, float upper, Expr* expr) {
    for (size_t i = 0; i < undef.size(); i++) {
        if (undef[i] == identifier)
            undef.erase(undef.begin() + i);
    }
    if (undef.size() > 0)
        undefinedSymbol();
    else
        sum(lower, upper, expr);
}

void handleRPN(Expr* expr) {
    printf("\nExpression in RPN format:\n\n");
    solveRPN(expr);
    printf("\n\n");
}

std::string getKwName(int opType) {
    switch (opType) {
        case SENKW: 
            return "SEN";
        case COSKW: 
            return "COS";
        case TANKW: 
            return "TAN";
        case ABSKW: 
            return "ABS";
        default: 
            return "UNKNOWN";
    }
}

void undefinedSymbol() {
    printf("\n");
    for(size_t i = 0; i < undef.size(); i++)
        std::cout << "Undefined symbol [" << undef[i] << "]\n";
    printf("\n");
    undef.clear(); def = false;
};