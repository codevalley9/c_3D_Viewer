#include <check.h>
// #include <math.h>

#include "s21_3dviewer.h"

//несуществующий файл
START_TEST(test_parsing_1) {
  char *user_file_name = "./objects/none.txt";
  FILE *file_name = NULL;
  int err = open_file(user_file_name, &file_name);
  ck_assert_int_eq(err, 1);
}
END_TEST

// //пустой файл
START_TEST(test_parsing_2) {
  char *user_file_name = "./objects/empty.txt";
  FILE *file_name = NULL;
  open_file(user_file_name, &file_name);
  obj *my_obj;
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err = read_file(file_name, my_obj);
  ck_assert_int_eq(err, 2);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

//небитые и непустые файлы
START_TEST(test_parsing_3) {
  char *user_file_name = "./objects/cube.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 8);
  ck_assert_int_eq(my_obj->countIndices, 12);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_4) {
  char *user_file_name = "./objects/cat.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 1136);
  ck_assert_int_eq(my_obj->countIndices, 2082);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_5) {
  char *user_file_name = "./objects/eyeball.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 9667);
  ck_assert_int_eq(my_obj->countIndices, 9344);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_6) {
  char *user_file_name = "./objects/octopus.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 6424);
  ck_assert_int_eq(my_obj->countIndices, 6354);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_7) {
  char *user_file_name = "./objects/gnom.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 3618);
  ck_assert_int_eq(my_obj->countIndices, 3427);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_8) {
  char *user_file_name = "./objects/hand.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 4406);
  ck_assert_int_eq(my_obj->countIndices, 4404);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_9) {
  char *user_file_name = "./objects/dolphin.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 7338);
  ck_assert_int_eq(my_obj->countIndices, 7336);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

START_TEST(test_parsing_10) {
  char *user_file_name = "./objects/ring.txt";
  FILE *file_name = NULL;
  obj *my_obj = NULL;
  int err_1 = open_file(user_file_name, &file_name);
  my_obj = (obj *)calloc(1, sizeof(obj));
  int err_2 = read_file(file_name, my_obj);
  parser(file_name, my_obj);
  ck_assert_int_eq(err_1, 0);
  ck_assert_int_eq(err_2, 0);
  ck_assert_int_eq(my_obj->countVertices, 63);
  ck_assert_int_eq(my_obj->countIndices, 96);
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}
END_TEST

// Аффинные преобразования
START_TEST(test_affine_1) {
  obj *my_obj = (obj *)calloc(1, sizeof(obj));
  obj *my_obj_2 = (obj *)calloc(1, sizeof(obj));
  my_obj->vertices = (float *)calloc(24, sizeof(float));
  my_obj->indices = (unsigned int *)calloc(24, sizeof(unsigned int));
  my_obj_2->vertices = (float *)calloc(24, sizeof(float));
  my_obj_2->indices = (unsigned int *)calloc(24, sizeof(unsigned int));
  s21_vertices_and_index(my_obj);
  s21_vertices_and_index(my_obj_2);
  my_obj->countIndices = 8;
  my_obj->countVertices = 8;
  my_obj_2->countIndices = 8;
  my_obj_2->countVertices = 8;
  changing_the_movement(my_obj_2, 1.0, 1.0, 1.0);
  for (unsigned int i = 0; i < my_obj->countVertices; i++) {
    ck_assert_double_eq(my_obj->vertices[i] + 1, my_obj_2->vertices[i]);
    ck_assert_double_eq(my_obj->vertices[i + 1] + 1, my_obj_2->vertices[i + 1]);
    ck_assert_double_eq(my_obj->vertices[i + 2] + 1, my_obj_2->vertices[i + 2]);
  }
  free_dynam_memory_alloc(my_obj);
  free_dynam_memory_alloc(my_obj_2);
  free(my_obj);
  free(my_obj_2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("parser");
  TCase *test_case_1 = tcase_create("parser");
  SRunner *sr = srunner_create(s1);
  int res;
  srunner_set_fork_status(sr, CK_NOFORK);
  suite_add_tcase(s1, test_case_1);

  tcase_add_test(test_case_1, test_parsing_1);
  tcase_add_test(test_case_1, test_parsing_2);
  tcase_add_test(test_case_1, test_parsing_3);
  tcase_add_test(test_case_1, test_parsing_4);
  tcase_add_test(test_case_1, test_parsing_5);
  tcase_add_test(test_case_1, test_parsing_6);
  tcase_add_test(test_case_1, test_parsing_7);
  tcase_add_test(test_case_1, test_parsing_8);
  tcase_add_test(test_case_1, test_parsing_9);
  tcase_add_test(test_case_1, test_parsing_10);
  tcase_add_test(test_case_1, test_affine_1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  res = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (!res) ? EXIT_SUCCESS : EXIT_FAILURE;
}
