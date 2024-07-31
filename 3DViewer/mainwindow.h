#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/qtwidgetsglobal.h>

#include <QApplication>
#include <QButtonGroup>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QSettings>
#include <QTimer>

#include "QtGifImage/src/gifimage/qgifimage.h"
#include "myopenglwidget.h"

extern "C" {
#include "../s21_3dviewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  float time;

 private slots:

  void on_pushButton_open_file_clicked();
  void on_pushButton_screen_clicked();
  void on_color_line_clicked();
  void on_color_points_clicked();
  void on_size_of_point_valueChanged(double arg1);
  void on_size_lines_valueChanged(double arg1);
  void on_no_point_clicked();
  void on_round_point_clicked();
  void on_square_point_clicked();
  void on_pushButton_gif_clicked();
  void on_color_back_clicked();
  void updateFileNameLabel(QString fileName);
  void on_scale_valueChanged(double arg1);

  void on_line_dots_clicked();
  void on_line_solid_clicked();
  void on_projection_central_clicked();
  void on_projection_parallel_clicked();

  void on_rotate_X_valueChanged(double rot_x);
  void on_rotate_Y_valueChanged(double rot_y);
  void on_rotate_Z_valueChanged(double rot_z);
  void on_move_X_valueChanged(double rot_x);
  void on_move_Y_valueChanged(double rot_y);
  void on_move_Z_valueChanged(double rot_z);

  void save_settings();
  void apply_settings();
  void saveLine();
  void on_use_settings_clicked();
  void on_save_settings_clicked();

 private:
  Ui::MainWindow *ui;

  QVector<QImage> gifFrames;
  QTimer *timer;

  bool is_recording = false;

  QSettings *settings;
  void saveGIF();
  void recording();
};
#endif  // MAINWINDOW_H
