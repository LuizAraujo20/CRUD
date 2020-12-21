#include "cabecalho.h"

int main(void){
	setlocale(LC_COLLATE, "Portuguese");
	setlocale(LC_MONETARY, "Portuguese");
	setlocale(LC_NUMERIC, "Portuguese");
	setlocale(LC_TIME, "Portuguese");
	char opcao;
	unsigned short contador = 5, contador_erros;
	struct dados_pessoais funcionario[MAX_FUNC];
	do{
		system("CLS");
		puts("MENU PRINCIPAL");
		puts("1 - CONSULTAR");
		puts("2 - CADASTRAR");
		puts("3 - ALTERAR");
		puts("4 - APAGAR");
		puts("0 - SAIR");
		printf("OPCAO: ");
		fflush(stdin);
		opcao = getche();
		contador_erros = 1;
		while((opcao > '4') || (isdigit(opcao) == 0)){
			if(contador_erros > 3){
				puts("OPCAO INVALIDA, INFORME UM NUMERO ENTRE 0 E 4!");
				puts("1 - CONSULTAR");
				puts("2 - CADASTRAR");
				puts("3 - ALTERAR");
				puts("4 - APAGAR");
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
				contador = lerArquivo(funcionario);
				if(contador <= 0){
					system("CLS");
					puts("NENHUM FUNCIONARIO ENCONTRADO!");
					getch();
					break;
				}
				break;
			case '2':
				cadastrarFuncionarios();
				break;
			case '3':
				contador = lerArquivo(funcionario);
				if(contador <= 0){
					system("CLS");
					puts("NENHUM FUNCIONARIO ENCONTRADO!");
					getch();
					break;
				}
				editarFuncionario();
				break;
			case '4':			
				zerarBackups();				
				contador = lerArquivo(funcionario);
				if(contador <= 0){
					system("CLS");
					puts("NENHUM FUNCIONARIO ENCONTRADO!");
					getch();
					break;
				}
				do{
					deletarFuncionario("MENU");					
					printf("\nNOVA OPERACAO?\n(s para sim) ");
					fflush(stdin);
					opcao = getche();
				}while(opcao == 's' || opcao == 'S');
				break;
		}
	}while(1);
	
	return 0;
}

#include "funcoes.c"
