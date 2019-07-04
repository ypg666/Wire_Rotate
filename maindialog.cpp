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

    //毛玻璃透明度效果 （未实现）
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

    //利用painEvent显示，会卡顿
//    ca =new CameraDisplay(20,this);
//    ui->horizontalLayout->addWidget(ca);

    ui->label_8->setText("欢迎使用！");

    //调用开启相机自带的窗口，不卡顿，但窗口适应有些问题
    cam.Camera(ui->widget);
//    cam.Trigger(ui->widget);

    detect_cam();
    detect_IO();
    //    easy = easymodbus.initSerialPort();

    //show1(0);

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

//    QImage *img=new QImage("./00.jpg");
//    QPixmap pixmap("00.jpg");
//    ui->label_7->setPixmap(pixmap);
    //slot
    //主界面按钮信号槽
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(fun()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(debug()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(password()));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(password1()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(historyimage()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    //调试窗口的信号槽
    connect(&w3, SIGNAL(grab_signal()), this, SLOT(grab1()));
    connect(&w3, SIGNAL(caculate()), this, SLOT(caculate1()));
    connect(&w3, SIGNAL(outcome()), this, SLOT(outcome1()));
    connect(&w3, SIGNAL(out(int)), this, SLOT(outcome2(int)));
    connect(&w3, SIGNAL(deflection(int)), this, SLOT(set_deflection(int)));
    //更新相机设置和算法计算后的信号槽
    connect(TIS_Camera::Instance(), SIGNAL(ini()), this, SLOT(normal()));
    connect(Listener1::Instance(), SIGNAL(finish(int)), this, SLOT(show1(int)));
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
//开始检测 进入触发模式
void MainDialog::fun()
{
    if(ui->pushButton->text()==(QString("开始运行")))
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        //ui->pushButton_10->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        //ui->pushButton_9->setEnabled(false);
        ui->pushButton->setText(QString("停止检测"));
        cam.Trigger(ui->widget);
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
        ui->label_8->setText("未开始运行");
        this->update();
    }

}
//显示函数  输入：l为旋转角度 直接modbus输出 并且在对应界面显示角度 并增加检测数量
void MainDialog::show1(int l)
{
    easymodbus.sendMsg(l);
    ui->lcdNumber_2->display(l);
    ui->lcdNumber->display(l1);
    l1=l;

    QString str1=p.readhis();
    int num2 = str1.toInt();  //历史检测数量
    num1=QString::number(num);  //QString::fromLocal8Bit  QStringLiteral
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
    w1.show();
}
//调试界面
void MainDialog::debug()
{
    w3.show();
}
//系统设置
void MainDialog::password()
{
    w2.setflag(0);
    w2.show();
}
//相机设置
void MainDialog::password1()
{
    w2.setflag(1);
    w2.show();
}
//调试窗口抓图
void MainDialog::grab1()
{
    if(cam.Valid())
    {
//    int n = p.readcur(); //用来命名  不显示角度了  直接用来看存的图
//    QString filename;QString path=image_path;
//    QString str=QString::number(i);

    grab_img = cam.GetMatImage();
    cv::flip(grab_img, grab_img, 0);//垂直反转
    cv::imshow("Test", grab_img);
//    cv::waitKey();
//    QImage img = cam.cvMat2QImage(grab_img,true,false);
//    img.save("test/Qimg.jpg", "JPG", 100);
    cv::imwrite("test/grab_img.bmp", grab_img);
//    filename = filename.append(path + "90°-" + str +".jpg");
//    grab_img.save(filename, "JPG", 100); 要用OPENCV mat保存图片
}
    else {qDebug() << "相机未连接";}

//    QString str1=p.readhis();
//    int num2 = str1.toInt();
//    num++; num2++;
//    str1=QString::number(num2);
//    p.sethis(str1);
//    num1=QString::number(num);  //QString::fromLocal8Bit  QStringLiteral
//    ui->label_5->setText(num1);
//    ui->label_6->setText(str1);
//    this->update();
}
void MainDialog::caculate1() //分步计算
{
    LineRotate c;
    rotate = c.getRotate(grab_img);
    ui->lcdNumber_2->display(rotate);
}
void MainDialog::outcome1()     //分步输出
{
    easymodbus.sendMsg(rotate);
}
void MainDialog::outcome2(int val)  //直接输出角度
{
    easymodbus.sendMsg(val);
}
void MainDialog::set_deflection(int val)  //设置偏转角度  需要写到数据类里
{
    easymodbus.sendMsg(val);
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
        mess = QMessageBox::warning(this,QString("错误"),QString("串口未连接"),QMessageBox::Retry,QMessageBox::Ignore);
        if (mess == 524288 )
        {detect_IO();}
        else if (mess == 1048576 )
        {}
    }
}
//检测相机连接
void MainDialog::detect_cam()
{
    if (cam.Valid() == false)
    {
        int mess;
        mess = QMessageBox::warning(this,QString("错误"),QString("相机未连接"),QMessageBox::Retry,QMessageBox::Ignore);
        //qDebug() << mess;
        if (mess == 524288 )
        {detect_cam();}
        else if (mess == 1048576 )
        {}
    }
}
//别的图像显示方式（没用到）
//获取图片像素
//{
//QPainter painter(this);

// srcImage = new QImage("Image\\test.jpg");
// if (srcImage->isNull())
//     return;
// int srcH = srcImage->height();
// int srcW = srcImage->width();
// //显示源图像
// painter.drawImage(srcH, srcW, *srcImage, 0, 0);

// destImage = new QImage(srcW, srcH, srcImage->format());
// //扫描源图像素，实现翻转
// for (int line=0; line<srcW; line++)
//     for (int row=0; row<srcH; row++)
//     {
//         QRgb value = srcImage->pixel(row, line);
//         destImage->setPixel(line, row,value);
//     }

// painter.drawImage(srcW, srcH, *destImage, 200, 200);
// }


    //局部放大图片
//1.       setMouseTracking（）; 打开鼠标移动跟踪
//2.       局部放大图片的方法
//void Widget::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.drawPixmap(0,0,background);
//    painter.drawPixmap(x+20,y+20,pixmap);
//}
//void Widget::mouseMoveEvent(QMouseEvent *event)
//{
//    x = event->x();
//    y = event->y();
//    //pixmap.fill(QColor(255,255,255,100));
//    mypixmap = mypixmap.grabWidget(this,x,y,10,10);
//    width = mypixmap.width();
//    height = mypixmap.height();
//    pixmap = mypixmap.scaled(width * 5,height * 5，Qt::KeepAspectRatio);         //适应横纵比


////    QPainter painter(&pixmap);
////    painter.setPen(QColor(255,0,0));
////painter.drawText(20,40,QString("%1").arg(x) + "," + QString("%1").arg(y));
//    update();
//}
