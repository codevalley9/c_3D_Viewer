#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D Viewer ^-^");

  ui->label->setText("Нет открытого файла");
  ui->label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
  time = 0.0;
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::recording);
  settings = new QSettings("3D", "Config");
}

MainWindow::~MainWindow() {
  save_settings();
  delete settings;
  delete ui;
}

void MainWindow::on_pushButton_open_file_clicked() {
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  QDir dir(QDir::currentPath());
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cd("data-samples");
  QString dataSamplesDir = dir.absolutePath();

  QFileDialog::Options options;
  options |= QFileDialog::DontUseNativeDialog;

  QString filePath = QFileDialog::getOpenFileName(
      this, "Choose a picture", dataSamplesDir,
      "OBJ Files (*.obj);;All Files (*)", nullptr, options);

  if (!filePath.isEmpty()) {
    ui->GLWidget->flag_open_file = true;
    ui->GLWidget->currentFilePath = filePath;
    ui->GLWidget->readFile();
    updateFileNameLabel(filePath);
  }
}

void MainWindow::updateFileNameLabel(QString filePath) {
  QFileInfo file(filePath);
  QString fileName = file.fileName();
  int numVertices = ui->GLWidget->my_obj->countVertices * 3;
  int numEdges = ui->GLWidget->my_obj->countIndices * 6;
  ui->label->setText("Открыт файл: " + fileName +
                     "\t Количество вершин: " + QString::number(numVertices) +
                     "\t Количество ребер: " + QString::number(numEdges));
}

void MainWindow::on_pushButton_screen_clicked() {
  QString imageDirPath = QDir::currentPath() + "../../../../../image";
  QDir imageDir(imageDirPath);
  if (!imageDir.exists()) {
    imageDir.mkpath(".");
  }

  QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
  QString filenameBMP = imageDirPath + "/screenshot_" + timestamp + ".bmp";
  QString filenameJPEG = imageDirPath + "/screenshot_" + timestamp + ".jpeg";

  QScreen *screen = QGuiApplication::primaryScreen();
  QPixmap screenshot =
      screen->grabWindow(QApplication::activeWindow()->winId());

  if (screenshot.save(filenameBMP, "BMP"))
    qDebug() << "Скриншот сохранен в формате BMP: " << filenameBMP;
  else
    qDebug() << "Ошибка при сохранении скриншота в формате BMP.";

  if (screenshot.save(filenameJPEG, "JPEG"))
    qDebug() << "Скриншот сохранен в формате JPEG: " << filenameJPEG;
  else
    qDebug() << "Ошибка при сохранении скриншота в формате JPEG.";
}

void MainWindow::on_pushButton_gif_clicked() {
  if (!is_recording) {
    is_recording = true;
    timer->start(100);
  }
}
