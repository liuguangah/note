#include "mainwindow.h"
#include <QApplication>
#include<QPixmap>
#include<QSplashScreen>
#include<windows.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

  /*  QPixmap pixmap("001.png");
    QSplashScreen splash(pixmap); //显示加载屏幕
    splash.show(); //显示出来
    // app.processEvents(); //显示处理应用程序的过程
    //...
    for(int i=0;i<2;i++)
    {
        Sleep(30000);
    }
    */
    //加载完成后显示 主窗口
    MainWindow w;
    w.setWindowTitle("LG");
    w.show();
    //关闭初化始屏幕
 //   splash.finish(&w);
    return app.exec();

    //eturn a.exec();
}
