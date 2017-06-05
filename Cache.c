/* Implementacão da Memoria Cache */
/* Disciplina : Organizacão e Arquitetura de Computadores II */
/* Professor : Mr.Luciano Lores Caimi */
/* Aluno : Raffael Bottoli Schemmer */
/* Data Termino : 24/11/2008 */
/* Politica de Mapeamento : Mapeamento Associativo : Cada bloco pode ocupar qualquer quadro */
/* Politica de Substituicao : LFU : O Bloco que tem o menor numero de acessos é o que será sobrescrito */
/* Politica de Escrita : Escreve o dado tanto na cache quanto na memoria principal */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h> // scanf printf fflush stdin
#include <stdlib.h> // srand rand ltoa strtol system atoi
#include<string.h> // strlen strcat
#include<time.h> // time
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char binario[8];
char temp_char[8]; // Declaracao de variaveis char
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int tamanho;
int x,y,z;
int temp1,temp2,temp4,temp5;
int temp; // Declaracao de variaveis inteiras
int temp_int[8];
int rotulo,deslocamento;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct memoria_principal // Estrutura responsavel por alocar a memoria principal
{
	int conteudo; 
}mp[32][4];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct cache // Estrutura responsavel por alocar a memoria cache
{
	int conteudo[4];
	int rotulo; 
	int numero_acessos;
}c[8];
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct estatistica // Estrutura responsavel por alocar as estatisticas do simulador
{
	int numero_acessos;
	int numero_acertos;
	int numero_faltas;
	int numero_leituras;
	int numero_escritas; 
	int numero_acertos_leitura;
	int numero_acertos_escrita;
	int numero_faltas_leitura;
	int numero_faltas_escrita;
}estatistica;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void iniciar_simulador() // Funcao reponsavel por inicializar os valores da memoria principal e da cache e das estatisticas
{
	x=0,y=0,z=0; // Inicializacao de variaveis temporarias
	srand(time(NULL)); // Gerador de sementes
	while(x < 32) // Iniciando memoria principal
	{
		y=0;
		while(y < 4) // Inicializando o conteudo dos blocos
		{
			do
			{
				z = rand()%255; // Gera um valor aleatorio entre 0 - 255
			}while(z < 0 || z > 255);
			mp[x][y].conteudo = z; // Memoria principal [x]bloco [y]celula recebe o valor aleatorio de 0 - 255
			y++; // Contador de celulas
		}
		x++; // Contador de blocos
	}
	x=0;
	while(x < 8) // Inicializando a memoria cache
	{
		y=0;
		while(y < 4) // Inicializando o conteudo dos quadros
		{
			c[x].conteudo[y] = mp[x][y].conteudo; // Quadro recebe o conteudo dos blocos da memoria principal
			c[x].numero_acessos = 0; // Contador de substituicao do quadro da cache é inicializado com zero
			y++; // Incrementa o contador de celulas dos quadros
		}
		c[x].rotulo = x; // Rotulo recebe o numero do bloco da memoria principal
		x++; // Contador de blocos
	}
	estatistica.numero_acessos=0;
	estatistica.numero_acertos=0;
	estatistica.numero_faltas=0;
	estatistica.numero_leituras=0; // As estatisticas do simulador são inicializadas com zero
	estatistica.numero_escritas=0;
	estatistica.numero_acertos_leitura=0;
	estatistica.numero_acertos_escrita=0;
	estatistica.numero_faltas_leitura=0;
	estatistica.numero_faltas_escrita=0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar_memorias() // Funcao reponsavel por mostrar os valores da memoria principal e da cache no simulador
{
	x=0,y=0; // Inicializacao de variaveis temporarias
	printf("          | -- Memoria Principal -- |\t\t\t      | -- Memoria Cache -- |\n\n\n\n"); // Titulo inicial da cache e da memoria principal
	while(x < 32) // Contador de blocos
	{
		y=0; // Inicializacao de variavel temporaria responsavel por andar no bloco
		ltoa(x,binario,2); // Converte o valor inteiro para binario
		tamanho = strlen(binario); // Conta o tamanho da string em binario
		printf("| "); 
		if(tamanho == 1){printf("0000%s ",binario);} // Completa com zeros a esquerda o valor em binario para que ele tenha tamanho igual a 5 
		if(tamanho == 2){printf("000%s ",binario);}
		if(tamanho == 3){printf("00%s ",binario);}
		if(tamanho == 4){printf("0%s ",binario);}
		if(tamanho == 5){printf("%s ",binario);}
		while(y < 4) // Varre o bloco a procura das celulas para imprimir em tela
		{
			ltoa(mp[x][y].conteudo,binario,2); // Converte o valor do conteudo da celula de inteiro decimal para binario caracter
			tamanho = strlen(binario); // Conta o tamanho da string em binario
			if(tamanho == 1){printf("0000000%s",binario);}
			if(tamanho == 2){printf("000000%s",binario);} // Completa com zeros a esquerda o valor em binario para que ele tenha tamanho igual a 8
			if(tamanho == 3){printf("00000%s",binario);}
			if(tamanho == 4){printf("0000%s",binario);}
			if(tamanho == 5){printf("000%s",binario);}
			if(tamanho == 6){printf("00%s",binario);}
			if(tamanho == 7){printf("0%s",binario);}
			if(tamanho == 8){printf("%s",binario);}
			printf(" ");
			y++;
		}
		printf("|");
		if(x < 8) // Estrutura responsavel por imprimir os 8 quadros da memoria cache
		{
			ltoa(x,binario,2); // Converte o valor de inteiro decimal para binario caracter
			tamanho = strlen(binario); // Conta o tamanho da string em binario
			if(tamanho == 1){printf("  | 00%s ",binario);} // Completa com zeros a esquerda o valor em binario para que ele tenha tamanho igual a 3
			if(tamanho == 2){printf("  | 0%s ",binario);}
			if(tamanho == 3){printf("  | %s ",binario);}
			ltoa(c[x].rotulo,binario,2); // Converte o rotulo de inteiro decimal para binario caracter
			tamanho = strlen(binario); // Conta o tamanho da string em binario
			if(tamanho == 1){printf(" 0000%s ",binario);}
			if(tamanho == 2){printf(" 000%s ",binario);} // Completa com zeros a esquerda o valor em binario para que ele tenha tamanho igual a 5
			if(tamanho == 3){printf(" 00%s ",binario);}
			if(tamanho == 4){printf(" 0%s ",binario);}
			if(tamanho == 5){printf(" %s ",binario);}			
			y=0;
			while(y < 4) // Estrutura responsavel por imprimir o conteudo das celulas do quadro
			{
				ltoa(c[x].conteudo[y],binario,2); // Converte o conteudo da celula para binario caracter
				tamanho = strlen(binario); // Conta o tamanho da string em binario
				if(tamanho == 1){printf("0000000%s",binario);}
				if(tamanho == 2){printf("000000%s",binario);} // Completa com zeros a esquerda o valor em binario para que ele tenha tamanho igual a 8
				if(tamanho == 3){printf("00000%s",binario);}
				if(tamanho == 4){printf("0000%s",binario);}
				if(tamanho == 5){printf("000%s",binario);}
				if(tamanho == 6){printf("00%s",binario);}
				if(tamanho == 7){printf("0%s",binario);}
				if(tamanho == 8){printf("%s",binario);}
				printf(" ");
				y++;
			}
			printf("%d ",c[x].numero_acessos); // Mostra o numero de acessos do quadro 
			printf("|");
		}
		printf("\n"); // Quebra de linha para formatacao em tela
		x++; // Incrementa o contador de quadros/blocos
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void prenche_endereco(int endereco,char binario[8]) // Funcao reponsavel por prencher com zeros a esquerda um endereco informado pelo usuario
{
	temp1=0; // Inicializacao de variavel temporaria
	ltoa(endereco,binario,2); // Converte a variavel endereco inteira  para binario caracter
	temp = strlen(binario); // Conta o tamanho da string em binario
	temp = 7 - temp;  // Subtrai o tamanho de 7 para saber quantos zeros precisa adicionar a esquerda
	while(temp1 < temp) // Adiciona zeros enquanto o contador for diferente do valor subtraido acima ao vetor tempchar
	{
		temp_char[temp1] = '0';
		temp1++;
	}
	temp_char[temp1] = '\0'; // Coloca \0 dizendo que a string termina nessa posicao
	strcat(temp_char,binario); // Contacena o endereco contido em binario informado pelo usuario ao vetor de zeros criados
	tamanho = strlen(temp_char); // Conta o tamanho da nova string
	z=0; 
	while(z < 7) // Enquanto o contador z for menor que 7 transfere o conteudo de tempchar para a string binario
	{
		binario[z] = temp_char[z];
		z++;				
	}
	binario[z] = '\0'; // Coloca \0 em binario indicando que a string termina aqui
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void divide_endereco(int endereco,int *rotulo,int *deslocamento) // Funcao responsavel por dividir o endereco em rotulo e deslocamento
{
	y=0; // Inicializa contadores temporarios
	z=0;
	prenche_endereco(endereco,binario); // Chama a funcao prenche endereco passando o endereco(inteiro) e um vetor de caracteres que ira receber o endereco deslocado N vezes
	z=0;
	while(z < 5) // Enquanto o contador for menor que 5 faz o vetor tempchar receber os 5 primeiros caracteres (rotulo) do endereco binario
	{
		temp_char[z] = binario[z];
		z++;	
		
	}
	temp_char[z] = '\0'; // Coloca \0 em tempchar indicando que a string termina aqui
	*rotulo = strtol(temp_char,NULL,2); // Converte o valor em binario de tempchar para inteiro e atribui o resultado a rotulo
	y=0;
	while(z < 7) // Enquanto o contador for menor que 7 faz o vetor tempchar receber os 2 ultimos caracteres (deslocamento) do endereco binario
	{
		temp_char[y] = binario[z];
		z++;
		y++;
	}
	temp_char[y] = '\0'; // Coloca \0 em tempchar indicando que a string termina aqui
	*deslocamento = strtol(temp_char,NULL,2); // Converte o valor em binario de tempchar para inetiro e atribui o reultado a deslocamento
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int procura_quadro_menor_acesso() // Funcao responsavel por procurar o quadro com o menor numero de acessos
{
	y=0; // Inicializacao de variavel temporaria
	temp4 = c[0].numero_acessos; // Inicializa temp4 com o numero de acesso do primeiro quadro
	temp5 = 0; 
	while(y < 8) // Varre os 8 quadros da memoria cache
	{
		if(temp4 > c[y].numero_acessos) // Caso o quadro temporario seja maior que o quadro indice contador
		{
			temp4 = c[y].numero_acessos; // O numero de acesso do quadro é então alocado em temp4
			temp5 = y; // temp5 aloca o numero de quadro que tem o menor numero de acesso
		}
		y++;
	}
	return(temp5); // É retornado o quadro que tiver o quadro com o menor numero de acessos
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int le_endereco(int endereco,int *_rotulo,int *_deslocamento,int *_valor,int *_quadro) // Funcao responsavel por ler enderecos na cache ou na memoria principal
{	
	divide_endereco(endereco,&rotulo,&deslocamento);  // Chama a funcao divide endereco passando o endereco a ser dividido em rotulo (5bits) e deslocamento (2bits)
	temp=0,temp1=0; // Inicializa variaveis temporarias
	while(temp < 8) // Array que varre a cache
	{
		if(c[temp].rotulo == rotulo) // Caso o rotulo do endereco informado for igual a um rotulo da cache o endereco se encontra na cache
		{
			*_valor = c[temp].conteudo[deslocamento]; // Faz o valor que vai ser retornado ao usuario receber o valor presente na celula do quadro da cache onde os rotulos foram iguais
			c[temp].numero_acessos++; // O contador de acesso do quadro é incrementado
			*_deslocamento = deslocamento; // Retorna o deslocamento para a chamada para mostrar ao usuario
			*_rotulo = rotulo; // Retorna o rotulo para a chamada para mostrar ao usuario
			*_quadro = temp; // Retorna o quadrp para a chamada para mostrar ao usuario
			estatistica.numero_acessos++; // Incrementa o numero de acessos da cache pois a cache foi acessada
			estatistica.numero_acertos++; // Incrementa o numero de acertos pois a cache acertou
			estatistica.numero_leituras++; // Incrementa o numero de leituras pois a cache leu
			estatistica.numero_acertos_leitura++; // Incrementa o numero de acertos em leituras pois a cache acertou lendo
			return(1); // Retorna 1 informando que a cache acertou
		}
		temp++;
	}
	temp2 = procura_quadro_menor_acesso(); // Caso a cache erre ele procura o quadro com o menor numero de acesso para ser substituido 
	c[temp2].numero_acessos = 0;  // O quadro a ser substituido então é zerado
	c[temp2].rotulo = rotulo; // O quadro recebe o novo rotulo informado pelo endereco do usuario
	*_quadro = temp2; // O valor do novo quadro é retornado para o usuario
	*_deslocamento = deslocamento; // O valor do deslocamento é retornado para o usuario
	*_rotulo = rotulo; // O valor do rotulo é retornado para o usuario
	c[temp2].conteudo[0] = mp[rotulo][0].conteudo;  // O conteudo do quadro da cache é atualizado com o bloco da RAM de indice rotulo do endereco solicitado
	c[temp2].conteudo[1] = mp[rotulo][1].conteudo; 
	c[temp2].conteudo[2] = mp[rotulo][2].conteudo; 
	c[temp2].conteudo[3] = mp[rotulo][3].conteudo; 
	*_valor = c[temp2].conteudo[deslocamento]; // O novo valor do endereco solicitado para a leituar é lido da cache
	c[temp2].numero_acessos++;
	estatistica.numero_acessos++; // Incrementa o numero de acessos pois a cache foi acessada
	estatistica.numero_faltas++; // Incrementa o numero de faltas pois o endereco nao foi encotrado na cache
	estatistica.numero_leituras++; // Incrementa o numero de leituras pois a cache foi lida
	estatistica.numero_faltas_leitura++; // Incrementa o numero de faltas de leitura pois houve uma falta ao ler a cache
	return(0); // retorna zero indicando que o endereco nao foi lido diretamente da cache mas sim da memoria principal
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int escreve_endereco(int endereco,int * _rotulo,int * _deslocamento,int * _valor,int * _quadro) // Funcao responsavel por escrever enderecos na cache ou na memoria principal
{
	divide_endereco(endereco,&rotulo,&deslocamento); // Chama a funcao divide endereco passando o endereco a ser dividido em rotulo (5bits) e deslocamento (2bits)
	temp=0,temp1=0; // Inicializacao de variaveis temporarias
	while(temp < 8)  // Array que varre a cache
	{
		if(c[temp].rotulo == rotulo) // Caso o rotulo do endereco informado for igual a um rotulo da cache o endereco se encontra na cache
		{
			c[temp].numero_acessos++;  // Incrementa o contado de numero de acesso da cache
			c[temp].conteudo[deslocamento] = *_valor; // faz a celula do quado receber o dado informado pelo usuario
			mp[rotulo][0].conteudo = c[temp].conteudo[0];  // O valor do rotulo será utilizado para atualizar o valor bloco correspondente na memoria principal pois como a politica
			mp[rotulo][1].conteudo = c[temp].conteudo[1];  // é de escrita em ambas, toda vez que o quadro da cache for atualizado o seu bloco correspondente no rotulo deve ser 
			mp[rotulo][2].conteudo = c[temp].conteudo[2];  // tambem atualizada
			mp[rotulo][3].conteudo = c[temp].conteudo[3]; 
			*_deslocamento = deslocamento; // Retorna para a chama da funcao o valor do deslocamento para mostrar ao usuario
			*_rotulo = rotulo; // Retorna para a chamada da funcao o valor do rotulo para mostrar ao usuario
			*_quadro = temp; // Retorna para a chamada da funcao o valor do quadro para mostrar ao usuario
			estatistica.numero_acessos++; // Incrementa o contador de acessos do simulador
			estatistica.numero_acertos++; // Incrementa o contador de acertos pois a cache acertou
			estatistica.numero_escritas++; // Incrementa o contador de escritas pois a cache escreveu
			estatistica.numero_acertos_escrita++; // Incrementa o contador de acertos na escrita pois a cache acertou em uma escrita
			return(1); // Retorna 1 indicando que o endereco foi encontrado na cache
		}
		temp++;
	}
	temp2 = procura_quadro_menor_acesso();  // Caso o endereco nao for encontrado na cache é necessario chamar a funcao procura_quadro_menor_acesso que vai procurar o quadro 
	c[temp2].numero_acessos = 0;  // que ira armazenar o valor que será buscado na memoria principal
	c[temp2].conteudo[0] = mp[rotulo][0].conteudo;  // O contador de numero de acessos do quadro localizado pela chamada da funcao é zerado (pois ira receber um novo bloco)
	c[temp2].conteudo[1] = mp[rotulo][1].conteudo; // O quadro da cache é atualizado com o valor do bloco da memoria principal
	c[temp2].conteudo[2] = mp[rotulo][2].conteudo; 
	c[temp2].conteudo[3] = mp[rotulo][3].conteudo; 
	c[temp2].conteudo[deslocamento] = *_valor; // o conteudo da memoria cache é atualizado com o valor do dado informado pelo usuario
	c[temp2].rotulo = rotulo;  // o rotulo da cache recebe o novo rotulo(endereco do bloco)
	mp[rotulo][0].conteudo = c[temp2].conteudo[0]; // A memoria principal novamente é atualizada com seu novo valor devido a politica de escrita em ambas
	mp[rotulo][1].conteudo = c[temp2].conteudo[1]; 
	mp[rotulo][2].conteudo = c[temp2].conteudo[2]; 
	mp[rotulo][3].conteudo = c[temp2].conteudo[3];
	*_deslocamento = deslocamento; // Retorna para a chamada da funcao o valor do deslocamento para mostrar ao usuario
	*_rotulo = rotulo; // Retorna para a chamada da funcao o valor do rotulo para mostrar ao usuario
	*_quadro = temp2; // Retorna para a chamada da funcao o valor do quadro para mostrar ao usuario
	c[temp2].numero_acessos++;
	estatistica.numero_faltas++; // Incrementa o contador de faltas pois houve falta na cache
	estatistica.numero_acessos++; // Incrementa o contador de numero de acessos pois a cache foi acessada
	estatistica.numero_escritas++; // Incrementa o numero de escritas pois a cache foi acessada para fazer uma escrita
	estatistica.numero_faltas_escrita++; // Incrementa o numero de faltas de escrita pois ao escrever o endereco nao foi encontrado
	return(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrar_estatisticas()
{
	if(estatistica.numero_acessos > 0) // Caso o numero de acessos for maior que zero imprime a sequencia abaixo
	{
		printf("\n\nGeral : %d (%d%%)\n\n",estatistica.numero_acessos,100); // Imprime o numero geral de acessos
		printf("Numero de acertos : %d (%0.0f%%)\n",estatistica.numero_acertos,(float)(estatistica.numero_acertos*100)/(float)estatistica.numero_acessos);  // Imprime o numero de acertos
		printf("Numero de faltas  : %d (%0.0f%%)\n\n",estatistica.numero_faltas,(float)(estatistica.numero_faltas*100)/(float)estatistica.numero_acessos);  // Imprime o numero de faltas
		printf("Leitura : %d (%0.0f%%)\n\n",estatistica.numero_leituras,(float)(estatistica.numero_leituras*100)/(float)estatistica.numero_acessos);  // Imprime o numero de leituras
	}
	else // Caso contrario é igual a zero e por isso para evitar a divisão por zero imprime somente zero
	{
		printf("\n\nGeral : %d (%d%%)\n\n",estatistica.numero_acessos,0); // Imprime o numero geral de acessos 
		printf("Numero de acertos : %d (%d%%)\n",estatistica.numero_acertos,0); // Imprime o numero de acertos
		printf("Numero de faltas  : %d (%d%%)\n\n",estatistica.numero_faltas,0); // Imprime o numero de faltas
		printf("Leitura : %d (%d%%)\n\n",estatistica.numero_leituras,0); // Imprime o numero de leitura
	}
	if(estatistica.numero_leituras > 0) // Caso o numero de leituras for maior que zero imprime a sequencia abaixo
	{	
		printf("Numero de acertos em leituras : %d (%0.0f%%)\n",estatistica.numero_acertos_leitura,(float)(estatistica.numero_acertos_leitura*100)/(float)estatistica.numero_leituras); // em relacao ao numero de leitura
		printf("Numero de faltas em leituras  : %d (%0.0f%%)\n\n",estatistica.numero_faltas_leitura,(float)(estatistica.numero_faltas_leitura*100)/(float)estatistica.numero_leituras); // em relacao ao numero de leitura
	}
	else // Caso contrario é igual a zero e por isso para evitar a divisão por zero imprime somente zero
	{
		printf("Numero de acertos em leituras : %d (%d%%)\n",estatistica.numero_acertos_leitura,0); // Imprime o numero de acertos em leituras
		printf("Numero de faltas em leituras  : %d (%d%%)\n\n",estatistica.numero_faltas_leitura,0); // Imprime o numero de faltas em leituras
	}
	if(estatistica.numero_acessos > 0) // Caso o numero de acessos for maior que zero imprime a sequencia abaixo
	{
		printf("Escrita : %d (%0.0f%%)\n\n",estatistica.numero_escritas,(float)(estatistica.numero_escritas*100)/(float)estatistica.numero_acessos); // em relacao ao numero de acessos
	}
	else // Caso contrario é igual a zero e por isso para evitar a divisão por zero imprime somente zero
	{
		printf("Escrita : %d (%d%%)\n\n",estatistica.numero_escritas,0); // Imprime o numero de escritas
	}
	if(estatistica.numero_escritas > 0) // Caso o numero de escritas for maior que zero imprime a sequencia abaixo
	{
		printf("Numero de acertos em escrita : %d (%0.0f%%)\n",estatistica.numero_acertos_escrita,(float)(estatistica.numero_acertos_escrita*100)/(float)estatistica.numero_escritas); // em relacao ao numero de escrita
		printf("Numero de faltas em escrita  : %d (%0.0f%%)\n\n\n",estatistica.numero_faltas_escrita,(float)(estatistica.numero_faltas_escrita*100)/(float)estatistica.numero_escritas); // em relacao ao numero de escrita
	}
	else // Caso contrario é igual a zero e por isso para evitar a divisão por zero imprime somente zero
	{
		printf("Numero de acertos em escrita : %d (%d%%)\n",estatistica.numero_acertos_escrita,0); // Imprime o numero de acertos em escrit	as
		printf("Numero de faltas em escrita  : %d (%d%%)\n\n\n",estatistica.numero_faltas_escrita,0); // Imprime o numero de faltas em escritas
	}
}
