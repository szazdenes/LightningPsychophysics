#ifndef SESSIONREADYDIALOG_H
#define SESSIONREADYDIALOG_H

#include <QDialog>

namespace Ui {
class SessionReadyDialog;
}

class SessionReadyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionReadyDialog(QWidget *parent = 0);
    ~SessionReadyDialog();

signals:
    void signalSessionReady();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SessionReadyDialog *ui;
};

#endif // SESSIONREADYDIALOG_H
