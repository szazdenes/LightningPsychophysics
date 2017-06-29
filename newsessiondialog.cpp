#include "newsessiondialog.h"
#include "ui_newsessiondialog.h"

NewSessionDialog::NewSessionDialog(QWidget *parent, QString patientName, int sessionNumber) :
    QDialog(parent),
    ui(new Ui::NewSessionDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(patientName);
    ui->spinBox->setValue(sessionNumber);
}

NewSessionDialog::~NewSessionDialog()
{
    delete ui;
}

QString NewSessionDialog::getPatientName()
{
    return ui->lineEdit->text();
}

int NewSessionDialog::getSessionNumber()
{
    return ui->spinBox->value();
}
