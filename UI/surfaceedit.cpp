#include "surfaceedit.h"
#include "ui_surfaceedit.h"

SurfaceEdit::SurfaceEdit(QWidget *parent, MainWindow *mw) : AddDialog(parent, mw),
    ui(new Ui::SurfaceEdit)
{
    ui->setupUi(this);
}

SurfaceEdit::~SurfaceEdit()
{
    delete ui;
}

void SurfaceEdit::initFields(DrawableObject *obj)
{

}
