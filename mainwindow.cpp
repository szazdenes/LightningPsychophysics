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
    ui->newSessionPushButton->setDisabled(true);
    ui->photoRadioButton->toggle();

    imageIndex = -1;
    patientName = "";
    sessionNumber = 0;

    connect(this, &MainWindow::signalShowImage, ui->graphicsView, &ImageHandlingForm::slotLoadImage);

    forwardShortcut.setKey(Qt::Key_Space);
    forwardShortcut.setContext(Qt::ApplicationShortcut);

    backwardShortcut.setKey(Qt::Key_Left);
    backwardShortcut.setContext(Qt::ApplicationShortcut);

    shuffledImageList.clear();
    QFile imageListFile("../../selected/lightningList.dat");
    if(!imageListFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug("ImageList opening error");
    QTextStream stream(&imageListFile);
    while(!stream.atEnd()){
        QString line = stream.readLine();
        QTextStream lineStream(&line);
        QString name, branch;
        lineStream >> name >> branch;
        while(name.size() < 4)
            name.prepend("0");
        QPair<QString, QString> currentPair;
        currentPair.first = name;
        currentPair.second = branch;
        shuffledImageList.append(QPair<QPair<QString, QString>, int>(currentPair, 500));
        shuffledImageList.append(QPair<QPair<QString, QString>, int>(currentPair, 750));
        shuffledImageList.append(QPair<QPair<QString, QString>, int>(currentPair, 1000));
    }
    imageListFile.close();
    refreshCounter(imageIndex+1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadPushButton_clicked()
{
    ui->forwardPushButton->setDisabled(true);
    std::random_shuffle(shuffledImageList.begin(), shuffledImageList.end());
    std::random_shuffle(shuffledImageList.begin(), shuffledImageList.end());
    std::random_shuffle(shuffledImageList.begin(), shuffledImageList.end());
    ui->newSessionPushButton->setEnabled(true);
}

void MainWindow::on_backwardPushButton_clicked()
{
    if(imageIndex >= 0 && imageIndex < shuffledImageList.size() && !shuffledImageList.isEmpty()){
        if(imageIndex > 0) imageIndex--;
        QString imagePath;
        if(ui->photoRadioButton->isChecked()) imagePath = "../../selected/" + shuffledImageList.at(imageIndex).first.first + ".jpg";
        if(ui->skeletonRadioButton->isChecked()) imagePath = "../../Agrajz/" + shuffledImageList.at(imageIndex).first.first + "-agrajz.png";
        QImage image = QImage(imagePath);
        if(image.isNull()){
            if(ui->photoRadioButton->isChecked()) imagePath = "../../selected/" + shuffledImageList.at(imageIndex).first.first + ".JPG";
            if(ui->skeletonRadioButton->isChecked()) imagePath = "../../Agrajz/" + shuffledImageList.at(imageIndex).first.first + "-agrajz.PNG";
            image = QImage(imagePath);
        }
        int duration_ms = shuffledImageList.at(imageIndex).second;
        emit signalShowImage(image, duration_ms);
        refreshCounter(imageIndex+1);
    }
}

void MainWindow::on_forwardPushButton_clicked()
{
    if(imageIndex < shuffledImageList.size()-1 && !shuffledImageList.isEmpty()){
        imageIndex++;
        QString imagePath;
        if(ui->photoRadioButton->isChecked()) imagePath = "../../selected/" + shuffledImageList.at(imageIndex).first.first + ".jpg";
        if(ui->skeletonRadioButton->isChecked()) imagePath = "../../Agrajz/" + shuffledImageList.at(imageIndex).first.first + "-agrajz.png";
        QImage image = QImage(imagePath);
        if(image.isNull()){
            if(ui->photoRadioButton->isChecked()) imagePath = "../../selected/" + shuffledImageList.at(imageIndex).first.first + ".JPG";
            if(ui->skeletonRadioButton->isChecked()) imagePath = "../../Agrajz/" + shuffledImageList.at(imageIndex).first.first + "-agrajz.PNG";
            image = QImage(imagePath);
        }
        int duration_ms = shuffledImageList.at(imageIndex).second;
        emit signalShowImage(image, duration_ms);
        refreshCounter(imageIndex+1);
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

    QFile outFile;
    if(ui->photoRadioButton->isChecked()) outFile.setFileName("../../" + patientName + "_" + QString::number(sessionNumber) + "_photo.csv");
    if(ui->skeletonRadioButton->isChecked()) outFile.setFileName("../../" + patientName + "_" + QString::number(sessionNumber) + "_skeleton.csv");
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug("outFile opening error");
    QTextStream out(&outFile);
    out << "#filename" << "\t" << "real branches" << "\t" << "observation time (ms)" << "\t" << "estimated branches" << "\n";
    for(int i = 0; i < shuffledImageList.size(); i++){
        QPair<QPair<QString, QString>, int> current = shuffledImageList.at(i);
        if(i < shuffledImageList.size()-1) out << current.first.first << "\t" << QString::number(current.first.second.toInt()+1) << "\t" << QString::number(current.second) << "\n";
        else out << current.first.first << "\t" << QString::number(current.first.second.toInt()+1) << "\t" << QString::number(current.second);
    }
    outFile.close();

    ui->forwardPushButton->setEnabled(true);
    ui->newSessionPushButton->setDisabled(true);
    ui->loadPushButton->setDisabled(true);
    ui->photoRadioButton->setDisabled(true);
    ui->skeletonRadioButton->setDisabled(true);
}

void MainWindow::slotSessionReady()
{
    ui->forwardPushButton->setDisabled(true);
    disconnect(&forwardShortcut, &QShortcut::activated, this, &MainWindow::on_forwardPushButton_clicked);
    disconnect(&backwardShortcut, &QShortcut::activated, this, &MainWindow::on_backwardPushButton_clicked);
    imageIndex = -1;

    ui->forwardPushButton->setDisabled(true);
    ui->loadPushButton->setEnabled(true);
    ui->newSessionPushButton->setDisabled(true);
    ui->photoRadioButton->setEnabled(true);
    ui->skeletonRadioButton->setEnabled(true);
    refreshCounter(imageIndex+1);
}

void MainWindow::refreshCounter(int num)
{
    ui->lcdNumber->display(QString::number(num));
}
