#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->movie = new QMovie("G:\\QT\\notepad\\102.gif");
    ui->movieLabel->setMovie(this->movie);
    this->movie->start();

    //QObject::connect(ui->pushButton,SIGNAL(clicked(bool)),ui->movieLabel,SLOT()
}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    this->movie->start();
}

void about::on_pushButton_2_clicked()
{
    this->movie->stop();
}
