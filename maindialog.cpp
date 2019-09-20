#include "maindialog.h"
#include "ui_maindialog.h"


MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    p.initFromConfig();

    this->showFullScreen();
    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    setWindowFlag(Qt::FramelessWindowHint);     //设置窗体的标识，此处设置窗体为一个没有面板边框和标题栏的窗体
    this->setObjectName("dialog");    //这句话一定要有，不然，整个界面上的控件背景都跟界面背景一样
    this->setStyleSheet("QDialog#dialog{border-image:url(2.jpg)}");
    //ui->pushButton->setStyleSheet(“border-image:url(me.png)”); 按钮添加背景图片
    ui->pushButton->setText(QString("开始运行"));

    //毛玻璃透明度效果 （未实现） 会与背景图片冲突
    if (QtWin::isCompositionEnabled())
    {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        this->setAttribute(Qt::WA_TranslucentBackground, true);
        this->setAttribute(Qt::WA_NoSystemBackground, false);
        this->setStyleSheet("widget { background: transparent; }");
    }
    else
    {
        QtWin::resetExtendedFrame(this);
        this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->setStyleSheet(QString("widget { background: %1; }").arg(QtWin::realColorizationColor().name()));
    }

    //USER目录调试
    //qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    //qDebug() << QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    //左状态栏 右状态栏
    ui->label_8->setText("欢迎使用！");
    ui->label_9->setText("中山爱博机器人有限公司   "
                         "张生   "
                         "电话：13610482491   ");

    //开机检测相机和串口
    detect_IO();
    //调用开启相机自带的窗口
//    cam.Camera(ui->widget);
    cam2.Camera(ui->widget_2);

    //黑色背景框
    ui->widget->setAutoFillBackground(true);
    QPalette qplte;
    qplte.setColor(QPalette::Window, QColor(0,0,0));
    ui->widget->setPalette(qplte);

    //黑色背景框2
    ui->widget_2->setAutoFillBackground(true);
    qplte.setColor(QPalette::Window, QColor(0,0,0));
    ui->widget_2->setPalette(qplte);

    detect_cam();

    if(easymodbus.initSerialPort() > 0)  //串口初始化
    {
    show1(0);
    }

    //算法参数初始化
    threeparams.write_params(params);//读算法参数
    lineRotate.init(params);
    threeparams2.write_params(params2);//读算法参数2
    lineRotate2.init(params2);

    //设置晶体管控件QLCDNumber能显示的位数
    ui->lcdNumber_3->setDigitCount(8);
      //设置显示的模式为十进制
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);
      //设置显示方式
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(1000);
    //启动定时器
    timer->start();

    //slot
    //主界面按钮信号槽
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(fun()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(debug()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(password()));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(password1()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(AutoClose()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(historyimage()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //调试窗口的信号槽
    connect(&w3, SIGNAL(grab_signal()), this, SLOT(grab1()));
    connect(&w3, SIGNAL(caculate()), this, SLOT(caculate1()));
    connect(&w3, SIGNAL(outcome()), this, SLOT(outcome1()));
    connect(&w3, SIGNAL(out(int)), this, SLOT(outcome2(int)));
    connect(&w3, SIGNAL(deflection(int)), this, SLOT(set_deflection(int)));
    //下相机
    connect(&w3_2, SIGNAL(grab_signal()), this, SLOT(grab2()));
    connect(&w3_2, SIGNAL(caculate()), this, SLOT(caculate2()));
    connect(&w3_2, SIGNAL(outcome()), this, SLOT(outcome1()));
    connect(&w3_2, SIGNAL(out(int)), this, SLOT(outcome2(int)));
    connect(&w3_2, SIGNAL(deflection(int)), this, SLOT(set_deflection(int)));
    //更新相机设置和算法计算后的信号槽
    connect(TIS_Camera::Instance(), SIGNAL(ini()), this, SLOT(normal()));
    connect(Listener1::Instance(), SIGNAL(finish(int)), this, SLOT(show1(int)));;
    connect(TIS_Camera2::Instance(), SIGNAL(ini()), this, SLOT(normal2()));
    connect(Listener2::Instance(), SIGNAL(finish(int)), this, SLOT(show2(int)));;
    //回调时算法报错的信号槽
    connect(Listener1::Instance(), SIGNAL(no_roi()), this, SLOT(ROI_error()));
    connect(Listener2::Instance(), SIGNAL(no_roi()), this, SLOT(ROI_error()));
}

MainDialog::~MainDialog()
{
    delete ui;
}
//实时显示图像
void MainDialog::normal()
{
    cam.Camera(ui->widget);
}
void MainDialog::normal2()
{
    cam2.Camera(ui->widget_2);
}
//开始检测 进入触发模式
void MainDialog::fun()
{
    if(ui->pushButton->text()==(QString("开始运行")))
    {
        detect_cam();
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        //ui->pushButton_10->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        //ui->pushButton_9->setEnabled(false);
        ui->pushButton->setText(QString("停止检测"));
        cam.Trigger(ui->widget);
        cam2.Trigger(ui->widget_2);
        ui->label_8->setText("正在运行,等待触发");
        this->update();
    }
    else if(ui->pushButton->text()==(QString("停止检测")))
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        //ui->pushButton_9->setEnabled(true);
        //ui->pushButton_10->setEnabled(true);
        ui->pushButton->setText(QString("开始运行"));
        cam.Camera(ui->widget);
        cam2.Camera(ui->widget_2);
        ui->label_8->setText("未开始运行");
        this->update();
    }

}
//显示函数  输入：l为旋转角度 与偏转角度相加 后modbus输出 并且在对应界面显示角度 并增加检测数量
void MainDialog::show1(int l)
{
    int symbol;
    if (l == 0){symbol = 1 ;}
    else
    {symbol = l / (abs(l));}
    temp = symbol * p.read_deflection();

    if (l+temp > 180 || l+temp < -180)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("加入偏转角度后超出范围"),QMessageBox::Yes);
        return;
    }
    try {
        easymodbus.sendMsg(l+temp);
    }
    catch (const int errorcode)
    {
//        QMessageBox::warning(NULL,QString("错误"),QString("发送失败,正在检测串口"),QMessageBox::Yes);
        if (easymodbus.initSerialPort() > 0)
        {easymodbus.sendMsg(l+temp);}
        else {QMessageBox::warning(NULL,QString("错误"),QString("串口未连接"),QMessageBox::Yes);}
    }
    ui->lcdNumber_2->display(l+temp);
    ui->lcdNumber->display(l1);
    l1=l+temp;

    QString str1=p.readhis();
    int num2 = str1.toInt();  //历史检测数量
    num1=QString::number(num);  //当前检测数量
    if(num != 0)
    {
        num2++;
        if(num2 == 10000)
        {num2 = 0;}
    }
    num++;
    str1=QString::number(num2);
    p.sethis(str1);
    ui->label_5->setText(num1);
    ui->label_6->setText(str1);
    this->update();
}

void MainDialog::show2(int l)
{
    int symbol;
    if (l == 0){symbol = 1 ;}
    else
    {symbol = l / (abs(l));}
    temp = symbol * p.read_deflection();

    if (l+temp > 180 || l+temp < -180)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("加入偏转角度后超出范围"),QMessageBox::Yes);
        return;
    }
    try {
        easymodbus.sendMsg(l+temp);
    }
    catch (const int errorcode)
    {
//        QMessageBox::warning(NULL,QString("错误"),QString("发送失败,正在检测串口"),QMessageBox::Yes);
        if (easymodbus.initSerialPort() > 0)
        {easymodbus.sendMsg(l+temp);}
        else {QMessageBox::warning(NULL,QString("错误"),QString("串口未连接"),QMessageBox::Yes);}
    }
    ui->lcdNumber_3->display(l+temp);
    ui->lcdNumber_4->display(l2);
    l2=l+temp;

    QString str1=p.readhis();
    int num2 = str1.toInt();  //历史检测数量
    num1=QString::number(num);  //当前检测数量
    if(num != 0)
    {
        num2++;
        if(num2 == 10000)
        {num2 = 0;}
    }
    num++;
    str1=QString::number(num2);
    p.sethis(str1);
    ui->label_5->setText(num1);
    ui->label_6->setText(str1);
    this->update();
}
//历史图像界面
void MainDialog::historyimage()
{
    w1.hisupdate();
    w1.exec();
}
//调试界面
void MainDialog::debug()
{
    int mess = QMessageBox::information(this,QString("选择相机"),QString("请选择调试相机"),QString("上相机"),QString("下相机"));
    if (mess == 0 )
    {
        w3.exec();
    }
    else if (mess == 1 )
    {
        w3_2.exec();
    }
//    w3.exec();
}
//系统设置
void MainDialog::password()
{
    w2.setflag(0);
    //w2.show();
    w2.exec();
}
//相机设置
void MainDialog::password1()
{
    int mess = QMessageBox::information(this,QString("选择相机"),QString("请选择调试相机"),QString("上相机"),QString("下相机"));
    if (mess == 0 )
    {
        w2.setflag(1);
        w2.exec();
    }
    else if (mess == 1 )
    {
        w2.setflag(2);
        w2.exec();
    }
}

//调试窗口抓图
void MainDialog::grab1()
{
    if(cam.Valid())
    {
    //grab_img = cv::imread("imaging.bmp");
    //直接传图会出错 ， 存图再读图不报错
    grab_img = cam.GetMatImage(); //不是线材图像的时候会BUG
    cv::flip(grab_img, grab_img, 0);//垂直反转
    cv::imwrite("grab_img.bmp", grab_img);
    grab_img = cv::imread("grab_img.bmp");
    threeparams.inputImg = grab_img;
    //在这里catch不到
    try {
        if (threeparams.hasInputImg = true )
        {
            // threeparams.hasInputImg = false;
            threeparams.exec();
        }
    }
    catch (const int errorcode)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("图像中无线材"),QMessageBox::Yes);
    }

//    cv::imshow("Test", grab_img);
    cv::imwrite("test/grab_img.bmp", grab_img);
}
    else {
        QMessageBox::warning(NULL,QString("错误"),QString("相机未连接"),QMessageBox::Yes);
    }
}

void MainDialog::grab2()
{
    if(cam2.Valid())
    {
    //grab_img = cv::imread("imaging.bmp");
    //直接传图会出错 ， 存图再读图不报错
    grab_img = cam2.GetMatImage(); //不是线材图像的时候会BUG
    cv::flip(grab_img, grab_img, 0);//垂直反转
    cv::imwrite("grab_img.bmp", grab_img);
    grab_img = cv::imread("grab_img.bmp");
    threeparams2.inputImg = grab_img;
    //在这里catch不到
    try {
        if (threeparams2.hasInputImg = true )
        {
            // threeparams.hasInputImg = false;
            threeparams2.exec();
        }
    }
    catch (const int errorcode)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("图像中无线材"),QMessageBox::Yes);
    }

//    cv::imshow("Test", grab_img);
    cv::imwrite("test/grab_img.bmp", grab_img);
}
    else {
        QMessageBox::warning(NULL,QString("错误"),QString("相机未连接"),QMessageBox::Yes);
    }
}
void MainDialog::caculate1() //分步计算
{
    try {
        //rotate = lineRotate.getRotate(testImage, true, "D:/lineDebug/");
        rotate = lineRotate.getRotate(grab_img);
        //qDebug() << rotate;
        //lineRotate.clearTempData(); // 这一句可加 可不加 有洁癖的话可以加一下确保每次检测完后回到初始值
    }
    catch (const int errorcode)
    {
        //mei you chuang kou yao yong NULL
        QMessageBox::warning(NULL,QString("错误"),QString("图像中没有线材"),QMessageBox::Yes);
        //std::cout << "ERROR CODE: "<< errorcode << std::endl;
    }
    //rotate = c.getRotate(grab_img);
    ui->lcdNumber_2->display(rotate);
}
void MainDialog::caculate2() //分步计算
{
    try {
        //rotate = lineRotate.getRotate(testImage, true, "D:/lineDebug/");
        rotate = lineRotate2.getRotate(grab_img);
        //qDebug() << rotate;
        //lineRotate.clearTempData(); // 这一句可加 可不加 有洁癖的话可以加一下确保每次检测完后回到初始值
    }
    catch (const int errorcode)
    {
        //mei you chuang kou yao yong NULL
        QMessageBox::warning(NULL,QString("错误"),QString("图像中没有线材"),QMessageBox::Yes);
        //std::cout << "ERROR CODE: "<< errorcode << std::endl;
    }
    //rotate = c.getRotate(grab_img);
    ui->lcdNumber_3->display(rotate);
}
void MainDialog::outcome1()     //分步输出
{
    int symbol;
    if (rotate == 0)
    {symbol = 1;}
    else
    {symbol = rotate / (abs(rotate));}
    temp = symbol * p.read_deflection();

    if (rotate+temp > 180 || rotate+temp < -180)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("加入偏转角度后超出范围"),QMessageBox::Yes);
        return;
    }
    try {
        easymodbus.sendMsg(rotate+temp);
        QMessageBox::warning(NULL,QString("成功"),QString("设置成功"),QMessageBox::Yes);
    }
    catch (const int errorcode)
    {
//        QMessageBox::warning(NULL,QString("错误"),QString("发送失败,正在检测串口"),QMessageBox::Yes);
        if (easymodbus.initSerialPort() > 0)
        {easymodbus.sendMsg(rotate+temp);}
        else {QMessageBox::warning(NULL,QString("错误"),QString("串口未连接"),QMessageBox::Yes);}
    }
    //if (easymodbus.initSerialPort() > 0)
    //{easymodbus.sendMsg(rotate+temp);}
    //else {QMessageBox::warning(NULL,QString("错误"),QString("串口未连接"),QMessageBox::Yes);}
}
void MainDialog::outcome2(int val)  //直接输出角度
{
    int symbol;
    if (val == 0){symbol = 1;}
    else
    {symbol = val / (abs(val));}
    temp = symbol * p.read_deflection();

    if (val+temp > 180 || val+temp < -180)
    {
        QMessageBox::warning(NULL,QString("错误"),QString("加入偏转角度后超出范围"),QMessageBox::Yes);
        return;
    }
    try {
        easymodbus.sendMsg(val+temp);
        QMessageBox::warning(NULL,QString("成功"),QString("设置成功"),QMessageBox::Yes);
    }
    catch (const int errorcode)
    {
//        QMessageBox::warning(NULL,QString("错误"),QString("发送失败,正在检测串口"),QMessageBox::Yes);
        if (easymodbus.initSerialPort() > 0)
        {
            easymodbus.sendMsg(val+temp);
        QMessageBox::warning(NULL,QString("成功"),QString("设置成功"),QMessageBox::Yes);
        }
        else {QMessageBox::warning(NULL,QString("错误"),QString("串口未连接"),QMessageBox::Yes);}
    }
    qDebug() << val+temp << endl ;
}
void MainDialog::set_deflection(int val)  //设置偏转角度  需要写到数据类里
{
    QMessageBox::warning(NULL,QString("成功"),QString("设置成功"),QMessageBox::Yes);
    p.set_deflection(val);
    p.initFromConfig();
}
//时钟
void MainDialog::onTimerOut()
{
  //获取系统当前时间
  QTime time = QTime::currentTime();
  //设置晶体管控件QLCDNumber上显示的内容
  ui->lcdNumber_3->display(time.toString("hh:mm:ss"));
}
//检测串口连接
void MainDialog::detect_IO()
{
    if (easymodbus.initSerialPort() < 0)
    {
        int mess;
        mess = QMessageBox::warning(this,QString("错误"),QString("串口未连接"),QString("重试"),QString("忽略"));
        if (mess == 0 )
        {detect_IO();}
        else if (mess == 1 )
        {}
    }
}
//检测相机连接
void MainDialog::detect_cam()
{
    if (cam.Valid() == false)
    {
        int mess;
        mess = QMessageBox::warning(this,QString("错误"),QString("相机未连接"),QString("重试"),QString("忽略"));
        //qDebug() << mess;
        if (mess == 0 )
        {
            cam.Camera(ui->widget);
            detect_cam();}
        else if (mess == 1 )
        {}
    }
}
void MainDialog::ROI_error()
{
    QMessageBox::information(this,QString("错误"),QString("图像中没有线材"),QMessageBox::Yes);
}
void MainDialog::AutoClose()
{
    int mess;
    mess = QMessageBox::warning(this,QString("退出"),QString("是否直接关机?"),QString("是"),QString("否(仅退出程序)"),QString("取消退出"));
    //qDebug() << mess;
    if (mess == 0 )
    {
    QProcess pro;    //通过QProcess类来执行第三方程序
    QString cmd = QString("shutdown -s -t 0"); //shutdown -s -t 0 是window下的关机命令，

    pro.start(cmd);    //执行命令cmd
    pro.waitForStarted();
    pro.waitForFinished();
    }
    else if (mess == 1 )
    {qApp ->quit();}
    else if (mess == 2 )
    {return;}
}
