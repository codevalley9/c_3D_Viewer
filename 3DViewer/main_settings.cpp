#include "mainwindow.h"
#include "ui_mainwindow.h"

// изменение цвета
void MainWindow::on_color_back_clicked() {
  QColor color = QColorDialog::getColor(Qt::blue).toRgb();
  ui->GLWidget->red_f = color.red();
  ui->GLWidget->green_f = color.green();
  ui->GLWidget->blue_f = color.blue();
  ui->GLWidget->clarity_f = color.alpha();
  ui->GLWidget->update();
}

void MainWindow::on_color_line_clicked() {
  QColor color = QColorDialog::getColor(Qt::blue).toRgb();
  ui->GLWidget->red_line = color.red();
  ui->GLWidget->green_line = color.green();
  ui->GLWidget->blue_line = color.blue();
  ui->GLWidget->update();
}

void MainWindow::on_color_points_clicked() {
  QColor color = QColorDialog::getColor(Qt::blue).toRgb();
  ui->GLWidget->red_point = color.red();
  ui->GLWidget->green_point = color.green();
  ui->GLWidget->blue_point = color.blue();
  ui->GLWidget->update();
}

// изменение размера вершин
void MainWindow::on_size_of_point_valueChanged(double arg1) {
  ui->GLWidget->dots_size = arg1;
  ui->GLWidget->update();
}

// изменение размера рёбер
void MainWindow::on_size_lines_valueChanged(double arg1) {
  ui->GLWidget->line_size = arg1;
  ui->GLWidget->update();
}

// изменение формы вершин
void MainWindow::on_no_point_clicked() {
  ui->GLWidget->point_type = 0;
  ui->GLWidget->update();
}

void MainWindow::on_round_point_clicked() {
  ui->GLWidget->point_type = 1;
  ui->GLWidget->update();
}

void MainWindow::on_square_point_clicked() {
  ui->GLWidget->point_type = 2;
  ui->GLWidget->update();
}

// масштаб
void MainWindow::on_scale_valueChanged(double arg1) {
  scale_changed(ui->GLWidget->my_obj, 1 / (ui->GLWidget->scale_value));
  scale_changed(ui->GLWidget->my_obj, arg1);
  ui->GLWidget->scale_value = arg1;
  ui->GLWidget->update();
}

// изменение формы линий
void MainWindow::on_line_dots_clicked() {
  if (ui->line_dots->isChecked()) {
    ui->GLWidget->line_check = 1;
    ui->GLWidget->update();
  }
}

void MainWindow::on_line_solid_clicked() {
  if (ui->line_solid->isChecked()) ui->GLWidget->line_check = 0;
  ui->GLWidget->update();
}

// изменение проекции
void MainWindow::on_projection_central_clicked() {
  if (ui->projection_central->isChecked()) {
    ui->GLWidget->projection_check = 1;
    ui->GLWidget->update();
  }
}

void MainWindow::on_projection_parallel_clicked() {
  if (ui->projection_parallel->isChecked()) {
    ui->GLWidget->projection_check = 0;
    ui->GLWidget->update();
  }
}

// аффинные преобразования
void MainWindow::on_rotate_X_valueChanged(double rot_x) {
  changing_the_rotation(this->ui->GLWidget->my_obj, rot_x, 'x');
  this->ui->GLWidget->update();
}

void MainWindow::on_rotate_Y_valueChanged(double rot_y) {
  changing_the_rotation(this->ui->GLWidget->my_obj, rot_y, 'y');
  this->ui->GLWidget->update();
}

void MainWindow::on_rotate_Z_valueChanged(double rot_z) {
  changing_the_rotation(this->ui->GLWidget->my_obj, rot_z, 'z');
  this->ui->GLWidget->update();
}

void MainWindow::on_move_X_valueChanged(double rot_x) {
  for (unsigned int i = 0;
       i < this->ui->GLWidget->my_obj->countVertices * 3 - 2; i += 3) {
    this->ui->GLWidget->my_obj->vertices[i] -= this->ui->GLWidget->xPos;
    this->ui->GLWidget->my_obj->vertices[i] += rot_x;
  }
  this->ui->GLWidget->xPos = rot_x;
  this->ui->GLWidget->update();
}

void MainWindow::on_move_Y_valueChanged(double rot_y) {
  for (unsigned int i = 1; i < this->ui->GLWidget->my_obj->countVertices * 3;
       i += 3) {
    this->ui->GLWidget->my_obj->vertices[i] -= this->ui->GLWidget->yPos;
    this->ui->GLWidget->my_obj->vertices[i] += rot_y;
  }
  this->ui->GLWidget->yPos = rot_y;
  this->ui->GLWidget->update();
}

void MainWindow::on_move_Z_valueChanged(double rot_z) {
  for (unsigned int i = 2; i < this->ui->GLWidget->my_obj->countVertices * 3;
       i += 3) {
    this->ui->GLWidget->my_obj->vertices[i] -= this->ui->GLWidget->zPos;
    this->ui->GLWidget->my_obj->vertices[i] += rot_z;
  }
  this->ui->GLWidget->zPos = rot_z;
  this->ui->GLWidget->update();
}

// сохранение настроек
void MainWindow::save_settings() {
  settings->setValue("red_back", ui->GLWidget->red_f);
  settings->setValue("green_back", ui->GLWidget->green_f);
  settings->setValue("blue_back", ui->GLWidget->blue_f);
  settings->setValue("clarity_back", ui->GLWidget->clarity_f);

  settings->setValue("point_type", ui->GLWidget->point_type);
  settings->setValue("size_point", ui->GLWidget->dots_size);
  settings->setValue("red_point", ui->GLWidget->red_point);
  settings->setValue("green_point", ui->GLWidget->green_point);
  settings->setValue("blue_point", ui->GLWidget->blue_point);

  settings->setValue("size_line", ui->GLWidget->line_size);
  settings->setValue("red_line", ui->GLWidget->red_line);
  settings->setValue("green_line", ui->GLWidget->green_line);
  settings->setValue("blue_line", ui->GLWidget->blue_line);

  settings->setValue("ortho", ui->GLWidget->projection_check);
  settings->setValue("line_check", ui->GLWidget->line_check);

  settings->setValue("x", ui->GLWidget->xPos);
  settings->setValue("y", ui->GLWidget->yPos);
  settings->setValue("z", ui->GLWidget->zPos);
}

void MainWindow::apply_settings() {
  ui->GLWidget->red_f = settings->value("red_back", 0).toDouble();
  ui->GLWidget->green_f = settings->value("green_back", 0).toDouble();
  ui->GLWidget->blue_f = settings->value("blue_back", 0).toDouble();
  ui->GLWidget->clarity_f = settings->value("clarity_back", 0).toDouble();

  ui->GLWidget->red_line = settings->value("red_line", 0).toDouble();
  ui->GLWidget->green_line = settings->value("green_line", 0).toDouble();
  ui->GLWidget->blue_line = settings->value("blue_line", 0).toDouble();

  ui->GLWidget->red_point = settings->value("red_point", 0).toDouble();
  ui->GLWidget->green_point = settings->value("green_point", 0).toDouble();
  ui->GLWidget->blue_point = settings->value("blue_point", 0).toDouble();

  ui->GLWidget->dots_size = settings->value("size_point", 0).toInt();
  ui->size_of_point->setValue(ui->GLWidget->dots_size);

  ui->GLWidget->line_size = settings->value("size_line", 0).toInt();
  ui->size_lines->setValue(ui->GLWidget->line_size);
  saveLine();
  ui->GLWidget->xPos = settings->value("x", 0).toDouble();
  ui->GLWidget->yPos = settings->value("y", 0).toDouble();
  ui->GLWidget->zPos = settings->value("z", 0).toDouble();
}

void MainWindow::saveLine() {
  ui->GLWidget->projection_check = settings->value("ortho").toInt();
  int selectedTypeOrto = settings->value("ortho", 0).toInt();
  if (selectedTypeOrto == 0) {
    ui->projection_central->setChecked(false);
    ui->projection_parallel->setChecked(true);
  } else if (selectedTypeOrto == 1) {
    ui->projection_parallel->setChecked(false);
    ui->projection_central->setChecked(true);
  }

  ui->GLWidget->line_check = settings->value("line_check", 0).toInt();
  int selectedTypeLine = settings->value("line_check", 0).toInt();
  if (selectedTypeLine == 0) {
    ui->line_dots->setChecked(false);
    ui->line_solid->setChecked(true);
  } else if (selectedTypeLine == 1) {
    ui->line_solid->setChecked(false);
    ui->line_dots->setChecked(true);
  }

  ui->GLWidget->point_type = settings->value("point_type", 0).toInt();
  int selectedType = settings->value("point_type", 0).toInt();
  if (selectedType == 0) {
    ui->round_point->setChecked(false);
    ui->square_point->setChecked(false);
    ui->no_point->setChecked(true);
  } else if (selectedType == 1) {
    ui->round_point->setChecked(true);
    ui->no_point->setChecked(false);
    ui->square_point->setChecked(false);
  } else if (selectedType == 2) {
    ui->square_point->setChecked(true);
    ui->no_point->setChecked(false);
    ui->round_point->setChecked(false);
  }
}

void MainWindow::on_use_settings_clicked() {
  apply_settings();
  ui->GLWidget->update();
}

void MainWindow::on_save_settings_clicked() { save_settings(); }

// функции для сохранения гифки
void MainWindow::recording() {
  if (is_recording && time <= 5.0) {
    gifFrames.push_back(ui->GLWidget->grab().toImage());
    time += 0.1;
  } else {
    saveGIF();
    timer->stop();
    time = 0.0;
  }
}

void MainWindow::saveGIF() {
  QString gifDirPath = QDir::currentPath() + "../../../../../gif";
  QDir gifDir(gifDirPath);
  if (!gifDir.exists()) {
    gifDir.mkpath(".");
  }
  QGifImage gif(QSize(1300, 1100));
  for (QVector<QImage>::Iterator frame = gifFrames.begin();
       frame != gifFrames.end(); frame++) {
    gif.addFrame(*frame, 0);
  }
  QTime time = QTime::currentTime();
  QString curTime = time.toString("hh_mm_ss");
  QString filenameGIF = gifDirPath + "/" + "gif_" + curTime + ".gif";

  if (gif.save(filenameGIF))
    qDebug() << "Гифка сохранена в: " << filenameGIF;
  else
    qDebug() << "Ошибка при сохранении гифки.";
  gifFrames.clear();
  is_recording = false;
}
