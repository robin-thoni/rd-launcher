#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"
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

RdpOptions MainDialog::getRdpOptions() const
{
    RdpOptions opt;
    opt.setHost(ui->lineComputer->currentText());
    opt.setUsername(ui->lineUsername->text());
    opt.setPassword(ui->linePassword->text());
    opt.setFullescreen(ui->slidResolution->value() == m_resolutions.size());
    if (!opt.fullescreen())
        opt.setResolution(m_resolutions.at(m_resolutions.size() - 1));
    opt.setUseAllMonitors(ui->checkAllDisplays->isChecked());

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

    opt.setFullscreenBar(ui->checkFullscreenBar->isChecked());
    int meta = ui->comboMetaKeys->currentIndex();
    opt.setMetaKeys(meta == 0 || (opt.fullescreen() && meta == 2));
    opt.setUseShell(ui->checkShell->isChecked());
    if (opt.useShell())
    {
        opt.setShell(ui->lineShellPath->text());
        opt.setShellWorkingDir(ui->lineShellWorkingDir->text());
    }
    opt.setExperience((RdpOptions::Experience)ui->comboExperience->currentIndex());
    opt.setBitmapCache(ui->checkCacheBitmap->isChecked());
    opt.setAutoReconnect(ui->checkAutoReconnect->isChecked());
    return opt;
}

void MainDialog::setRdpOptions(const RdpOptions &opt)
{
    ui->lineComputer->lineEdit()->setText(opt.host());
    ui->lineUsername->setText(opt.username());
    ui->linePassword->setText(opt.password());
    if (opt.fullescreen())
    {
        ui->slidResolution->setValue(ui->slidResolution->maximum());
    }
    else
    {

    }
    ui->checkAllDisplays->setChecked(opt.useAllMonitors());

    int index = 0;
    RdpOptions::Colors c = opt.colors();
    if (c == RdpOptions::HighColor_15)
        index = 0;
    else if (c == RdpOptions::HighColor_16)
        index = 1;
    else if (c == RdpOptions::TrueColor)
        index = 2;
    else if (c == RdpOptions::HighestQuality)
        index = 3;
    ui->comboColors->setCurrentIndex(index);

    ui->checkFullscreenBar->setChecked(opt.fullscreenBar());
    ui->comboMetaKeys->setCurrentIndex(opt.metaKeys() ? 2 : 1);
    ui->checkShell->setChecked(opt.useShell());
    ui->lineShellPath->setText(opt.shell());
    ui->lineShellWorkingDir->setText(opt.shellWorkingDir());
    ui->comboExperience->setCurrentIndex((int)opt.experience());
    ui->checkCacheBitmap->setChecked(opt.bitmapCache());
    ui->checkAutoReconnect->setChecked(opt.autoReconnect());
}

void MainDialog::on_btnConnect_clicked()
{
    RdpOptions opt = getRdpOptions();

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

void MainDialog::on_btnSaveSession_clicked()
{

}

void MainDialog::on_btnSaveAsSession_clicked()
{

}

void MainDialog::on_btnOpenSession_clicked()
{

}
