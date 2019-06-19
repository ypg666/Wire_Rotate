#include "sys.h"
#include "ui_sys.h"

Sys::Sys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sys)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    setWindowTitle(QString::fromLocal8Bit("系统设置"));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(Password()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(PicNum()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(close()));
}

Sys::~Sys()
{
    delete ui;
}

void Sys::Password()
{
    if (ui->lineEdit->text() == ui->lineEdit_2->text())
    {
        p.setpass(ui->lineEdit->text());
        QMessageBox::warning(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("密码已修改"),QMessageBox::Yes);
        qDebug() <<  p.readpass();
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("确认密码不一致！"),QMessageBox::Yes);
        //清除内容并定位光标
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}

void Sys::PicNum()
{
        p.setpic(ui->lineEdit_3->text());
        QMessageBox::warning(this,QString::fromLocal8Bit("成功"),QString::fromLocal8Bit("图片数量已修改"),QMessageBox::Yes);
        qDebug() <<  p.readpic();
}
