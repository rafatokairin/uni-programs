#ifndef LINEARSCAN_HPP
#define LINEARSCAN_HPP
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct Res {
    int k;
    bool spill;
    std::vector<int> it;
};

struct Reg {
    std::string id;
    int ini, fim, reg;
    Reg();
};

struct LS {
    std::vector<Reg *> registrador;
    std::vector<Res> res;
    int k;

    LS();

    void setK(int k);

    void addReg(char* id, int ini, int fim);

    int getRegInd(std::string id);

    void ajustarAtivo(int current);

    void alocar(int i);

    void reiniciar();

    void removerReg();
};

extern LS* linearScan;

void handleLinearScan();

#endif
