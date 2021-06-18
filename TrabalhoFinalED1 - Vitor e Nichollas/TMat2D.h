typedef struct TMat2D TMat2D; 

TMat2D* mat2D_create(int nrows, int ncolumns);

int mat2D_free(TMat2D *mat);

void mat2D_print(TMat2D * mat);

int mat2D_set_value(TMat2D *mat, int i, int j, int val);

int mat2D_get_value(TMat2D *mat, int i, int j, int* val);

int mat2D_set_RandomValues(TMat2D *mat, int min, int max);

int mat2D_info(TMat2D *mat, int *nrows, int *ncolumns);