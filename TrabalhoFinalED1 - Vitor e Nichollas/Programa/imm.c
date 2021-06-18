#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TImage.h"

void ErrorManager(int error, char mensage[50]);

int main(int argc, char *argv[])
{
	/*for (int i = 0; i < argc; i++)
		printf("\nParametro %d: %s\n", i, argv[i]);*/

	if(strcmp(argv[1], "-open") == 0)
	{
		ErrorManager(
			open_file(argv[2]), "\nArquivo iniciado!\n");
	}
    else
    {
        printf("Comando Invalido!\n");
        exit;
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