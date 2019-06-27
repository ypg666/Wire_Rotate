#include "statewidget.h"

stateWidget::stateWidget(QWidget *parent)
	: QWidget(parent), m_on(false) {}

bool stateWidget::isOn() const
{
	return m_on;
}

void stateWidget::setOn(bool on)
{
	if (on == m_on)
		return;
	m_on = on;
	update();
}

void stateWidget::turnOff()
{
	setOn(false);
}

void stateWidget::turnOn()
{
	setOn(true);
}

void stateWidget::paintEvent(QPaintEvent *)
{

	if (!m_on)
		return;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(m_color);
	painter.drawEllipse(0, 0, this->width(), this->height());

	// 放弃以下面这种方式添加字体 -- 不知为何会出现乱码
	QFont font;
	font.setFamily("宋体");
	// 大小
	font.setPointSize(16);
	// 斜体
	//font.setItalic(true);
	// 设置下划线
	//font.setUnderline(true);
	// 设置上划线
	//font.setOverline(true);
	// 设置字母大小写
	//font.setCapitalization(QFont::SmallCaps);
	// 设置字符间距
	font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
	painter.setFont(font);
	painter.setPen(Qt::white);
	//lightTextStr = QString::fromLocal8Bit(lightText);
	// qDebug() << lightTextStr<< endl;
	painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter, lightTextStr);
}