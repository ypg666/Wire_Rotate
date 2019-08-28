/*********************************************************************************
  *Copyright(C)
  *ClassName:  debugMode
  *Author:  佳豪
  *Version: 1.0
  *Date:  2019.7.12
  *Description: 调试窗口
                直接show
                在对应调试步骤的回调里加入信号量
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
  *History:  加入了一些信号量  2019.7.12 璞光
**********************************************************************************/
#pragma once

#include <QtWidgets/QDialog>
#include <QDebug>
#include <QPainter>
#include <vector>
#include <QMessageBox>
#include <QObject>
#include "statewidget.h"
#include "ui_debugmode.h"

class debugMode : public QDialog
{
	Q_OBJECT

public:
	debugMode(QWidget *parent = Q_NULLPTR);

private:
	Ui::DebugMode ui;


private:
	// 状态指示灯
	int numberOfLight = 3;
    std::vector<stateWidget *> vStateWidget; //定义对象的数组
	int stateNumber = 0;

signals:
    //分步
    void grab_signal();
    void caculate();
    void outcome();
    //直接
    void out(int);
    void deflection(int);

private slots:
	void on_pb_nextStep_clicked();

	void on_pb_reset_clicked();

	void on_pb_confirmOutputO_clicked();

	void on_le_inputDegreeO_textChanged(const QString &arg1);

	void on_le_inputDegreeT_textChanged(const QString &arg1);

	void on_pb_confirmOutputT_clicked();

};
