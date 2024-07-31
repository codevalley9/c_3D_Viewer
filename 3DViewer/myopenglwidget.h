#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QColor>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>
#include <iostream>

extern "C" {
#include "../s21_3dviewer.h"
}

#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT

 signals:
  void errorOccurred(const QString &errorMessage);

 public slots:
  void handleParsingError(const QString &errorMessage) {
    // Вывод сообщения об ошибке
    qDebug() << "Ошибка при парсинге файла:" << errorMessage;
    // Дополнительные действия при ошибке
  }

 public:
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  double red_f = 89, green_f = 122, blue_f = 94, clarity_f = 1.0;
  double red_line = 255.0, green_line = 255.0, blue_line = 255.0;

  void readFile();
  bool flag_open_file = false;
  QString currentFilePath;
  obj *my_obj = nullptr;

  double red_point = 0.0, green_point = 0.0, blue_point = 0.0;

  double dots_size = 0.0, line_size = 0.0;
  int point_type = 0;
  double scale_value = 1;

  int line_check = 0, projection_check = 0;
  float xPos = 0.0, yPos = 0.0, zPos = 0.0;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void drawCube(float a);

  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;
  void showObg();
  void baseReadFile();
  void draw_points();

  void lines_and_projection();

  float find_min_point(char coordinat_line, obj *my_obj);
  float find_max_point(char coordinat_line, obj *my_obj);
  float max_of_3values(double a, double b, double c);
  void normalize(obj *my_obj);

 private:
  float xRot = 0.0, yRot = 0.0, zRot = 0.0, mXRot = 0.0, mYRot = 0.0;
  QPoint mPos;
};

#endif  // MYOPENGLWIDGET_H
