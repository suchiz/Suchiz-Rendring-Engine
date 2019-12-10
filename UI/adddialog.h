#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "../Objects/drawableobject.h"
#include <regex>
#include "checkui.h"

class MainWindow;
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog, public CheckUI
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
    void clearFields();
};

#endif // ADDDIALOG_H
