#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "../Objects/drawableobject.h"
#include <regex>

class MainWindow;
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0, MainWindow *mw = 0);
    ~AddDialog();

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::AddDialog *ui;
    MainWindow *mw;

    //METHODS
    float checkFloat_1(QString ref);
    float checkFloat_0(QString ref);
    int checkInt_3(QString ref);
};

#endif // ADDDIALOG_H
