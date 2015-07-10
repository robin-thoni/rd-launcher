#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "rdpoptions.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

    RdpOptions getRdpOptions() const;

public slots:
    void setRdpOptions(const RdpOptions& opt);

private slots:
    void on_btnConnect_clicked();

    void textChanged(QString);

    void computeResolutions();

    void on_slidResolution_valueChanged(int value);

    void on_btnSaveSession_clicked();

    void on_btnSaveAsSession_clicked();

    void on_btnOpenSession_clicked();

private:
    Ui::MainDialog *ui;

    QList<QSize> m_resolutions;
};

#endif // MAINDIALOG_H
