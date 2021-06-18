#include <stdlib.h>
#include <stdio.h>
#include <time.h> //necessário p/ função time()
#include "TMat2D.h"

struct TMat2D
{
    int nrows;    // número de linhas
    int ncolumns; // número de colunas
    int *data; // ponteiro para os dados da matriz
};

TMat2D *mat2D_create(int nrows, int ncolumns)
{
    TMat2D *mat;
    mat = malloc(sizeof(TMat2D));
    if (mat == NULL)
        return NULL;

    mat->nrows = nrows;
    mat->ncolumns = ncolumns;
    mat->data = calloc(nrows * ncolumns, sizeof(int));
}

void mat2D_print(TMat2D * mat)
{
    int val;
    int nrows, ncolumns;
    mat2D_info(mat,&nrows,&ncolumns);

    printf("\nLinhas: %d, Colunas: %d\n", nrows, ncolumns);
    for(int i = 0; i<nrows; i++)
    {
        for(int j = 0; j<ncolumns; j++)
        {
            if(mat2D_get_value(mat,i,j,&val) != 0)
                printf("Erro!");
            printf("%d ", val);
        }printf("\n");
    }
}

int mat2D_set_value(TMat2D *mat, int i, int j, int val)
{
    if (mat == NULL)
        return -1;
    if(i >= mat->nrows || j >= mat->ncolumns)
        return -1;

    int pos = i * mat->ncolumns + j;
    mat->data[pos] = val;
    //printf("Coloquei na linha: %d, coluna: %d, o valor: %d, pos: %d\n",i,j,val,pos);
    return 0;
}

int mat2D_get_value(TMat2D *mat, int i, int j, int *val)
{
    if (mat == NULL)
        return -1;
    if(i >= mat->nrows || j >= mat->ncolumns)
        return -1;

    int pos = i * mat->ncolumns + j;
    *val = mat->data[pos];
    return 0;
}

int mat2D_set_RandomValues(TMat2D *mat, int min, int max)
{
    if (mat == NULL)
        return -1;

    srand(time(0));
    int sort;
    int pos;
    int nrows = mat->nrows;
    int ncolumns = mat->ncolumns;

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncolumns; j++)
        {
            sort = min + (rand() % (max + 1 - min));
            pos = i * mat->nrows + j;
            mat->data[pos] = sort;
        }
    }

    return 0;
}

TMat2D *mat2D_sum(TMat2D *mat1, TMat2D *mat2)
{
    if (mat1 == NULL || mat2 == NULL)
        return NULL;
    if (mat1->nrows != mat2->nrows || mat1->ncolumns != mat2->ncolumns)
        return NULL;

    int pos;
    int nrows = mat1->nrows;
    int ncolumns = mat1->ncolumns;

    TMat2D *res;
    res = mat2D_create(nrows, ncolumns);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncolumns; j++)
        {
            pos = i * res->nrows + j;
            res->data[pos] = mat1->data[pos] + mat2->data[pos];
        }
    }

    return res;
}

int mat2D_info(TMat2D *mat, int *nrows, int *ncolumns)
{
    if(mat == NULL)
        return -1;

    *nrows = mat->nrows;
    *ncolumns = mat->ncolumns;

    return 0;
}

int mat2D_free(TMat2D *mat)
{
    if(mat==NULL)
        return -1;

    free(mat);
}