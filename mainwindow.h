#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QShortcut>
#include <QFileDialog>

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
    int duration_ms;
    QStringList openFileNames;
    QShortcut forwardShortcut, backwardShortcut;
    QFile outfile;
    QString patientName;
    int sessionNumber;
};

#endif // MAINWINDOW_H
