/*
历史图片对话框
需图片存放格式.jpg或者.png
命名格式  "旋转角度-流程编号.jpg/png" 如旋转角度 第1流程编号 "2-1.jpg"
 */
/*******************************************************************************
* 类 名         : HistoryImage
* 类功能		   : 历史图片界面
* 输    入         : 无，注意图片存放路径和格式
* 输    出         : 无
*******************************************************************************/
#ifndef HISTORYIMAGE_H
#define HISTORYIMAGE_H

#include <QDialog>
#include <QDir>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QDateTime>
#include <Qstring>
#include <QLabel>
#include <QScrollBar>

#define maxrow 100   //列表最大显示数
#define image_path "C:/Users/Administrator/Desktop/1/"  //存放图片的路径
static int nCurScroller=0; //翻页时的当时滑动条位置
static int pageValue = 10; // 一页显示条数

namespace Ui {
class HistoryImage;
}

class HistoryImage : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryImage(QWidget *parent = 0);
    ~HistoryImage();
    void hisupdate();
    const QString path=image_path;  //文件夹目录
    QDir *dir=new QDir(path);
    QStringList filter;
    QList<QFileInfo> *fileInfo;


private slots:
    void onContextMenu(const QPoint &pt);
    void printAllSelect();
    void nextPageHis();
    void prePageHis();

private:
    Ui::HistoryImage *ui;
};

#endif // HISTORYIMAGE_H
