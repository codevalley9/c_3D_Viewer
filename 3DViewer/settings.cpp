#include "myopenglwidget.h"

void MyOpenGLWidget::showObg() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, my_obj->vertices);
  glColor3f(red_line / 255.0, green_line / 255.0, blue_line / 255.0);
  glLineWidth(line_size);
  int n = 0;
  if (!flag_open_file)
    n = 3;
  else
    n = 6;
  glDrawElements(GL_LINES, my_obj->countIndices * n, GL_UNSIGNED_INT,
                 my_obj->indices);
  draw_points();
  glDisableClientState(GL_VERTEX_ARRAY);

  update();
}

void MyOpenGLWidget::baseReadFile() {
  my_obj = (obj *)calloc(1, sizeof(obj));
  my_obj->vertices = (float *)calloc(24, sizeof(float));
  my_obj->indices = (unsigned int *)calloc(24, sizeof(unsigned int));
  s21_vertices_and_index(my_obj);
  my_obj->countIndices = 8;
  my_obj->countVertices = 8;
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *mo) {
  mPos = mo->pos();
  mXRot = xRot;
  mYRot = yRot;
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = mXRot + (mo->pos().y() - mPos.y());
  yRot = mYRot + (mo->pos().x() - mPos.x());
  update();
}

void MyOpenGLWidget::lines_and_projection() {
  float fov = 60.0 * M_PI / 180;
  float size = 1;
  float heapHeight = size / (2 * tan(fov / 2));
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_check)
    glOrtho(-1, 1, -1, 1, 1, 30);
  else
    glFrustum(-size, size, -size, size, heapHeight, 30);
  glEnable(GL_LINE_STIPPLE);
  if (line_check)
    glLineStipple(2, 0x00FF);
  else
    glLineStipple(2, 0xFFFF);
}

void MyOpenGLWidget::draw_points() {
  if (point_type != 0) {
    glColor3f(red_point / 255.0, green_point / 255.0, blue_point / 255.0);
    glPointSize(dots_size);
    glDrawArrays(GL_POINTS, 0, my_obj->countVertices);
    if (point_type == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else if (point_type == 2) {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_POINT);
    }
  }
  update();
}

float MyOpenGLWidget::find_min_point(char coordinat_line, obj *my_obj) {
  int index = 0;
  if (coordinat_line == 'x')
    index = 0;
  else if (coordinat_line == 'y')
    index = 1;
  else if (coordinat_line == 'z')
    index = 2;
  float find_min_point = my_obj->vertices[index];
  for (int i = index; i < my_obj->countVertices * 3; i += 3) {
    if (my_obj->vertices[i] < find_min_point) {
      find_min_point = my_obj->vertices[i];
    }
  }
  return find_min_point;
}

float MyOpenGLWidget::find_max_point(char coordinat_line, obj *my_obj) {
  int index = 0;
  if (coordinat_line == 'x') {
    index = 0;
  } else if (coordinat_line == 'y') {
    index = 1;
  } else if (coordinat_line == 'z') {
    index = 2;
  }
  float find_max_point = my_obj->vertices[index];
  for (int i = index; i < my_obj->countVertices * 3; i += 3) {
    if (my_obj->vertices[i] > find_max_point) {
      find_max_point = my_obj->vertices[i];
    }
  }
  return find_max_point;
}

float MyOpenGLWidget::max_of_3values(double a, double b, double c) {
  float max = 0.0;
  if (a >= b && a >= c)
    max = a;
  else if (b >= a && b >= c)
    max = b;
  else
    max = c;
  return max;
}

void MyOpenGLWidget::normalize(obj *my_obj) {
  float min_x = find_min_point('x', my_obj);
  float min_y = find_min_point('y', my_obj);
  float min_z = find_min_point('z', my_obj);
  float max_x = find_max_point('x', my_obj);
  float max_y = find_max_point('y', my_obj);
  float max_z = find_max_point('z', my_obj);

  float mean_x = max_x - min_x;
  float mean_y = max_y - min_y;
  float mean_z = max_z - min_z;

  float center_x = min_x + (max_x - min_x) / 2;
  float center_y = min_y + (max_y - min_y) / 2;
  float center_z = min_z + (max_z - min_z) / 2;

  for (int i = 0; i < my_obj->countVertices * 3; i += 3) {
    my_obj->vertices[i] -= center_x;
    my_obj->vertices[i + 1] -= center_y;
    my_obj->vertices[i + 2] -= center_z;
  }

  float dmax = max_of_3values(mean_x, mean_y, mean_z);

  float value = 1;
  float scale = (value - (value * (-3))) / dmax;
  scale_changed(my_obj, scale);
}
