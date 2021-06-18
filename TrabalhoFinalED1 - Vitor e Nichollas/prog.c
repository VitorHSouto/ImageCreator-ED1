#include <stdio.h>
#include "TMat2D.h" 

void MostraMatriz(TMat2D* mat);
void PegaMatriz(TMat2D* mat);

int main()
{ 
    TMat2D* mat1;
    TMat2D* mat2;
    TMat2D* res;
    int nrows, ncolumns;
    double val;

    printf("Digite o numero de linhas da matriz 1: ");
    scanf("%d",&nrows);
    printf("Digite o numero de colunas da matriz 1: ");
    scanf("%d",&ncolumns);
    mat1 = mat2D_create(nrows, ncolumns);
    printf("\n");

    printf("Digite o numero de linhas da matriz 2: ");
    scanf("%d",&nrows);
    printf("Digite o numero de colunas da matriz 2: ");
    scanf("%d",&ncolumns);
    mat2 = mat2D_create(nrows, ncolumns);
    printf("\nMATRIZES CRIADAS!\n");

    int opcao;
    printf("Como deseja preencher as matrizes?\n");
    printf("1- DIGITAR\n");
    printf("2- RANDOMIZAR\n");
    printf("OPCAO: ");
    scanf("%d", &opcao);

    if(opcao==1) //SCANF
    {
        printf("\n---- MATRIZ 01 ----\n");
        PegaMatriz(mat1);

        printf("\n---- MATRIZ 02 ----\n");
        PegaMatriz(mat2);
    }

    if(opcao==2) //RANDOMIZAR
    {
        int min, max;
        printf("Digite o valor minimo: ");
        scanf("%d", &min);
        printf("Digite o valor maximo: ");
        scanf("%d", &max);
        if(mat2D_set_RandomValues(mat1, min, max) != 0)
            printf("ERRO!");
        if(mat2D_set_RandomValues(mat2, min, max) != 0)
            printf("ERRO!");
    }

    printf("\nMatrizes definidas: ");
    printf("\n---- MATRIZ 01 ----\n");
    MostraMatriz(mat1);
    printf("\n---- MATRIZ 02 ----\n");
    MostraMatriz(mat2);

    opcao=0;
    while (1) //MENU
    {
        int change = 0;

        printf("\nO que deseja fazer?\n");
        printf("1- SOMAR MATRIZES\n");
        printf("2- MULTIPLICAR MATRIZES\n");
        printf("3- MULTIPLICAR POR CONSTANTE\n");
        printf("4- SOMA DA DIAGONAL\n");
        printf("5- SOMA DAS LINHAS\n");
        printf("6- SOMA DAS COLUNAS\n");
        printf("9- SAIR\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        if(opcao==9)
            break;

        switch (opcao)
        {
        case 1:
            res = mat2D_sum(mat1,mat2); change = 1;
            if(res == NULL)
                printf("\nNAO EH POSSIVEL REALIZAR ESSA SOMA\n");
            else
                printf("\n--- Resultado da soma de matrizes ---\n");
            break;
            
        case 2:
            res = mat2D_multiply(mat1,mat2); change = 1;
            if(res == NULL)
                printf("\nNAO EH POSSIVEL REALIZAR ESSA MULTIPLICACAO\n");
            else
                printf("\n--- Resultado da multiplicacao de matrizes ---\n");
            break;
        case 3:
            printf("\nDigite o numero multiplicador: ");
            scanf("%lf", &val);
            res = mat2D_multiply_N(mat1,val); change = 1;
            if(res == NULL)
                printf("\nNAO EH POSSIVEL REALIZAR ESSA MULTIPLICACAO\n");
            else
                printf("\n--- Resultado da multiplicacao de matrizes ---\n");
            break;
        case 4:
            val = mat2D_diagonal(mat1);
            if(res == NULL)
                printf("\nNAO EH POSSIVEL CALCULAR A DIAGONAL\n");
            else
                printf("\nVALOR DA DIAGONAL: %.lf\n", val);
            break;
        case 5:
            res = mat2D_sum_rows(mat1); change = 1;
            if(res == NULL)
                printf("\nNAO EH POSSIVEL CALCULAR A SOMA DE LINHAS\n");
            else
                printf("\n--- Resultado da soma das linhas ---\n");
            break;
        case 6:
            res = mat2D_sum_columns(mat1); change = 1;
            if(res == NULL)
                printf("\nNAO EH POSSIVEL CALCULAR A SOMA DE COLUNAS\n");
            else
                printf("\n--- Resultado da soma das colunas ---\n");
            break;
        }

        if(change == 1)
        {
            MostraMatriz(res);
            change = 0;
        }
    }

    mat2D_free(mat1);
    mat2D_free(mat2);
    mat2D_free(res);

}

void MostraMatriz(TMat2D * mat)
{
    double val;
    int nrows, ncolumns;
    mat2D_info(mat,&nrows,&ncolumns);

    for(int i = 0; i<nrows; i++)
    {
        for (int j = 0; j<ncolumns; j++)
        {
            if(mat2D_get_value(mat,i,j,&val) != 0)
                printf("Erro!");
            printf("%.lf  ", val);
        }printf("\n");
    }
}

void PegaMatriz(TMat2D* mat)
{
    double val, val1;
    int nrows, ncolumns;
    mat2D_info(mat,&nrows,&ncolumns);

    for(int i = 0; i<nrows; i++)
    {
        for (int j = 0; j<ncolumns; j++)
        {
            printf("Digite o valor da %d%c Linha e da %d%c Coluna: ", i+1, 167, j+1, 167);
            scanf("%lf", &val);
            mat2D_set_value(mat,i,j,val);
            mat2D_get_value(mat,i,j, &val1);
            printf("%.lf", val1);
        }   
    }
}