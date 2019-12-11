#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<int> sizeSceneSplitter;
    sizeSceneSplitter << 200 << 1080;
    ui->sceneSplitter->setSizes(sizeSceneSplitter);
    QList<int> sizeButtonSplitter;
    sizeButtonSplitter << 150 << 570;
    ui->buttonSplitter->setSizes(sizeButtonSplitter);
    scene = new Scene();
    QHBoxLayout *tempLayout = new QHBoxLayout;
    tempLayout->addWidget(scene);
    ui->sceneContainer->setLayout(tempLayout);
    scene->setFocus();
    oed = new ObjectEdit(this, this);
    sed = new SurfaceEdit(this, this);
    ad = new AddDialog(this, this);
}

void MainWindow::addSceneObject(DrawableObject *object)
{
    scene->addObject(object);
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(object->getName());
    item->setCheckState(Qt::Unchecked);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->objectListView->addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_moveLightCheckBox_toggled(bool checked)
{
    scene->setMoveLight(checked);
    scene->setFocus();
}

void MainWindow::on_demoButton_clicked()
{
    scene->clearScene();
    scene->createDemo();
    clearObjectList();
    scene->setFocus();
}

void MainWindow::on_editButton_clicked()
{

    if (scene->getObjectsToDraw().size() > 0 && ui->objectListView->currentRow() != -1){
        DrawableObject *obj = scene->getObjectsToDraw()[ui->objectListView->currentRow()];
        if (obj->getType() == SURFACE){
            sed->editSurface(ui->objectListView->currentRow(), (TensorProduct*) obj);
            sed->show();
        } else {
            oed->editObject(ui->objectListView->currentRow(), obj);
            oed->show();
        }
    }
    scene->setFocus();
}

void MainWindow::on_addButton_clicked()
{
    ad->show();
    scene->setFocus();
}
void MainWindow::on_clearButton_clicked()
{
    scene->clearScene();
    scene->setFocus();
}

void MainWindow::on_deleteButton_clicked()
{
    if (scene->getObjectsToDraw().size() > 0 && ui->objectListView->currentRow() != -1){
        scene->deleteObject(ui->objectListView->currentRow());
        deleteObjectFromList(ui->objectListView->currentRow());
    }
    scene->setFocus();
}

void MainWindow::deleteObjectFromList(int ind)
{
    ui->objectListView->model()->removeRow(ind);
}

void MainWindow::clearObjectList()
{
    ui->objectListView->clear();
    for (unsigned int i(0); i < scene->getObjectsToDraw().size(); ++i){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(scene->getObjectsToDraw()[i]->getName());
        item->setCheckState(Qt::Unchecked);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->objectListView->addItem(item);
    }
}

void MainWindow::updateObjectName(int ind, QString name)
{
    ui->objectListView->item(ind)->setText(name);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    scene->setFocus();
}

void MainWindow::on_objectListView_itemClicked(QListWidgetItem *item)
{
    if (scene->getObjectsToDraw().size() > 0){
        if (item->checkState() == Qt::Checked)
            scene->getObjectsToDraw()[ui->objectListView->row(item)]->setWire(true);
        else
            scene->getObjectsToDraw()[ui->objectListView->row(item)]->setWire(false);
    }
}

void MainWindow::on_objectListView_itemChanged(QListWidgetItem *item)
{
    if (scene->getObjectsToDraw().size() > 0)
        scene->getObjectsToDraw()[ui->objectListView->row(item)]->setName(item->text());
}
