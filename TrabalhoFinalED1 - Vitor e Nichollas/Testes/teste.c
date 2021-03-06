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

	if(strcmp(argv[1], "-open") == 0)
	{
		ErrorManager(
			open_file(argv[2]), "\nArquivo iniciado!\n");
	}
	else if(strcmp(argv[1], "-convert") == 0)
	{
		ErrorManager(
			convert_file(argv[2],argv[3]), "Arquivo Convertido!\n");
	}	
	else if(strcmp(argv[1], "-cc") == 0)
	{
		segfile(argv[2],argv[3]);
	}	
	else if(strcmp(argv[1], "-lab") == 0)
	{
		labfile(argv[2],argv[3]);
	}
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