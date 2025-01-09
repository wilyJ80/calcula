#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"
#include "Tabidentific.h"
#include "Cores.h"
#include "ansi_escapes.h"


/* Variaveis globais */
TOKEN t;
FILE *fd_in, *fd_out;
int contLinha;
TAB_IDENTIF tabIdentif;
bool mostraArvore;
char TABS[MAX_TABS] = "";



void ExecAnalex() {

    if ((fd_in=fopen("expressao.dat", "r")) == NULL)
        erro("Arquivo de entrada da expressao nao encontrado!");

    printf("\nLINHA %d: ", contLinha);
    while (true) {
        t = Analex(fd_in);
        if (t.cat == FIM_ARQ) {
            printf(_YELLOW_); printf("\n\nFim do arquivo encontrado."); printf(_STD_);
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
    }
    fclose(fd_in);
}

void ExecAnasint() {

    if ((fd_in=fopen("expressao.dat", "r")) == NULL)
        erro("Arquivo de entrada da expressao nao encontrado!");

    if ((fd_out=fopen("expressao.obj", "w")) == NULL)
        erro("Arquivo de saída do codigo gerado nao pode ser criado!");

    IniciaTabIdentif();

    do
        Atrib();
    while (t.cat==FIM_EXPR);

    if (t.cat==FIM_ARQ) {
        printf(_YELLOW_);
        printf("Expressões OK. Codigo objeto gerado!\n");
        printf(_STD_);
    }
    else {
        erro("Erro de sintaxe!");
    }
    fclose(fd_in);
    fclose(fd_out);
}

int main() {

    system("chcp 65001");  // Troca a página de códigos de caracteres 
                           // da console para UTF-8 na execução
    contLinha = 1;
    setupConsole();
    printf(_GREEN_); // Muda cor do texto para verde
    printf("\n\n[Analise Léxica --------------------------------]\n");
    printf(_STD_);    // Retorna cor do texto para padrao
    ExecAnalex(); 

    contLinha = 1;
    mostraArvore = true;
    printf(_GREEN_); // Muda cor do texto para verde
    printf("\n\n[Tradução Dirigida pela Sintaxe ----------------]\n");
    printf(_STD_);
    ExecAnasint();
    restoreConsole();
}
