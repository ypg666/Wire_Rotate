#include "cameradisplay.h"

CameraDisplay::CameraDisplay(int frameRate, QWidget *parent) :QWidget(parent)
{
    frameTimer = new QTimer(this);
    cam.CameraInit();
    QObject::connect(frameTimer, &QTimer::timeout, this, &CameraDisplay::refresh);//根据帧率刷新
    frameTimer->start((int)(1000.0 / (float)frameRate));
}

CameraDisplay::~CameraDisplay()
{

}
//绘图 重写事件处理函数
void CameraDisplay::paintEvent(QPaintEvent *event){
    QPainter painter(this); //定义画家

        QImage tImage;  //定义画板
        tImage = cam.GetMatImage();
        tImage = tImage.scaled(size(), Qt::KeepAspectRatio);
        //开始绘制的点，绘制的位置
        QPoint imageBeginPoint((size().width() - tImage.width()) / 2, (size().height() - tImage.height()) / 2);
        QRect imageRect(imageBeginPoint, tImage.size());
        painter.drawImage(imageBeginPoint, tImage);

//    else{ //No video image
//        painter.setPen(QPen(QColor(0, 255, 0)));
//        painter.setFont(QFont(QString("宋体"), 20));
//        painter.drawText(this->rect(), Qt::AlignCenter, QString(tr("无视频信号")));
//    }
    QWidget::paintEvent(event);
}

//更新
void CameraDisplay::refresh(){
    update();
}
