#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"
#include "rdpoptions.h"
#include "rdesktoplauncher.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    connect(ui->lineComputer->lineEdit(), SIGNAL(returnPressed()), ui->btnConnect, SLOT(animateClick()));
    connect(ui->lineComputer->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    computeResolutions();
    ui->lineComputer->setFocus();
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_btnConnect_clicked()
{
    RdpOptions opt;
    opt.setBitmapCache(ui->checkCacheBitmap->isChecked());
    opt.setExperience((RdpOptions::Experience)ui->comboExperience->currentIndex());
    opt.setFullescreen(ui->slidResolution->value() == m_resolutions.size());
    opt.setHost(ui->lineComputer->currentText());
    int meta = ui->comboMetaKeys->currentIndex();
    opt.setMetaKeys(meta == 0 || (opt.fullescreen() && meta == 2));
    opt.setPassword(ui->linePassword->text());
    opt.setResolution(m_resolutions.at(m_resolutions.size() - 1));
    opt.setUsername(ui->lineUsername->text());
    opt.setUseShell(ui->checkShell->isChecked());
    if (opt.useShell())
    {
        opt.setShell(ui->lineShellPath->text());
        opt.setShellWorkingDir(ui->lineShellWorkingDir->text());
    }
    int colors = ui->comboColors->currentIndex();
    RdpOptions::Colors c;
    if (colors == 0)
        c = RdpOptions::HighColor_15;
    else if (colors == 1)
        c = RdpOptions::HighColor_16;
    else if (colors == 2)
        c = RdpOptions::TrueColor;
    else if (colors == 3)
        c = RdpOptions::HighestQuality;
    opt.setColors(c);
    RDesktopLauncher launcher;
    launcher.start(opt);
}

void MainDialog::textChanged(QString)
{
    ui->btnConnect->setEnabled(!ui->lineComputer->lineEdit()->text().isEmpty());
}

void MainDialog::computeResolutions()
{
    m_resolutions.append(QApplication::desktop()->availableGeometry().size());
    ui->slidResolution->setMinimum(0);
    ui->slidResolution->setMaximum(m_resolutions.size());
    ui->slidResolution->setValue(m_resolutions.size());
}

void MainDialog::on_slidResolution_valueChanged(int value)
{
    if (value < m_resolutions.size())
    {
        QSize reso = m_resolutions.at(value);
        ui->lblResolution->setText(QString("%1x%2").arg(reso.width()).arg(reso.height()));
    }
    else
    {
        ui->lblResolution->setText(tr("Plein écran"));
    }
}
