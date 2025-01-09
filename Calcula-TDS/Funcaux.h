#ifndef _FUNC_AUX_
#define _FUNC_AUX_
#include <stdbool.h>

#define MAX_TABS 200       // Deslocamento dos nodos no desenho da arvore de derivacao

enum MOVIM {AVANCA, MANTEM, RETROCEDE};

extern bool mostraArvore;
extern char TABS[MAX_TABS];
extern int contLinha;

void erro(char msg[]);
void PrintNodo(char info[], int movim);
void PrintNodoInt(int val, int movim);


#endif
