#ifndef CAMERADISPLAY_H
#define CAMERADISPLAY_H

#include <QWidget>
#include "TIS_Camera.h"

using namespace std;
using namespace cv;

namespace Ui {
class CameraDisplay;
}

class CameraDisplay : public QWidget
{
    Q_OBJECT

public:
    CameraDisplay(int frameRate,QWidget *parent = 0);
    ~CameraDisplay();
    //相机的类
//    TIS_Camera  tisCamera;

protected:
    void paintEvent(QPaintEvent *event);

private:
    TIS_Camera cam;
    QTimer* frameTimer;
        void refresh();
};

#endif // CAMERADISPLAY_H
