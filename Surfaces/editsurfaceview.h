#ifndef EDITSURFACEVIEW_H
#define EDITSURFACEVIEW_H

#include "../Scene/scene.h"

class EditSurfaceView : public Scene
{
public:
    //CONSTRUCTOR
    explicit EditSurfaceView(QWidget *parent = 0);

    //OPENGL FUNCTIONS
    void initializeGL();
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );

    //FUNCTIONS
    void addCubeSelected(DrawableObject *obj, int i) {selectedCubes.push_back(obj);
                                                     indices.push_back(i);}
    void deleteCubeSelected(DrawableObject *obj, int i) {selectedCubes.erase(std::remove(selectedCubes.begin(),
                                                                                         selectedCubes.end(), obj),
                                                                                         selectedCubes.end());
                                                         indices.erase(std::remove(indices.begin(),
                                                                                   indices.end(), i),
                                                                                   indices.end());}

    //GETTERS
    bool getCubeSelected() const {return cubeSelected;}
    std::vector<DrawableObject*> getVectorCubeSelected() const {return selectedCubes;}

    //SETTERS
    void setCubeSelected(bool b) {cubeSelected = b;}
    void setCurrentTp(TensorProduct *tp) {currentTp = tp;}
private:
    std::vector<DrawableObject*> selectedCubes;
    std::vector<int> indices;
    TensorProduct *currentTp;
    bool cubeSelected = false;
};

#endif // EDITSURFACEVIEW_H
