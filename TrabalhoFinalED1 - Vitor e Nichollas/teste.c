#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TImage.h"

void ErrorManager(int error, char mensage[50]);

int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("\nParametro %d: %s\n", i, argv[i]);
	}

	FILE *arq, *arq2;

	if(strcmp(argv[1], "-open") == 0)
	{
		ErrorManager(open_file(&arq,argv[2]), "Arquivo iniciado!");
		show_image(&arq);
	}
	else if(strcmp(argv[1], "-convert") == 0)
	{
		ErrorManager(open_file(&arq,argv[2]), "Arquivo .txt iniciado!\n");
		ErrorManager(open_file(&arq2,argv[3]), "Arquivo .imm iniciado!\n");
		ErrorManager(convert_file(&arq,&arq2), "Arquivo Convertido!\n");
	}
	else if(strcmp(argv[1], "-ler") == 0)
	{
		arq2 = fopen(argv[3],"rb");
        if (arq2 == NULL)
            return INVALID_FILE;
		
		int v, nrows, ncols;
		fread(&nrows,sizeof(int),1,arq2);
		fread(&ncols,sizeof(int),1,arq2);
		for (int i = 0; i < nrows; i++)
		{
			for (int j = 0; j < ncols; j++)
			{
				fread(&v,sizeof(int),1,arq2);
				printf("%d ",v);
			} printf("\n");		
		}
	}

	/*arq2 = fopen(argv[3], "w+");
	if (arq2 == NULL)
	{
		printf("Erro! Arquivo2 nao encontrado");
		exit(1);
	}*/

	/*arq = fopen(argv[2], "r+");
	if (arq == NULL)
		printf("Erro!");

	printf("Erro!");

	char c;

	for (int i = 0; i < 5; i++)
	{
		fwrite(&i, sizeof(int), 1, arq);
	}
	*/	

	fclose(arq);
	fclose(arq2);
}

void ErrorManager(int error, char mensage[50])
{
	switch (error)
	{
	case SUCCESS:
		printf("%s", mensage);
		break;

	case INVALID_NULL_POINTER:
		printf("\n ----- FALHA NO PONTEIRO! ----- \n");
		break;

	case INVALID_FILE:
		printf("\n ----- FALHA NO INICIO DO ARQUIVO! ----- \n");
		break;

	default:
		break;
	}
}