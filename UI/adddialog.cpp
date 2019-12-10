#include "adddialog.h"
#include "ui_adddialog.h"
#include "../Scene/mainwindow.h"

AddDialog::AddDialog(QWidget *parent, MainWindow *mw) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    this->mw = mw;
    ui->setupUi(this);
    ui->objectsComboBox->addItem("CUBE");
    ui->objectsComboBox->addItem("SPHERE");
    ui->objectsComboBox->addItem("PLANE");
    ui->objectsComboBox->addItem("CAPSULE");
    ui->knotVectComboBox->addItem("UNIFORM");
    ui->knotVectComboBox->addItem("OPEN UNIFORM");
}

AddDialog::~AddDialog()
{
    delete ui;
}


void AddDialog::on_cancelButton_clicked()
{
    close();
}

void AddDialog::on_okButton_clicked()
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
    if (ui->objectsComboBox->currentText().toStdString() == "CUBE"){
        if (name == "")
            name = "Cube";
        Cube *cube = new Cube(name);
        cube->setSize(size);
        cube->setPosition(position);
        cube->setColor(color);
        cube->setRotation(rotation);
        mw->addSceneObject(cube);
    } else if (ui->objectsComboBox->currentText().toStdString() == "PLANE"){
        if (name == "")
            name = "Plane";
        Plane *plane = new Plane(name);
        plane->setSize(size);
        plane->setPosition(position);
        plane->setColor(color);
        plane->setRotation(rotation);
        mw->addSceneObject(plane);
    } else if (ui->objectsComboBox->currentText().toStdString() == "SPHERE"){
        if (name == "")
            name = "Sphere";
        Sphere *sphere = new Sphere(name);
        sphere->setSize(size);
        sphere->setPosition(position);
        sphere->setColor(color);
        sphere->setRotation(rotation);
        mw->addSceneObject(sphere);
    }
    clearFields();
    close();
}

void AddDialog::clearFields()
{
    ui->nameLineEdit->clear();
    ui->rLineEdit->clear();
    ui->gLineEdit->clear();
    ui->bLineEdit->clear();
    ui->xLineEdit->clear();
    ui->yLineEdit->clear();
    ui->zLineEdit->clear();
    ui->xSizeLineEdit->clear();
    ui->ySizeLineEdit->clear();
    ui->zSizeLineEdit->clear();
    ui->rollLineEdit->clear();
    ui->pitchLineEdit->clear();
    ui->yawLineEdit->clear();
}
