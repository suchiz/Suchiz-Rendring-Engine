#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Scene/scene.h"
#include "../UI/adddialog.h"
#include "../UI/objectedit.h"
#include "../UI/surfaceedit.h"
#include <regex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void addSceneObject(DrawableObject* object);
    void deleteObjectFromList(int ind);
    void clearObjectList();
    void updateObjectName(int ind, QString name);
    void mouseReleaseEvent(QMouseEvent *event);
    ~MainWindow();

private slots:
    void on_moveLightCheckBox_toggled(bool checked);
    void on_demoButton_clicked();
    void on_clearButton_clicked();
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

    void on_objectListView_itemClicked(QListWidgetItem *item);

    void on_objectListView_itemChanged(QListWidgetItem *item);

private:

    //MODIFICIATION NURBS POP UP
    void createEditSurfaceWindow(TensorProduct tp);

    //MAIN WINDOW
    Ui::MainWindow *ui;
    Scene *scene;
    AddDialog *ad = NULL;
    ObjectEdit *oed = NULL;
    SurfaceEdit *sed = NULL;


};

#endif // MAINWINDOW_H
