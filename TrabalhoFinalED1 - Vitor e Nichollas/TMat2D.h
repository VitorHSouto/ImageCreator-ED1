typedef struct TMat2D TMat2D; 

TMat2D* mat2D_create(int nrows, int ncolumns);

int mat2D_free(TMat2D *mat);

void mat2D_print(TMat2D * mat);

int mat2D_set_value(TMat2D *mat, int i, int j, int val);

int mat2D_get_value(TMat2D *mat, int i, int j, int* val);

int mat2D_set_RandomValues(TMat2D *mat, int min, int max);

TMat2D* mat2D_sum(TMat2D *mat1, TMat2D *mat2);

TMat2D *mat2D_multiply(TMat2D *mat1, TMat2D *mat2);

TMat2D *mat2D_multiply_N(TMat2D *mat, int mult);

int mat2D_diagonal(TMat2D *mat);

TMat2D *mat2D_sum_rows(TMat2D *mat);

TMat2D *mat2D_sum_columns(TMat2D *mat);

int mat2D_info(TMat2D *mat, int *nrows, int *ncolumns);