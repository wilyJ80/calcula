#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"

/* Variaveis globais */
TOKEN t;
FILE *fd;
int contLinha;
bool mostraArvore;
char TABS[200] = "";


void TestaAnalex() {
    
    if ((fd=fopen("expressao.dat", "r")) == NULL)
        erro("Arquivo de entrada da expressão nao encontrado!");
    
    printf("\nLINHA %d: ", contLinha);
    while (true) {
        t = Analex(fd);
        if (t.cat == FIM_ARQ) {
            printf("Fim do arquivo fonte encontrado!\n");
            break;
        }
        switch (t.cat) {
            case ID: printf("<ID, %s> ", t.lexema);
                     break;
            case SN: switch (t.codigo) {
                        case ADICAO: printf("<SN, ADICAO> ");
                        break;
                        case SUBTRACAO: printf("<SN, SUBTRACAO> ");
                        break;
                        case MULTIPLIC: printf("<SN, MULTIPLICACAO> ");
                        break;
                        case DIVISAO: printf("<SN, DIVISAO> ");
                        break;
                        case ATRIB: printf("<SN, ATRIBUICAO> ");
                        break;
                        case ABRE_PAR: printf("<SN, ABRE_PARENTESES> ");
                        break;
                        case FECHA_PAR: printf("<SN, FECHA_PARENTESES> ");
                        break;
                     }
                     break;
            case CT_I: printf("<CT_I, %d> ", t.valInt);
                       break;
            case FIM_EXPR: printf("<FIM_EXPR, %d>\n", 0);
                           printf("\nLINHA %d: ", contLinha);
                           break;           
        }
        if (t.cat == FIM_ARQ) break;
    }
    fclose(fd);
}

void TestaAnasint() {
    
    if ((fd=fopen("expressao.dat", "r")) == NULL)
        erro("Arquivo de entrada da expressão nao encontrado!");
    
    while (true) {
        t = Analex(fd);
        if (t.cat == FIM_ARQ) {
            printf("\nFim do arquivo fonte encontrado!\n");
            break;
        }
        Atrib();
        if (t.cat==FIM_EXPR)
            printf("\nLINHA %d: Expressão sintaticamente correta!\n\n", contLinha - 1);
        else {
            erro("Erro de sintaxe!");
        }
    }
    fclose(fd);
}

int main() {

    system("chcp 65001");  // Troca a página de códigos de caracteres 
                           // da console para UTF-8 na execução

    contLinha = 1;
    printf("\n\n[Análise Léxica -------------------]\n");
    TestaAnalex();

    contLinha = 1;
    mostraArvore = false;
    printf("\n\n[Análise Sintática ----------------]\n");
    TestaAnasint();

}
