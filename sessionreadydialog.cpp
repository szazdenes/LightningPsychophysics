#include "sessionreadydialog.h"
#include "ui_sessionreadydialog.h"

SessionReadyDialog::SessionReadyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionReadyDialog)
{
    ui->setupUi(this);
}

SessionReadyDialog::~SessionReadyDialog()
{
    delete ui;
}

void SessionReadyDialog::on_buttonBox_accepted()
{
    emit signalSessionReady();
}
