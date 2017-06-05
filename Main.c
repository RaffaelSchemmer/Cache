#include "cache.h"
#include<stdio.h> // scanf printf fflush stdin
#include<ctype.h> // toupper
#include <stdlib.h> // srand rand ltoa strtol system atoi
#include<string.h> // strlen strcat
/////////////////////////////////////////////////////////////
char binario[8];
char endereco[8]; // Declaracao de variavel caracter
////////////////////////////////////////////////////////////
int tamanho;
int temp1,temp3,temp4;
int dado,quadro; // Declaracao de variaveis inteiras
int rotulo,deslocamento,valor;
/////////////////////////////////////////////////////////////
int main() // Funcao main
{
	char opcao;
	iniciar_simulador(); // Chama Inicializar simulador que incializa a cache a memoria principal e as estatisticas do simulador
	do
	{
		system("cls");
		mostrar_memorias(); // Chama mostrar memorias que mostra a memoria principal e a cache
		printf("\n\nR - Ler   W - Escrever   E - Estatisticas   S- Sair [ ]\b\b");
		scanf("%c",&opcao); // Menu principal de entradas do usuario
		fflush(stdin);
		opcao = toupper(opcao); // Converte as entradas para maiusculo
		if(opcao != 'R' && opcao != 'W' && opcao != 'E' && opcao != 'S')  // Tratamento de opcoes invalidas
		{
			printf("\nOpcao invalida, digite novamente !!\n\n");
			system("pause");
			continue;
		}
		switch(opcao) 
		{
			case('R'): // Opcao de leitura de endereco
			{
				do
				{
					system("cls");
					mostrar_memorias();  // Chama mostrar memorias que mostra a memoria principal e a cache
					printf("\n\nEntre com um endereco a ser lido(0-7bits) : [       ]\b\b\b\b\b\b\b\b");
					scanf("%s",endereco); // Solicita que o usuario entre com um endereco
					fflush(stdin);
					temp1 = atoi(endereco); // Converte o endereco para inteiro(decimal)
					temp3 = strtol(endereco,NULL,2); // Converte o endereco para inteiro(binario)
					temp4 = strlen(endereco); // Captura o tamanho do endereco informado
					if(temp1 == temp3 && temp4 <=7) // Verificacao para caso o usuario entre com numero == 0 
					{
						break;
					}
					if(temp3 < 1  || temp3 > 127) // Tratamento de opcao invalida 
					{
						printf("\nEndereco invalido,digite novamente !!\n\n");
						system("pause");
						system("cls");
					}
				}while(temp3 < 1  || temp3 > 127); // continua enquanto o endereco for menor que 0 e maior que 127
				if(le_endereco(temp3,&rotulo,&deslocamento,&valor,&quadro) == 1) // Chama a funcao le_endereco passando o endereco e que retorna o rotulo o deslocamento, o valor do endereco e o quadro onde esta localizado
				{ // Se retornar 1 é sinal que o endereco estava na cache
					system("cls"); 
					mostrar_memorias();  // Chama mostrar memorias que mostra a memoria principal e a cache
					ltoa(temp3,binario,2); // Converte o endereco de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do endereco
					printf("\n\nO endereco solicitado ");
					if(tamanho == 1){printf("[000000%s] ",binario);}
					if(tamanho == 2){printf("[00000%s] ",binario);}
					if(tamanho == 3){printf("[0000%s] ",binario);}
					if(tamanho == 4){printf("[000%s] ",binario);} // Prenche com zeros a esquerda a impressao do endereco para que ele sempre tenha 7 bits
					if(tamanho == 5){printf("[00%s] ",binario);}
					if(tamanho == 6){printf("[0%s]",binario);}
					if(tamanho == 7){printf("[%s] ",binario);}
					printf("estava na cache !!\n");
					ltoa(quadro,binario,2); // Converte o quadro de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do quadro
					printf("\nQuadro         : ");
					if(tamanho == 1){printf("[00%s] ",binario);}
					if(tamanho == 2){printf("[0%s] ",binario);}
					if(tamanho == 3){printf("[%s] ",binario);} // Prenche com zeros a esquerda a impressao do quadro para que ele sempre tenha 3 bits
					ltoa(rotulo,binario,2); // Converte o rotulo de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do rotulo
					printf("\nRotulo         : ");
					if(tamanho == 1){printf("[0000%s] ",binario);}
					if(tamanho == 2){printf("[000%s] ",binario);}
					if(tamanho == 3){printf("[00%s] ",binario);} // Prenche com zeros a esquerda a impressao do rotulo para que ele sempre tenha 5bits
					if(tamanho == 4){printf("[0%s] ",binario);}
					if(tamanho == 5){printf("[%s] ",binario);}
					ltoa(deslocamento,binario,2); // Converte o deslocametno de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do deslocamento
					printf("\n\nDeslocamento   : ");
					if(tamanho == 1){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do deslocamento para que ele sempre tenha 2bits
					if(tamanho == 2){printf("[%s] ",binario);}
					ltoa(valor,binario,2); // Converte o valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do valor
					printf("\nValor          : ");
					if(tamanho == 1){printf("[0000000%s] ",binario);}
					if(tamanho == 2){printf("[000000%s] ",binario);}
					if(tamanho == 3){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do valor para que ele sempre tenha 8bits 
					if(tamanho == 4){printf("[0000%s] ",binario);}
					if(tamanho == 5){printf("[000%s] ",binario);}
					if(tamanho == 6){printf("[00%s] ",binario);}
					if(tamanho == 7){printf("[0%s] ",binario);}
					if(tamanho == 8){printf("[%s] ",binario);}
					printf("\n\n");
					system("pause");
				}
				else // Se retornar diferente de 1 é sinal que o endereco nao estava na cache
				{
					system("cls"); 
					mostrar_memorias();  // Chama mostrar memorias que mostra a memoria principal e a cache
					ltoa(temp3,binario,2); // Converte o valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do endereco
					printf("\n\nO endereco solicitado ");
					if(tamanho == 1){printf("[000000%s] ",binario);}
					if(tamanho == 2){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do endereco para que ele sempre tenha 8bits
					if(tamanho == 3){printf("[0000%s] ",binario);}
					if(tamanho == 4){printf("[000%s] ",binario);}
					if(tamanho == 5){printf("[00%s] ",binario);}
					if(tamanho == 6){printf("[0%s]",binario);}
					if(tamanho == 7){printf("[%s] ",binario);}
					printf("nao estava na cache !!\n");
					ltoa(quadro,binario,2); // Converte o valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do quadro
					printf("\nO Quadro ");
					if(tamanho == 1){printf("[00%s] ",binario);}
					if(tamanho == 2){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do quadro para que ele sempre tenha 3bits
					if(tamanho == 3){printf("[%s] ",binario);}
					ltoa(rotulo,binario,2); // Converte o valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do rotulo
					printf("da cache foi atualizado");
					printf("\n\nRotulo         : ");
					if(tamanho == 1){printf("[0000%s] ",binario);}
					if(tamanho == 2){printf("[000%s] ",binario);}
					if(tamanho == 3){printf("[00%s] ",binario);} // Prenche com zeros a esquerda a impressao do rotulo para que ele sempre tenha 5bits
					if(tamanho == 4){printf("[0%s] ",binario);}
					if(tamanho == 5){printf("[%s] ",binario);}
					ltoa(deslocamento,binario,2); // Converte o valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do deslocamento
					printf("\nDeslocamento   : ");
					if(tamanho == 1){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do deslocamento para quee ele sempre tenha 2bits
					if(tamanho == 2){printf("[%s] ",binario);}
					ltoa(valor,binario,2); // Converte oo valor de inteiro para binario
					tamanho = strlen(binario); // Captura o tamanho do valor
					printf("\nValor          : "); 
					if(tamanho == 1){printf("[0000000%s] ",binario);}
					if(tamanho == 2){printf("[000000%s] ",binario);}
					if(tamanho == 3){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do valor para que ele sempre tenha 8bits
					if(tamanho == 4){printf("[0000%s] ",binario);}
					if(tamanho == 5){printf("[000%s] ",binario);}
					if(tamanho == 6){printf("[00%s] ",binario);}
					if(tamanho == 7){printf("[0%s] ",binario);}
					if(tamanho == 8){printf("[%s] ",binario);}
					printf("\n\n");
					system("pause");
				}
				break;
			}
			case('W'):
			{
				do
				{
					system("cls");
					mostrar_memorias(); // Chama mostrar memorias que mostra a memoria principal e a cache
					printf("\n\nEntre com um endereco a ser escrito(0-7 bits) : [       ]\b\b\b\b\b\b\b\b");
					scanf("%s",endereco);  // Le um endereco do usuario
					fflush(stdin);  
					temp1 = atoi(endereco);  // Converte o endereco para inteiro(decimal)
					temp3 = strtol(endereco,NULL,2);  // Converte o endereco para decimal(binario)
					temp4 = strlen(endereco); // Conta o tamanho da string
					if(temp1 == temp3 && temp4 <=7) // Verificacao para caso o usuario entre com numero == 0 
					{
						break;
					}
					if(temp3 < 1  || temp3 > 127) // Tratamento de opcao invalida
					{
						printf("\nEndereco invalido,digite novamente !!\n\n");
						system("pause");
						system("cls");
					}
				}while(temp3 < 1  || temp3 > 127); // continua enquanto o endereco for menor que 0 e maior que 127
				do
				{
					system("cls"); 
					mostrar_memorias(); // Chama mostrar memorias que mostra a memoria principal e a cache
					printf("\n\nEntre com o dado(0-255 decimal) [   ]\b\b\b\b"); 
					scanf("%d",&dado); // Solicita que o usuario entre com um dado de 0 - 255
					fflush(stdin); 
					if(dado < 0  || dado > 255) // Tratamento de opcao invalida
					{
						printf("\nEndereco invalido,digite novamente !!\n\n");
						system("pause");
						system("cls");
					}
				}while(dado < 0  || dado > 255); // Continua enquanto o dado for menor que zero e maior que 255
				if(escreve_endereco(temp3,&rotulo,&deslocamento,&dado,&quadro) == 1) // Chama a funcao escreve_endereco passando o endereco e que retorna o rotulo o deslocamento, o valor do endereco e o quadro onde esta localizado
				{
					system("cls");
					mostrar_memorias(); // Chama mostrar memorias que mostra a memoria principal e a cache
					ltoa(temp3,binario,2); // Converte o endereco de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do endereco
					printf("\n\nO endereco solicitado ");
					if(tamanho == 1){printf("[000000%s] ",binario);}
					if(tamanho == 2){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do endereco para que ele sempre tenha 7bits
					if(tamanho == 3){printf("[0000%s] ",binario);}
					if(tamanho == 4){printf("[000%s] ",binario);}
					if(tamanho == 5){printf("[00%s] ",binario);}
					if(tamanho == 6){printf("[0%s]",binario);}
					if(tamanho == 7){printf("[%s] ",binario);}
					printf("estava na cache !!\n");
					ltoa(quadro,binario,2); // Converte o quadro de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do quadro
					printf("\nQuadro         : ");
					if(tamanho == 1){printf("[00%s] ",binario);}
					if(tamanho == 2){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do quadro para que ele tenha sempes 3bits
					if(tamanho == 3){printf("[%s] ",binario);}
					ltoa(rotulo,binario,2); // Converte o rotulo de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do rotulo
					printf("\nRotulo         : ");
					if(tamanho == 1){printf("[0000%s] ",binario);}
					if(tamanho == 2){printf("[000%s] ",binario);} // Prenche com zeros a esquerda a impressao do quadro para que ele tenha sempre 5bits
					if(tamanho == 3){printf("[00%s] ",binario);}
					if(tamanho == 4){printf("[0%s] ",binario);}
					if(tamanho == 5){printf("[%s] ",binario);}
					ltoa(deslocamento,binario,2); // Converte o deslocamento de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do deslocamento
					printf("\n\nDeslocamento   : ");
					if(tamanho == 1){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do deslocamento para que ele tenha sempre 2bits
					if(tamanho == 2){printf("[%s] ",binario);}
					ltoa(dado,binario,2); // Converte o valor de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do valor
					printf("\nValor          : ");
					if(tamanho == 1){printf("[0000000%s] ",binario);}
					if(tamanho == 2){printf("[000000%s] ",binario);}
					if(tamanho == 3){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do valor para que ele sempre tenha 8bits
					if(tamanho == 4){printf("[0000%s] ",binario);}
					if(tamanho == 5){printf("[000%s] ",binario);}
					if(tamanho == 6){printf("[00%s] ",binario);}
					if(tamanho == 7){printf("[0%s] ",binario);}
					if(tamanho == 8){printf("[%s] ",binario);}
					printf("\n\n");
					system("pause");
				}
				else // Se retornar diferente de 1 é sinal que o endereco nao estava na cache e foi carregado da memoria para cache e novamente atualizado na RAM
				{
					system("cls");
					mostrar_memorias(); // Chama mostrar memorias que mostra a memoria principal e a cache
					ltoa(temp3,binario,2); // Converte o endereco de inteiro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do endereco
					printf("\n\nO endereco solicitado ");
					if(tamanho == 1){printf("[000000%s] ",binario);}
					if(tamanho == 2){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do endereco para que ele sempre tenha 7bits
					if(tamanho == 3){printf("[0000%s] ",binario);}
					if(tamanho == 4){printf("[000%s] ",binario);}
					if(tamanho == 5){printf("[00%s] ",binario);}
					if(tamanho == 6){printf("[0%s]",binario);}
					if(tamanho == 7){printf("[%s] ",binario);}
					printf("nao estava na cache !!\n");
					ltoa(quadro,binario,2); // Converte o quadro decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do quadro
					printf("\nO Quadro ");
					if(tamanho == 1){printf("[00%s] ",binario);}
					if(tamanho == 2){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do quadro para que ele sempre tenha 3bits
					if(tamanho == 3){printf("[%s] ",binario);}
					printf("da cache foi atualizado com o bloco ");
					ltoa(rotulo,binario,2); // Converte o rotulo decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do rotulo
					if(tamanho == 1){printf("[0000%s] ",binario);}
					if(tamanho == 2){printf("[000%s] ",binario);} // Prenche com zeros a esquerda a impressao do rotulo para que ele sempre tenha 5bits
					if(tamanho == 3){printf("[00%s] ",binario);}
					if(tamanho == 4){printf("[0%s] ",binario);}
					if(tamanho == 5){printf("[%s] ",binario);}
					printf("da memoria principal");
					printf("\n\nRotulo         : ");
					if(tamanho == 1){printf("[0000%s] ",binario);}
					if(tamanho == 2){printf("[000%s] ",binario);}
					if(tamanho == 3){printf("[00%s] ",binario);} // Prenche com zeros a esquerda a impressao do rotulo para que ele sempre tenha 5bits
					if(tamanho == 4){printf("[0%s] ",binario);}
					if(tamanho == 5){printf("[%s] ",binario);}
					ltoa(deslocamento,binario,2); // Converte o deslocamento decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do rotulo
					printf("\nDeslocamento   : ");
					if(tamanho == 1){printf("[0%s] ",binario);} // Prenche com zeros a esquerda a impressao do deslocamento para que ele sempre tenha 2bits 
					if(tamanho == 2){printf("[%s] ",binario);}
					ltoa(dado,binario,2); // Converte o dado decimal para caracter binario
					tamanho = strlen(binario); // Captura o tamanho da string do rotulo
					printf("\nValor          : ");
					if(tamanho == 1){printf("[0000000%s] ",binario);} 
					if(tamanho == 2){printf("[000000%s] ",binario);}
					if(tamanho == 3){printf("[00000%s] ",binario);} // Prenche com zeros a esquerda a impressao do dado para que ele sempre tenha 8bits
					if(tamanho == 4){printf("[0000%s] ",binario);}
					if(tamanho == 5){printf("[000%s] ",binario);}
					if(tamanho == 6){printf("[00%s] ",binario);}
					if(tamanho == 7){printf("[0%s] ",binario);}
					if(tamanho == 8){printf("[%s] ",binario);}
					printf("\n\n");
					system("pause");
				}
				break;
			}
			case('E'): // Mostra as estatisticas
			{
				system("cls");
				mostrar_memorias();  // Chama mostrar memorias que mostra a memoria principal e a cache
				mostrar_estatisticas();
				system("pause");
				break;
			}
		}
	}while(opcao != 'S'); // Condicao de saida do simulador
	return(0);
}
