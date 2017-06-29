#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->backwardPushButton->setHidden(true);
    ui->forwardPushButton->setDisabled(true);

    imageIndex = -1;
    duration_ms = 500;
    connect(this, &MainWindow::signalShowImage, ui->graphicsView, &ImageHandlingForm::slotLoadImage);

    new QShortcut(QKeySequence(Qt::Key_Space), this, SLOT(on_forwardPushButton_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(on_forwardPushButton_clicked()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(on_backwardPushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    openFileNames = QFileDialog::getOpenFileNames(this, QDir::currentPath());
    imageIndex = -1;
}

void MainWindow::on_backwardPushButton_clicked()
{
    if(imageIndex > 0 && !openFileNames.isEmpty()){
        imageIndex--;
        QImage image = QImage(openFileNames.at(imageIndex));
        emit signalShowImage(image, duration_ms);
    }
}

void MainWindow::on_forwardPushButton_clicked()
{
    if(imageIndex < openFileNames.size()-1 && !openFileNames.isEmpty()){
        imageIndex++;
        QImage image = QImage(openFileNames.at(imageIndex));
        emit signalShowImage(image, duration_ms);
    }
}
