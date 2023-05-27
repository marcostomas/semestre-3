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
		fscanf(fp, "%d\n", &(M[i]));
		printf("conteúdo: %d ", M[i]);
		++i;
	}
	fclose(fp);
}

void dumpM()
{
	for (int i = 0; i < MEMSIZE; i++)
	{
		printf("(%d,%d)\t", i, M[i]);
	}
}

int acc; // acumulador
int pc;	 // ou ai
int mbr;

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
	int retorno, pcOld;

	for (pc = 1; pc < MEMSIZE;)
	{
		pcOld = pc;
		retorno = controle(M[pc]);
		if (retorno == 1)
			return;
		else if (pc == pcOld)
			pc++;
	}

	return;
}

void main(int argc, char *argv[])
{
	if (argc > 1)
	{
		loadM(argv[1]);
		dumpM();
		executa();
	}
}