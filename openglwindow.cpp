#include "openglwindow.h"

OpenGLWindow::OpenGLWindow(int framesPerSecond, QWidget *parent, const char* name)
    : QGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else {
        int seconde = 1000;
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
}

void OpenGLWindow::keyPressEvent(QKeyEvent *keyEvent)
{

}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *mouseEvent)
{

}

void OpenGLWindow::wheelEvent(QWheelEvent *wheelEvent)
{

}

void OpenGLWindow::timeOutSlot()
{
    updateGL();
}
