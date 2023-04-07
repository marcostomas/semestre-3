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
		printf("conteudo: %d ", M[i]);
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
			printf("Endereco: %d \n", endereco);
			printf("Instrucao 31 (LER). Digite um inteiro: ");
			scanf("%i\n", &M[endereco]);
			printf("Valor armazenado: %d \n", M[endereco]);
		}
		break;

	case 4:
		if (instrucao == 41)
			printf("Endereco: %d. Conteudo: %d", endereco, M[endereco]); // imprimir apenas o cont. mudar depois
		break;

	case 5:
		if (instrucao == 50)
			break;
		else if (instrucao == 51)
			pc = endereco;
		else if (instrucao == 52)
		{
			if (pc > 0)
				pc = endereco;
		}
		else if (instrucao == 53)
		{
			if (pc >= 0)
				pc = endereco;
		}
		else if (instrucao == 54)
		{
			if (pc < 0)
				pc = endereco;
		}
		else if (instrucao == 55)
		{
			if (pc <= 0)
				pc = endereco;
		}
		else if (instrucao == 56)
		{
			if (pc != 0)
				pc = endereco;
		}
		else if (instrucao == 57)
		{
			if (pc == 0)
				pc = endereco;
		}
		break;

	case 6:
		if (instrucao == 61)
			printf("INSTRUCAO 61 PENDENTE DE IMPLEMENTACAO");
		else if (instrucao == 62)
			printf("INSTRUCAO 62 PENDENTE DE IMPLEMENTACAO");

		break;

	case 7:
		if (instrucao == 70)
			return 0;

	default:
		break;
	}
	return 0;
}

void executa()
{
	puts("Execucao:");

	for (int i = 0; i < 14; i++)
	{
		controle(M[i]);
	}

	for (int i = 0; i < 54; i++)
	{
		;
		printf("i: %d. valor: %d", i, M[i]);
	}
	/* insira seu programa aqui. */
	/* caso crie outras funções, crie neste arquivo (e chame-as aqui ou onde
	 * for conveniente */
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
		 * */
		loadM(argv[1]);
		dumpM();
		executa();
	}
}