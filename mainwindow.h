#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include <regex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_moveLightCheckBox_toggled(bool checked);
    void on_demoButton_clicked();
    void on_clearButton_clicked();
    void on_addButton_clicked();
    void on_nurbsButton_clicked();
    void on_editButton_clicked();
    void on_modifyButton_clicked();

private:
    void createAddBox();
    float checkFloat_1(QString ref);
    float checkFloat_0(QString ref);
    int checkInt_3(QString ref);
    void clearEditLines();
    void createEditSurfaceWindow(TensorProduct tp);

    QWidget *editPopup;
    QComboBox *xSelect, *ySelect;
    QLineEdit *weightEdit, *xNewEdit, *yNewEdit, *zNewEdit;
    QLabel *weightLabel, *pointLabel, *newPositionLabel;
    QCheckBox *moveManually;
    QPushButton *modifyButton;


    QLabel *addLabel, *sizeLabel;
    QLabel *rotationLabel;
    QLabel *colorLabel;
    QLabel *positionLabel;
    QComboBox *objectComboBox;
    QPushButton *addButton;


    QLineEdit *r, *g, *b;
    QLineEdit *x, *y, *z;
    QLineEdit *roll, *pitch, *yaw;
    QLineEdit *sizeEdit;

    void createNURBSBox();
    QLabel *nurbsLabel, *sizeNurbsLabel, *nameNurbsLabel, *positionNurbsLabel, *colorNurbsLabel;
    QLineEdit *widthNurbsEdit, *heightNurbsEdit, *nameNurbsEdit;
    QLineEdit *xNurbs, *yNurbs, *zNurbs, *rNurbs, *gNurbs, *bNurbs;
    QPushButton *editNurbsButton;
    QComboBox *surfaceCBox;

    Ui::MainWindow *ui;
    Scene *scene;
    QWidget *mainContainer;
    QSplitter *mainSplitter;
    QPushButton *nurbsButton;
    QPushButton *demoButton ;
    QPushButton *clearButton;
    QCheckBox *moveLightCheckBox ;
    QWidget *buttonWidget;
    QGridLayout *addBoxGridLayout;
    QGridLayout *nurbsBoxGridLayout;
    QVBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer ;
    QHBoxLayout *mainLayout;

};

#endif // MAINWINDOW_H
