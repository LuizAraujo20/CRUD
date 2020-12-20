//=============================================================================
// MISCELÂNEA

void listarFuncionarios(char tipo){
	struct dados_pessoais funcionario[MAX_FUNC];
	unsigned short int indice, contador_entradas;

	contador_entradas = lerArquivo(funcionario);
	system("CLS");
	printf("QUANTIDADE DE FUNCIONARIOS: %i\n", contador_entradas);
	if((tipo == 'v') || (tipo == 'V')){
//		LISTA VERTICALIZADA
		for(indice = 0; indice < contador_entradas; indice++){//mostra nome de todos os func
			printf("\nCodigo : %03u ", funcionario[indice].codigo);
			printf("\nNome   : %s",funcionario[indice].nome);
			printf("\nIdade  : %d",funcionario[indice].idade);
			if(funcionario[indice].sexo == 'f'){
				printf("\nSexo   : feminino");
			}else if(funcionario[indice].sexo == 'm'){
				printf("\nSexo   : masculino");
			}else{
				printf("\nSexo   : indefinido");
			}
			printf("\nCargo  : %s",funcionario[indice].cargo);
			printf("\nSALARIO: R$ %10.2f",funcionario[indice].salario);
			printf("\n");
		}
	}else{
//		LISTA HORIZONTAL
		printf("COD %-30s%-6s%-6s%-20s%-10s\n","NOME","IDADE","SEXO","CARGO","SALARIO(R$)");
		for(indice = 0; indice < contador_entradas; indice++){//mostra nome de todos os func
			printf("%03u ", funcionario[indice].codigo);
			printf("%-30s",funcionario[indice].nome);
			printf("%-6d",funcionario[indice].idade);
			if(funcionario[indice].sexo == 'f'){
				printf("%-6s","FEM");
			}else if(funcionario[indice].sexo == 'm'){
				printf("%-6s","MASC");
			}else{
				printf("%-6s","INDEF");
			}
			printf("%-20s",funcionario[indice].cargo);
			printf("%10.2f",funcionario[indice].salario);
			printf("\n");
		}
	}
}

unsigned short int lerArquivo(struct dados_pessoais funcionario[]){
	unsigned short int contador_entradas;

	FILE *arq;
	arq = fopen("dados_funcionarios.bin", "rb");
	if(arq == NULL){
		puts("\a\a\a\nSEM FUNCIONARIOS CADASTRADOS, VERIFIQUE OS DADOS SALVOS E TENTE NOVAMENTE!");
		Sleep(3);
		exit(1);
	}
	contador_entradas = fread(funcionario, sizeof(struct dados_pessoais), MAX_FUNC, arq);
	fclose(arq);
	return contador_entradas;
}

void zerarBackups(){
	FILE *bkp;
	int indice, contador_bkp = 0, resposta;
	char arquivo_novo[32], arquivo_temp[32];
	char s_indice[2];
    strcpy(arquivo_novo, "BKP\\dados_funcionarios.bin");
//	strcpy(arquivo_anterior, "BKP\\dados_funcionarios.bin");

	strcpy(arquivo_temp, "BKP\\dados_funcionarios");
	itoa(MAX_BKP, s_indice, 10);
	strcat(arquivo_temp, s_indice);		
	strcat(arquivo_temp, ".bin");
	bkp = fopen(arquivo_temp, "rb");
	if(bkp != NULL){
		remove(arquivo_novo);
		fclose(bkp);
		resposta = rename(arquivo_temp, arquivo_novo);

		for(indice = 1; indice < MAX_BKP; indice++){
			strcpy(arquivo_temp, "BKP\\dados_funcionarios");
			itoa(indice, s_indice, 10);
			strcat(arquivo_temp, s_indice);		
			strcat(arquivo_temp, ".bin");
			remove(arquivo_temp);
		}
	}
}

void encerrar(){
	int contador = 3;
	printf("\nENCERRANDO EM:");
	while(contador > 0){
		printf(" %d", contador);
		sleep(1);
		contador--;
		if(contador == 0){
			system("CLS");
			exit(0);
		}
	}
}
//=============================================================================


//=============================================================================
// CONSULTAR

void menuConsulta(){
	unsigned short int contador_erros = 0, contador_entradas;
	struct dados_pessoais funcionario[MAX_FUNC];
	char opcao;
	
	do{
		contador_entradas = lerArquivo(funcionario);
		system("CLS");
		puts("MENU DE CONSULTA FUNCIONARIOS");
		puts("1 - LISTAR TODOS");
		puts("2 - PESQUISAR POR CODIGO");
		puts("3 - PESQUISAR POR NOME");
		puts("4 - PESQUISAR POR IDADE");
		puts("5 - PESQUISAR POR SEXO");
		puts("6 - PESQUISAR POR CARGO");
		puts("7 - PESQUISAR POR SALARIO");
		puts("0 - CANCELAR PESQUISA");
		printf("TIPO DE CONSULTA: ");
		fflush(stdin);
		opcao = getche();

		contador_erros = 0;
		while((opcao > '7')||(isdigit(opcao) == 0)){
			contador_erros++;
			if(contador_erros > 2){		
				printf("\n\nINFORME UM NUMERO DE 0 a 7.");		
				printf("\nTIPO DE CONSULTA: ");
			}else{
				printf("\nOPCAO INVALIDA!");
			}		 
			fflush(stdin);
			opcao = getche();
		}
		switch(opcao){
			case '1':
				listarFuncionarios('h');
				break;	
			case '2':
				pesquisarFuncionarios("CODIGO");
				break;
			case '3':
				pesquisarFuncionarios("NOME");
				break;
			case '4':
				pesquisarFuncionarios("IDADE");
				break;
			case '5':
				pesquisarFuncionarios("SEXO");
				break;
			case '6':
				pesquisarFuncionarios("CARGO");
				break;
			case '7':
				pesquisarFuncionarios("SALARIO");
				break;		
		}
		if(opcao != '0'){			
			printf("\nPRESSIONE QUALQUER TECLA PARA CONTINUAR.\n");
			getch();
		}
	}while(opcao != '0');
}

void pesquisarFuncionarios(char tipo[]){
	struct dados_pessoais funcionario_temp[MAX_FUNC], funcionario[MAX_FUNC];
	unsigned short int indice, cod, posicao, compara_nomes, tamanho, contador_entradas, 
	encontrados = 0, cod_errado = 0, flag = 0;

	contador_entradas = lerArquivo(funcionario);	
//	system("CLS");
	if(strcmp(tipo, "CODIGO") == 0){	//pesquisar por codigo
		cod_errado = 0;
		do{
			printf("\nCODIGO: ");	
			fflush(stdin);
			scanf("%d", &cod);
			encontrados = 0;
			for(indice = 0; indice < contador_entradas; indice++){
				if(funcionario[indice].codigo == cod){
					posicao = indice;
					funcionario_temp[encontrados] = funcionario[posicao];
					encontrados++;
				}
			}
			if(encontrados == 0){
				printf("CODIGO NAO CADASTRADO!\n");
			}
			if(cod_errado > 2){
				listarFuncionarios('h');
			}
			cod_errado++;
		}while(encontrados == 0);
	}//fim if codigo
			
	if(strcmp(tipo, "NOME") == 0){	//pesquisar por nome
		char nome[31];

		puts("\nNOME:");
		fflush(stdin);
		gets(nome);
		strlwr(nome);
		
		char *sub, texto[31];
		encontrados = 0;
		for(indice = 0; indice < contador_entradas; indice++){
			flag = 0;
			strcpy(texto, funcionario[indice].nome);
			strlwr(texto);
			sub = strtok(texto, " !.,");
			while(sub != NULL){
				compara_nomes = strncmp(nome, sub, (strlen(nome)));
				if(compara_nomes == 0){	
					flag = 1;
					break;	
				}
				sub = strtok(NULL, " !.,");
			}
			if(flag == 1){
				funcionario_temp[encontrados] = funcionario[indice];
				encontrados++;
			}
		}		
	}//fim if nome
		
	if(strcmp(tipo, "IDADE") == 0){	//pesquisar por idade	
		unsigned short int idade, contadorTemp = 0;
		char opcao;
		do{
			puts("\nIDADE:");
			scanf("%hu", &idade);
			if(idade < 14){
				puts("Na CLT, a idade mínima prevista é de 14 anos, desde que o menor seja contratado na condição de aprendiz.");
			}
			if(idade > 120){
				puts("Informe uma idade válida, pois com mais de 120 anos é improvável que ainda esteja trabalhando.");
			}
		}while((idade < 14) || (idade > 120));
				
		printf("\n\n1 - menores ou com idade igual a %d", idade);
		printf("\n2 - com idade igual a %d", idade);
		printf("\n3 - maiores ou com idade igual a %d", idade);
		printf("\nDESEJA PROCURAR OS FUNCIONARIOS: ");
		fflush(stdin);
		opcao = getche();
		while((opcao == '0')||(opcao > '3')){
			printf("TIPO DE CONSULTA INVALIDO: ");
			contadorTemp++;
			if(contadorTemp > 2){				
				printf("\n1 - menores ou com idade igual a %d", idade);
				printf("\n2 - com idade igual a %d", idade);
				printf("\n3 - maiores ou com idade igual a %d", idade);
				printf("\nDESEJA PROCURAR OS FUNCIONARIOS: ");
			}
			fflush(stdin);
			opcao = getche();
		}
		encontrados = 0;
		switch(opcao){
			case '1':
				for(indice = 0; indice < contador_entradas; indice++){
					flag = 0;
					if(funcionario[indice].idade <= idade){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}
			break;
			case '2':
				for(indice = 0; indice < contador_entradas; indice++){
					if(idade == funcionario[indice].idade){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}
			break;
			case '3':
				for(indice = 0; indice < contador_entradas; indice++){
					if(funcionario[indice].idade >= idade){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}	
			break;
		}
	}//fim if idade		

	if(strcmp(tipo, "SEXO") == 0){	//pesquisar por sexo
		char sexo;
		
		do{
			puts("\nSEXO: ");
			fflush(stdin);
			sexo = getche();
			sexo = tolower(sexo);
			if(sexo != 'f' && sexo != 'm' && sexo != 'x'){
				puts("F para feminino | M para masculino | X para indefinido ");
			}		
		}while(sexo != 'f' && sexo != 'm' && sexo != 'x');

		encontrados = 0;
		for(indice = 0; indice < contador_entradas; indice++){
			if(sexo == funcionario[indice].sexo){
				funcionario_temp[encontrados] = funcionario[indice];
				encontrados++;
			}
		}	
	}//fim if sexo

	if(strcmp(tipo, "CARGO") == 0){	//pesquisar por cargo
		char cargo[21];

		puts("\nCARGO:");
		fflush(stdin);
		gets(cargo);
		strlwr(cargo);
		
		char *sub, texto[21];
		encontrados = 0;
		for(indice = 0; indice < contador_entradas; indice++){
			flag = 0;
			strcpy(texto, funcionario[indice].cargo);
			strlwr(texto);
			sub = strtok(texto, " !.,");
			while(sub != NULL){				
				compara_nomes = strcmp(cargo, funcionario[indice].cargo);
				if(compara_nomes == 0){	
					flag = 1;
					break;	
				}
				compara_nomes = strncmp(cargo, sub, (strlen(cargo)));
				if(compara_nomes == 0){	
					flag = 1;
					break;	
				}
				sub = strtok(NULL, " !.,");
			}
			if(flag == 1){
				funcionario_temp[encontrados] = funcionario[indice];
				encontrados++;
			}
		}		
	}//fim if cargo

	if(strcmp(tipo, "SALARIO") == 0){	//pesquisar por salario	
		unsigned short int contadorTemp = 0;
		float salario;
		char opcao;

		do{
			printf("\nSALARIO: R$ ");
			scanf("%f", &salario);
			if(salario < 400){
				puts("Informe um salário válido, pois menos que R$ 400,00 nem jovem aprendiz recebe...");
			}
		}while(salario < 400);
		printf("\nDESEJA PROCURAR OS FUNCIONARIOS: ");
		printf("\n1 - com salario igual ou menor que R$%.2f", salario);
		printf("\n2 - com salario igual a R$%.2f", salario);
		printf("\n3 - com salario igual ou maior que R$%.2f", salario);
		fflush(stdin);
		opcao = getche();
		while((opcao == '0')||(opcao > '3')){
			printf("\nTIPO DE CONSULTA INVALIDO: ");
			contadorTemp++;
			if(contadorTemp > 2){				
				printf("\nDESEJA PROCURAR OS FUNCIONARIOS: ");
				printf("\n1 - com salario igual ou menor que R$%.2f", salario);
				printf("\n2 - com salario igual a R$%.2f", salario);
				printf("\n3 - com salario igual ou maior que R$%.2f", salario);
			}
			fflush(stdin);
			opcao = getche();
		}
		
		encontrados = 0;
		switch(opcao){
			case '1':
				for(indice = 0; indice < contador_entradas; indice++){
					if(funcionario[indice].salario <= salario){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}
				break;
			case '2':
				for(indice = 0; indice < contador_entradas; indice++){
					if(salario == funcionario[indice].salario){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}
				break;
			case '3':
				for(indice = 0; indice < contador_entradas; indice++){
					if(funcionario[indice].salario >= salario){	
						funcionario_temp[encontrados] = funcionario[indice];
						encontrados++;
					}
				}	
				break;
		}
	}//fim if salario
	system("CLS");
	printf("PESQUISA POR %s", tipo);
	printf("\nQUANTIDADE DE FUNCIONARIOS ENCONTRADOS: %i\n\n", encontrados);
	
//	fazer somatorio dos salarios

	printf("%-4s%-30s%-6s%-6s%-20s%-10s\n", "COD","NOME","IDADE","SEXO","CARGO","SALARIO(R$)");
	if(encontrados <= 0){
		puts("NENHUM FUNCIONARIO ENCONTRADO COM A INFORMACAO SOLICITADA.");
	}else{
		for(indice = 0; indice < encontrados; indice++){//mostra nome de todos os func		
			printf("%03u ", funcionario_temp[indice].codigo);
			printf("%-30s",funcionario_temp[indice].nome);
			printf("%-6d",funcionario_temp[indice].idade);
			if(funcionario_temp[indice].sexo == 'f'){
				printf("%-6s%","FEM");
			}else if(funcionario_temp[indice].sexo == 'm'){
				printf("%-6s%","MASC");
			}else{
				printf("%-6s%","INDEF");
			}
			printf("%-20s",funcionario_temp[indice].cargo);
			printf("%10.2f",funcionario_temp[indice].salario);
			printf("\n");
		}
	}
	printf("\n\n");
}
//=============================================================================


//=============================================================================
// CADASTRO & ALTERAÇÃO

void lerValidarNome(char nome[]){
	struct dados_pessoais funcionario[MAX_FUNC];
	unsigned short int contador_entradas, indice;
	do{
		contador_entradas = lerArquivo(funcionario);
		puts("\nNOME COMPLETO:");
		fflush(stdin);
		gets(nome);
		if((strlen(nome) <= 5)){
			puts("informe um nome valido!");
		}
		if((strlen(nome) > 30)){
			puts("informe um nome menor!");
		}
	}while((strlen(nome) <= 5)||(strlen(nome) > 30));

	for(indice = 0; indice < contador_entradas; indice++){
		while(strcmp(nome, funcionario[indice].nome) == 0){
			puts("FuncionÃ¡rio jÃ¡ cadastrado, informe outro nome:");
			fflush(stdin);
			gets(nome);
			if((strlen(nome) <= 5)){
				puts("informe um nome vÃ¡lido!");
			}
			indice = 0;
		}
	}
}

int lerValidarIdade(){
	unsigned int idade;
	do{
		puts("IDADE:");
		scanf("%d", &idade);
		if(idade < 14){
			puts("Na CLT, a idade mÃ­nima prevista Ã© de 14 anos, desde que o \nmenor seja contratado na condiÃ§Ã£o de aprendiz.");
		}
		if(idade > 100){
			puts("Informe uma idade vÃ¡lida, pois com mais de 100 anos Ã© \nimprovÃ¡vel que ainda esteja trabalhando.");
		}
	}while((idade < 14) || (idade > 120));
	return idade;
}

char lerValidarSexo(){
	char sexo;
	do{
		puts("SEXO: ");
		fflush(stdin);
		sexo = getchar();
		sexo = tolower(sexo);
		if(sexo != 'f' && sexo != 'm' && sexo != 'x'){
			puts("F para feminino | M para masculino | X para indefinido ");
		}
	}while(sexo != 'f' && sexo != 'm' && sexo != 'x');
	return sexo;
}

void lerValidarCargo(char cargo[]){
	do{
		puts("CARGO:");
		fflush(stdin);
		gets(cargo);
		if(strlen(cargo) < 3){
			puts("Informe um cargo vÃ¡lido!");
		}
		if(strlen(cargo) > 20){
			puts("Informe um cargo menor que 20!");
		}
	}while((strlen(cargo) < 3)||(strlen(cargo) > 20));
}

float lerValidarSalario(){
	float salario;
	do{
		printf("SALARIO:\nR$ ");
		scanf("%f", &salario);
		if(salario < 400){
			puts("Informe um salÃ¡rio vÃ¡lido, pois menos que R$ 400,00 \nnem jovem aprendiz recebe...");
		}
	}while(salario < 400);
	return salario;
}
//=============================================================================


//=============================================================================
// CADASTRO

void cadastrarFuncionarios(){
	FILE *arq;
	char continuar = 's';
	unsigned short int contador_entradas;
	struct dados_pessoais funcionario_gravar, funcionario[MAX_FUNC];
	
	system("CLS");
	puts("CADASTRO DE FUNCIONARIOS");
	do{
		contador_entradas = lerArquivo(funcionario);

		unsigned short entradas_temp = (funcionario[contador_entradas - 1].codigo);
		funcionario_gravar.codigo =  entradas_temp + 1;
		printf("\nFUNCIONARIO %d", (contador_entradas + 1));
		lerValidarNome(funcionario_gravar.nome);
		funcionario_gravar.idade = lerValidarIdade();
		funcionario_gravar.sexo = lerValidarSexo();
		lerValidarCargo(funcionario_gravar.cargo);
		funcionario_gravar.salario = lerValidarSalario();

		arq = fopen("dados_funcionarios.bin", "ab");
		contador_entradas = fwrite(&funcionario_gravar, sizeof(struct dados_pessoais), 1, arq);
		if((arq == NULL) || (contador_entradas == 0)){
			printf("\a\a\a\nERRO AO SALVAR CADASTRO!");
			encerrar();
		}else{
			printf("\a\a\a\nCADASTRO SALVO COM SUCESSO!\n");
		}
		fclose(arq);
		printf("\nNovo cadastro? (s para continuar) ");
		fflush(stdin);
		continuar = getchar();
		if(continuar != 's' && continuar != 'S'){
			break;
		}
	}while(contador_entradas < MAX_FUNC);
}
//=============================================================================


//=============================================================================
// ALTERAÇÃO

void editarFuncionario(){	
	FILE *arq;
	char continuar = 's', opcao;
	int indice, posicao, cod, resultado, controle_erros, contadorTemp, contador_entradas;
//	struct dados_pessoais c[MAX_FUNC];
	struct dados_pessoais funcionario[MAX_FUNC];

	do{	
		system("CLS");
		puts("EDITAR CADASTRO DE FUNCIONARIOS");
		
		contador_entradas = lerArquivo(funcionario);
		puts("TEM O CODIGO DO FUNCIONARIO?\n(s para sim)");
		fflush(stdin);
		continuar = getche();
		if(continuar != 's' && continuar != 'S'){			
			listarFuncionarios('h');
		}
		//pesquisar por codigo
		controle_erros = 0;
		printf("\nCODIGO: ");
		fflush(stdin);
		scanf("%d", &cod);
		while((cod < 0) || (cod >= MAX_FUNC)){
			controle_erros++;
			if(controle_erros > 2){
				printf("\nCODIGO INVALIDO, INFORME ALGO ENTRE 0 E %d.", (contador_entradas - 1));
			}				
			printf("\nCODIGO DO FUNCIONARIO: ");
			scanf("%d", &cod);

		}
//		pegar a posicao do cod inserido
		for(indice = 0; indice < contador_entradas; indice++){
			if(funcionario[indice].codigo == cod){
				posicao = indice;
//				break;
			}
		}
		do{
			system("CLS");
			printf("CADASTRO DO FUNCIONARIO:");
			printf("\nCODIGO : %u ", funcionario[posicao].codigo);
			printf("\n1 - NOME   : %s", funcionario[posicao].nome);
			printf("\n2 - IDADE  : %d", funcionario[posicao].idade);

			if(funcionario[posicao].sexo == 'f'){
				printf("\n3 - SEXO   : %s","FEMININO");
			}else if(funcionario[posicao].sexo == 'm'){
				printf("\n3 - SEXO   : %s","MASCULINO");
			}else{
				printf("\n3 - SEXO   : %s","INDEFINIDO");
			}
			printf("\n4 - CARGO  : %s", funcionario[posicao].cargo);
			printf("\n5 - SALARIO: R$ %.2f", funcionario[posicao].salario);
//			fclose(arq);		
			printf("\n0 - CANCELAR");
			printf("\nALTERAR:");
			fflush(stdin);
			opcao = getche();		

			controle_erros = 0;
			if(opcao != '!'){			
				while((opcao > '5') || (isdigit(opcao) == 0)){
					controle_erros++;
					if(controle_erros > 2){		
						printf("\n\nINFORME UM NUMERO DE 0 a 5.");		
						puts("\n1 - NOME");
						puts("2 - IDADE");
						puts("3 - SEXO");
						puts("4 - CARGO");
						puts("5 - SALARIO");
						puts("0 - CANCELAR");
						printf("ALTERAR:");
					}else{
						printf("\nOPCAO INVALIDA: ");
					}		 
					fflush(stdin);
					opcao = getche();
				}
			}
			if(opcao != '0'){			
				switch(opcao){
					char texto_temp[31], sexo_temp;
					float salario_temp;
					int idade_temp;
					case '1':
						do{
							puts("\nNOME COMPLETO:");
							fflush(stdin);
							gets(texto_temp);
							if((strlen(texto_temp) <= 5)){
								puts("informe um nome válido!");
							}
							if((strlen(texto_temp) > 30)){
								puts("informe um nome menor!");
							}
						}while((strlen(texto_temp) <= 5) || (strlen(texto_temp) > 30));							
						printf("\nANTES : %s", funcionario[posicao].nome);
						printf("\nDEPOIS: %s", texto_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");//tive que passar todos pra dentro dos IFs, pois, às vezes, qndo fechava o prg apagava o arquivo
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								strcpy(funcionario[posicao].nome, texto_temp);
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}						
						break;
					case '2':			
						do{
							printf("\nIDADE:");
							scanf("%d", &idade_temp);
							if(idade_temp < 14){
								puts("Na CLT, a idade mínima prevista é de 14 anos, desde que o menor seja contratado na condição de aprendiz.");
							}
							if(idade_temp > 120){
								puts("Informe uma idade válida, pois com mais de 120 anos é improvável que ainda esteja trabalhando.");
							}
						}while((idade_temp < 14) || (idade_temp > 120));						
						printf("\nANTES : %d", funcionario[posicao].idade);
						printf("\nDEPOIS: %d", idade_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].idade = idade_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);							
						}
						break;
					case '3':
						do{
							printf("\nSEXO: ");
							fflush(stdin);
							sexo_temp = getche();
							sexo_temp = tolower(sexo_temp);
							if(sexo_temp != 'f' && sexo_temp != 'm' && sexo_temp != 'x'){
								puts("F para feminino | M para masculino | X para indefinido ");
							}		
						}while(sexo_temp != 'f' && sexo_temp != 'm' && sexo_temp != 'x');						
						printf("\nANTES : %c", funcionario[posicao].sexo);
						printf("\nDEPOIS: %c", sexo_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].sexo = sexo_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}
						break;
					case '4':
						do{
							puts("\nCARGO:");
							fflush(stdin);
							gets(texto_temp);
							if(strlen(texto_temp) < 3){
								puts("Informe um cargo válido!");
							}
							if(strlen(texto_temp) > 20){
								puts("Informe um cargo menor que 20!");
							}
						}while((strlen(texto_temp) < 3)||(strlen(texto_temp) > 20));
						printf("\nANTES : %s", funcionario[posicao].cargo);
						printf("\nDEPOIS: %s", texto_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								strcpy(funcionario[posicao].cargo, texto_temp);
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}						
						break;
					case '5':					      
						do{  
							printf("\nSALARIO:\nR$ ");
							scanf("%f", &salario_temp);
						//		salário mínimoR$ 1.045,00 
							if(salario_temp < 400){
								puts("Informe um salário válido, pois menos que R$ 400,00 nem jovem aprendiz recebe...");
							}    
						}while(salario_temp < 400);						
						printf("\nANTES : R$%.2f", funcionario[posicao].salario);
						printf("\nDEPOIS: R$%.2f", salario_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].salario = salario_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}
						break;	
					case '!':
							printf("\nALTERAR CODIGO DESSE FUNCIONARIO? ");
							printf("\n('s' para sim | 'x' para cancelar):  ");

							fflush(stdin);
							continuar = getche();
							if(continuar == 'x' || continuar == 'X'){
								break;
							}
							if(continuar != 's' && continuar != 'S'){
								int cod_errado = 0;
								do{
									printf("\nINFORME OUTRO CODIGO: ");		
									fflush(stdin);
									scanf("%d", &cod);
									for(indice = 0; indice < contador_entradas; indice++){
										if(funcionario[indice].codigo == cod){
											posicao = indice;
											cod_errado++;
										}
									}
									if(cod_errado == 0){
										printf("\nCODIGO INVALIDO!");		
									}
								}while(cod_errado == 0);

								printf("\nCODIGO : %u ", funcionario[posicao].codigo);
								printf("\n1 - NOME   : %s", funcionario[posicao].nome);
								printf("\n2 - IDADE  : %d", funcionario[posicao].idade);

								if(funcionario[posicao].sexo == 'f'){
									printf("\n3 - SEXO   : %s","FEMININO");
								}else if(funcionario[posicao].sexo == 'm'){
									printf("\n3 - SEXO   : %s","MASCULINO");
								}else{
									printf("\n3 - SEXO   : %s","INDEFINIDO");
								}
								printf("\n4 - CARGO  : %s", funcionario[posicao].cargo);
								printf("\n5 - SALARIO: R$ %.2f", funcionario[posicao].salario);

							}
						int codigo_temp;
						printf("\n\nCODIGO NOVO: ");
						scanf("%d", &codigo_temp);

						printf("\nANTES : %d", funcionario[posicao].codigo);
						printf("\nDEPOIS: %d", codigo_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's' || continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].codigo = codigo_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
								fclose(arq);
							}
						}
						break;							
				}//fim switch
			}//fim if != '0'
			printf("\nEditar o mesmo funcionario? (s para sim) ");
			fflush(stdin);
			continuar = getche();
//			contador_entradas = lerArquivo(c);
		}while(continuar == 's' || continuar == 'S');

		printf("\nEditar outro funcionario? (s para sim) ");
		fflush(stdin);
		continuar = getche();
		if(continuar != 's' && continuar != 'S'){
			break;
		}			
	}while(contador_entradas < MAX_FUNC);
}
//=============================================================================


//=============================================================================
// DELETAR

void deletarFuncionario(char tipo[]){	
	FILE *arq, *bkp;
	char continuar, opcao;
	int contador_entradas, resultado, cod, controle_erros, contadorTemp, indice, posicao;
	struct dados_pessoais c[MAX_FUNC], funcionario[MAX_FUNC];

	if(strcmp(tipo, "MENU") == 0){
		system("CLS");
		puts("APAGAR CADASTRO DE FUNCIONARIOS");
		arq = fopen("dados_funcionarios.bin", "rb");
		if(arq == NULL){
			printf("\a\a\nNENHUM BANCO DE DADOS ENCONTRADO!");
			printf("\nDESEJA CRIAR UM NOVO BANCO DE DADOS? 's' para sim: ");
			fflush(stdin);
			opcao = getchar();
			if(opcao == 's' || opcao == 'S'){
				bkp = fopen("dados_funcionarios.bin", "wb");
				fclose(bkp);
//				deletarFuncionario("MENU");
			}else{
				puts("DESEJA RESTAURAR O ULTIMO BACKUP?");
				puts("'s' para sim: ");
				fflush(stdin);
				opcao = getchar();
				if(opcao == 's' || opcao == 'S'){
					deletarFuncionario("RESTAURAR");
				}else{
					printf("\nENCERRANDO PROGRAMA!");
					sleep(5);
					exit(1);
				}
			}
		}
		fclose(arq);
		
		puts("1 - LISTAR TODOS");
		puts("2 - INSERIR CODIGO");
		puts("3 - RESTAURAR BACKUP");
		puts("0 - APAGAR TODOS");
		printf("OPCAO: ");
		fflush(stdin);
		opcao = getche();
		contadorTemp = 0;
		while((opcao > '3') || (isdigit(opcao) == 0)){
			contadorTemp++;
			if(contadorTemp > 2){	
				printf("\n\nINFORME UM NUMERO DE 0 a 2.");	
				puts("\n1 - LISTAR TODOS");	
				puts("2 - INSERIR CODIGO");
				puts("3 - RESTAURAR BACKUP");
				puts("0 - APAGAR TODOS");
				printf("OPCAO:");
			}else{
				printf("\nOPCAO INVALIDA: ");
			}		 
			fflush(stdin);
			opcao = getche();
		}
		if(opcao == '0'){
			deletarFuncionario("TODOS");
		}
		if(opcao == '1'){
			deletarFuncionario("LISTAR");
		}
		if(opcao == '2'){
			deletarFuncionario("INSERIR");
		}
		if(opcao == '3'){
			deletarFuncionario("RESTAURAR");
		}
	}	//fim if menu
	    
	if(strcmp(tipo, "TODOS") == 0){	
	    char arquivo_anterior[32];
	    char arquivo_novo[32];
	    char arquivo_temp[32];
	    char s_indice[2];
	    int flag = 0;
			printf("\a\a\n's' PARA APAGAR OS DADOS DE TODOS OS FUNCIONARIOS:\n");
			fflush(stdin);
			continuar = getchar();

			if(continuar == 's' || continuar == 'S'){
			    strcpy(arquivo_anterior, "dados_funcionarios.bin");
			    strcpy(arquivo_novo, "BKP\\dados_funcionarios.bin");
				int resposta;
			    if((arq = fopen("dados_funcionarios.bin", "rb")) == NULL){
					puts("ERRO AO APAGAR O ARQUIVO, NENHUM BANCO DE DADOS ENCONTRADO!");
					sleep(5);
					exit(1);
				}else{
					fclose(arq);
					bkp = fopen("BKP\\dados_funcionarios.bin", "rb");						
					if(bkp != NULL){
						for(indice = 1; indice <= MAX_BKP; indice++){	
				   			strcpy(arquivo_temp, "BKP\\dados_funcionarios");
							itoa(indice, s_indice, 10);
							strcat(arquivo_temp, s_indice);
							strcat(arquivo_temp, ".bin");
							fclose(bkp);
							if((arq = fopen(arquivo_temp, "rb")) == NULL){
								break;
							}
							fclose(arq);
						}
						strcpy(arquivo_novo, arquivo_temp);
					}
				}
				resposta = rename(arquivo_anterior, arquivo_novo);
			    if(resposta == 0) {
			      printf("\nARQUIVO APAGADO COM SUCESSO.\n");
			    }else{
			       printf("\nNAO FOI POSSIVEL APAGAR O ARQUIVO\n");
			    }	
			}
		}	//fim if pagar
	if(strcmp(tipo, "LISTAR") == 0){
		listarFuncionarios('h');
	}	//fim if listar
	
	if(strcmp(tipo, "INSERIR") == 0){	
		puts("\nPOSSUI O CODIGO DO FUNCIONARIO?");
		printf("'s' para sim: ");
		fflush(stdin);
		continuar = getchar();
		contador_entradas = lerArquivo(funcionario);	//atualizar funcionario e contador
		if(continuar != 's' && continuar != 'S'){
			listarFuncionarios('h');
		}
		puts("\nINFORME O CODIGO DO FUNCIONARIO:");
		scanf("%u", &cod);
		controle_erros = 0;
		for(indice = 0; indice < contador_entradas; indice++){
			if(funcionario[indice].codigo == cod){
				posicao = indice;
				controle_erros++;
			}
		}
		if(controle_erros == 0){
			puts("\nNENHUM FUNCIONARIO ENCONTRADO!");
		}else{
			printf("\nCodigo : %03u ", funcionario[posicao].codigo);
			printf("\nNome   : %s",funcionario[posicao].nome);
			printf("\nIdade  : %d",funcionario[posicao].idade);
			if(funcionario[posicao].sexo == 'f'){
				printf("\nSexo   : feminino");
			}else if(funcionario[posicao].sexo == 'm'){
				printf("\nSexo   : masculino");
			}else{
				printf("\nSexo   : indefinido");
			}
			printf("\nCargo  : %s",funcionario[posicao].cargo);
			printf("\nSALARIO: R$ %10.2f",funcionario[posicao].salario);
			printf("\n");
			
			puts("DESEJA APAGAR DADOS DESSE FUNCIONARIO?");
			fflush(stdin);
			continuar = getchar();
			if(continuar == 's' || continuar == 'S'){
				for(indice = posicao; indice < (contador_entradas - 1); indice++){
					funcionario[indice] = funcionario[indice + 1];
				}
				arq = fopen("dados_funcionarios.bin", "wb");
				if(arq == NULL){
					printf("\a\a\nFALHA AO DELETAR! NÂO FOI POSSIVEL ACESSAR O BANCO DE DADOS.");
					sleep(5);
					exit(1);
				}			
				fwrite(funcionario, sizeof(struct dados_pessoais), (contador_entradas - 1), arq);
				fclose(arq);
				puts("CADASTRO APAGADO COM SUCESSO!");
				struct dados_pessoais funcionario_temp[contador_entradas];
				for(indice = posicao; indice < (contador_entradas - 1); indice++){
					funcionario_temp[indice] = funcionario[indice];
				}
			}
		}
	}	//fim if inserir
			
	if(strcmp(tipo, "RESTAURAR") == 0){
	    char arquivo_anterior[32];
	    char arquivo_novo[32];
	    char arquivo_temp[32];
	    char s_indice[2];
	    int flag = 0;
	    
		printf("\a\a\n's' PARA RESTAURAR O BACKUP MAIS RECENTE: ");
		fflush(stdin);
		continuar = getchar();
		if(continuar == 's' || continuar == 'S'){
		    strcpy(arquivo_anterior, "BKP\\dados_funcionarios.bin");
		    strcpy(arquivo_novo, "dados_funcionarios.bin");
			int resposta;
		    if((arq = fopen("BKP\\dados_funcionarios.bin", "rb")) == NULL){
		    	flag = 0;
		    	for(indice = 1; indice <= MAX_BKP; indice++){
					strcpy(arquivo_temp, "BKP\\dados_funcionarios");
					itoa(indice, s_indice, 10);
					strcat(arquivo_temp, s_indice);
					strcat(arquivo_temp, ".bin");
					if((arq = fopen(arquivo_temp, "rb")) != NULL){
						fclose(arq);
						flag = 1;
						strcpy(arquivo_anterior, arquivo_temp);
					}
				}
		    	if(flag == 0){
					puts("ERRO AO RESTAURAR O ARQUIVO, NENHUM BACKUP ENCONTRADO!");
					sleep(5);
					exit(1);
				}
			}else{
				fclose(arq);
				flag = 0;
		    	for(indice = 1; indice <= MAX_BKP; indice++){
					strcpy(arquivo_temp, "BKP\\dados_funcionarios");
					itoa(indice, s_indice, 10);
					strcat(arquivo_temp, s_indice);
					strcat(arquivo_temp, ".bin");
					if((arq = fopen(arquivo_temp, "rb")) != NULL){
						fclose(arq);
						flag = 1;
						strcpy(arquivo_anterior, arquivo_temp);	
					}
				}
				if(flag == 0){						
					strcpy(arquivo_anterior, "BKP\\dados_funcionarios.bin");
				}
			}
			arq = fopen("dados_funcionarios.bin", "rb");
			if(arq != NULL){
				puts("JA EXISTE UM BANCO DE DADOS, DESEJA SUBSTITUIR?('s' para sim) ");
				fflush(stdin);
				continuar = getchar();
				fclose(arq);
				if(continuar != 's' && continuar != 'S'){
					deletarFuncionario("MENU");
				}
			}
			remove(arquivo_novo);
			fclose(arq);
			
			resposta = rename(arquivo_anterior, arquivo_novo);
		    if(resposta == 0) {
		      printf("\nARQUIVO RESTAURADO COM SUCESSO.\n");
			  contador_entradas = lerArquivo(funcionario);			      
		    }else{
		       printf("\nNAO FOI POSSIVEL RESTAURAR O ARQUIVO\n");
		    }	
		}
	}	// fim if restaurar
}
//=============================================================================


//=============================================================================
// ANALISAR

void analisarCadastros(char tipo[]){
	char opcao;	
	int contador_erros;
	
	if(strcmp(tipo, "MENU") == 0){
		system("CLS");
		puts("MENU ANALISE DO CADASTRO");
		puts("1 - ANALISE GERAL");
		puts("2 - ANALISE DOS CODIGOS");
		puts("3 - ANALISE DOS NOMES");
		puts("4 - ANALISE DAS IDADES");
		puts("5 - ANALISE DOS SEXOS");
		puts("6 - ANALISE DOS CARGOS");
		puts("7 - ANALISE DOS SALARIOS");
		puts("0 - MENU PRINCIPAL");
		printf("OPCAO: ");
		fflush(stdin);
		opcao = getche();
		contador_erros = 1;
		while((opcao > '7') || (isdigit(opcao) == 0)){
			if(contador_erros > 3){
				puts("\nOPCAO INVALIDA, INFORME UM NUMERO ENTRE 0 E 4!");
				puts("1 - ANALISE GERAL");
				puts("2 - ANALISE DOS CODIGOS");
				puts("3 - ANALISE DOS NOMES");
				puts("4 - ANALISE DAS IDADES");
				puts("5 - ANALISE DOS SEXOS");
				puts("6 - ANALISE DOS CARGOS");
				puts("7 - ANALISE DOS SALARIOS");
				puts("0 - MENU PRINCIPAL");
			}
			printf("\nOPCAO: ");
			fflush(stdin);
			opcao = getche();
			contador_erros++;
		}
		system("CLS");
	}

	if(opcao == '1'){
		analisarCadastros("GERAL");
	}
	if(opcao == '2'){
		analisarCadastros("CODIGO");
	}
	if(opcao == '3'){
		analisarCadastros("NOME");
	}
	if(opcao == '4'){
		analisarCadastros("IDADE");
	}
	if(opcao == '5'){
		analisarCadastros("SEXO");
	}
	if(opcao == '6'){
		analisarCadastros("CARGO");
	}
	if(opcao == '7'){
		analisarCadastros("SALARIO");
	}
	
	if(strcmp(tipo, "GERAL") == 0){
		analisarCadastros("CODIGO");
		puts("\n");
		analisarCadastros("NOME");
		puts("\n");
		analisarCadastros("IDADE");
		puts("\n");
		analisarCadastros("SEXO");
		puts("\n");
		analisarCadastros("CARGO");
		puts("\n");
		analisarCadastros("SALARIO");
		puts("\n");
	}	
	if(strcmp(tipo, "CODIGO") == 0){
		puts("ccccooooooooddddiiiiiiiiiiggggggggoooooooo");
		
		
	}
	if(strcmp(tipo, "NOME") == 0){
		puts("NNNNNNNNOOOOOOOOOOOOOOMMMMMMMMEEEEEEEEE");
		
		
	}
	if(strcmp(tipo, "IDADE") == 0){
		puts("iiiiiiiiiiidddddddddaaaaaaaadddddddeeeee");
		
		
	}
	if(strcmp(tipo, "SEXO") == 0){
		puts("sssssssseeeeeeeexxxxxxxxoooooooooooo");
		
		
	}
	if(strcmp(tipo, "CARGO") == 0){
		puts("cccccccccaaaaaarrrrgooooooooooo");
		
		
	}
	if(strcmp(tipo, "SALARIO") == 0){
		puts("sssssssssssaaaaallllllarrrrriiiiiiiiiiiooooooooo");
		
		
		
	}
}
//=============================================================================

















