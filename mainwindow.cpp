#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageIndex = 0;
    connect(this, &MainWindow::signalShowImage, ui->graphicsView, &ImageHandlingForm::slotLoadImage);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    openFileNames = QFileDialog::getOpenFileNames(this, QDir::currentPath());
    QImage image = QImage(openFileNames.at(0));
    emit signalShowImage(image, 500);
}

void MainWindow::on_backwardPushButton_clicked()
{
    if(imageIndex > 0 && !openFileNames.isEmpty()){
        imageIndex--;
        QImage image = QImage(openFileNames.at(imageIndex));
        emit signalShowImage(image, 500);
    }
}

void MainWindow::on_forwardPushButton_clicked()
{
    if(imageIndex < openFileNames.size()-1 && !openFileNames.isEmpty()){
        imageIndex++;
        QImage image = QImage(openFileNames.at(imageIndex));
        emit signalShowImage(image, 500);
    }
}
