#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <ui_objectedit.h>
#include "../Objects/drawableobject.h"
#include "checkui.h"

class MainWindow;
namespace Ui {
class ObjectEdit;
}


class ObjectEdit: public QDialog, public CheckUI
{
    Q_OBJECT

public:
    explicit ObjectEdit(QWidget *parent = 0, MainWindow *mw = 0);
    ~ObjectEdit();

    void editObject(int ind, DrawableObject *obj);

private slots:
    void on_okButton_pressed();

private:
    Ui::ObjectEdit *ui;
    DrawableObject *obj;
    MainWindow *mw;
    int ind;
};

#endif // EDITDIALOG_H
