#ifndef _ANASINT_
#define _ANASINT_

#include <stdio.h>
#include <stdbool.h>
#include "Analex.h"
#include "Funcaux.h"
#include "Tabidentific.h"



/* Variaveis globais */
extern TOKEN t;
extern FILE *fd_in, *fd_out;
extern TAB_IDENTIF tabIdentif;
extern bool mostraArvore;
extern char TABS[MAX_TABS];

/* Assinaturas das funcoes */
void Atrib();
void Expr();
void Termo();
void Resto();
void Sobra();
void Fator();

#endif // ANASINT
