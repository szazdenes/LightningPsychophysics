#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "imagehandlingform.h"

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

private:
    Ui::MainWindow *ui;
    int imageIndex;
    QStringList openFileNames;
};

#endif // MAINWINDOW_H
