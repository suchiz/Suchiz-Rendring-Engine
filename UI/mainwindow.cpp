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
    ui->animationSplitter->setSizes(sizeButtonSplitter);
    ui->tabWidget->setCurrentIndex(0);
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
    updateObjectList();
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
    ui->addKeyFrameButton->setEnabled(false);
    ui->objectListView->clear();
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

void MainWindow::updateObjectList()
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

bool MainWindow::checkWire(int ind)
{
    if (ui->objectListView->item(ind)->checkState() == Qt::Checked && scene->getObjectsToDraw()[ind]->getWire())
        return true;
    return false;
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

void MainWindow::on_animationDemoButton_pressed()
{
    ui->addKeyFrameButton->setEnabled(true);
    if (ui->boneComboBox->count() == 0)
        for (Bone* b : scene->getAnimatedModel()->getSkeleton())
            ui->boneComboBox->addItem(b->getName());

    scene->clearScene();
    scene->createAnimationDemo();
    updateObjectList();
    scene->setFocus();
}

void MainWindow::on_clearKeyFramesButton_pressed()
{
    ui->keyFramesList->clear();
    scene->getAnimation()->clearKeyFrames();
}

void MainWindow::on_addKeyFrameButton_pressed()
{
    float lastTime = 0;
    if (ui->keyFramesList->count() != 0)
        lastTime = scene->getAnimation()->getLasTime();
    QString time = ui->timeLineEdit->text();
    if(std::regex_match(time.toStdString(), std::regex{"^[0-9]*.?[0-9]+$"})){
        if (time.toFloat() > 0 && ui->keyFramesList->count() == 0){
            scene->addKeyFrame(-1);
            ui->keyFramesList->addItem("(0s)");
            scene->addKeyFrame(time.toFloat());
            ui->keyFramesList->addItem("("+time+ "s)");
        } else if (time.toFloat() > lastTime || ui->keyFramesList->count() == 0){
            scene->addKeyFrame(time.toFloat());
            ui->keyFramesList->addItem("("+time+ "s)");
        }
    }
}

void MainWindow::on_deleteKeyFrameButton_pressed()
{
    if (ui->keyFramesList->currentRow() != -1){
        scene->stopAnimation();
        ui->keyFramesList->model()->removeRow(ui->keyFramesList->currentRow());
        scene->getAnimation()->deleteKeyFrame(ui->keyFramesList->currentRow());
    }
    scene->setFocus();
}


void MainWindow::on_playButton_pressed()
{
    scene->playAnimation();
}

void MainWindow::on_stopButton_pressed()
{
    scene->stopAnimation();
}

void MainWindow::on_rotateCheckBox_toggled(bool checked)
{
    scene->setRotateBone(checked);
    scene->setFocus();
}

void MainWindow::on_translateCheckBox_toggled(bool checked)
{
    scene->setTranslateBone(checked);
    scene->setFocus();
}

void MainWindow::on_boneComboBox_currentIndexChanged(int index)
{
    scene->setSelectedBone(index);
    scene->setFocus();
}
