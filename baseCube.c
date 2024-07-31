#include "s21_3dviewer.h"

void s21_vertices_and_index(obj *obj) {
  obj->vertices[0] = -1.0f;
  obj->vertices[1] = -1.0f;
  obj->vertices[2] = 1.0f;
  obj->vertices[3] = 1.0f;
  obj->vertices[4] = -1.0f;
  obj->vertices[5] = 1.0f;
  obj->vertices[6] = 1.0f;
  obj->vertices[7] = 1.0f;
  obj->vertices[8] = 1.0f;
  obj->vertices[9] = -1.0f;
  obj->vertices[10] = 1.0f;
  obj->vertices[11] = 1.0f;

  obj->vertices[12] = -1.0f;
  obj->vertices[13] = -1.0f;
  obj->vertices[14] = -1.0f;
  obj->vertices[15] = 1.0f;
  obj->vertices[16] = -1.0f;
  obj->vertices[17] = -1.0f;
  obj->vertices[18] = 1.0f;
  obj->vertices[19] = 1.0f;
  obj->vertices[20] = -1.0f;
  obj->vertices[21] = -1.0f;
  obj->vertices[22] = 1.0f;
  obj->vertices[23] = -1.0f;

  obj->indices[0] = 0;
  obj->indices[1] = 1;
  obj->indices[2] = 1;
  obj->indices[3] = 2;
  obj->indices[4] = 2;
  obj->indices[5] = 3;
  obj->indices[6] = 3;
  obj->indices[7] = 0;
  obj->indices[8] = 4;
  obj->indices[9] = 5;
  obj->indices[10] = 5;
  obj->indices[11] = 6;
  obj->indices[12] = 6;
  obj->indices[13] = 7;
  obj->indices[14] = 7;
  obj->indices[15] = 4;
  obj->indices[16] = 0;
  obj->indices[17] = 4;
  obj->indices[18] = 1;
  obj->indices[19] = 5;
  obj->indices[20] = 2;
  obj->indices[21] = 6;
  obj->indices[22] = 3;
  obj->indices[23] = 7;
}
