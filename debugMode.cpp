#include "debugmode.h"

debugMode::debugMode(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
	// 槽信号连接
	// connect(ui.pb_nextStep, SIGNAL(clicked()), this, SLOT(on_pb_nextStep_clicked()));

	// ============= 状态指示灯设置 ==================//
	vStateWidget.resize(numberOfLight);
	for (int i = 0; i < numberOfLight; i++) {
		vStateWidget.at(i) = new stateWidget();
	}

	vStateWidget.at(0) = dynamic_cast<stateWidget*>(ui.wd_cameraGrabber);
	vStateWidget.at(1) = dynamic_cast<stateWidget*>(ui.wd_calculateDegree);
	vStateWidget.at(2) = dynamic_cast<stateWidget*>(ui.wd_outputDegree);

	vStateWidget.at(0)->lightTextStr = "相机抓图";
	vStateWidget.at(1)->lightTextStr = "计算角度";
	vStateWidget.at(2)->lightTextStr = "输出角度";

	// ui.lb_cameraGrabber->setAlignment(Qt::AlignCenter);

	for (int i = 0; i < numberOfLight; i++) {
		vStateWidget.at(i)->turnOn();
	}

}

void debugMode::on_pb_nextStep_clicked()
{
	this->stateNumber += 1;
	this->stateNumber %= (this->numberOfLight + 1);

	if (this->stateNumber == 0) {
		for (int i = 0; i < this->numberOfLight; i++) {
            vStateWidget.at(i)->m_color = Qt::blue;
			vStateWidget.at(i)->turnOn();
			vStateWidget.at(i)->update();
		}
	}
	else {
		for (int i = 0; i < this->stateNumber; i++) {
			vStateWidget.at(i)->m_color = Qt::green;
			vStateWidget.at(i)->turnOn();
			vStateWidget.at(i)->update();
		}
	}

	// qDebug() << this->stateNumber << endl;
	if (this->stateNumber == 1) {
		// 执行=相机抓图=的=回调函数=
        emit grab_signal();

	}
	else if (this->stateNumber == 2) {
		// 执行=计算角度=的=回调函数=
        emit caculate();
	}
	else if (this->stateNumber == 3) {
		// 执行=输出角度=的=回调函数=
        emit outcome();
	}

}

void debugMode::on_pb_reset_clicked()
{
	for (int i = 0; i < this->numberOfLight; i++) {
        vStateWidget.at(i)->m_color = Qt::blue;
		vStateWidget.at(i)->turnOn();
		vStateWidget.at(i)->update();
	}
	this->stateNumber = 0;
}

void debugMode::on_pb_confirmOutputO_clicked()
{
	QString temp = ui.le_inputDegreeO->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// 执行所需调用的函数
			// =回调函数= （输出角度的回调函数）
            emit out(val);
			qDebug() << "确认输出角度正确" << "\n";
		}
		else
		{
			// 报错
			qDebug() << "数字越界" << "\n";
			QMessageBox::critical(NULL, "", ("数字越界，请重新输入（-180°, 180°）的整数角度"), QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// 报错
		qDebug() << "输入错误" << "\n";
		QMessageBox::critical(NULL, "", "输入包含无效字符或小数点", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_le_inputDegreeO_textChanged(const QString &arg1)
{
	if (arg1.isEmpty()) {
		ui.lb_warningMsg->setText("");
		return;
	}

	bool okNow = false;
	int val = arg1.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			ui.lb_warningMsg->setText("");
		}
		else
		{
			//ui.lb_warningMsg->setText("-180, 180");
			ui.lb_warningMsg->setText("请输入（-180°, 180°）的整数值");
		}
	}
	else
	{
		ui.lb_warningMsg->setText("输入包含无效字符或小数点");
	}
}

void debugMode::on_le_inputDegreeT_textChanged(const QString &arg1)
{
	if (arg1.isEmpty()) {
		ui.lb_warningMsg_2->setText("");
		return;
	}

	bool okNow = false;
	int val = arg1.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			ui.lb_warningMsg_2->setText("");
		}
		else
		{
			// ui.lb_warningMsg_2->setText("-180, 180");
			ui.lb_warningMsg->setText("请输入（-180°, 180°）的整数值");
		}
	}
	else
	{
		ui.lb_warningMsg_2->setText("输入包含无效字符或小数点");
	}
}

void debugMode::on_pb_confirmOutputT_clicked()
{
	QString temp = ui.le_inputDegreeT->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// ===============执行所需调用的函数
			// =回调函数= （偏转角度的回调函数）
            emit deflection(val);
			qDebug() << "确认输出角度正确" << "\n";


		}
		else
		{
			// 报错
			qDebug() << "数字越界" << "\n";
			QMessageBox::critical(NULL, "", QObject::trUtf8("数字越界，请重新输入（-180°, 180°）的整数角度"), QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// 报错
		qDebug() << "输入错误" << "\n";
		QMessageBox::critical(NULL, "", "输入包含无效字符或小数点", QMessageBox::Ok, QMessageBox::Ok);
	}
}
