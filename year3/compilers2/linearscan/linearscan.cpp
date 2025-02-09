#include "linearscan.hpp"

std::vector<Reg *> actives;
std::map<int, bool> freeRegs;
LS* linearScan = new LS();

Reg::Reg() : id(""), ini(0), fim(0), reg(-1) {}

LS::LS() : k(0) {}

void LS::setK(int k) {
    this->k = k;
}

void LS::addReg(char* id, int ini, int fim) {
    Reg *reg = new Reg();
    reg->id = id;
    reg->ini = ini;
    reg->fim = fim;
    reg->reg = -1;
    registrador.push_back(reg);
}

int LS::getRegInd(std::string id) {
    for (int i = 0; i < registrador.size(); i++) {
        if (registrador[i]->id == id) {
            return i;
        }
    }
    return -1;
}

void LS::ajustarAtivo(int current) {
    for (auto ativo : actives) {
        if (ativo->fim <= current) {
            actives.erase(std::remove(actives.begin(), actives.end(), ativo), actives.end());
            freeRegs[ativo->reg] = false;
        }
    }
}

void LS::alocar(int i) {
    Res result;
    for (int j = 0; j < i; j++) {
        freeRegs[j] = false;
    }

    for (int j = 0; j < registrador.size(); j++) {
        Reg* reg = registrador[j];
        ajustarAtivo(reg->ini);
        ajustarAtivo(reg->ini);
        for (auto free : freeRegs) {
            if (free.second == false) {
                actives.push_back(reg);
                reg->reg = free.first;
                freeRegs[free.first] = true;
                break;
            }
        }

        if (reg->reg == -1) {
            Reg* spill = reg;
            for (int k = 0; k < actives.size(); k++) {
                Reg* ativo = actives[k];
                if (ativo->fim > spill->fim) {
                    spill = ativo;
                    continue;
                } else if (ativo->fim == spill->fim) {
                    if (ativo->ini > spill->ini) {
                        spill = ativo;
                        continue;
                    } else if (ativo->ini == spill->ini) {
                        int indexSpill = getRegInd(spill->id);
                        int indexAtivo = getRegInd(ativo->id);

                        if (indexAtivo > indexSpill) {
                            spill = ativo;
                            continue;
                        }
                    }
                }
            }

            if (spill->id != reg->id) {
                actives.erase(std::remove(actives.begin(), actives.end(), spill), actives.end());
                actives.push_back(reg);
                reg->reg = spill->reg;
                spill->reg = -1;
            }
            result.it.push_back(j);
        }
    }
    result.k = i;
    result.spill = result.it.size() > 0;
    res.push_back(result);
    std::cout << "K = " << i << "\n" << std::endl;
    for (int j = 0; j < registrador.size(); j++) {
        Reg* reg = registrador[j];
        if (reg->reg == -1) {
            std::cout << reg->id << ": " << "SPILL" << std::endl;
            continue;
        }
        std::cout << reg->id << ": " << reg->reg << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;

    reiniciar();
}

void LS::reiniciar() {
    for (auto reg : registrador) {
        reg->reg = -1;
    }
    actives.clear();
    freeRegs.clear();
}

void LS::removerReg() {
    for (auto reg : registrador) {
        delete reg;
    }
}

void handleLinearScan() {
    for(int i = linearScan->k; i > 1; i--)
        linearScan->alocar(i);
    std::cout << "----------------------------------------";
    for(auto result : linearScan->res){
        std::cout << "\nK = " << result.k << ": ";
        if(result.spill){
            std::cout << "SPILL on interation(s): " << result.it[0];
            for(int i = 1; i < result.it.size(); i++){
                std::cout << ", " << result.it[i];
            }
            continue;
        }
        std::cout << "Successful Allocation";
    }
    linearScan->removerReg();
    delete linearScan;
}