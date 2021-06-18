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
        for (int j = 0; j<ncolumns; j++)
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

    int pos = i * mat->nrows + j;
    mat->data[pos] = val;
    return 0;
}

int mat2D_get_value(TMat2D *mat, int i, int j, int *val)
{
    if (mat == NULL)
        return -1;
    if(i >= mat->nrows || j >= mat->ncolumns)
        return -1;

    int pos = i * mat->nrows + j;
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

TMat2D *mat2D_multiply(TMat2D *mat1, TMat2D *mat2)
{
    if (mat1 == NULL || mat2 == NULL)
        return NULL;
    /*if (mat1->nrows != mat2->ncolumns)
        return NULL;*/

    int pos, aux = 0;
    int nrows = mat1->nrows;
    int ncolumns = mat2->ncolumns;

    TMat2D *res;
    res = mat2D_create(nrows, ncolumns);

    for (int i = 0; i < mat1->nrows; i++)
    {
        for (int j = 0; j < mat2->ncolumns; j++)
        {
            for (int x = 0; x < mat2->nrows; x++)
            {
                int pos1 = i * mat1->nrows + x;
                int pos2 = x * mat2->nrows + j;
                aux += mat1->data[pos1] * mat1->data[pos2];
            }
            pos = i * res->nrows + j;
            res->data[pos] = aux;
            aux = 0;
        }
    }

    return res;
}

TMat2D *mat2D_multiply_N(TMat2D *mat, int mult)
{
    if (mat == NULL)
        return NULL;

    int pos;
    int nrows = mat->nrows;
    int ncolumns = mat->ncolumns;

    TMat2D *res;
    res = mat2D_create(nrows, ncolumns);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncolumns; j++)
        {
            pos = i * res->nrows + j;
            res->data[pos] = mat->data[pos] * mult;
        }
    }

    return res;
}

int mat2D_diagonal(TMat2D *mat)
{
    if (mat == NULL)
        return -1;

    int ncolumns = mat->ncolumns;
    int pos;
    int soma = 0;

    int i, j;
    for (i = 0, j = 0; j < ncolumns; i++, j++)
    {       
        pos = i * mat->nrows + j;
        soma += mat->data[pos];      
    }

    return soma;
}

TMat2D *mat2D_sum_rows(TMat2D *mat)
{
    if (mat == NULL)
        return NULL;

    int pos;
    int nrows = mat->nrows;
    int ncolumns = mat->ncolumns;

    TMat2D *res;
    res = mat2D_create(1, nrows);

    int aux = 0;
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncolumns; j++)
        {
            pos = i * mat->nrows + j;
            aux += mat->data[pos];
        }
        res->data[i] = aux;
        aux = 0;
    }

    return res;
}

TMat2D *mat2D_sum_columns(TMat2D *mat)
{
    if (mat == NULL)
        return NULL;

    int pos;
    int nrows = mat->nrows;
    int ncolumns = mat->ncolumns;

    TMat2D *res;
    res = mat2D_create(1, ncolumns);

    int aux = 0;
    for (int i = 0; i < ncolumns; i++)
    {
        for (int j = 0; j < nrows; j++)
        {
            pos = j * mat->ncolumns + i;
            aux += mat->data[pos];
        }
        res->data[i] = aux;
        aux = 0;
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