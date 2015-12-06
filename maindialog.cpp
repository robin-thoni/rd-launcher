#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include "maindialog.h"
#include "ui_maindialog.h"
#include "rdesktoplauncher.h"
#include "rdpoptionshelper.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    connect(ui->lineComputer->lineEdit(), SIGNAL(returnPressed()), ui->btnConnect, SLOT(animateClick()));
    connect(ui->lineComputer->lineEdit(), SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    computeResolutions();
    QStringList layouts;
    for (int l = QLocale::Abkhazian; l <= QLocale::Shambala; ++l)
    {
        QString name = QLocale((QLocale::Language)l).name().replace("_", "-").toLower();
        if (!layouts.contains(name))
            layouts.append(name);
    }
    layouts.sort();
    ui->comboKeyboard->addItems(layouts);
    ui->comboKeyboard->lineEdit()->setText("en-us");

    loadAll();
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
    opt.setFullscreen(ui->slidResolution->value() == m_resolutions.size());
    if (!opt.fullscreen())
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
    opt.setMetaKeys(meta == 0 || (opt.fullscreen() && meta == 2));
    opt.setUseShell(ui->checkShell->isChecked());
    if (opt.useShell())
    {
        opt.setShell(ui->lineShellPath->text());
        opt.setShellWorkingDir(ui->lineShellWorkingDir->text());
    }
    opt.setExperience((RdpOptions::Experience)ui->comboExperience->currentIndex());
    opt.setBitmapCache(ui->checkCacheBitmap->isChecked());
    opt.setAutoReconnect(ui->checkAutoReconnect->isChecked());
    opt.setKeymap(ui->comboKeyboard->currentText());
    return opt;
}

void MainDialog::setRdpOptions(const RdpOptions &opt)
{
    ui->lineComputer->lineEdit()->setText(opt.host());
    ui->lineUsername->setText(opt.username());
    ui->linePassword->setText(opt.password());
    if (opt.fullscreen())
    {
        ui->slidResolution->setValue(ui->slidResolution->maximum());
    }
    else
    {
        ui->slidResolution->setValue(ui->slidResolution->maximum() - 1);
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
    ui->comboKeyboard->lineEdit()->setText(opt.keymap());
}

void MainDialog::loadAll()
{
    m_rdpOptions = RdpOptionsHelper::loadAll();
    ui->lineComputer->clear();
    ui->lineComputer->addItem("");
    for (int i = 1; i < m_rdpOptions.size(); ++i)
    {
        RdpOptions opt = m_rdpOptions.at(i);
        ui->lineComputer->addItem(opt.host());
    }

    ui->lineComputer->setFocus();
}

void MainDialog::on_btnConnect_clicked()
{
    RdpOptions opt = getRdpOptions();
    RdpOptionsHelper::save(opt);
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
    RdpOptionsHelper::save(getRdpOptions());
    loadAll();
}

void MainDialog::on_btnSaveAsSession_clicked()
{
    on_btnSaveSession_clicked();
}

void MainDialog::on_btnOpenSession_clicked()
{

}

void MainDialog::on_lineComputer_currentIndexChanged(int index)
{
    if (index >= 0 && index < m_rdpOptions.size())
    {
        setRdpOptions(m_rdpOptions.at(index));
    }
}

void MainDialog::on_btnRemoveSession_clicked()
{
    RdpOptionsHelper::remove(getRdpOptions());
    loadAll();
}
