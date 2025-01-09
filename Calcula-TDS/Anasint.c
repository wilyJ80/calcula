/*  Gramática livre de Contexto de Cálcula

    <ARTIB> ::= ID = <EXPR>
	<EXPR> ::= <TERMO> <RESTO>
	<RESTO> ::= + <TERMO> <RESTO> |	- <TERMO> <RESTO> | e
	<TERMO> ::= <FATOR> <SOBRA>
	<SOBRA> ::= * <FATOR> <SOBRA> | / <FATOR> <SOBRA> | e
	<FATOR> ::= CT_I | ID | (<EXPR>)

   Símbolo de partida: <ATRIB>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"
#include "Cores.h"



void Atrib() {

    int k;
    char cmdObj[20];

	if (mostraArvore) PrintNodo("<Atrib>", AVANCA);
	t = Analex(fd_in);
	if (t.cat != ID) {
        erro("Identificador esperado!");
	}

	if ((k = BuscaTabIdetif(t.lexema)) < 0)    // Localiza ou insere identificador na
        k = InsereTabIdentif(t.lexema);        // Tabela de Identificadores

	if (mostraArvore) PrintNodo(t.lexema, MANTEM);
	t = Analex(fd_in);
	if (t.cat != SN || t.codigo != ATRIB) {
		erro("Sinal de atribuicao esperado!");
	}
	t.processado = true;

	if (mostraArvore) PrintNodo("=", MANTEM);

	Expr();     // Constroi sub-arvore de EXPR

	sprintf(cmdObj, "STOR %d\n", tabIdentif.identificador[k].ender);
	fputs(cmdObj, fd_out);

	if (mostraArvore) {
	    printf(_RED_);   // Muda cor do texto para vermelho
        PrintNodo(cmdObj, MANTEM);
        printf(_STD_);    // Retorna cor do texto para padrao
	}
	if (mostraArvore) PrintNodo("", RETROCEDE);
}


void Expr() {

	if (mostraArvore) PrintNodo("<Expr>", AVANCA);

	Termo();    // Constroi sub-arvore de TERMO
	Resto();    // Constroi sub-arvore de RESTO

	if (mostraArvore) PrintNodo("", RETROCEDE);
}

void Termo(){

	if (mostraArvore) PrintNodo("<Termo>", AVANCA);

	Fator();  // Constroi sub-arvore de FATOR
	Sobra();  // Constroi sub-arvore de SOBRA

	if (mostraArvore) PrintNodo("", RETROCEDE);

}

void Resto() {

    int codOper;

	if (mostraArvore) PrintNodo("<Resto>", AVANCA);

	if (t.processado) t = Analex(fd_in);
	if (t.cat == SN && (t.codigo == ADICAO || t.codigo == SUBTRACAO)) {
		t.processado = true;
		codOper = t.codigo;

		if (mostraArvore) {
			if (t.codigo == ADICAO) PrintNodo("+", MANTEM);
			else PrintNodo("-", MANTEM);
		}

		Termo();        // Constroi sub-arvore de TERMO

		if (codOper == ADICAO) fputs("ADD\n", fd_out);
        else fputs("SUB\n", fd_out);

        if (mostraArvore) {
            printf(_RED_);   // Muda cor do texto para vermelho
			if (codOper == ADICAO) PrintNodo("ADD", MANTEM);
			else PrintNodo("SUB", MANTEM);
            printf(_STD_);    // Retorna cor do texto para padrao
		}

		Resto();        // Constroi sub-arvore de RESTO

	}
	else if (mostraArvore) PrintNodo("<e>", MANTEM); // Sai por cadeia vazia

	if (mostraArvore) PrintNodo("", RETROCEDE);
}

void Sobra() {

    int codOper;

	if (mostraArvore) PrintNodo("<Sobra>", AVANCA);

	if (t.processado) t = Analex(fd_in);
	if(t.cat == SN && (t.codigo == MULTIPLIC || t.codigo == DIVISAO)) {
		t.processado = true;
		codOper = t.codigo;

		if (mostraArvore) {
			if (t.codigo == MULTIPLIC) PrintNodo("*", MANTEM);
			else PrintNodo("/", MANTEM);
		}

		Fator();   // Constroi sub-arvore de FATOR

		if (codOper == MULTIPLIC) fputs("MUL\n", fd_out);
        else fputs("DIV\n", fd_out);
        if (mostraArvore) {
            printf(_RED_);   // Muda cor do texto para vermelho
			if (codOper == MULTIPLIC) PrintNodo("MUL", MANTEM);
			else PrintNodo("DIV", MANTEM);
            printf(_STD_);    // Retorna cor do texto para padrao
		}

		Sobra(); // Constroi sub-arvore de SOBRA

	}
	else if (mostraArvore) PrintNodo("<e>", MANTEM);  // Sai por cadeia vazia

	if (mostraArvore) PrintNodo("", RETROCEDE);
}

void Fator() {

    char cmdObj[20];
    int k;

	if (mostraArvore) PrintNodo("<Fator>", AVANCA);

	if (t.processado) t = Analex(fd_in);

	if(t.cat == ID) {
		t.processado = true;
		if (mostraArvore) PrintNodo(t.lexema, MANTEM);

		if ((k = BuscaTabIdetif(t.lexema)) < 0) erro("Identificador nao definido!");
		sprintf(cmdObj, "LOAD %d\n", tabIdentif.identificador[k].ender);
	    fputs(cmdObj, fd_out);

	    if (mostraArvore) {
            printf(_RED_);   // Muda cor do texto para vermelho
            PrintNodo(cmdObj, MANTEM);
            printf(_STD_);    // Retorna cor do texto para padrao
	    }
	}

	else if (t.cat == CT_I) {
		t.processado = true;
		if (mostraArvore) PrintNodoInt(t.valInt, MANTEM);

		sprintf(cmdObj, "PUSH %d\n", t.valInt);
	    fputs(cmdObj, fd_out);

	    if (mostraArvore) {
            printf(_RED_);   // Muda cor do texto para vermelho
            PrintNodo(cmdObj, MANTEM);
            printf(_STD_);    // Retorna cor do texto para padrao
	    }
	}

	else if (t.cat == SN && t.codigo == ABRE_PAR) {
		t.processado = true;
		if (mostraArvore) PrintNodo("(", MANTEM);
		Expr();
		if(t.cat != SN || t.codigo != FECHA_PAR) {
			erro("Fecha parenteses esperado!");
		}
		else {
			t.processado = true;
			if (mostraArvore) PrintNodo(")", MANTEM);
		}
	}

	else {
		erro("Identificador, constante inteira ou abre parenteses esperado!");
	}

	if (mostraArvore) PrintNodo("", RETROCEDE);
}
