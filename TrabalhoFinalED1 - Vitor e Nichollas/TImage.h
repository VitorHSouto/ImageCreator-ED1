#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define INVALID_FILE -5
#include "TMat2D.h"

int open_file(FILE **fp, char* arg);
int show_image(FILE **fp);
TMat2D* image_create(FILE **fp);
int convert_file(FILE **fpT, FILE **fpB);