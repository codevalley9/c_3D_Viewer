#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() {
  free_dynam_memory_alloc(my_obj);
  free(my_obj);
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST | GL_LINE_STIPPLE);
}

void MyOpenGLWidget::paintGL() {
  glClearColor(red_f / 255.0, green_f / 255.0, blue_f / 255.0,
               clarity_f / 255.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  lines_and_projection();
  glTranslatef(0, 0, -3);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  if (my_obj == nullptr) baseReadFile();
  showObg();
  update();
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-1, 1, -1, 1, 1, 3000);
}

void MyOpenGLWidget::readFile() {
  free_dynam_memory_alloc(my_obj);
  QByteArray byteArray = currentFilePath.toLocal8Bit();
  char *user_file_name = byteArray.data();
  FILE *file_name = NULL;
  if (!open_file(user_file_name, &file_name)) {
    int error = read_file(file_name, my_obj);
    if (error == FAIL)
      QMessageBox::critical(nullptr, "Ошибка", "Детка, выбери другой файл!");
    else if (error == BAD_FILE)
      QMessageBox::critical(nullptr, "Ошибка", "Детка, выбери другой файл!");
    else if (parser(file_name, my_obj) == FAIL)
      QMessageBox::critical(nullptr, "Ошибка", "Детка, выбери другой файл!");
    else
      normalize(my_obj);
  }

  if (file_name) fclose(file_name);
  update();
}
