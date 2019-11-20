#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainContainer = new QWidget;
    mainSplitter = new QSplitter;
    demoButton = new QPushButton("Demo scene");
    clearButton = new QPushButton("Clear scene");
    moveLightCheckBox = new QCheckBox("Move Light");
    buttonWidget = new QWidget;
    buttonLayout = new QVBoxLayout;
    buttonSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);;
    buttonLayout->addWidget(demoButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(moveLightCheckBox);
    createAddBox();
    buttonLayout->addLayout(addBoxGridLayout);
    createNURBSBox();
    buttonLayout->addLayout(nurbsBoxGridLayout);
    buttonLayout->addItem(buttonSpacer);
    buttonWidget->setLayout(buttonLayout);
    scene = new Scene();
    mainSplitter->addWidget(buttonWidget);
    mainSplitter->addWidget(scene);
    QList<int> sizes;
    sizes << 200 << 900;
    mainSplitter->setSizes(sizes);
    mainSplitter->setStretchFactor(0,0);
    mainSplitter->setStretchFactor(1,1);
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mainSplitter);
    mainContainer->setLayout(mainLayout);
    setWindowTitle("Suchiz Rendering Engine");
    setCentralWidget(mainContainer);
    scene->setFocus();
    modifyButton = new QPushButton("Modify");
    connect(moveLightCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_moveLightCheckBox_toggled(bool)));
    connect(demoButton, SIGNAL(clicked()), this, SLOT(on_demoButton_clicked()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
    connect(nurbsButton, SIGNAL(clicked()), this, SLOT(on_nurbsButton_clicked()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
    connect(editNurbsButton, SIGNAL(clicked()), this, SLOT(on_editButton_clicked()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(on_modifyButton_clicked()));
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
    scene->setFocus();
}
void MainWindow::on_nurbsButton_clicked()
{
    if (!nameNurbsEdit->text().isEmpty()){
        std::vector<glm::vec3> pt;
        TensorProduct tp = TensorProduct(nameNurbsEdit->text(),
                                         std::pair<int, int> {checkInt_3(heightNurbsEdit->text()),
                                                              checkInt_3(widthNurbsEdit->text())},
                                         pt);
        tp.setPosition(glm::vec3(checkFloat_0(xNurbs->text()),
                                 checkFloat_0(yNurbs->text()),
                                 checkFloat_0(zNurbs->text())));
        tp.setColor(glm::vec3(checkFloat_1(rNurbs->text()),
                              checkFloat_1(gNurbs->text()),
                              checkFloat_1(bNurbs->text())));
        surfaceCBox->addItem(nameNurbsEdit->text());
        scene->addSurface(tp);
        clearEditLines();
    } else
        QMessageBox::information(this, "Name is empty", "Insert at least a name");
    scene->setFocus();
}

void MainWindow::on_editButton_clicked()
{
    if (scene->getSurfaceToDraw().size()>0){
        TensorProduct tp = scene->getSurfaceToDraw()[surfaceCBox->currentIndex()];
        createEditSurfaceWindow(tp);
        editPopup->show();
    }
    scene->setFocus();
}

void MainWindow::on_modifyButton_clicked()
{
    TensorProduct tp = scene->getSurfaceToDraw()[surfaceCBox->currentIndex()];
    std::vector<glm::vec3> pts = tp.getControlPointsVect();
    glm::vec3 newPt = glm::vec3(checkFloat_0(xNewEdit->text()),
                                checkFloat_0(yNewEdit->text()),
                                checkFloat_0(zNewEdit->text()));
    pts[xSelect->currentIndex()*tp.getSize().first+ySelect->currentIndex()] = newPt;
    TensorProduct tp2 = TensorProduct(tp.getName(), tp.getSize(), pts);
    tp2.setColor(tp.getColor());
    tp2.setPosition(tp.getPosition());
    scene->addSurface(tp2);
    scene->delSurface(surfaceCBox->currentIndex());

    editPopup->close();
}

void MainWindow::on_addButton_clicked()
{
    if (objectComboBox->currentText().toStdString() == "CUBE"){
        Cube cube(checkFloat_1(sizeEdit->text()));
        cube.setPosition(glm::vec3(checkFloat_0(x->text()),
                                   checkFloat_0(y->text()),
                                   checkFloat_0(z->text())));
        cube.setColor(glm::vec3(checkFloat_1(r->text()),
                                checkFloat_1(g->text()),
                                checkFloat_1(b->text())));
        cube.setRotation(checkFloat_0(roll->text()), glm::vec3(1.0, 0, 0));
        cube.setRotation(checkFloat_0(pitch->text()), glm::vec3(0, 1.0, 0));
        cube.setRotation(checkFloat_0(yaw->text()), glm::vec3(0, 0, 1.0));
        scene->addCube(cube);
    } else if (objectComboBox->currentText().toStdString() == "PLANE"){
        Plane plane(checkFloat_1(sizeEdit->text()));
        plane.setPosition(glm::vec3(checkFloat_0(x->text()),
                                    checkFloat_0(y->text()),
                                    checkFloat_0(z->text())));
        plane.setColor(glm::vec3(checkFloat_1(r->text()),
                                 checkFloat_1(g->text()),
                                 checkFloat_1(b->text())));
        plane.setRotation(checkFloat_0(roll->text()), glm::vec3(1.0, 0, 0));
        plane.setRotation(checkFloat_0(pitch->text()), glm::vec3(0, 1.0, 0));
        plane.setRotation(checkFloat_0(yaw->text()), glm::vec3(0, 0, 1.0));
        scene->addPlane(plane);
    } else if (objectComboBox->currentText().toStdString() == "SPHERE"){
        Sphere sphere(checkFloat_1(sizeEdit->text()));
        sphere.setPosition(glm::vec3(checkFloat_0(x->text()),
                                     checkFloat_0(y->text()),
                                     checkFloat_0(z->text())));
        sphere.setColor(glm::vec3(checkFloat_1(r->text()),
                                  checkFloat_1(g->text()),
                                  checkFloat_1(b->text())));
        sphere.setRotation(checkFloat_0(roll->text()), glm::vec3(1.0, 0, 0));
        sphere.setRotation(checkFloat_0(pitch->text()), glm::vec3(0, 1.0, 0));
        sphere.setRotation(checkFloat_0(yaw->text()), glm::vec3(0, 0, 1.0));
        scene->addSphere(sphere);
    }
    clearEditLines();
    scene->setFocus();
}
void MainWindow::on_clearButton_clicked()
{
    scene->clearScene();
    scene->setFocus();
}

void MainWindow::createAddBox()
{
    addLabel = new QLabel("--- ADD AN OBJECT ---");
    rotationLabel = new QLabel("Rotation");
    colorLabel = new QLabel("Color");
    positionLabel = new QLabel("Position");
    sizeLabel = new QLabel("Size");

    sizeEdit = new QLineEdit;
    sizeEdit->setToolTip("Size");

    objectComboBox = new QComboBox;
    objectComboBox->addItem("CUBE");objectComboBox->addItem("SPHERE");objectComboBox->addItem("PLANE");
    addButton = new QPushButton("ADD");
    r = new QLineEdit;
    r->setToolTip("red value");
    g = new QLineEdit;
    g->setToolTip("green value");
    b = new QLineEdit;
    b->setToolTip("blue value");
    x = new QLineEdit;
    x->setToolTip("x value");
    y = new QLineEdit;
    y->setToolTip("y value");
    z = new QLineEdit;
    z->setToolTip("z value");
    roll = new QLineEdit;
    roll->setToolTip("rotation around x");
    pitch = new QLineEdit;
    pitch->setToolTip("rotation around y");
    yaw = new QLineEdit;
    yaw->setToolTip("rotation around z");

    addBoxGridLayout = new QGridLayout;
    addBoxGridLayout->addWidget(addLabel, 0, 0, 1, 3);
    addBoxGridLayout->addWidget(objectComboBox, 1, 0, 1, 2);
    addBoxGridLayout->addWidget(sizeEdit, 1, 2);
    addBoxGridLayout->addWidget(colorLabel, 2, 0);
    addBoxGridLayout->addWidget(r, 3, 0);addBoxGridLayout->addWidget(g, 3, 1);addBoxGridLayout->addWidget(b, 3, 2);
    addBoxGridLayout->addWidget(positionLabel, 4, 0);
    addBoxGridLayout->addWidget(x, 5, 0);addBoxGridLayout->addWidget(y, 5, 1);addBoxGridLayout->addWidget(z, 5, 2);
    addBoxGridLayout->addWidget(rotationLabel, 6, 0);
    addBoxGridLayout->addWidget(roll, 7, 0);addBoxGridLayout->addWidget(pitch, 7, 1);addBoxGridLayout->addWidget(yaw, 7, 2);
    addBoxGridLayout->addWidget(addButton, 8, 0, 1, 3);
}

float MainWindow::checkFloat_1(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[-+]?[0-9]*.?[0-9]+$"}))
        return ref.toFloat();
    else
        return 1;
}
float MainWindow::checkFloat_0(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[-+]?[0-9]*.?[0-9]+$"}))
        return ref.toFloat();
    else
        return 0;
}

int MainWindow::checkInt_3(QString ref)
{
    if (std::regex_match(ref.toStdString(), std::regex{"^[0-9]+$"}))
        if (ref.toInt() > 3)
            return ref.toInt();
    return 3;
}

void MainWindow::clearEditLines()
{
    sizeEdit->clear();
    r->clear();
    g->clear();
    b->clear();
    x->clear();
    y->clear();
    z->clear();
    roll->clear();
    pitch->clear();
    yaw->clear();

    rNurbs->clear();
    gNurbs->clear();
    bNurbs->clear();
    xNurbs->clear();
    yNurbs->clear();
    zNurbs->clear();
    widthNurbsEdit->clear();
    heightNurbsEdit->clear();
    nameNurbsEdit->clear();
}

void MainWindow::createEditSurfaceWindow(TensorProduct tp)
{
    std::pair<int, int> size = tp.getSize();
    xSelect = new QComboBox;
    ySelect = new QComboBox;

    for (int i(0); i < size.first; ++i)
        xSelect->addItem(QString::number(i));

    for (int i(0); i < size.second; ++i)
        ySelect->addItem(QString::number(i));

    weightLabel = new QLabel("Weight");
    weightEdit = new QLineEdit;
    newPositionLabel = new QLabel("New point position");
    pointLabel = new QLabel("Point");

    xNewEdit = new QLineEdit;
    yNewEdit = new QLineEdit;
    zNewEdit = new QLineEdit;

    moveManually = new QCheckBox("Move point");


    editPopup = new QWidget;
    editPopup->resize(300, 200);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(pointLabel, 0, 0);
    layout->addWidget(xSelect, 0, 1);
    layout->addWidget(ySelect, 0, 2);
    layout->addWidget(newPositionLabel, 1, 0);
    layout->addWidget(xNewEdit, 2, 0);layout->addWidget(yNewEdit, 2, 1);layout->addWidget(zNewEdit, 2, 2);
    //    layout->addWidget(weightLabel, 3, 0);
    //    layout->addWidget(weightEdit, 3, 1);
    layout->addWidget(modifyButton, 3, 1);

    editPopup->setLayout(layout);

}

void MainWindow::createNURBSBox()
{
    nurbsLabel = new QLabel("--- DRAW A SURFACE ---");
    sizeNurbsLabel = new QLabel("Size");
    nameNurbsLabel = new QLabel("Name");
    positionNurbsLabel = new QLabel("Position");
    colorNurbsLabel = new QLabel("Color");

    widthNurbsEdit = new QLineEdit;
    widthNurbsEdit->setToolTip("Width");

    heightNurbsEdit = new QLineEdit;
    heightNurbsEdit->setToolTip("Height");
    nameNurbsEdit = new QLineEdit;
    nameNurbsEdit->setToolTip("Name");
    xNurbs = new QLineEdit;
    xNurbs->setToolTip("x value");
    yNurbs = new QLineEdit;
    yNurbs->setToolTip("y value");
    zNurbs = new QLineEdit;
    zNurbs->setToolTip("z value");

    rNurbs = new QLineEdit;
    rNurbs->setToolTip("red value");
    gNurbs = new QLineEdit;
    gNurbs->setToolTip("green value");
    bNurbs = new QLineEdit;
    bNurbs->setToolTip("blue value");

    surfaceCBox = new QComboBox;

    editNurbsButton = new QPushButton("Edit");
    nurbsButton = new QPushButton("Draw surface");

    nurbsBoxGridLayout = new QGridLayout;
    nurbsBoxGridLayout->addWidget(nurbsLabel, 0, 0, 1, 3);
    nurbsBoxGridLayout->addWidget(nameNurbsLabel, 1, 0);
    nurbsBoxGridLayout->addWidget(nameNurbsEdit, 2, 0, 1, 3);
    nurbsBoxGridLayout->addWidget(sizeNurbsLabel, 3, 0);
    nurbsBoxGridLayout->addWidget(heightNurbsEdit, 4, 0);nurbsBoxGridLayout->addWidget(widthNurbsEdit, 4, 1);
    nurbsBoxGridLayout->addWidget(colorNurbsLabel, 5, 0);
    nurbsBoxGridLayout->addWidget(rNurbs, 6, 0);nurbsBoxGridLayout->addWidget(gNurbs, 6, 1);
    nurbsBoxGridLayout->addWidget(bNurbs, 6, 2);
    nurbsBoxGridLayout->addWidget(positionNurbsLabel, 7, 0);
    nurbsBoxGridLayout->addWidget(xNurbs, 8, 0);nurbsBoxGridLayout->addWidget(yNurbs, 8, 1);
    nurbsBoxGridLayout->addWidget(zNurbs, 8, 2);
    nurbsBoxGridLayout->addWidget(nurbsButton, 9, 0, 1, 3);
    nurbsBoxGridLayout->addWidget(surfaceCBox, 10, 0, 1, 2);
    nurbsBoxGridLayout->addWidget(editNurbsButton, 10, 2);
}
