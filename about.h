#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include<QLabel>
#include<QMovie>
#include<QVBoxLayout>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::about *ui;
    QMovie *movie;
};

#endif // ABOUT_H
