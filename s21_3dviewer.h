#ifndef SRC_3DVIEWER_H
#define SRC_3DVIEWER_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL 1
#define BAD_FILE 2

// #define PI 3.14159265358979323846

typedef struct {
  unsigned int countVertices;
  unsigned int countIndices;
  float *vertices;
  unsigned int *indices;
} obj;

void s21_vertices_and_index(obj *obj);

int open_file(char *user_file_name, FILE **file_name);
int parser(FILE *file, obj *obj);
void initObj(obj *obj);
int read_file(FILE *file, obj *obj);
int dynam_memory_alloc(obj *obj);
void free_dynam_memory_alloc(obj *obj);

// аффинные преобразования
void changing_the_rotation(obj *obj, double degree, char coordinate);
void changing_the_movement(obj *obj, double x, double y, double z);
void scale_changed(obj *obj, double scale);
#endif  // SRC_3DVIEWER_H
