#include "cabecalho.h"

int main(void){
	setlocale(LC_COLLATE, "Portuguese");
	setlocale(LC_MONETARY, "Portuguese");
	setlocale(LC_NUMERIC, "Portuguese");
	setlocale(LC_TIME, "Portuguese");
	char opcao;
	unsigned short contador = 5, contador_erros;
	

	printf("%c%c%c%c%c\n", 201, 205, 205, 205, 187);
	printf("%c   %c\n", 186, 186);
	printf("%c   %c\n", 186, 186);
	printf("%c   %c\n", 186, 186);
	printf("%c   %c\n", 186, 186);
	printf("%c%c%c%c%c\n", 204, 205, 205, 205, 185);	
	printf("%c%c%c%c%c\n", 200, 205, 205, 205, 188);
	
	do{
		system("CLS");
		puts("MENU PRINCIPAL - FUCIONARIOS");
		puts("1 - CONSULTAR");
		puts("2 - CADASTRAR");
		puts("3 - ANALISAR");
		puts("4 - ALTERAR");
		puts("5 - APAGAR");
		puts("0 - SAIR");
		printf("OPCAO: ");
		fflush(stdin);
		opcao = getche();
		contador_erros = 1;
		while((opcao > '5') || (isdigit(opcao) == 0)){
			if(contador_erros > 3){
				puts("OPCAO INVALIDA, INFORME UM NUMERO ENTRE 0 E 4!");
				puts("1 - CONSULTAR");
				puts("2 - CADASTRAR");
				puts("3 - ANALISAR");
				puts("4 - ALTERAR");
				puts("5 - APAGAR");
				puts("0 - SAIR");
			}
			printf("OPCAO: ");
			fflush(stdin);
			opcao = getche();
			contador_erros++;
		}
		switch(opcao){
			case '0':
				encerrar();
				break;
			case '1':
				menuConsulta();
				break;
			case '2':
				cadastrarFuncionarios();
				break;
			case '3':
				do{
					analisarCadastros("MENU");
					printf("\nNOVA ANALISE?\n(s para sim) ");
					fflush(stdin);
					opcao = getche();
				}while(opcao == 's' || opcao == 'S');
					
				
					
				break;
			case '4':				
				zerarBackups();
				do{
					deletarFuncionario("MENU");					
					printf("\nNOVA OPERACAO?\n(s para sim) ");
					fflush(stdin);
					opcao = getche();
				}while(opcao == 's' || opcao == 'S');
				break;
			case '5':
				editarFuncionario();
				break;
		}
	}while(1);
	
	return 0;
}

#include "funcoes.c"
