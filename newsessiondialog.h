#ifndef NEWSESSIONDIALOG_H
#define NEWSESSIONDIALOG_H

#include <QDialog>

namespace Ui {
class NewSessionDialog;
}

class NewSessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSessionDialog(QWidget *parent = 0, QString patientName = "", int sessionNumber = 1);
    ~NewSessionDialog();

    QString getPatientName();
    int getSessionNumber();

private:
    Ui::NewSessionDialog *ui;
};

#endif // NEWSESSIONDIALOG_H
