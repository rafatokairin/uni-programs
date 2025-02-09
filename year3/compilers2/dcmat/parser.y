%{
    #include "hash.hpp"
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
    #include <parser.tab.h>
    extern char *yytext;
    extern int yychar;
    extern int yyleng;
    extern bool axis;
    extern bool erase_matrix;
    extern bool def;
    extern bool quit_prog;
    extern std::vector<std::string> undef;
    bool is_lex = false;
    extern int yylex();
    void continueProgram();
    void undefProgram();
    void yyerror(const void *s);
%}

%code requires {
    class Expr;
    class Matrix;
}

%union {
    int intValue;
    float floatValue;
    bool boolValue;
    char *stringValue;
    Expr *exprValue;
    Matrix *matrixValue;
}

%token <intValue>INT;
%token <floatValue>REAL;
%token <stringValue>IDENTIFIER;
%token ABOUT;
%token ABS;
%token AXIS;
%token COS;
%token DETERMINANT;
%token ERASE;
%token FLOAT;
%token H_VIEW;
%token INTEGRAL_STEPS;
%token INTEGRATE;
%token LINEAR_SYSTEM;
%token MATRIX;
%token OFF;
%token ON;
%token PLOT;
%token PRECISION;
%token QUIT;
%token RESET;
%token RPN;
%token SEN;
%token SET;
%token SETTINGS;
%token SHOW;
%token SOLVE;
%token SUM;
%token SYMBOLS;
%token TAN;
%token V_VIEW;
%token VAR;
%token PI;
%token E; 
%token ADD;
%token SUB;
%token MUL;
%token DIV;
%token POW;
%token REST;
%token LPAREN;
%token RPAREN;
%token EQUAL;
%token ASSIGN;
%token COLON;
%token LBRACKET;
%token RBRACKET;
%token SEMICOLON;
%token COMMA;
%token EOL;
%type <intValue>intValue;
%type <floatValue>floatValue;
%type <exprValue>exprValue;
%type <boolValue>boolean;
%type <exprValue>expr;
%type <exprValue>func;
%type <exprValue>exprSumSub;
%type <exprValue>exprPowRest;
%type <exprValue>exprMulDiv;
%type <exprValue>sign;
%type <floatValue>limit;
%type <matrixValue>matrix;
%type <matrixValue>matrixCol;
%type <matrixValue>matrixLin;
%type <matrixValue>matrixValue;
%start start;

%%
start:
    commands EOL { continueProgram(); return 0; }
    | EOL { undefProgram(); return 0; }
    | QUIT EOL { clearMemory(); exit(0);}

commands:
    SHOW SETTINGS SEMICOLON { showSettings(); }
    | RESET SETTINGS SEMICOLON { resetSettings(); }
    | SET set;
    | PLOT LPAREN expr RPAREN SEMICOLON { plotExpr($3); }
    | PLOT SEMICOLON { handlePlot(); }
    | RPN LPAREN expr RPAREN SEMICOLON { handleRPN($3); };
    | INTEGRATE LPAREN limit COLON limit COMMA expr RPAREN SEMICOLON { handleIntegrate($3, $5, $7); }
    | SUM LPAREN IDENTIFIER COMMA limit COLON limit COMMA expr RPAREN SEMICOLON { handleSum($3, $5, $7, $9); }
    | expr { handleExpr($1); }
    | MATRIX EQUAL matrix SEMICOLON { matrixEqual($3); }
    | SOLVE DETERMINANT SEMICOLON { handleSolveDeterminant(); }
    | SOLVE LINEAR_SYSTEM SEMICOLON { handleSolveLinearSystem(); }
    | ABOUT SEMICOLON { showAbout(); }
    | IDENTIFIER SEMICOLON { identifier($1); }
    | SHOW MATRIX SEMICOLON { handleShowMatrix(); }
    | IDENTIFIER ASSIGN expr SEMICOLON { assignmentExpr($1, $3); }
    | IDENTIFIER ASSIGN matrix SEMICOLON { assignmentMatrix($1, $3); }
    | SHOW SYMBOLS SEMICOLON { showSymbols(); }
set: 
    H_VIEW limit COLON limit SEMICOLON { setHView($2, $4); }
    | V_VIEW limit COLON limit SEMICOLON { setVView($2, $4); }
    | FLOAT PRECISION limit[value] SEMICOLON { setFloatPrecision($value); }
    | INTEGRAL_STEPS limit SEMICOLON { setIntegralSteps((int)$2); };
    | AXIS boolean SEMICOLON { axis = $2; }
    | ERASE PLOT boolean SEMICOLON { erase_matrix = $3; }
limit: 
    floatValue { $$ = $1;};
    | ADD floatValue { $$ = $2;};
    | SUB floatValue { $$ = -$2; }
    | intValue { $$ = $1;};
    | ADD intValue { $$ = $2;};
    | SUB intValue { $$ = -$2;}
boolean: 
    ON { $$ = true; }; 
    | OFF { $$ = false; };

expr: exprSumSub { $$ = $1; };
exprSumSub: 
    exprSumSub ADD exprMulDiv { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(ADDKW, $1, $3); };
    | exprSumSub SUB exprMulDiv { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(SUBKW, $1, $3); };
    | exprMulDiv { $$ = $1; };
exprMulDiv: 
    exprMulDiv MUL exprPowRest { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(MULKW, $1, $3); };
    | exprMulDiv DIV exprPowRest { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(DIVKW, $1, $3); };
    | exprPowRest {$$ = $1;};
exprPowRest: 
    exprPowRest POW sign { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(POWKW, $1, $3); };
    | exprPowRest REST sign { $$ = ($1 == nullptr || $3 == nullptr)? nullptr:AST(REST, $1, $3); };
    | sign {$$ = $1;};

sign: 
    func { $$ = $1; };
    | ADD func { $$ = $2; };
    | SUB func { $$ = negateTerm($2); };

func: 
    IDENTIFIER { $$ = handleIdentifier($1); }
    | exprValue { $$ = $1; }
    | SEN LPAREN expr RPAREN { $$ = unaryOperation($3, SENKW); }
    | COS LPAREN expr RPAREN { $$ = unaryOperation($3, COSKW); }
    | TAN LPAREN expr RPAREN { $$ = unaryOperation($3, TANKW); }
    | ABS LPAREN expr RPAREN { $$ = unaryOperation($3, ABSKW); };

exprValue: 
    intValue { $$ = createNode(INTKW, OPKW, $1, nullptr); }; 
    | floatValue { $$ = createNode(FLOATKW, OPKW, $1, nullptr); };
    | LPAREN expr RPAREN { 
        int element = $2->element;
        $$ = createNode($2->type, EXPKW, $2->value, $2, element);
    };
    | VAR { $$ = createNode(VARKW, OPKW, 0, nullptr); }
    | PI { $$ = createNode(FLOATKW, OPKW, 3.14159265, nullptr); };
    | E  { $$ = createNode(FLOATKW, OPKW, 2.71828182, nullptr); } ;
intValue: 
    INT { $$ = $1; };
floatValue: 
    REAL { $$ = $1; };

matrix:
    LBRACKET matrixLin matrixCol RBRACKET { $$ = setMatrix($2, $3); };
matrixCol:
    matrixCol COMMA matrixLin { $$ = setMatrixColum($1, $3); }
    | { $$ = nullptr; };
matrixLin:
    LBRACKET limit matrixValue RBRACKET { $$ = setMatrixLine($2, $3); };
matrixValue:
    matrixValue COMMA limit { $$ = setMatrixValue($1, $3); }
    | { $$ = nullptr; };
%%

void incomplete() {
    printf("\nSYNTAX ERROR: Incomplete Command.\n\n");
}

void syntaxError() {
    std::cout << "\nSYNTAX ERROR: [" << yytext << "]\n\n";   
    quit_prog = true;
}

void yyerror(const void* s) {
    if (quit_prog) 
        return;
    if (is_lex)
        is_lex = false;
    else {
        if (yychar == EOL)
            incomplete();
        else 
            syntaxError();
    }
    undef.clear();
    def = false;
}

void continueProgram() {
    quit_prog = def = is_lex = false; 
    undef.clear(); 
}

void undefProgram() {
    quit_prog = is_lex = false; 
    undef.clear(); 
}

int main(int argc, char **argv) {
    while(1) {
        if (!quit_prog)
            printf("> ");
        yyparse();
    }
    return 0;
}