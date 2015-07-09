#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void on_btnConnect_clicked();

    void textChanged(QString);

    void computeResolutions();

    void on_slidResolution_valueChanged(int value);

private:
    Ui::MainDialog *ui;

    QList<QSize> m_resolutions;
};

#endif // MAINDIALOG_H
