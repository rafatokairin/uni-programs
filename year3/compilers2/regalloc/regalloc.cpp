#include "regalloc.hpp"

std::stack<Vert*> s;
Grafo* grafo = new Grafo();

Vert::Vert(int vert, int cor) {
    this->vert = vert;
    this->cor = -1;
    this->virtualReg = vert >= cor;
    this->spill = false;
    this->cntAresta = 0;
    this->removido = false;
}

void Vert::addAresta(int vert, Vert *v) {
    for (int i = 0; i < aresta.size(); i++) {
        if (aresta[i] == vert) {
            return;
        }
    }
    aresta.push_back(vert);
    v->aresta.push_back(this->vert);
}

int Vert::getVert() {
    return vert;
}

std::vector<int> Vert::getAresta() {
    return aresta;
}

int Vert::getCor() {
    return cor;
}

void Vert::setCor(int cor) {
    this->cor = cor;
}

Grafo::Grafo() {
    this->g = 0;
    this->cor = 0;
    this->virtualRegs = 0;
    this->max = nullptr;
    this->min = nullptr;
}

Grafo::Grafo(int V) {
    this->g = V;
}

void Grafo::addVert(Vert* vert) {
    if (!vertices[vert->vert]) {
        vertices[vert->vert] = vert;
        if (vert->virtualReg) {
            virtualRegs++;
        }
    }
}

bool Grafo::buscarVert(int vert) {
    return vertices[vert] != nullptr;
}

void Grafo::removerVert(int vert) {
    if (vertices[vert] && vertices[vert]->virtualReg) {
        vertices[vert]->removido = true;
    }
}

Vert* Grafo::getVert(int vert) {
    return vertices[vert];
}

int Grafo::cntAresta(int vert) {
    int count = 0;
    Vert* v = vertices[vert];
    for (int i = 0; i < v->aresta.size(); i++) {
        Vert* u = getVert(v->aresta[i]);
        if (!u->removido) {
            count++;
        }
    }
    v->cntAresta = count;
    return count;
}

int Grafo::cntVirtualReg(int vert) {
    int count = 0;
    Vert* v = vertices[vert];
    for (int i = 0; i < v->aresta.size(); i++) {
        Vert* u = getVert(v->aresta[i]);
        if (!u->removido && u->virtualReg) {
            count++;
        }
    }
    return count;
}

void Grafo::setMaxMinVert() {
    for (auto v : vertices) {
        if (v.second->virtualReg && !v.second->removido) {
            cntAresta(v.first);
            if (min == nullptr || v.second->cntAresta < min->cntAresta)
                min = v.second;
            else if (v.second->cntAresta == min->cntAresta && v.second->vert < min->vert)
                min = v.second;
            
            if (max == nullptr || v.second->cntAresta > max->cntAresta)
                max = v.second;
            else if (v.second->cntAresta == max->cntAresta && v.second->vert < max->vert)
                max = v.second;
        }
    }
}

void Grafo::getCor(int vert, int maxCor) {
    std::vector<int> avaliableColors;
    Vert* v = vertices[vert];

    for (int i = 0; i <= maxCor; i++)
        avaliableColors.push_back(i);
    for (int i = 0; i < v->aresta.size(); i++) {
        Vert* u = getVert(v->aresta[i]);
        if (!u->virtualReg)
            avaliableColors.erase(std::remove(avaliableColors.begin(), avaliableColors.end(), u->vert), avaliableColors.end());
        else if (!u->removido)
            avaliableColors.erase(std::remove(avaliableColors.begin(), avaliableColors.end(), u->cor), avaliableColors.end());
    }
    v->cor = !avaliableColors.empty() ? avaliableColors[0] : -1;
}

void Grafo::reiniciaVert() {
    for (auto& iter : vertices) {
        iter.second->cor = -1;
        iter.second->spill = false;
        iter.second->removido = false;
    }
}

void Grafo::freeGrafo() {
    for (auto& iter : vertices) {
        delete iter.second;
    }
}

void handleInterference(Grafo* grafo, int val, const std::vector<int>& interf) {
    Vert* v;

    if (!grafo->buscarVert(val))
        v = new Vert(val, grafo->cor);
    else
        v = grafo->vertices[val];

    for (int i = 0; i < interf.size(); i++) {
        if (!grafo->buscarVert(interf[i])) {
            Vert* z = new Vert(interf[i], grafo->cor);
            grafo->addVert(z);
        }
        v->addAresta(interf[i], grafo->vertices[interf[i]]);
    }

    grafo->addVert(v);
}

void handleGrafo() {
    std::cout << "Graph " << grafo->g << " -> Physical Registers: " << grafo->cor << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (int i = grafo->cor; i > 1; i--) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "K = " << i << "\n" << std::endl;

        while(grafo->virtualRegs > 0) {
            grafo->setMaxMinVert();
            if (grafo->min->cntAresta < i) {
                std::cout << "Push: " << grafo->min->vert << std::endl;
                s.push(grafo->min);
                grafo->removerVert(grafo->min->vert);
            }
            else {
                std::cout << "Push: " << grafo->max->vert << " *" << std::endl;
                s.push(grafo->max);
                grafo->removerVert(grafo->max->vert);
            }
            grafo->max = nullptr;
            grafo->min = nullptr;
            grafo->virtualRegs--;
        }

        bool spill = false;
        while(s.size() > 0) {
            Vert *v = s.top();
            grafo->virtualRegs++;
            grafo->addVert(v);
            s.pop();
            grafo->getCor(v->vert, i-1);
            v->removido = false;
            std::cout << "Pop: " << v->vert << " -> ";
            if(v->cor == -1){
                std::cout << "NO COLOR AVAILABLE" << std::endl;
                spill = true;
                break;
            }
            else
                std::cout << v->cor << std::endl;
        }

        if(spill) {
            while(s.size() > 0) {
                grafo->virtualRegs++;
                grafo->addVert(s.top());
                s.pop();
            }
            grafo->result.push_back({spill: true, k: i});
        }
        else
            grafo->result.push_back({spill: false, k: i});
        grafo->reiniciaVert();
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "----------------------------------------";
    for (auto element:grafo->result) {
        std::cout << "\nGraph " << grafo->g;
        if(element.k > 9)
            std::cout << " -> K = ";
        else
            std::cout << " -> K =  ";
        std::cout << element.k << ": ";
        if(element.spill)
            std::cout << "SPILL";
        else
            std::cout << "Successful Allocation";
    }
    grafo->freeGrafo();
    delete grafo;
}
