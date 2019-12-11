#ifndef SURFACEEDIT_H
#define SURFACEEDIT_H

#include <QDialog>
#include "checkui.h"
#include "../Surfaces/tensorproduct.h"
#include "../Surfaces/editsurfaceview.h"

class MainWindow;
namespace Ui {
class SurfaceEdit;
}

class SurfaceEdit : public QDialog, public CheckUI
{
    Q_OBJECT

public:
    explicit SurfaceEdit(QWidget *parent = 0, MainWindow *mw = 0);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);
    ~SurfaceEdit();

    void editSurface(int ind, TensorProduct *obj);

private slots:
    void on_okButton_pressed();
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::SurfaceEdit *ui;
    MainWindow *mw;
    TensorProduct *obj;
    int ind;
    EditSurfaceView *scene;
};

#endif // SURFACEEDIT_H
