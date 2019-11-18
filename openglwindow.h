#ifndef OPENGLWINDOW
#define OPENGLWINDOW

#include <QtOpenGL>
#include <QGLWidget>

class OpenGLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWindow(int framesPerSecond = 0, QWidget *parent = 0, const char* name = 0);
    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent);
    virtual void wheelEvent(QWheelEvent *wheelEvent);

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;

};

#endif // OPENGLWINDOW

