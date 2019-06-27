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
	// ״ָ̬ʾ��
	int numberOfLight = 3;
	std::vector<stateWidget *> vStateWidget;
	int stateNumber = 0;

signals:
    void grab_signal();
    void caculate();
    void outcome();
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
