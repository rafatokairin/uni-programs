#ifndef REGALLOC_HPP
#define REGALLOC_HPP

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stack>

struct Vert {
    int vert;
    std::vector<int> aresta;
    int cor;
    bool virtualReg;
    bool spill;
    bool removido;
    int cntAresta;

    Vert(int vert, int cor);

    void addAresta(int vert, Vert *v);

    int getVert();

    std::vector<int> getAresta();

    int getCor();

    void setCor(int cor);
};

struct Grafo {
    struct Res {
        bool spill;
        int k;
    };

    int g;
    int cor;
    int virtualRegs;
    std::unordered_map<int, Vert*> vertices;
    std::vector<Res> result;
    Vert *max, *min;

    Grafo();

    Grafo(int V);

    void addVert(Vert* vert);

    bool buscarVert(int vert);

    void removerVert(int vert);

    Vert* getVert(int vert);

    int cntAresta(int vert);

    int cntVirtualReg(int vert);

    void setMaxMinVert();

    void getCor(int vert, int maxCor);

    void reiniciaVert();

    void freeGrafo();
};

extern Grafo* grafo;

void handleInterference(Grafo* grafo, int val, const std::vector<int>& interf);

void handleGrafo();

#endif
