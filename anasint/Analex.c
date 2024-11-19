#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#include "Funcaux.h"

#define TAM_LEXEMA 50
#define TAM_NUM 20


TOKEN Analex(FILE *fd) {

    int estado;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_NUM] = "";
    int tamD = 0;


    estado = 0;
    t.processado = false;
    while (true) {
        char c = fgetc(fd);
        switch (estado) {
            case 0: if (c == ' ' || c == '\t') estado = 0;
                    else if (c >= 'a' && c <= 'z') {  // início de identificador - inicializa lexema
                        estado = 1;
                        lexema[tamL] = c; 
                        lexema[++tamL] = '\0';
                    }
                    else if (c >= '1' && c <= '9') {  // início de constante inteira - inicializa digitos
                        estado = 10;
                        digitos[tamD] = c; 
                        digitos[++tamD] = '\0';       
                    }
                    else if (c == '+') {    // sinal de adição - monta e devolve token
                        estado = 3;
                        t.cat = SN;
                        t.codigo = ADICAO;
                        return t;
                    }
                    else if (c == '-') {    // sinal de subtração - monta e devolve token
                        estado = 4;
                        t.cat = SN;
                        t.codigo = SUBTRACAO;
                        return t;
                    }
                    else if (c == '*') {    // sinal de multiplicação - monta e devolve token
                        estado = 6;
                        t.cat = SN;
                        t.codigo = MULTIPLIC;
                        return t;
                    }
                    else if (c == '/') {    // sinal de divisao - monta e devolve token
                        estado = 5;
                        t.cat = SN;
                        t.codigo = DIVISAO;
                        return t;
                    }
                    else if (c == '=') {    // sinal de atribuicao - monta e devolve token
                        estado = 7;
                        t.cat = SN;
                        t.codigo = ATRIB;
                        return t;
                    }
                    else if (c == '(') {   // sinal de abre parênteses - monta e devolve token
                        estado = 8;
                        t.cat = SN;
                        t.codigo = ABRE_PAR;
                        return t;
                    }
                    else if (c == ')') {    // sinal de fecha parênteses - monta e devolve token
                        estado = 9;
                        t.cat = SN;
                        t.codigo = FECHA_PAR;
                        return t;
                    }
                    else if (c == '\n') {
                        estado = 0;
                        t.cat = FIM_EXPR;   // fim de linha (ou expressão) encontrado
                        contLinha++;
                        return t;
                    }
                    else if (c=='\r') {    // para tratar arquivos de dados Windows no Mac
                        estado = 0;
                    }
                    else if (c == EOF) {    // fim da expressão encontrado
                           t.cat = FIM_ARQ;
                           return t;
                    }
                    else  
                        erro("Caracter inválido na expressão!");    // sem transição válida no AFD
                    break;
            case 1: if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_')) {   
                        estado = 1;
                        lexema[tamL] = c;      // acumula caracteres lidos em lexema
                        lexema[++tamL] = '\0';
                    }
                    else {                     // transição OUTRO* do estado 1 do AFD
                        estado = 2;            // monta token identificador e retorna
                        ungetc(c, fd);
                        t.cat = ID;
                        strcpy(t.lexema, lexema);
                        return t;
                    }
                    break;
            case 10:if (c >= '0' && c <= '9') {
                        estado = 10;
                        digitos[tamD] = c;       // acumula dígitos lidos na variável dígitos
                        digitos[++tamD] = '\0';
                    }
                    else {                       // transição OUTRO* do estado 10 do AFD
                        estado = 11;             // monta token constante inteira e retorna
                        ungetc(c, fd);
                        t.cat = CT_I;
                        t.valInt = atoi(digitos);
                        return t;
                    }
        }                    
    }
}

