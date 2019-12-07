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
}

void MainWindow::addSceneObject(DrawableObject *object)
{
    scene->addObject(object);
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(object->getName());
    item->setCheckState(Qt::Unchecked);
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
//void MainWindow::on_nurbsButton_clicked()
//{
//    if (!nameNurbsEdit->text().isEmpty()){
//        std::vector<glm::vec3> pt;
//        TensorProduct *tp = new TensorProduct(nameNurbsEdit->text(),
//                                         std::pair<int, int> {checkInt_3(heightNurbsEdit->text()),
//                                                              checkInt_3(widthNurbsEdit->text())},
//                                         pt);
//        tp->setPosition(glm::vec3(checkFloat_0(xNurbs->text()),
//                                 checkFloat_0(yNurbs->text()),
//                                 checkFloat_0(zNurbs->text())));
//        tp->setColor(glm::vec3(checkFloat_1(rNurbs->text()),
//                              checkFloat_1(gNurbs->text()),
//                              checkFloat_1(bNurbs->text())));
//        surfaceCBox->addItem(nameNurbsEdit->text());
//        scene->addObject(tp);
//        clearEditLines();
//    } else
//        QMessageBox::information(this, "Name is empty", "Insert at least a name");
//    scene->setFocus();
//}

void MainWindow::on_editButton_clicked()
{
//    if (scene->getSurfaceToDraw().size()>0){
//        TensorProduct tp = scene->getSurfaceToDraw()[surfaceCBox->currentIndex()];
//        createEditSurfaceWindow(tp);
//        editPopup->show();
//    }
    scene->setFocus();
}

void MainWindow::on_addButton_clicked()
{
    if (ad == NULL)
        ad = new AddDialog(this, this);
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
    if (scene->getObjectsToDraw().size() > 0){
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
        ui->objectListView->addItem(item);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    scene->setFocus();
}

void MainWindow::on_objectListView_itemClicked(QListWidgetItem *item)
{
    if (scene->getObjectsToDraw().size() > 0)
        if (item->checkState() == Qt::Checked)
            scene->getObjectsToDraw()[ui->objectListView->row(item)]->setWire(true);
        else
            scene->getObjectsToDraw()[ui->objectListView->row(item)]->setWire(false);
}
