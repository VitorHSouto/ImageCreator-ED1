#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define INVALID_FILE -5
#include "TMat2D.h"

int open_file(char* arg);
int show_image(FILE **fp);
TMat2D* image_create(FILE **fp);
int convert_file(char* texto, char* binario);
int show_image_bin(char* arg);
int segment_image(char* thr, char* file, char* segFile);
int segfile(char* texto, char* binario);
int write_bin(char* arg, TMat2D* mat);