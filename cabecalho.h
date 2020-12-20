/*
Name: gerenciamento_de_funcionarios.c
Copyright: MIT License
Author: Luiz Araujo - luizcarlos_bsb2006@hotmail.com
Date: 19/12/2020
Description: manipulação de arquivos, utilizando struct; com cadastro, atualização ,
exclusÃ£o e consulta de funcionarios de uma forma que persista apÃ³s o fechamento do programa.
*/

#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

#define MAX_FUNC 100//se mais que 30.000 alterar de unsigned short para unsigned int
#define MAX_BKP 10	//quantidade de backups
struct dados_pessoais{
	unsigned short codigo;	//2bytes
	char nome[31];			//31bytes
	unsigned short idade;	//2bytes
	char sexo;				//1bytes
	char cargo[21];			//21bytes
	float salario;			//4bytes
};

//============================================================================
// MISCELÂNEA

// Retorna a quantidade de funcinários cadastrados e todos os cadastros
//em um vetor de struct
unsigned short int lerArquivo(struct dados_pessoais funcionario[]);

// Mostra todo o cadastro, argumentos:
// -> 'v' : lista verticalmente, melhor visualização de cada;
// -> 'h' : lista horizontalmente, melhor visualização de tudo.
void listarFuncionarios(char tipo);

//usado no deletar, transforma o último backup em primeiro e apaga os seguintes
void zerarBackups();

// Encerra o programa com uma contagem regressiva
void encerrar();
//=============================================================================

//=============================================================================
// CONSULTAR

// Dá opções de filtro para consulta
void menuConsulta();

// Efetua a pesquisa e mostra o resultado.
// Argumentos: "CODIGO", "NOME", "IDADE", "SEXO", "CARGO" ou "SALARIO".
void pesquisarFuncionarios(char tipo[]);
//=============================================================================

//=============================================================================
// CADASTRO & ALTERAÇÃO

// Lê e valida as entradas,
// Retornam para: cadastrarFuncionarios(); & editarFuncionarios();
void lerValidarNome();
int lerValidarIdade();
char lerValidarSexo();
void lerValidarCargo();
float lerValidarSalario();

// CADASTRA OS FUNCIONARIOS
void cadastrarFuncionarios();
//=============================================================================

//=============================================================================
// ALTERAR

// Edita cadastro pelo código do funcionário.
void editarFuncionario();
//=============================================================================

//=============================================================================
// APAGAR

// Apaga cadastros de funcionários, argumentos:
// "TODOS" - apaga tudo, mas faz backup;
// "LISTAR" - lista tudo;
// "INSERIR" - apaga funcionário específico, pelo código;
// "RESTAURAR" - restaura o backup mais recente, se houver.
void deletarFuncionario(char tipo[]);

//=============================================================================

//=============================================================================
// ANALISAR

void analisarCadastros(char tipo[]);
//=============================================================================



















































































#endif // CABECALHO_H_INCLUDED

