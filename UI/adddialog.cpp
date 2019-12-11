#include "adddialog.h"
#include "ui_adddialog.h"
#include "../UI/mainwindow.h"

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

void AddDialog::on_okButton_clicked()
{
    if (ui->tabWidget->currentIndex() == 0){
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
    } else if (ui->tabWidget->currentIndex() == 1){
        QString name = ui->nameSurfLineEdit->text();
        if (name == "")
            name = "Surface";

        glm::vec3 position = checkPostion(ui->xLineEdit_2->text(),
                                          ui->yLineEdit_2->text(),
                                          ui->zLineEdit_2->text());
        glm::vec3 color = checkColor(ui->rLineEdit_2->text(),
                                     ui->gLineEdit_2->text(),
                                     ui->bLineEdit_2->text());
        glm::vec3 rotation = checkRotation(ui->rollLineEdit_2->text(),
                                           ui->pitchLineEdit_2->text(),
                                           ui->yawLineEdit_2->text());
        int order = checkOrder(ui->orderLineEdit->text());
        int w = checkWidth(ui->widthLineEdit->text());
        int h = checkHeight(ui->heightLineEdit->text());
        if (order <= std::min(w,h)) {
            KVType kvtype;
            if (ui->knotVectComboBox->currentText() == "UNIFORM")
                kvtype = KVType::UNIFORM;
            else
                kvtype = KVType::OPEN_UNIFORM;
            TensorProduct *tp = new TensorProduct(name, std::pair<int, int> {w, h}, kvtype, order);
            tp->setPosition(position);
            tp->setColor(color);
            tp->setRotation(rotation);
            mw->addSceneObject(tp);
        }
    }
    clearFields();
    close();
}

void AddDialog::clearFields()
{
    ui->nameLineEdit->clear();
    ui->nameSurfLineEdit->clear();
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
    ui->rLineEdit_2->clear();
    ui->gLineEdit_2->clear();
    ui->bLineEdit_2->clear();
    ui->xLineEdit_2->clear();
    ui->yLineEdit_2->clear();
    ui->zLineEdit_2->clear();
    ui->widthLineEdit->clear();
    ui->heightLineEdit->clear();
    ui->orderLineEdit->clear();
}
