#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TImage.h"
#include "TQueue.h"
#include "TStack.h"

int open_file(char* arg)
{
    if(strlen(arg) <= 4)
        return INVALID_FILE;

    int length = strlen(arg)-3;

    if(arg[length]=='t')
    {
        show_image(arg);
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
    TMat2D* mat;
    mat = image_create(texto);
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    int val;
    int nrows, ncol;
    mat2D_info(mat,&nrows,&ncol);
    //printf("\nLinhas: %d, Colunas: %d\n", nrows, ncol);

    write_bin(binario,mat);

    return SUCCESS;    
}

TMat2D* image_create(char* arg)
{
    FILE *fp;
    fp = fopen(arg,"r+");
        if (fp == NULL)
            return NULL;

    int nrows = 0, ncol = 0, val;
    char c;
    
    while((c = fgetc(fp)) != EOF) //PEGA NMR DE LINHAS E COLUNAS
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
    rewind(fp);

    while(!feof(fp)) {
        for (int i = 0; i < nrows; i++)
        {
            for (int j = 0; j < ncol; j++)
            {
                fscanf(fp,"%d",&val);
                //printf("Linha: %d, Coluna: %d, Valor: %d\n", i,j,val);
                mat2D_set_value(mat,i,j,val);
            }
            
        }     
	}

    fclose(fp);
    return mat;
}

int show_image(char* arg)
{
    TMat2D* mat = image_create(arg);
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
    TMat2D* mat;
    mat = image_create_bin(arg);
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    mat2D_print(mat);

    return 0;
}

int segment_image(char* thrStr, char* file, char* segFile)
{
    int thr = atoi(thrStr);
    int v, val, nrows, ncols;

    TMat2D* mat;
    mat = image_create_bin(file);
    if(mat==NULL)
        return INVALID_NULL_POINTER;
    mat2D_info(mat,&nrows,&ncols);

    TMat2D* matRes;
    matRes = mat2D_create(nrows,ncols);
    if(matRes==NULL)
        return INVALID_NULL_POINTER;

    //printf("\nLinhas: %d, Colunas: %d\n", nrows, ncols);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            mat2D_get_value(mat,i,j,&v);

            if(v>=thr) val = 1;
            else val = 0;    
            
            mat2D_set_value(matRes,i,j,val);
        }	
    }

    write_bin(segFile, matRes);

    return SUCCESS;
}

TMat2D* image_create_bin(char* arg)
{
    FILE *fp;
    fp = fopen(arg,"rb");
    if (fp == NULL)
        return NULL;

    int v, nrows, ncols;

    fread(&nrows,sizeof(int),1,fp);
    fread(&ncols,sizeof(int),1,fp);

    TMat2D* mat;
    mat = mat2D_create(nrows,ncols);


    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            fread(&v,sizeof(int),1,fp);
            mat2D_set_value(mat,i,j,v);
        }
    }

    //mat2D_print(mat);
    fclose(fp);

    return mat;
}

int segfile(char* texto, char* binario)
{
    int v, val, nrows, ncols;  

    TMat2D* im;
    im = image_create_bin(texto);
    if(im==NULL)
        return INVALID_NULL_POINTER;
    mat2D_info(im,&nrows,&ncols);
    //mat2D_print(im);

    //printf("\nLinhas: %d, Colunas: %d\n", nrows, ncols);

    TMat2D* im_root;
    im_root = mat2D_create(nrows,ncols);

    TQueue* lista_proximos;
    lista_proximos = queue_create();

    ponto p, p_atual;
    int val_im, val_im_root;
    int label=1;

    for (int i = 1; i < nrows-1; i++)
    {
        for (int j = 0; j < ncols-1; j++)
        {
            p.x = i;
            p.y = j;
            mat2D_get_value(im, p.x, p.y, &val_im);
            mat2D_get_value(im_root, p.x, p.y, &val_im_root);
            if(val_im==1 && val_im_root==0)
            {
                mat2D_set_value(im_root, p.x, p.y, label);
                queue_push(lista_proximos,p);

                while (!queue_empty(lista_proximos))
                {
                    queue_top(lista_proximos,&p_atual);
                    queue_pop(lista_proximos);

                    //////////////////////////////
                    p.x = p_atual.x - 1;
                    p.y = p_atual.y;
                    mat2D_get_value(im, p.x, p.y, &val_im);
                    mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                    if(val_im == 1 && val_im_root==0)
                    {
                        mat2D_set_value(im_root, p.x, p.y, label);
                        queue_push(lista_proximos,p);
                    }

                    //////////////////////////////
                    p.x = p_atual.x + 1;
                    p.y = p_atual.y;
                    mat2D_get_value(im, p.x, p.y, &val_im);
                    mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                    if(val_im == 1 && val_im_root==0)
                    {
                        mat2D_set_value(im_root, p.x, p.y, label);
                        queue_push(lista_proximos,p);
                    }

                    //////////////////////////////
                    p.x = p_atual.x;
                    p.y = p_atual.y - 1;
                    mat2D_get_value(im, p.x, p.y, &val_im);
                    mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                    if(val_im == 1 && val_im_root==0)
                    {
                        mat2D_set_value(im_root, p.x, p.y, label);
                        queue_push(lista_proximos,p);
                    }

                    //////////////////////////////
                    p.x = p_atual.x;
                    p.y = p_atual.y + 1;
                    mat2D_get_value(im, p.x, p.y, &val_im);
                    mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                    if(val_im == 1 && val_im_root==0)
                    {
                        mat2D_set_value(im_root, p.x, p.y, label);
                        queue_push(lista_proximos,p);
                    }
                }
                label += 1; 
            }
        } 
    }

    mat2D_print(im_root);
    write_bin(binario,im_root);

    return SUCCESS;
}

int write_bin(char* arg, TMat2D* mat)
{
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    FILE *segFp;
    segFp = fopen(arg,"wb");
    if (segFp == NULL)
        return INVALID_FILE;

    int val, nrows, ncols;

    mat2D_info(mat,&nrows,&ncols);

    fwrite(&nrows,sizeof(int),1,segFp);
    fwrite(&ncols,sizeof(int),1,segFp);

    for(int a = 0; a<nrows; a++)
    {
        for (int b = 0; b<ncols; b++)
        {
            mat2D_get_value(mat,a,b,&val);
            fwrite(&val, sizeof(int), 1, segFp);
        }
    }

    fclose(segFp);

    return SUCCESS;
}

int labfile(char* text, char* res)
{
    int v, val, val_root, nrows, ncols;

    TMat2D* im;
    im = image_create(text);
    if(im==NULL)
        return INVALID_NULL_POINTER;
    mat2D_info(im,&nrows,&ncols);

    TMat2D* im_root;
    im_root = mat2D_create(nrows,ncols);

    Stack* lista;
    lista = stack_create(100);

    Ponto p, p_atual;
    int val_im, val_im_root;
    int label=1;

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            p.x = i;
            p.y = j;
            mat2D_get_value(im, p.x, p.y, &val_im);
            mat2D_get_value(im_root, p.x, p.y, &val_im_root);
            if(val_im == 1 && (val_im_root!=3 && val_im_root!=2))
            {
                mat2D_set_value(im_root, p.x, p.y,2);
                stack_push(lista,p);

                
                if(p_atual.x==0 && p_atual.y == ncols-1)
                    break;

                while(!stack_empty(lista))
                {
                    stack_top(lista,&p_atual);
                    int vizinho = 0;

                    
                    if(p_atual.x==0 && p_atual.y == ncols-1)
                        break;

                    /////////ESQUERDA/////////////////////
                    if(p_atual.x - 1 >= 0)
                    {
                        p.x = p_atual.x - 1;
                        p.y = p_atual.y;
                        mat2D_get_value(im, p.x, p.y, &val_im);
                        mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                        if(val_im == 1 && (val_im_root!=3 && val_im_root!=2))
                        {
                            mat2D_set_value(im_root, p.x, p.y, 2);
                            stack_push(lista,p);
                            vizinho = 1;
                            if(p.x==0 && p.y == ncols-1)
                            {
                                break;
                            }
                        }
                    }

                    ////////DIREITA//////////////////////
                    if(p_atual.x - 1 <= nrows-1)
                    {
                        p.x = p_atual.x + 1;
                        p.y = p_atual.y;
                        mat2D_get_value(im, p.x, p.y, &val_im);
                        mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                        if(val_im == 1 && (val_im_root!=3 && val_im_root!=2))
                        {
                            mat2D_set_value(im_root, p.x, p.y, 2);
                            stack_push(lista,p);
                            vizinho = 1;
                            if(p.x==0 && p.y == ncols-1)
                            {
                                break;
                            }
                        }
                    }

                    ////////BAIXO//////////////////////
                    if(p_atual.y - 1 >= 0)
                    {
                        p.x = p_atual.x;
                        p.y = p_atual.y - 1;
                        mat2D_get_value(im, p.x, p.y, &val_im);
                        mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                        if(val_im == 1 && (val_im_root!=3 && val_im_root!=2))
                        {
                            mat2D_set_value(im_root, p.x, p.y, 2);
                            stack_push(lista,p);
                            vizinho = 1;
                            if(p.x==0 && p.y == ncols-1)
                            {
                                break;
                            }
                        }
                    }

                    ////////CIMA//////////////////////
                    if(p_atual.y + 1 <= ncols-1)
                    {
                        p.x = p_atual.x;
                        p.y = p_atual.y + 1;
                        mat2D_get_value(im, p.x, p.y, &val_im);
                        mat2D_get_value(im_root, p.x, p.y, &val_im_root);
                        if(val_im == 1 && (val_im_root!=3 && val_im_root!=2))
                        {
                            mat2D_set_value(im_root, p.x, p.y, 2);
                            stack_push(lista,p);
                            vizinho = 1;
                            if(p.x==0 && p.y == ncols-1)
                            {
                                break;
                            }
                        }
                    }       

                    if(!vizinho)
                    {
                        stack_pop(lista);
                        mat2D_set_value(im_root, p_atual.x, p_atual.y, 3);
                    }
                }
            }
        }
    }

    correct_infos(&im_root);
    //mat2D_print(im_root);
    write_txt(res,im_root);

    return SUCCESS;
}

int write_txt(char* arg, TMat2D* mat)
{
    if(mat==NULL)
        return INVALID_NULL_POINTER;

    FILE *segFp;
    segFp = fopen(arg,"w+");
    if (segFp == NULL)
        return INVALID_FILE;

    int nrows, ncols, val;
    mat2D_info(mat,&nrows,&ncols);

    for(int a = 0; a<nrows; a++)
    {
        for (int b = 0; b<ncols; b++)
        {
            mat2D_get_value(mat,a,b,&val);

            if(val==2) fprintf(segFp, "%d", val);
            else if(val==3||val==1) fprintf(segFp, "1");
            else fprintf(segFp, "0");

            if(b!=ncols-1) fprintf(segFp, " ");
        }if(a!=nrows-1)fprintf(segFp, "\n");
    }

    //mat2D_print(mat);
    fclose(segFp);

    return SUCCESS;

}

int correct_infos(TMat2D** mat)
{
    int nrows, ncols, val, aux, neighbor;
    mat2D_info(*mat,&nrows,&ncols);

    for(int a = 0; a<nrows; a++)
    {
        for (int b = 0; b<ncols; b++)
        {
            mat2D_get_value(*mat,a,b,&val);
            neighbor=0;
            if(val==2 && (a!=0 && b!=0))
            {
                aux=a-1;
                mat2D_get_value(*mat,aux,b,&val); if(val==2) neighbor++;
                aux=a+1;
                mat2D_get_value(*mat,aux,b,&val); if(val==2) neighbor++;
                aux=b-1;
                mat2D_get_value(*mat,a,aux,&val); if(val==2) neighbor++;
                aux=b+1;
                mat2D_get_value(*mat,a,aux,&val); if(val==2) neighbor++;
                if(neighbor<2)
                    mat2D_set_value(*mat,a,b,1);
            }
        }
    }

    return SUCCESS;
}