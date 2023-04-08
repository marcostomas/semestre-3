/* Marcos Paulo Tomás Ferreira - NUSP 13747950 */

/* O processador executa instruções a partir do endereço zero.
 * as instruções DDF e DFF não precisam ser codificadas.
 * as instruções de deslocamento preservam o sinal.
 * a instrução PAR termina o simulador. */

#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 10000

int M[MEMSIZE]; // representa a memória do HIPO.

void loadM(char *imgFileName)
{
	FILE *fp;
	fp = fopen(imgFileName, "rt");
	int i = 0;
	while (!feof(fp))
	{
		printf("lendo linha %d ", i);
		/* quem escrever o conteúdo da memória deve ter o cuidado de fazê-lo
		 * conforme a especificação. Esta função não checa. */
		/* podem acontecer coisas inesperadas caso falte ou sobre \n no arquivo.
		 * */
		fscanf(fp, "%d\n", &(M[i]));
		printf("conteúdo: %d \n", M[i]);
		++i;
	}
	fclose(fp);
}

void dumpM()
{
	for (int i = 0; i < 15; i++)
	{
		printf("(%d,%d)\t", i, M[i]);
	}
}

int acc; // acumulador
int pc;	 // ou ai = apontador de instrução
int mbr; // talvez não seja necessário.

int controle(int codigo)
{
	int algarismo = codigo / 1000;
	int instrucao = codigo / 100;
	int endereco = codigo % 100;

	switch (algarismo)
	{

	case 1:
		if (instrucao == 11)
			acc = M[endereco];
		else if (instrucao == 12)
			M[endereco] = acc;
		break;

	case 2:
		if (instrucao == 21)
			acc = M[endereco] + acc;
		else if (instrucao == 22)
			acc = acc - M[endereco];
		else if (instrucao == 23)
			acc = acc * M[endereco];
		else if (instrucao == 24)
			acc = acc / M[endereco];
		else if (instrucao == 25)
			acc = acc % M[endereco];
		break;

	case 3:
		if (instrucao == 31)
		{
			printf("Instrucao 31 (LER). Digite um inteiro: ");
			scanf("%d", &M[endereco]);
			printf("\n");
		}
		break;

	case 4:
		if (instrucao == 41)
			printf("%d\n", M[endereco]);
		break;

	case 5:
		if (instrucao == 50)
			break;
		else if (instrucao == 51)
			pc = endereco;
		else if (instrucao == 52)
		{
			if (acc > 0)
				pc = endereco;
		}
		else if (instrucao == 53)
		{
			if (acc >= 0)
				pc = endereco;
		}
		else if (instrucao == 54)
		{
			if (acc < 0)
				pc = endereco;
		}
		else if (instrucao == 55)
		{
			if (acc <= 0)
				pc = endereco;
		}
		else if (instrucao == 56)
		{
			if (acc != 0)
				pc = endereco;
		}
		else if (instrucao == 57)
		{
			if (acc == 0)
				pc = endereco;
		}
		break;

	case 6:
		if (instrucao == 61)
			acc = acc % 10000 * 10;
		else if (instrucao == 62)
			acc = acc / 10;
		break;

	case 7:
		if (instrucao == 70)
			return 1;

	default:
		break;
	}
	return 0;
}

void executa()
{
	puts("Execucao:");
	int retorno;
	pc = 1;
	do
	{
		retorno = controle(M[pc]);
	} while (retorno != 1);

	return;
}

void main(int argc, char *argv[])
{
	puts("Hello");
	if (argc > 1)
	{
		/* Um computador frequentemente tem um programa que carrega um
		 * executável na memória. Esse programa é mais complicado que o tipo
		 * de programa que é suficiente para oferecer um entendimento básico
		 * dos conceitos que quero explorar na disciplina. Por isso, a carga de
		 * um programa na memória, neste simulador, é algo feito "por fora"
		 * da simulação.
		 */
		// loadM(argv[1]);
		M[0] = 5000;
		M[1] = 1130;
		M[2] = 1240;
		M[3] = 3150;
		M[4] = 4150;
		M[5] = 1150;
		M[6] = 5411;
		M[7] = 1140;
		M[8] = 2150;
		M[9] = 1240;
		M[10] = 5103;
		M[11] = 4140;
		M[12] = 7000;
		M[13] = 0000;
		for (int i = 14; i < MEMSIZE; i++)
		{
			M[i] = 0;
		}
		dumpM();
		executa();
	}
}