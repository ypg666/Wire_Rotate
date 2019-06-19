#pragma once

#include <QtWidgets/QDialog>
//#include "ui_debugMode.h"
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QSizePolicy>

// #include <QSpacerItem>

// 支持中文
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


class debugMode : public QDialog
{
	Q_OBJECT

public:
	debugMode(QWidget *parent = Q_NULLPTR);

private slots:
// 第一组
void on_nextStep_clicked();
void on_resetButton_clicked();
// 第二组
void on_confirmOutput_clicked();
void on_degreeText_textChanged(QString text);

// 第三组
void on_confirmOutput2_clicked();
void on_degreeText2_textChanged(QString text);

private:
// 相机抓图的回调函数
void on_cb_cameraGrabber_stateChanged(int flag);
// 计算角度的回调函数
void on_cb_calculateDegree_stateChanged(int flag);
// 输出角度的回调函数
void on_cb_outputDegree_stateChanged(int flag);

private:
//	Ui::debugModeClass ui;

	// 分布调试组
	QGroupBox *createStepGroup();
	// 旋转角度调试组
	QGroupBox *createOutputGroup();
	// 偏转角度调试组
	QGroupBox *createOutput2Group();

	int widthOfDialog = 500;

	QLabel *debugInStep;

	//========== 状态显示 ================//
	QCheckBox *cb_cameraGrabber;
	QCheckBox *cb_calculateDegree;
	QCheckBox *cb_outputDegree;
	QPushButton *nextStep;
	QPushButton *resetButton;

	// 第二个GroupBox
	QLabel *debugInOutput;
	QLabel *inputDegrees;
	QLabel *warningMassege;
	QLineEdit *degreeText;
	QPushButton *confirmOutput;

	// 第三个GroupBox
	QLabel *debugInOutput2;
	QLabel *inputDegrees2;
	QLabel *warningMassege2;
	QLineEdit *degreeText2;
	QPushButton *confirmOutput2;

    const int widthD = 120;
    const int heightD = 50;

};
