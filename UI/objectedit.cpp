#include "objectedit.h"
#include "ui_objectedit.h"
#include "../UI/mainwindow.h"

ObjectEdit::ObjectEdit(QWidget *parent, MainWindow *mw) : QDialog(parent),
    ui(new Ui::ObjectEdit)
{
    this->mw = mw;
    ui->setupUi(this);
}

ObjectEdit::~ObjectEdit()
{
    delete ui;
}

void ObjectEdit::editObject(int ind, DrawableObject *obj)
{
    this->obj = obj;
    this->ind = ind;
    glm::vec3 color = obj->getColor();
    glm::vec3 rotation = obj->getRotation();
    glm::vec3 size = obj->getSize();
    glm::vec3 position = obj->getPosition();

    ui->nameLineEdit->setText(obj->getName());

    ui->rLineEdit->setText(QString::number((int)(color.x*255)));
    ui->gLineEdit->setText(QString::number((int)(color.y*255)));
    ui->bLineEdit->setText(QString::number((int)(color.z*255)));

    ui->xLineEdit->setText(QString::number(position.x));
    ui->yLineEdit->setText(QString::number(position.y));
    ui->zLineEdit->setText(QString::number(position.z));

    ui->xSizeLineEdit->setText(QString::number(size.x));
    ui->ySizeLineEdit->setText(QString::number(size.y));
    ui->zSizeLineEdit->setText(QString::number(size.z));

    ui->rollLineEdit->setText(QString::number(rotation.x));
    ui->pitchLineEdit->setText(QString::number(rotation.y));
    ui->yawLineEdit->setText(QString::number(rotation.z));
}



void ObjectEdit::on_okButton_pressed()
{
    glm::vec3 position = checkPostion(ui->xLineEdit->text(),
                                      ui->yLineEdit->text(),
                                      ui->zLineEdit->text());
    glm::vec3 color = checkColor(ui->rLineEdit->text(),
                                 ui->gLineEdit->text(),
                                 ui->bLineEdit->text());
    glm::vec3 rotation = checkRotation(ui->rollLineEdit->text(),
                                       ui->pitchLineEdit->text(),
                                       ui->yawLineEdit->text());
    glm::vec3 size = checkSize(ui->xSizeLineEdit->text(),
                               ui->ySizeLineEdit->text(),
                               ui->zSizeLineEdit->text());;
    QString name = ui->nameLineEdit->text();
    obj->setName(name);
    obj->setSize(size);
    obj->setPosition(position);
    obj->setColor(color);
    obj->setRotation(rotation);
    mw->updateObjectName(ind, name);
    close();
}
