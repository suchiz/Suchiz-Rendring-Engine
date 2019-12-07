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
    glm::vec3 position = glm::vec3(checkFloat_0(ui->xLineEdit->text()),
                                   checkFloat_0(ui->yLineEdit->text()),
                                   checkFloat_0(ui->zLineEdit->text()));
    glm::vec3 color = glm::vec3(glm::vec3(checkFloat_1(ui->rLineEdit->text()),
                                          checkFloat_1(ui->gLineEdit->text()),
                                          checkFloat_1(ui->bLineEdit->text())));
    glm::vec3 rotation = glm::vec3(checkFloat_0(ui->rollLineEdit->text()),
                                   checkFloat_0(ui->pitchLineEdit->text()),
                                   checkFloat_0(ui->yawLineEdit->text()));
    glm::vec3 size = glm::vec3(checkFloat_1(ui->xSizeLineEdit->text()),
                               checkFloat_1(ui->ySizeLineEdit->text()),
                               checkFloat_1(ui->zSizeLineEdit->text()));
    QString name = ui->nameLineEdit->text();
    if (ui->objectsComboBox->currentText().toStdString() == "CUBE"){
        Cube *cube = new Cube(name);
        cube->setSize(size);
        cube->setPosition(position);
        cube->setColor(color);
        cube->setRotation(rotation);
        mw->addSceneObject(cube);
    } else if (ui->objectsComboBox->currentText().toStdString() == "PLANE"){
        Plane *plane = new Plane(name);
        plane->setSize(size);
        plane->setPosition(position);
        plane->setColor(color);
        plane->setRotation(rotation);
        mw->addSceneObject(plane);
    } else if (ui->objectsComboBox->currentText().toStdString() == "SPHERE"){
        Sphere *sphere = new Sphere(name);
        sphere->setSize(size);
        sphere->setPosition(position);
        sphere->setColor(color);
        sphere->setRotation(rotation);
        mw->addSceneObject(sphere);
    }
    close();
}

float AddDialog::checkFloat_1(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[-+]?[0-9]*.?[0-9]+$"}))
        return ref.toFloat();
    else
        return 1;
}
float AddDialog::checkFloat_0(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[-+]?[0-9]*.?[0-9]+$"}))
        return ref.toFloat();
    else
        return 0;
}

int AddDialog::checkInt_3(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[0-9]+$"}))
        if (ref.toInt() > 3)
            return ref.toInt();
    return 3;
}
