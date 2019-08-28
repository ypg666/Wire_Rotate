#include "password.h"
#include "ui_password.h"

int Password::flag=2;

Password::Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Password)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromLocal8Bit("请输出管理员密码"));
    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    ui->label->setText(QString::fromLocal8Bit("管理员密码:"));
    ui->lineEdit->setContextMenuPolicy(Qt::NoContextMenu);//干掉该部件的右键菜单
    ui->lineEdit->setPlaceholderText(QString::fromLocal8Bit("请输入密码"));//设置无输入时的提示信息
    ui->lineEdit->setMaxLength(16);//设置最大输入长度
    ui->lineEdit->setEchoMode(QLineEdit::Password);//输入时显示数字，失去焦点时显示圆点
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(on_loginBtn_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(close()));
    //connect(&w4, SIGNAL(ini()), this, SLOT(finish()));
}

Password::~Password()
{
    delete ui;
}

void Password::setflag(int i)
{
    flag =i;
}

void Password::on_loginBtn_clicked()
{
    p.initFromConfig();
    q=p.readpass();
        qDebug() << q;
    //如果用户名密码正确，则调用accept()槽函数。QDialog中的accept函数会关闭自身并发送QDialog::accepted标识
    if (ui->lineEdit->text() == q && flag ==0)
    {
        ui->lineEdit->clear();
        this->close();
        w3.exec();
    }
    else if (ui->lineEdit->text() == q && flag ==1)
    {
        ui->lineEdit->clear();
//        w4.CameraInit();
        TIS_Camera::Instance()->CameraInit();
//        w4.Camerapropery();
        this->close();
    }
    else if (ui->lineEdit->text() == q && flag ==2)
    {
        ui->lineEdit->clear();
//        w4.CameraInit();
        TIS_Camera2::Instance()->CameraInit();
//        w4.Camerapropery();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Yes);
        //清除内容并定位光标
        ui->lineEdit->clear();
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }
}

/*相机初始化传值 由于相机时序问题 改完相机设置后  主界面的相机并不会随之改变 故需要信号槽重新调用相机初始化
但是由于密码类里又创建了个相机对象 此时初始化后 会有这个对象发送信号 而主窗口的相机对象直接的更新槽函数不会受到信号
故再用一次信号与槽转接一下
  */
void Password::finish()
{
    emit fin();
}
