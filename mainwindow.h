#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtDebug>
#include <QFileDialog>
#include<QFile>
#include<QDir>
#include<QTextStream>
#include<QMessageBox>
#include<QFontDialog>
#include<QColorDialog>
#include<QFont>
#include<QDateTime>
#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>
#include<QProcess>
#include<QUrl>
#include<QDesktopServices> //用于桌面服务的类
#include<about.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString saveFileName;
    about *dialog;
private slots:
    void newFileSlot();
    void openFileSlot();    //打开一个文本文件
    void saveFileSlot();    //保存文件
    void saveAsFileSlot();  //另存文件
    void printfFileSlot();  //打印文件

    void setFontSlot(); //设置字体
    void setColorSlot();    //设置颜色
    void setCurrentTimeSlot();  //设置时间

    void aboutWebsiteSlot();    //打开一个网站，使用的是默认的浏览器
    void aboutSoftwareSlot();   // 弹出子对话框
};

#endif // MAINWINDOW_H
