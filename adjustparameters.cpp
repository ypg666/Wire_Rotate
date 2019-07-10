#include "adjustparameters.h"
#include "ui_adjustparameters.h"

AdjustParameters::AdjustParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustParameters)
{
    ui->setupUi(this);
    paramMin.resize(10);
    paramMax.resize(10);
    paramDefault.resize(10);

    // == 用来实时存储滑块的值 == //
    paramValue.resize(10);

    connect(ui->sd_Hmin, SIGNAL(valueChanged(int)), ui->sb_Hmin, SLOT(setValue(int)));
    connect(ui->sd_Hmax, SIGNAL(valueChanged(int)), ui->sb_Hmax, SLOT(setValue(int)));
    connect(ui->sd_Smin, SIGNAL(valueChanged(int)), ui->sb_Smin, SLOT(setValue(int)));
    connect(ui->sd_Smax, SIGNAL(valueChanged(int)), ui->sb_Smax, SLOT(setValue(int)));
    connect(ui->sd_Vmin, SIGNAL(valueChanged(int)), ui->sb_Vmin, SLOT(setValue(int)));
    connect(ui->sd_Vmax, SIGNAL(valueChanged(int)), ui->sb_Vmax, SLOT(setValue(int)));
    connect(ui->sd_Crmin, SIGNAL(valueChanged(int)), ui->sb_Crmin, SLOT(setValue(int)));
    connect(ui->sd_Crmax, SIGNAL(valueChanged(int)), ui->sb_Crmax, SLOT(setValue(int)));
    connect(ui->sd_Cbmin, SIGNAL(valueChanged(int)), ui->sb_Cbmin, SLOT(setValue(int)));
    connect(ui->sd_Cbmax, SIGNAL(valueChanged(int)), ui->sb_Cbmax, SLOT(setValue(int)));

    connect(ui->sb_Hmin, SIGNAL(valueChanged(int)), ui->sd_Hmin, SLOT(setValue(int)));
    connect(ui->sb_Hmax, SIGNAL(valueChanged(int)), ui->sd_Hmax, SLOT(setValue(int)));
    connect(ui->sb_Smin, SIGNAL(valueChanged(int)), ui->sd_Smin, SLOT(setValue(int)));
    connect(ui->sb_Smax, SIGNAL(valueChanged(int)), ui->sd_Smax, SLOT(setValue(int)));
    connect(ui->sb_Vmin, SIGNAL(valueChanged(int)), ui->sd_Vmin, SLOT(setValue(int)));
    connect(ui->sb_Vmax, SIGNAL(valueChanged(int)), ui->sd_Vmax, SLOT(setValue(int)));
    connect(ui->sb_Crmin, SIGNAL(valueChanged(int)), ui->sd_Crmin, SLOT(setValue(int)));
    connect(ui->sb_Crmax, SIGNAL(valueChanged(int)), ui->sd_Crmax, SLOT(setValue(int)));
    connect(ui->sb_Cbmin, SIGNAL(valueChanged(int)), ui->sd_Cbmin, SLOT(setValue(int)));
    connect(ui->sb_Cbmax, SIGNAL(valueChanged(int)), ui->sd_Cbmax, SLOT(setValue(int)));

    connect(ui->sd_Hmin, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Hmax, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Smin, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Smax, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Vmin, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Vmax, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Crmin, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Crmax, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Cbmin, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));
    connect(ui->sd_Cbmax, SIGNAL(valueChanged(int)), this, SLOT(updateParamValue()));

}

AdjustParameters::~AdjustParameters()
{
    delete ui;
}

void AdjustParameters::setWinTitle(QString titleStr)
{
    this->winTitle = titleStr;
    this->setWindowTitle(this->winTitle);
}

void AdjustParameters::setParamMin(std::vector<int> params)
{
    paramMin = params;
    ui->sb_Hmin->setMinimum(paramMin[0]);
    ui->sb_Hmax->setMinimum(paramMin[1]);
    ui->sb_Smin->setMinimum(paramMin[2]);
    ui->sb_Smax->setMinimum(paramMin[3]);
    ui->sb_Vmin->setMinimum(paramMin[4]);
    ui->sb_Vmax->setMinimum(paramMin[5]);
    ui->sb_Crmin->setMinimum(paramMin[6]);
    ui->sb_Crmax->setMinimum(paramMin[7]);
    ui->sb_Cbmin->setMinimum(paramMin[8]);
    ui->sb_Cbmax->setMinimum(paramMin[9]);

    ui->sd_Hmin->setMinimum(paramMin[0]);
    ui->sd_Hmax->setMinimum(paramMin[1]);
    ui->sd_Smin->setMinimum(paramMin[2]);
    ui->sd_Smax->setMinimum(paramMin[3]);
    ui->sd_Vmin->setMinimum(paramMin[4]);
    ui->sd_Vmax->setMinimum(paramMin[5]);
    ui->sd_Crmin->setMinimum(paramMin[6]);
    ui->sd_Crmax->setMinimum(paramMin[7]);
    ui->sd_Cbmin->setMinimum(paramMin[8]);
    ui->sd_Cbmax->setMinimum(paramMin[9]);

}

void AdjustParameters::setParamMax(std::vector<int> params)
{
    paramMax = params;
    ui->sb_Hmin->setMaximum(paramMax[0]);
    ui->sb_Hmax->setMaximum(paramMax[1]);
    ui->sb_Smin->setMaximum(paramMax[2]);
    ui->sb_Smax->setMaximum(paramMax[3]);
    ui->sb_Vmin->setMaximum(paramMax[4]);
    ui->sb_Vmax->setMaximum(paramMax[5]);
    ui->sb_Crmin->setMaximum(paramMax[6]);
    ui->sb_Crmax->setMaximum(paramMax[7]);
    ui->sb_Cbmin->setMaximum(paramMax[8]);
    ui->sb_Cbmax->setMaximum(paramMax[9]);

    ui->sd_Hmin->setMaximum(paramMax[0]);
    ui->sd_Hmax->setMaximum(paramMax[1]);
    ui->sd_Smin->setMaximum(paramMax[2]);
    ui->sd_Smax->setMaximum(paramMax[3]);
    ui->sd_Vmin->setMaximum(paramMax[4]);
    ui->sd_Vmax->setMaximum(paramMax[5]);
    ui->sd_Crmin->setMaximum(paramMax[6]);
    ui->sd_Crmax->setMaximum(paramMax[7]);
    ui->sd_Cbmin->setMaximum(paramMax[8]);
    ui->sd_Cbmax->setMaximum(paramMax[9]);
}

void AdjustParameters::setParamDefault(std::vector<int> params)
{
    paramDefault = params;
    ui->sb_Hmin->setValue(paramDefault[0]);
    ui->sb_Hmax->setValue(paramDefault[1]);
    ui->sb_Smin->setValue(paramDefault[2]);
    ui->sb_Smax->setValue(paramDefault[3]);
    ui->sb_Vmin->setValue(paramDefault[4]);
    ui->sb_Vmax->setValue(paramDefault[5]);
    ui->sb_Crmin->setValue(paramDefault[6]);
    ui->sb_Crmax->setValue(paramDefault[7]);
    ui->sb_Cbmin->setValue(paramDefault[8]);
    ui->sb_Cbmax->setValue(paramDefault[9]);

    ui->sd_Hmin->setValue(paramDefault[0]);
    ui->sd_Hmax->setValue(paramDefault[1]);
    ui->sd_Smin->setValue(paramDefault[2]);
    ui->sd_Smax->setValue(paramDefault[3]);
    ui->sd_Vmin->setValue(paramDefault[4]);
    ui->sd_Vmax->setValue(paramDefault[5]);
    ui->sd_Crmin->setValue(paramDefault[6]);
    ui->sd_Crmax->setValue(paramDefault[7]);
    ui->sd_Cbmin->setValue(paramDefault[8]);
    ui->sd_Cbmax->setValue(paramDefault[9]);
}

void AdjustParameters::setInDisplay(cv::Mat inputImg)
{
    this->inputImage = inputImg;
    cv::resize(inputImg, inputImg, cv::Size(setWidth, setHeight));

    QImage image = cvMat2QImage(inputImg);
    //image.scaled(ui->inDisplay->width(), ui->inDisplay->height()*2);
    QPixmap inputImg2 = QPixmap::fromImage(image);

    inputImg2.scaled(setWidth, setHeight);

    ui->inDisplay->setPixmap(inputImg2);

    cv::Mat resultImg;
    thresholdTools.getThresholdResult(this->inputImage, resultImg, paramValue);
    cv::resize(resultImg, resultImg, cv::Size(setWidth, setHeight));
    image = cvMat2QImage(resultImg);
    QPixmap resultImg2 = QPixmap::fromImage(image);
    resultImg2.scaled(setWidth, setHeight);
    ui->outDisplay->setPixmap(resultImg2);
    updataOutDisplay = true;
}

void AdjustParameters::on_saveParams_clicked()
{
    //qDebug() << winTitle << endl;
    if(winTitle == QString::fromLocal8Bit("蓝色通道参数调整")){
        ParamSetting paramSet;
        QString str;
        str.sprintf("Blue");
        paramSet.writeIni(str, paramValue);
    }
    else if(winTitle == QString::fromLocal8Bit("绿色通道参数调整")){
        ParamSetting paramSet;
        QString str;
        str.sprintf("Green");
        paramSet.writeIni(str, paramValue);
    }
    else if(winTitle == QString::fromLocal8Bit("黄色通道参数调整")){
        ParamSetting paramSet;
        QString str;
        str.sprintf("Yellow");
        paramSet.writeIni(str, paramValue);
    }
    else if(winTitle == QString::fromLocal8Bit("棕色通道参数调整")){
        ParamSetting paramSet;
        QString str;
        str.sprintf("Brown");
        paramSet.writeIni(str, paramValue);
    }
}

void AdjustParameters::on_resetParams_clicked()
{
    //qDebug() << winTitle << endl;
    if(winTitle == QString::fromLocal8Bit("蓝色通道参数调整")){
        paramDefault = paramBlueDefault;
    }
    else if(winTitle == QString::fromLocal8Bit("绿色通道参数调整")){
        paramDefault = paramGreenDefault;
    }
    else if(winTitle == QString::fromLocal8Bit("黄色通道参数调整")){
        paramDefault = paramYellowDefault;
    }
    else if(winTitle == QString::fromLocal8Bit("棕色通道参数调整")){
        paramDefault = paramBrownDefault;
    }
    ui->sb_Hmin->setValue(paramDefault[0]);
    ui->sb_Hmax->setValue(paramDefault[1]);
    ui->sb_Smin->setValue(paramDefault[2]);
    ui->sb_Smax->setValue(paramDefault[3]);
    ui->sb_Vmin->setValue(paramDefault[4]);
    ui->sb_Vmax->setValue(paramDefault[5]);
    ui->sb_Crmin->setValue(paramDefault[6]);
    ui->sb_Crmax->setValue(paramDefault[7]);
    ui->sb_Cbmin->setValue(paramDefault[8]);
    ui->sb_Cbmax->setValue(paramDefault[9]);
}

void AdjustParameters::updateParamValue()
{
    paramValue[0] = ui->sd_Hmin->value();
    paramValue[1] = ui->sb_Hmax->value();
    paramValue[2] = ui->sb_Smin->value();
    paramValue[3] = ui->sb_Smax->value();
    paramValue[4] = ui->sb_Vmin->value();
    paramValue[5] = ui->sb_Vmax->value();
    paramValue[6] = ui->sb_Crmin->value();
    paramValue[7] = ui->sb_Crmax->value();
    paramValue[8] = ui->sb_Cbmin->value();
    paramValue[9] = ui->sb_Cbmax->value();

    if(updataOutDisplay){
        //qDebug() << winTitle << endl;
        cv::Mat resultImg;
//        if(winTitle == QString::fromLocal8Bit("蓝色通道参数调整")){
//            qDebug() << QString::fromLocal8Bit("蓝色通道参数调整") << endl;
//            thresholdTools.getThresholdResult(this->inputImage, resultImg, paramValue);
//        }
//        else if(winTitle == QString::fromLocal8Bit("绿色通道参数调整")){
//            qDebug() << QString::fromLocal8Bit("绿色通道参数调整")<< endl;

//        }
//        else if(winTitle == QString::fromLocal8Bit("黄色通道参数调整")){
//            qDebug() << QString::fromLocal8Bit("黄色通道参数调整") << endl;
//            thresholdTools.getThresholdResult(this->inputImage, resultImg, paramValue);
//        }
//        else if(winTitle == QString::fromLocal8Bit("棕色通道参数调整")){
//            qDebug() << QString::fromLocal8Bit("棕色通道参数调整") << endl;

//        }
        thresholdTools.getThresholdResult(this->inputImage, resultImg, paramValue);
        cv::resize(resultImg, resultImg, cv::Size(setWidth, setHeight));
        QImage image = cvMat2QImage(resultImg);
        QPixmap resultImg2 = QPixmap::fromImage(image);
        resultImg2.scaled(setWidth, setHeight);
        ui->outDisplay->setPixmap(resultImg2);
    }

}

QImage AdjustParameters::cvMat2QImage(cv::Mat mat)
{
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    const uchar *pSrc = (const uchar*)mat.data;
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image;
    }
    else if (mat.type() == CV_8UC4)
    {
        // qDebug() << "CV_8UC4";
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image;
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
