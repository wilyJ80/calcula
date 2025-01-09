#ifndef _TAB_IDENTIFIC_
#define _TAB_IDENTIFIC_

#include <stdlib.h>
#include <stdio.h>
#include "Analex.h"

#define TAM_MAX_TAB_IDENTIF 200

typedef
    struct {
        char nomeId[TAM_MAX_LEXEMA];
        int ender;
    } REG_IDENTIF;                      // Uma entrada na Tabela de Identificadores


typedef
    struct {
        int tamTab;
        REG_IDENTIF identificador[TAM_MAX_TAB_IDENTIF];
    } TAB_IDENTIF;                      // Tabela de identificadores


/* Variaveis globais */
extern TOKEN t;
extern TAB_IDENTIF tabIdentif;

/* Assinaturas de funcoes */
void IniciaTabIdentif();
int BuscaTabIdetif(char []);
int InsereTabIdentif(char []);

#endif // _TAB_IDENTIFIC_
