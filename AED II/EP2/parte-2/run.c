#include "headers.h"

int main()
{

	puts("Por favor, entre com um dos comandos abaixo");
	puts("P1 --> Imprimir o índice");
	puts("P2 --> Imprimir o conteúdo do arquivo indice.dat");
	puts("P3 --> Imprimir o conteúdo do arquivo data.dat");
	puts("I  --> Insere livro atualizando o índice");
	puts("B  --> Busca livro a partir de seu código utilizando o índice");
	puts("R  --> Remove livro a partir do código atualizando o índice");
	puts("F  --> Finaliza a execução fechando o arquivo de índice e o arquivo de dados\n\n");

	// Abre o arquivo data.dat e lê a quantidade de registros nele inseridas
	// FILE *fData;
	// fData = fopen("data.dat", "a+");
	// int reg = nRecordsCount(fData);
	// fclose(fData);
	// printf("No de registros no data.dat: %i\n", reg);

	bTree *tree = createTree("indice.dat", false); // abre e cria indice.dat como a+
	printArvore(tree);

	// Dados livro (recordNode)
	char titulo[30], autor[30];
	int codigo, anoPublicacao;

	// Comando recebido via CL
	char *comando = (char *)malloc(sizeof(char) * 3);

	do
	{
		printf("Digite o comando: ");
		scanf("%s", comando);
		puts("");

		if (strcmp(comando, "I") == 0)
		{
			puts("===================================INSERÇÃO=======================================");
			printf("Escreva as informações do livro (<código> <título> <autor> <ano>): ");
			scanf("%i;%[^;];%[^;];%i", &codigo, &titulo, &autor, &anoPublicacao);
			// printf("código: %i\ntítulo: %s\nautor: %s\nano de publicação: %i\n\n", codigo, titulo, autor, anoPublicacao);

			insert(tree, codigo, titulo, autor, anoPublicacao);
			// reg++;

			// printf("reg: %d\n", reg);
			printArqData();

			puts("===================================FIM INSERÇÃO=======================================");
		}
		else if (strcmp(comando, "R") == 0)
		{
			puts("===================================REMOÇÃO=======================================");
			int key;
			printf("Digite o código do livro que será removido: ");
			scanf("%d", &key);
			printf("chave do livro a ser apagada: %d\n", key);

			bool res = removeFromTree(tree, key);
			if (res)
				printf("Apagado com sucesso.");
			else
				printf("Erro ao apagar.");
			puts("===================================FIM REMOÇÃO=======================================");
		}
		else if (strcmp(comando, "B") == 0)
		{
			puts("===================================BUSCA=======================================");

			int key;
			printf("Digite o código do livro que será buscado: ");
			scanf("%d", &key);
			puts("");

			puts("vou chamar o createTree()");
			tree = createTree("indice.dat", true); // true = arquivo já existe
			recordNode *res = search(tree, key);

			if (res != NULL)
			{
				printf("key\tcountry\tgrate\tscore\trate\n");
				printf("%d\t", res->codigoLivro);
				printf("%s\t", res->titulo);
				printf("%s\t", res->nomeCompletoPrimeiroAutor);
				printf("%d\t", res->anoPublicacao);

				free(res);
			}
			else
				printf("O livro com código %d não existe na biblioteca", key);
			puts("===================================FIM BUSCA=======================================");
		}
		else if (strcmp(comando, "P1") == 0)
		{
			puts("entrei no p1");
			traverse(tree, tree->root);
		}
		else if (strcmp(comando, "P2") == 0)
		{
			printArqIndice();
		}
		else if (strcmp(comando, "P3") == 0)
		{
			printArqData();
		}
		else
			continue;
	} while ((strcmp(comando, "F") != 0));

	fclose(tree);
	free(tree);

	return 0;
}
