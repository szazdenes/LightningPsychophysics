#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QShortcut>
#include <QTextStream>

#include "imagehandlingform.h"
#include "newsessiondialog.h"
#include "sessionreadydialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void signalShowImage(QImage &image, int timems);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadPushButton_clicked();
    void on_backwardPushButton_clicked();
    void on_forwardPushButton_clicked();
    void on_newSessionPushButton_clicked();
    void slotSessionReady();

private:
    Ui::MainWindow *ui;
    int imageIndex;
    QStringList openFileNames;
    QShortcut forwardShortcut, backwardShortcut;
    QFile outfile;
    QString patientName;
    int sessionNumber;
    QList<QPair<QPair<QString, QString>, int> > shuffledImageList; //first: 1:name 2:branches, second: time

    void refreshCounter(int num);
};

#endif // MAINWINDOW_H
