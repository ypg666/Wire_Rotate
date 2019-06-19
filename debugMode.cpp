#include "debugMode.h"

debugMode::debugMode(QWidget *parent)
	: QDialog(parent)
{
//	ui.setupUi(this);
	this->setWindowTitle("调试模式");
	this->setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
	this->setGeometry(widthOfDialog / 5, widthOfDialog / 5, widthOfDialog, widthOfDialog);

	QGridLayout *grid = new QGridLayout;
	grid->addWidget(createStepGroup(), 0, 0);
	grid->addWidget(createOutputGroup(), 1, 0);
	grid->addWidget(createOutput2Group(), 2, 0);
	setLayout(grid);

	// resize(480, 320);
}

void debugMode::on_confirmOutput_clicked() {
	QString temp = this->degreeText->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// 执行所需调用的函数
			qDebug() << "确认输出角度正确" << "\n";

		}
		else
		{
			// 报错
			qDebug() << "数字越界" << "\n";
			QMessageBox::critical(NULL, "", "数字越界，请重新输入（-180°, 180°）的整数角度", QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// 报错
		qDebug() << "输入错误" << "\n";
		QMessageBox::critical(NULL, "", "输入包含无效字符或小数点", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_degreeText_textChanged(QString text)
{

	if (text.isEmpty()) {
		this->warningMassege->setText("");
		return;
	}

	bool okNow = false;
	int val = text.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			this->warningMassege->setText("");
		}
		else
		{
			this->warningMassege->setText("请输入（-180°，180°）的整数值");
		}
	}
	else
	{
		this->warningMassege->setText("输入包含无效字符或小数点");
	}
}

void debugMode::on_confirmOutput2_clicked()
{
	QString temp = this->degreeText2->text();
	bool okNow = false;
	int val = temp.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			// 执行所需调用的函数
			qDebug() << "确认输出角度正确" << "\n";

		}
		else
		{
			// 报错
			qDebug() << "数字越界" << "\n";
			QMessageBox::critical(NULL, "", "数字越界，请重新输入（-180°, 180°）的整数角度", QMessageBox::Ok, QMessageBox::Ok);
		}
	}
	else
	{
		// 报错
		qDebug() << "输入错误" << "\n";
		QMessageBox::critical(NULL, "", "输入包含无效字符或小数点", QMessageBox::Ok, QMessageBox::Ok);
	}
}

void debugMode::on_degreeText2_textChanged(QString text)
{
	if (text.isEmpty()) {
		this->warningMassege2->setText("");
		return;
	}

	bool okNow = false;
	int val = text.toInt(&okNow);
	if (okNow) {
		if (val <= 180 && val >= -180) {
			this->warningMassege2->setText("");
		}
		else
		{
			this->warningMassege2->setText("请输入（-180°，180°）的整数值");
		}
	}
	else
	{
		this->warningMassege2->setText("输入包含无效字符或小数点");
	}
}

void debugMode::on_nextStep_clicked()
{
	if (this->cb_cameraGrabber->isChecked()) {
		if (this->cb_calculateDegree->isChecked()) {
			if (this->cb_outputDegree->isChecked()) {

				this->cb_cameraGrabber->setChecked(false);
				this->cb_calculateDegree->setChecked(false);
				this->cb_outputDegree->setChecked(false);

			}
			else{
				this->cb_outputDegree->setChecked(true);
			}
		}
		else {
			this->cb_calculateDegree->setChecked(true);
		}
	}
	else
	{
		this->cb_cameraGrabber->setChecked(true);
	}
}

void debugMode::on_resetButton_clicked()
{
	this->cb_cameraGrabber->setChecked(false);
	this->cb_calculateDegree->setChecked(false);
	this->cb_outputDegree->setChecked(false);
}

void debugMode::on_cb_cameraGrabber_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// 执行回调函数 -- 采集图片
		qDebug() << "相机抓图" << "\n";
	}
}

void debugMode::on_cb_calculateDegree_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// 执行回调函数 -- 计算角度
		qDebug() << "计算角度" << "\n";
	}
}

void debugMode::on_cb_outputDegree_stateChanged(int flag)
{
	if (flag == 0) {
		return;
	}
	else
	{
		// 执行回调函数 -- 输出角度
		qDebug() << "输出角度" << "\n";
	}
}

// 界面设置

QGroupBox * debugMode::createStepGroup()
{
	QGroupBox *groupBox = new QGroupBox(tr("分步调试"));

	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 相机抓图
	cb_cameraGrabber = new QCheckBox(this);
	cb_cameraGrabber->setText("相机抓图");
	//cb_cameraGrabber->setMaximumSize(widthD, heightD);
	//cb_cameraGrabber->setSizePolicy(sizePolicy);
	cb_cameraGrabber->setDisabled(true);
	//cb_cameraGrabber->setGeometry(widthOfDialog / 25, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_cameraGrabber, SIGNAL(stateChanged(int)), this, SLOT(on_cb_cameraGrabber_stateChanged(int)));

	// 计算角度
	cb_calculateDegree = new QCheckBox(this);
	cb_calculateDegree->setText("计算角度");
	cb_calculateDegree->setDisabled(true);
	//cb_calculateDegree->setMaximumSize(widthD, heightD);
	//cb_calculateDegree->setGeometry(widthOfDialog / 25 + widthOfDialog / 5 + 20, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_calculateDegree, SIGNAL(stateChanged(int)), this, SLOT(on_cb_calculateDegree_stateChanged(int)));

	// 输出角度
	cb_outputDegree = new QCheckBox(this);
	cb_outputDegree->setText("输出角度");
	cb_outputDegree->setDisabled(true);
	//cb_outputDegree->setMaximumSize(widthD, heightD);
	//cb_outputDegree->setGeometry(widthOfDialog / 25 + 2 * widthOfDialog / 5 + 2 * 20, widthOfDialog / 25 + 2 * widthOfDialog / 25, widthOfDialog / 5, widthOfDialog / 10);
	connect(cb_outputDegree, SIGNAL(stateChanged(int)), this, SLOT(on_cb_outputDegree_stateChanged(int)));

	// 下一步
	nextStep = new QPushButton(this);
	nextStep->setText("下一步");
	nextStep->setMaximumSize(widthD, heightD);
	
	//sizePolicy.setHorizontalStretch(0);
	//sizePolicy.setVerticalStretch(0);
	//sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
	nextStep->setSizePolicy(sizePolicy);
	//nextStep->setGeometry(widthOfDialog / 20, widthOfDialog / 3, widthOfDialog / 8, widthOfDialog / 16);
	connect(nextStep, SIGNAL(clicked(bool)), this, SLOT(on_nextStep_clicked()));

	// 重置
	resetButton = new QPushButton(this);
	resetButton->setText("重置");
	resetButton->setMaximumSize(widthD, heightD);
	resetButton->setSizePolicy(sizePolicy);
	//resetButton->setGeometry(widthOfDialog / 5, widthOfDialog / 3, widthOfDialog / 8, widthOfDialog / 16);
	connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(on_resetButton_clicked()));

	// 排版
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(cb_cameraGrabber);
	hbox->addWidget(cb_calculateDegree);
	hbox->addWidget(cb_outputDegree);
	//hbox->addStretch(1);

	QHBoxLayout *hbox2 = new QHBoxLayout;
	hbox2->addWidget(nextStep);
	//hbox2->addStretch(1);
	hbox2->addWidget(resetButton);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	groupBox->setLayout(vbox);

	return groupBox;
}

QGroupBox * debugMode::createOutputGroup()
{
	QGroupBox *groupBox = new QGroupBox(tr("输出调试"));

	// 请输入旋转角度
	inputDegrees = new QLabel(this);
	inputDegrees->setText("请输入旋转角度(/度):");
	//inputDegrees->setGeometry(widthOfDialog / 25, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 4, widthOfDialog / 16);

	// 旋转角度文本
	degreeText = new QLineEdit(this);
	degreeText->setText("");
	degreeText->setMaxLength(7);
	//degreeText->setGeometry(widthOfDialog / 25 + widthOfDialog / 4, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 8, widthOfDialog / 16);
	connect(degreeText, SIGNAL(textChanged(QString)), this, SLOT(on_degreeText_textChanged(QString)));
	// degreeText->setLineWidth(4);

	// 实时检测旋转角度文本框里面的值 -- 不满足则输出警报
	warningMassege = new QLabel(this);
	warningMassege->setText("");
	warningMassege->setStyleSheet("color: rgb(255, 0, 0); font: 10pt;");
	//warningMassege->setGeometry(widthOfDialog / 25 + widthOfDialog / 4 + widthOfDialog / 8 + 10, widthOfDialog / 2 + widthOfDialog / 16, 200, widthOfDialog / 16);
	  
	// 确认输出
	confirmOutput = new QPushButton(this);
	confirmOutput->setText("确认输出");
	confirmOutput->setMaximumSize(widthD, heightD);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmOutput->setSizePolicy(sizePolicy);
	//confirmOutput->setGeometry(widthOfDialog / 25 , widthOfDialog / 2 + widthOfDialog / 8, widthOfDialog / 8, widthOfDialog / 16);
	connect(confirmOutput, SIGNAL(clicked(bool)), this, SLOT(on_confirmOutput_clicked()));
	
	
	// 排版
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(inputDegrees);
	hbox->addWidget(degreeText);
	// hbox->addStretch(1);
	hbox->addWidget(warningMassege);
	// hbox->addStretch(1);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	QHBoxLayout *hbox4v = new QHBoxLayout;
	hbox4v->addStretch(0);
	hbox4v->addWidget(confirmOutput);
	hbox4v->addStretch(0);
	vbox->addLayout(hbox4v);
	groupBox->setLayout(vbox);

	return groupBox;
}

QGroupBox * debugMode::createOutput2Group()
{
	QGroupBox *groupBox = new QGroupBox(tr("偏转角度调试"));

	// 请输入旋转角度
	inputDegrees2 = new QLabel(this);
	inputDegrees2->setText("请输入角度(/度):");
	//inputDegrees->setGeometry(widthOfDialog / 25, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 4, widthOfDialog / 16);

	// 旋转角度文本
	degreeText2 = new QLineEdit(this);
	degreeText2->setText("");
	degreeText2->setMaxLength(7);
	//degreeText->setGeometry(widthOfDialog / 25 + widthOfDialog / 4, widthOfDialog / 2 + widthOfDialog / 16, widthOfDialog / 8, widthOfDialog / 16);
	connect(degreeText2, SIGNAL(textChanged(QString)), this, SLOT(on_degreeText2_textChanged(QString)));
	// degreeText->setLineWidth(4);

	// 实时检测旋转角度文本框里面的值 -- 不满足则输出警报
	warningMassege2 = new QLabel(this);
	warningMassege2->setText("");
	warningMassege2->setStyleSheet("color: rgb(255, 0, 0); font: 10pt;");
	//warningMassege->setGeometry(widthOfDialog / 25 + widthOfDialog / 4 + widthOfDialog / 8 + 10, widthOfDialog / 2 + widthOfDialog / 16, 200, widthOfDialog / 16);

	// 确认输出
	confirmOutput2 = new QPushButton(this);
	confirmOutput2->setText("确认输出");
	confirmOutput2->setMaximumSize(widthD,heightD);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmOutput2->setSizePolicy(sizePolicy);
	//confirmOutput->setGeometry(widthOfDialog / 25 , widthOfDialog / 2 + widthOfDialog / 8, widthOfDialog / 8, widthOfDialog / 16);
	connect(confirmOutput2, SIGNAL(clicked(bool)), this, SLOT(on_confirmOutput2_clicked()));


	// 排版
	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addWidget(inputDegrees2);
	hbox->addWidget(degreeText2);
	// hbox->addStretch(1);
	hbox->addWidget(warningMassege2);
	// hbox->addStretch(1);

	QVBoxLayout *vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	QHBoxLayout *hbox4v = new QHBoxLayout;
	hbox4v->addStretch(0);
	hbox4v->addWidget(confirmOutput2);
	hbox4v->addStretch(0);
	vbox->addLayout(hbox4v);
	groupBox->setLayout(vbox);

	return groupBox;
}
