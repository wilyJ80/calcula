#include <stdlib.h>
#include <string.h>
#include "Funcaux.h"
#include "Tabidentific.h"
#include "Cores.h"



void IniciaTabIdentif() {
    tabIdentif.tamTab = 0;
}


int BuscaTabIdetif(char nomeId[]) {

    int i;

    for (i=0; i<tabIdentif.tamTab; i++) {
        if (!(strcmp(nomeId, tabIdentif.identificador[i].nomeId))) return i;
    }
    return -1;
}


int InsereTabIdentif(char nomeId[]) {

    int i;
    if (tabIdentif.tamTab == TAM_MAX_TAB_IDENTIF) erro("Estouro na tabela de identificadores!");
    i = tabIdentif.tamTab;
    strcpy(tabIdentif.identificador[i].nomeId, nomeId);
    tabIdentif.identificador[i].ender = i;
    tabIdentif.tamTab++;
    return i;
}
