#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TImage.h"

int open_file(char* arg)
{
    if(strlen(arg) <= 4)
        return INVALID_FILE;

    FILE *fp;

    int length = strlen(arg)-3;

    if(arg[length]=='t')
    {
        fp = fopen(arg,"r+");
        if (fp == NULL)
            return INVALID_FILE;
        show_image(&fp);
    }
    else if(arg[length]=='i')
    {
        show_image_bin(arg);
    }
    else
        return INVALID_FILE;

    return SUCCESS;
}

int convert_file(char* texto, char* binario)
{
    FILE *fpT, *fpB;
    fpT = fopen(texto,"r+");
        if (fpT == NULL)
            return INVALID_FILE;
    fpB = fopen(binario,"wb");
        if (fpB == NULL)
            return INVALID_FILE;

    TMat2D* mat;
    mat = image_create(&fpT);
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    int val;
    int nrows, ncol;
    mat2D_info(mat,&nrows,&ncol);
    printf("\nLinhas: %d, Colunas: %d\n", nrows, ncol);

    fwrite(&nrows, sizeof(int), 1, fpB);
    fwrite(&ncol, sizeof(int), 1, fpB);

    for(int i = 0; i<nrows; i++)
    {
        for (int j = 0; j<ncol; j++)
        {
            mat2D_get_value(mat,i,j,&val);
            fwrite(&val, sizeof(int), 1, fpB);
        }
    }
    fclose(fpT);
    fclose(fpB);

    return SUCCESS;    
}

TMat2D* image_create(FILE **fp)
{
    int nrows = 0, ncol = 0, val;
    char c;
    
    while((c = fgetc(*fp)) != EOF) //PEGA NMR DE LINHAS E COLUNAS
    {
        if(c=='\n')
        {
            nrows+=1;
            ncol=0;
        }
        else if(c==' ')
            ncol+=1;

    }nrows++; ncol++;

    TMat2D* mat;
    mat = mat2D_create(nrows,ncol);
    rewind(*fp);

    while(!feof(*fp)) {
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < ncol; j++)
            {
                fscanf(*fp,"%d",&val);
                //printf("Linha: %d, Coluna: %d, Valor: %d\n", i,j,val);
                mat2D_set_value(mat,i,j,val);
            }
            
        }     
	}

    return mat;
}

int show_image(FILE **fp)
{
    TMat2D* mat = image_create(fp);
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    int nrows, ncolumns;
    mat2D_info(mat,&nrows,&ncolumns);

    mat2D_print(mat);
    mat2D_free(mat);

    return SUCCESS;
}

int show_image_bin(char* arg)
{ 
    FILE *fp;
    fp = fopen(arg,"rb");
    if (fp == NULL)
        return INVALID_FILE;
    
    int v, nrows, ncols;
    fread(&nrows,sizeof(int),1,fp);
    fread(&ncols,sizeof(int),1,fp);

    printf("\nLinhas: %d, Colunas: %d\n", nrows, ncols);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            fread(&v,sizeof(int),1,fp);
            printf("%3d ",v);
        } printf("\n");		
    }
}

int segment_image(char* thrStr, char* file, char* segFile)
{
    FILE *fp;
    fp = fopen(file,"rb");
    if (fp == NULL)
        return INVALID_FILE;

    FILE *segFp;
    segFp = fopen(segFile,"wb");
    if (segFp == NULL)
        return INVALID_FILE;

    int thr = atoi(thrStr);
    int v, val, nrows, ncols;
    fread(&nrows,sizeof(int),1,fp); fwrite(&nrows,sizeof(int),1,segFp);
    fread(&ncols,sizeof(int),1,fp); fwrite(&ncols,sizeof(int),1,segFp);

    printf("\nLinhas: %d, Colunas: %d\n", nrows, ncols);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            fread(&v,sizeof(int),1,fp);

            if(v>=thr) val = 1;
            else val = 0;    
            
            fwrite(&val, sizeof(int), 1, segFp);

        } printf("\n");		
    }

    fclose(fp);
    fclose(segFp);
}