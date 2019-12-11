#include "surfaceedit.h"
#include "ui_surfaceedit.h"
#include "../UI/mainwindow.h"

SurfaceEdit::SurfaceEdit(QWidget *parent, MainWindow *mw) : QDialog(parent),
    ui(new Ui::SurfaceEdit)
{
    this->mw = mw;
    ui->setupUi(this);
    QList<int> sizesButton;
    sizesButton << 200 << 200;
    ui->buttonSplitter->setSizes(sizesButton);
    QList<int> sizesEdit;
    sizesEdit << 400 << 600;
    ui->surfaceEditSplitter->setSizes(sizesEdit);
    ui->knotVectComboBox->addItem("UNIFORM");
    ui->knotVectComboBox->addItem("OPEN UNIFORM");
    scene = new EditSurfaceView();
    QHBoxLayout *tempLayout = new QHBoxLayout;
    tempLayout->addWidget(scene);
    ui->editSceneContainer->setLayout(tempLayout);
}

void SurfaceEdit::mousePressEvent(QMouseEvent *event)
{
    scene->setFocus();
}

void SurfaceEdit::closeEvent(QCloseEvent *event)
{
    if (!mw->checkWire(ind))
        obj->setWire(false);
}

SurfaceEdit::~SurfaceEdit()
{
    delete ui;
}

void SurfaceEdit::editSurface(int ind, TensorProduct *obj)
{
    this->obj = obj;
    this->ind = ind;
    glm::vec3 color = obj->getColor();
    glm::vec3 rotation = obj->getRotation();
    glm::vec3 size = obj->getSize();
    glm::vec3 position = obj->getPosition();

    ui->nameLineEdit->setText(obj->getName());
    ui->orderLineEdit->setText(QString::number(obj->getOrder()));

    ui->rLineEdit_2->setText(QString::number((int)(color.x*255)));
    ui->gLineEdit_2->setText(QString::number((int)(color.y*255)));
    ui->bLineEdit_2->setText(QString::number((int)(color.z*255)));

    ui->xLineEdit_2->setText(QString::number(position.x));
    ui->yLineEdit_2->setText(QString::number(position.y));
    ui->zLineEdit_2->setText(QString::number(position.z));

    ui->xSizeLineEdit->setText(QString::number(size.x));
    ui->ySizeLineEdit->setText(QString::number(size.y));
    ui->zSizeLineEdit->setText(QString::number(size.z));

    ui->rollLineEdit_2->setText(QString::number(rotation.x));
    ui->pitchLineEdit_2->setText(QString::number(rotation.y));
    ui->yawLineEdit_2->setText(QString::number(rotation.z));
    std::vector<glm::vec3> controlPointsPos = obj->getControlPointsVect();
    for (unsigned int i = 0; i < controlPointsPos.size(); ++i){
        Cube *c = new Cube("Point" + QString::number(i));
        c->setSize(glm::vec3(0.1f));
        c->setPosition(controlPointsPos[i]);
        c->setColor(glm::vec3(1.0f, 0.f, 0.f));
        scene->addObject(c);
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(c->getName());
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(item);
    }
    obj->setWire(true);
    scene->addObject(obj);
    scene->setCurrentTp(obj);
}


void SurfaceEdit::on_okButton_pressed()
{
    glm::vec3 position = checkPostion(ui->xLineEdit_2->text(),
                                      ui->yLineEdit_2->text(),
                                      ui->zLineEdit_2->text());
    glm::vec3 color = checkColor(ui->rLineEdit_2->text(),
                                 ui->gLineEdit_2->text(),
                                 ui->bLineEdit_2->text());
    glm::vec3 rotation = checkRotation(ui->rollLineEdit_2->text(),
                                       ui->pitchLineEdit_2->text(),
                                       ui->yawLineEdit_2->text());
    glm::vec3 size = checkSize(ui->xSizeLineEdit->text(),
                               ui->ySizeLineEdit->text(),
                               ui->zSizeLineEdit->text());;
    QString name = ui->nameLineEdit->text();
    int order = checkOrder(ui->orderLineEdit->text());
    KVType kvtype;
    if (ui->knotVectComboBox->currentText() == "UNIFORM")
        kvtype = KVType::UNIFORM;
    else
        kvtype = KVType::OPEN_UNIFORM;
    std::pair<int, int> sizeTp = obj->getHW();
    if (order <= std::min(sizeTp.first, sizeTp.second))
        obj->setOrder(order);

    obj->setKVType(kvtype);
    obj->setName(name);
    obj->setSize(size);

    obj->setPosition(position);
    obj->setColor(color);
    obj->setRotation(rotation);
    mw->updateObjectName(ind, name);
    ui->listWidget->clear();

    close();
}

void SurfaceEdit::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->listWidget->row(item);
    if (item->checkState() == Qt::Checked){
        scene->getObjectsToDraw()[row]->setColor(glm::vec3(0,1,0));
        scene->addCubeSelected(scene->getObjectsToDraw()[row], row);
    }
    else {
        scene->getObjectsToDraw()[row]->setColor(glm::vec3(1,0,0));
        scene->deleteCubeSelected(scene->getObjectsToDraw()[row], row);
    }
    scene->setCubeSelected(scene->getVectorCubeSelected().size()>0);
}
