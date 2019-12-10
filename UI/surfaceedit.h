#ifndef SURFACEEDIT_H
#define SURFACEEDIT_H

#include <QDialog>
#include "adddialog.h"

namespace Ui {
class SurfaceEdit;
}

class SurfaceEdit : public AddDialog
{
    Q_OBJECT

public:
    explicit SurfaceEdit(QWidget *parent = 0, MainWindow *mw = 0);
    ~SurfaceEdit();

    void initFields(DrawableObject *obj);

private:
    Ui::SurfaceEdit *ui;
};

#endif // SURFACEEDIT_H
