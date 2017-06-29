#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    forwardShortcut(this),
    backwardShortcut(this)
{
    ui->setupUi(this);

    ui->backwardPushButton->setHidden(true);
    ui->forwardPushButton->setDisabled(true);

    imageIndex = -1;
    duration_ms = 500;
    patientName = "";
    sessionNumber = 0;

    connect(this, &MainWindow::signalShowImage, ui->graphicsView, &ImageHandlingForm::slotLoadImage);

    forwardShortcut.setKey(Qt::Key_Space);
    forwardShortcut.setContext(Qt::ApplicationShortcut);

    backwardShortcut.setKey(Qt::Key_Left);
    backwardShortcut.setContext(Qt::ApplicationShortcut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    openFileNames = QFileDialog::getOpenFileNames(this, QDir::currentPath());
    imageIndex = -1;
    sessionNumber = 0;
    patientName = "";

    ui->forwardPushButton->setDisabled(true);
    ui->newSessionPushButton->setEnabled(true);
    outfile.close();
}

void MainWindow::on_backwardPushButton_clicked()
{
    if(imageIndex >= 0 && imageIndex < openFileNames.size() && !openFileNames.isEmpty()){
        if(imageIndex > 0) imageIndex--;
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
    else{
        SessionReadyDialog dialog;
        connect(&dialog, &SessionReadyDialog::signalSessionReady, this, &MainWindow::slotSessionReady);
        dialog.exec();
    }
}

void MainWindow::on_newSessionPushButton_clicked()
{
    NewSessionDialog dialog(this, patientName, sessionNumber+1);
    if(dialog.exec() != QDialog::Accepted)
        return;

    patientName = dialog.getPatientName();
    sessionNumber = dialog.getSessionNumber();
    connect(&forwardShortcut, &QShortcut::activated, this, &MainWindow::on_forwardPushButton_clicked);
    connect(&backwardShortcut, &QShortcut::activated, this, &MainWindow::on_backwardPushButton_clicked);
    imageIndex = -1;

    ui->forwardPushButton->setEnabled(true);
    ui->newSessionPushButton->setDisabled(true);
}

void MainWindow::slotSessionReady()
{
    ui->forwardPushButton->setDisabled(true);
    imageIndex = -1;
    disconnect(&forwardShortcut, &QShortcut::activated, this, &MainWindow::on_forwardPushButton_clicked);
    disconnect(&backwardShortcut, &QShortcut::activated, this, &MainWindow::on_backwardPushButton_clicked);

    ui->forwardPushButton->setDisabled(true);
    ui->newSessionPushButton->setEnabled(true);
}
