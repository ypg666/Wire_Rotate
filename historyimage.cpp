#include "historyimage.h"
#include "ui_historyimage.h"

HistoryImage::HistoryImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryImage)
{
    ui->setupUi(this);

    //界面初始化
    setWindowFlags(Qt::WindowCloseButtonHint); //隐藏标题栏问号
    ui->qTableWidget->setColumnCount(3);//设置列数
    ui->qTableWidget->setRowCount(maxrow);//设置行数
    ui->qTableWidget->setColumnWidth(0,250);//设置行宽   150
    ui->qTableWidget->setColumnWidth(1,180);//50
    ui->qTableWidget->setColumnWidth(2,180);//80
//    ui->qTableWidget->setColumnWidth(3,100);//80
    QStringList m_Header;
    m_Header<<QString::fromLocal8Bit("保存时间")<<QString::fromLocal8Bit("旋转角度")<<QString::fromLocal8Bit("流程编号");
    ui->qTableWidget->setHorizontalHeaderLabels(m_Header);//添加横向表头
    ui->qTableWidget->verticalHeader()->setVisible(true);//纵向表头可视化
    ui->qTableWidget->horizontalHeader()->setVisible(true);//横向表头可视化
    ui->qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置编辑方式：禁止编辑表格
    ui->qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置表格选择方式：设置表格为整行选中
    ui->qTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//选择目标方式
    ui->qTableWidget->setStyleSheet("selection-background-color:skyblue");//设置选中颜色
    ui->qTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //排序
    QHeaderView *headerGoods = ui->qTableWidget->horizontalHeader();
    //SortIndicator为水平标题栏文字旁边的三角指示器
    headerGoods->setSortIndicator(1, Qt::AscendingOrder);
    headerGoods->setSortIndicatorShown(true);
    headerGoods->setSectionsClickable(true);

//    //读文件夹
//    const QString path=image_path;  //文件夹目录
//    QDir *dir=new QDir(path);
//    //QDir *dir=new QDir(QDir::currentPath());现在的目录 QAppllication::appllicationDirPath()绝对路径
//    dir ->setSorting(QDir::Name);  //排列方式
//    dir ->sorting();
//    QStringList filter; //过滤格式
//    filter<<"*.jpg"<<"*.png";
//    dir->setNameFilters(filter);
//    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));

//    //读文件夹存入列表
//    for(int i = 0; i < (fileInfo->count()); i++)
//    {
//        QString number;QString number1;
//        QTableWidgetItem *item = new QTableWidgetItem(fileInfo->at(i).baseName());
//        QTableWidgetItem *item2 = new QTableWidgetItem(fileInfo->at(i).baseName());
//        number = item ->text();number =number.left(1); item ->setText(number);
//        ui->qTableWidget->setItem(i,1,item);
//        number1 = item2 ->text();number1 =number1.mid(2);item2 ->setText(number1);
//        ui->qTableWidget->setItem(i,2,item2);
//        QTableWidgetItem *item1 = new QTableWidgetItem(fileInfo->at(i).created().toString("yyyy-MM-dd hh:mm:ss"));
//        ui->qTableWidget->setItem(i,0,item1);
//    }

    //信号与槽函数
    connect(headerGoods, SIGNAL(sectionClicked(int)), ui->qTableWidget, SLOT(sortByColumn(int))); //用了qTableView的Public Functions作槽函数
    connect(ui->qTableWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onContextMenu(QPoint)));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(prePageHis()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(nextPageHis()));
}

HistoryImage::~HistoryImage()
{
    delete ui;
}

void HistoryImage::hisupdate()
{
    //QDir *dir=new QDir(QDir::currentPath());现在的目录 QAppllication::appllicationDirPath()绝对路径
    dir ->setSorting(QDir::Name);  //排列方式
    dir ->sorting();
    filter<<"*.jpg"<<"*.png";
    dir->setNameFilters(filter);
    fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    for(int i = 0; i < (fileInfo->count()); i++)
    {   /*qDebug() <<  fileInfo;*/
        QString number;QString number1;
        QTableWidgetItem *item = new QTableWidgetItem(fileInfo->at(i).baseName());
        QTableWidgetItem *item2 = new QTableWidgetItem(fileInfo->at(i).baseName());
        number = item ->text();number =number.section("-",0,0); item ->setText(number);
        ui->qTableWidget->setItem(i,1,item);
        number1 = item2 ->text();number1 =number1.section("-",1,1); item2 ->setText(number1);
        ui->qTableWidget->setItem(i,2,item2);
        QTableWidgetItem *item1 = new QTableWidgetItem(fileInfo->at(i).created().toString("yyyy-MM-dd hh:mm:ss"));
        ui->qTableWidget->setItem(i,0,item1);
    }
}

void HistoryImage::onContextMenu(const QPoint &pt)
{
    QMenu menu;
    menu.addAction(QString::fromLocal8Bit("打开图片"),this, SLOT(printAllSelect()));
    menu.exec(ui->qTableWidget->mapToGlobal(pt));
}

void HistoryImage::printAllSelect()
{
    QString filename;const QString path=image_path;  //文件夹目录
    QImage *img =new QImage;
    QLabel *label =new QLabel();
    //tableItemList[2]->text()是空的时候 判断也会出错
    QList<QTableWidgetItem*> tableItemList = ui->qTableWidget->selectedItems();
//    qDebug() << tableItemList.count();
    if(tableItemList.count() == 0){return;} //判断是否为空item
    filename = filename.append(path + tableItemList[1]->text() + "-" + tableItemList[2]->text() +".jpg");
    img->load(filename);
    label ->setWindowTitle(QString::fromLocal8Bit("流程编号：")+tableItemList[0]->text()
            +QString::fromLocal8Bit("，时间：")+tableItemList[1]->text()
            +QString::fromLocal8Bit("，相机:")+tableItemList[2]->text());
    label->setPixmap(QPixmap::fromImage(*img));
    label->show();
}

/***下一页***/
void HistoryImage::nextPageHis()
{
    int maxValue = ui->qTableWidget->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    nCurScroller = ui->qTableWidget->verticalScrollBar()->value(); //获得当前scroller值
    if(nCurScroller<maxValue)
        ui->qTableWidget->verticalScrollBar()->setSliderPosition(pageValue+nCurScroller);
    else
        ui->qTableWidget->verticalScrollBar()->setSliderPosition(0);
}
/***上一页***/
void HistoryImage::prePageHis()
{
    int maxValue = ui->qTableWidget->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值25
    nCurScroller = ui->qTableWidget->verticalScrollBar()->value();
    if(nCurScroller>0)
        ui->qTableWidget->verticalScrollBar()->setSliderPosition(nCurScroller-pageValue);
    else
        ui->qTableWidget->verticalScrollBar()->setSliderPosition(maxValue);
}
