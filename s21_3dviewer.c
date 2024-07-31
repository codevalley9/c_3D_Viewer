#include "s21_3dviewer.h"

int open_file(char *user_file_name, FILE **file_name) {
  *file_name = fopen(user_file_name, "r");
  if (!*file_name) {
    fprintf(stderr, "No such file: %s\n", user_file_name);
  }
  return (*file_name) ? SUCCESS : FAIL;
}

void initObj(obj *obj) {
  obj->countIndices = 0;
  obj->countVertices = 0;
  obj->vertices = NULL;
  obj->indices = NULL;
}

int read_file(FILE *file, obj *obj) {
  int err = SUCCESS;
  char line[256] = {0};
  if (fgets(line, sizeof(line), file) == NULL)
    err = FAIL;
  else
    fseek(file, 0, SEEK_SET);
  initObj(obj);
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == ' ')
      obj->countVertices++;
    else if (line[0] == 'f' && line[1] == ' ')
      obj->countIndices++;
  }
  if (obj->countVertices && obj->countIndices)
    err = dynam_memory_alloc(obj);
  else
    err = BAD_FILE;
  return err;
}

int dynam_memory_alloc(obj *obj) {
  int err = SUCCESS;
  obj->vertices = (float *)calloc(obj->countVertices * 3, sizeof(float));
  obj->indices =
      (unsigned int *)calloc(obj->countIndices * 6, sizeof(unsigned int));
  err = ((obj->indices) && (obj->vertices)) ? SUCCESS : FAIL;
  if (err) free_dynam_memory_alloc(obj);
  return err;
}

void free_dynam_memory_alloc(obj *obj) {
  if (obj->indices) free(obj->indices);
  if (obj->vertices) free(obj->vertices);
}

int parser(FILE *file, obj *obj) {
  int err = SUCCESS;
  char line[256] = {0};
  fseek(file, 0, SEEK_SET);
  int i = 0, j = 0, streak_of_indices = 0;

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      float x = 0.0, y = 0.0, z = 0.0;
      if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
        obj->vertices[i] = x;
        obj->vertices[++i] = y;
        obj->vertices[++i] = z;
        i++;
        streak_of_indices++;
      } else {
        err = FAIL;
        break;
      }
    } else if (strncmp(line, "f ", 2) == 0) {
      int v1 = 0, v2 = 0, v3 = 0;
      if (sscanf(line, "f %d", &v1) == 1 &&
          sscanf(line, "f %*[^ ] %d", &v2) == 1 &&
          sscanf(line, "f %*[^ ] %*[^ ] %d", &v3) == 1) {
        obj->indices[j] = v1 < 0 ? streak_of_indices + v1 : v1 - 1;
        obj->indices[++j] = v2 < 0 ? streak_of_indices + v2 : v2 - 1;
        obj->indices[++j] = v2 < 0 ? streak_of_indices + v2 : v2 - 1;
        obj->indices[++j] = v3 < 0 ? streak_of_indices + v3 : v3 - 1;
        obj->indices[++j] = v3 < 0 ? streak_of_indices + v3 : v3 - 1;
        obj->indices[++j] = v1 < 0 ? streak_of_indices + v1 : v1 - 1;
        j++;
      } else {
        err = FAIL;
        break;
      }
    }
  }
  int vLength = sizeof(&obj->vertices) / sizeof(obj->vertices[0]);
  int fLength = sizeof(&obj->indices) / sizeof(obj->indices[0]);
  if (vLength <= 0 && fLength <= 0) {
    err = FAIL;
  }
  return err;
}

void changing_the_rotation(obj *obj, double degree, char coordinate) {
  double radian = degree * M_PI / 180;
  for (unsigned int i = 0; i < obj->countVertices * 3 - 2; i += 3) {
    double x = obj->vertices[i];
    double y = obj->vertices[i + 1];
    double z = obj->vertices[i + 2];
    switch (coordinate) {
      case 'x':
        obj->vertices[i + 1] = y * cos(radian) - sin(radian) * z;
        obj->vertices[i + 2] = y * sin(radian) + cos(radian) * z;
        break;
      case 'y':
        obj->vertices[i] = x * cos(radian) + sin(radian) * z;
        obj->vertices[i + 2] = -x * sin(radian) + cos(radian) * z;
        break;
      case 'z':
        obj->vertices[i] = x * cos(radian) - sin(radian) * y;
        obj->vertices[i + 1] = x * sin(radian) + cos(radian) * y;
        break;
      default:;
    }
  }
}

void changing_the_movement(obj *obj, double x, double y, double z) {
  for (unsigned int i = 0; i < obj->countVertices * 3 - 2; i += 3) {
    obj->vertices[i] += x;
    obj->vertices[i + 1] += y;
    obj->vertices[i + 2] += z;
  }
}

void scale_changed(obj *obj, double scale) {
  for (unsigned int i = 0; i < obj->countVertices * 3; ++i)
    (obj->vertices)[i] *= scale;
}
