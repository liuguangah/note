#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QObject::connect(ui->newAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));
   QObject::connect(ui->openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   connect(ui->saveAsAction,SIGNAL(triggered(bool)),this,SLOT(saveAsFileSlot()));
   QObject::connect(ui->printfActio,SIGNAL(triggered(bool)),this,SLOT(printfFileSlot()));
   QObject::connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(close()));
   QObject::connect(ui->actionColor,SIGNAL(triggered(bool)),this,SLOT(setColorSlot()));
   QObject::connect(ui->actionFont,SIGNAL(triggered(bool)),this,SLOT(setFontSlot()));
   QObject::connect(ui->actionDate,SIGNAL(triggered(bool)),this,SLOT(setCurrentTimeSlot()));

   QObject::connect(ui->actionUndo,SIGNAL(triggered(bool)),ui->textEdit,SLOT(undo()));
   QObject::connect(ui->actionRedo,SIGNAL(triggered(bool)),ui->textEdit,SLOT(redo()));
   QObject::connect(ui->actionCopy,SIGNAL(triggered(bool)),ui->textEdit,SLOT(copy()));
   QObject::connect(ui->actionCut,SIGNAL(triggered(bool)),ui->textEdit,SLOT(cut()));
   QObject::connect(ui->actionPaste,SIGNAL(triggered(bool)),ui->textEdit,SLOT(paste()));
   QObject::connect(ui->actionSeleteAll,SIGNAL(triggered(bool)),ui->textEdit,SLOT(selectAll()));

   QObject::connect(ui->actionAboutQt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
   QObject::connect(ui->action_W,SIGNAL(triggered(bool)),this,SLOT(aboutWebsiteSlot()));

   QObject::connect(ui->action_S,SIGNAL(triggered(bool)),this,SLOT(aboutSoftwareSlot()));
}

MainWindow::~MainWindow()
{

    delete ui;

}

void MainWindow::newFileSlot()
{
    //ui->textEdit->clear();
    QString str = ui->textEdit->toPlainText();
     qDebug()<<"str.isEmpty()"<<str.isEmpty();
    if(ui->textEdit->document()->isModified()&& !str.isEmpty())
    {
        // qDebug()<<"current change";
        //如果有输入刚要跳出提示对话框问是否保存 不保存 取消

    }
    else
    {
        qDebug()<<"not modified";
       // this->clear();
        ui->textEdit->clear();
        this->setWindowTitle("Untitle.txt");
    }
}

void MainWindow::openFileSlot()
{

    //得到文件的名称
    //QString fileName = QFileDialog::getOpenFileName(this,"打开","/home");
    QString fileName = QFileDialog::getOpenFileName(this,"打开",QDir::currentPath());
    qDebug()<<fileName;
    //判断 fileName 是否为空. 注意与 isNull 的区别，isNull 是NULL 值为0 isEmpty是什么都没有为空
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error message","please select a file");
        return;
    }
   //   ui->textEdit->clear();
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::ReadOnly);  //设置权限
    //如果有权限
    if(ok)
    {  //文件流与文本流相关联
        QTextStream in(file);
        //读出流中全有的内容，并设置在 textEdit中
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else
    {
        //file->errorString() 获取错误信息
        QMessageBox::warning(this,"Error message","File Open Error"+file->errorString());
        return;
    }
}
/* 需要实现打印功能 */
void MainWindow::printfFileSlot()
{
/*
 * QPrintDialog printDialog(printer, parent);
if (printDialog.exec() == QDialog::Accepted) {
    // print ...
    }
*/

    QPrinter printer;
    QPrintDialog printfDialog(&printer,this);
    if(printfDialog.exec())
    {
        QTextDocument *doc = ui->textEdit->document();
        doc->print(&printer);
    }
}

void MainWindow::saveAsFileSlot()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,"保存",QDir::currentPath());
    if(saveFileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","please select a filename");
        return;
    }

    QFile *file = new QFile;
    file->setFileName(saveFileName);
    bool isok = file->open(QIODevice::WriteOnly); //写入
    if(isok)
    {
        QTextStream out(file);
        //ui->textEdit->toPlainText();//取出textEdit中的纯文本
        //重定向，写到磁盘中
        out<<ui->textEdit->toPlainText();//取出textEdit中的纯文本
        file->close(); //关闭文件
        delete file;    //删除文件对象
    }
    else
    {
        QMessageBox::warning(this,"Error Message","save error file");
        return;
    }
}

void MainWindow::saveFileSlot()
{
    if(saveFileName.isEmpty())
    {
        this->saveFileSlot();
    }
    else
    {
        QFile *file = new QFile;
        file->setFileName(saveFileName);
        bool isok = file->open(QIODevice::WriteOnly); //写入
        if(isok)
        {
            QTextStream out(file);
            //ui->textEdit->toPlainText();//取出textEdit中的纯文本
            //重定向，写到磁盘中
            out<<ui->textEdit->toPlainText();//取出textEdit中的纯文本
            file->close(); //关闭文件
            delete file;    //删除文件对象
        }
        else
        {
            QMessageBox::warning(this,"Error Message","save error file");
            return;
        }
    }
}

void MainWindow::setFontSlot()
{
   /*  QFont font;
    font.setBold(true);
    ui->textEdit->setFont( font);
    */
    /*bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
    if (ok) {
       // font is set to the font the user selected
    } else {
    // the user canceled the dialog; font is set to the initial
    // value, in this case Times, 12.
    }
  */
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Error set font");
        return;
    }

}

void MainWindow::setColorSlot()
{
    /*
     *  const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

    if (color.isValid()) {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
    */
    const QColor color = QColorDialog::getColor(Qt::black,this,"Select Color");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Error set color");
        return;
    }
}

void MainWindow::setCurrentTimeSlot()
{
    QDateTime dt=QDateTime::currentDateTime();
    QString curtime = dt.toString("yyyy-MM-dd hh:mm:ss");
    ui->textEdit->append(curtime);

}

void MainWindow::aboutWebsiteSlot()
{
    //打开IE
   QDesktopServices::openUrl(QUrl("http://user.qzone.qq.com/306516179/infocenter?ptsig=ji4KQx40nv6fZZ8S7GG0Oe*u0433vKg92Wap5Y9nTDk_"));
   // QDesktopServices::openUrl("c:\\",QUrl::TolerantMode);
   //打开文件夹
/*
   QString path=QDir::currentPath();//获取程序当前目录
   path.replace("/","\\");//将地址中的"/"替换为"\"，因为在Windows下使用的是"\"。
   QProcess::startDetached("explorer "+path);//打开上面获取的目录
*/
}

void MainWindow::aboutSoftwareSlot()
{
    dialog = new about;
    dialog->show();     //非模态的对话框
    //dialog->exec(); //模态的对话框
}
