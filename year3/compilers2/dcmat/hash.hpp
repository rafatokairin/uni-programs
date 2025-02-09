#ifndef HASH_HPP
#define HASH_HPP
#include "ast.hpp" 
#include <string>
#include <vector>

struct Symbol {
    bool exists;
    Expr *value;
    int type;
};

struct Hash {
    std::string name;
    Expr *value;
    int type;
};

extern std::vector<Hash> hash[211];

Symbol searchHash(char *name);

void createHash(char *name, Expr *expr, int type);

void removeHash();

void showSymbols();

#endif
