#include "hash.hpp"
#include <cstring>
#include <iostream>

std::vector<Hash> hash[211];

void showSymbols() {
    std::cout << "\n";
    for (int i = 0; i < 211; i++) {
        if (hash[i].size() > 0) {
            for (int j = 0; j < hash[i].size(); j++) {
                std::cout << hash[i][j].name << " - ";
                switch (hash[i][j].value->type) {
                    case FLOATKW:
                    case INTKW:
                        std::cout << "FLOAT" << std::endl;
                        break;
                    case MATRIXKW:
                        std::cout << "MATRIX [" << hash[i][j].value->matrix->lines << "][" << hash[i][j].value->matrix->columns << "]" << std::endl;
                        break;
                }
            }
        }
    }
    std::cout << "\n";
}

void createHash(char *name, Expr *expr, int type) {
    int ascii = 0;
    for (int i = 0; i < std::strlen(name); i++) 
        ascii += int(name[i]);
    ascii = ascii % 211;
    if (expr->left != nullptr) 
        removeExpr(expr->left);
    if (expr->right != nullptr) 
        removeExpr(expr->right);
    if (expr->expr != nullptr) 
        removeExpr(expr->expr);
    expr->left = expr->right = expr->expr = nullptr;
    expr->func = OPKW;

    if (hash[ascii].size() > 0) {
        for (int i = 0; i < hash[ascii].size(); i++) {
            if (hash[ascii][i].name == name) {
                hash[ascii][i].value = expr;
                hash[ascii][i].type = type;
                return;
            }
        }
        hash[ascii].push_back({name, expr, type});
    } 
    else 
        hash[ascii].push_back({name, expr, type});
}

Symbol searchHash(char *name) {
    int ascii = 0;
    for (int i = 0; i < std::strlen(name); i++) ascii += int(name[i]);
    ascii = ascii % 211;
    Symbol result;
    if (hash[ascii].size() > 0) {
        for (int i = 0; i < hash[ascii].size(); i++) {
            if (hash[ascii][i].name == name) {
                result.exists = true;
                result.value = hash[ascii][i].value;
                result.type = hash[ascii][i].type;
                return result;
            }
        }
    }
    result.exists = false;
    return result;
}

void removeHash() {
    for (int i = 0; i < 211; i++) {
        for (int j = 0; j < hash[i].size(); j++) 
            removeExpr(hash[i][j].value);
        hash[i].clear();
    }
}