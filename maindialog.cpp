#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    connect(ui->lineComputer->lineEdit(), SIGNAL(returnPressed()), ui->btnConnect, SLOT(animateClick()));
}

MainDialog::~MainDialog()
{
    delete ui;
}
