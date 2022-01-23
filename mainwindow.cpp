#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

int get_day_of_date(int year, int month, int day) {
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    switch ((year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7) {
    case 0: return 0;
        break;
    case 1: return 1;
        break;
    case 2: return 2;
        break;
    case 3: return 3;
        break;
    case 4: return 4;
        break;
    case 5: return 5;
        break;
    case 6: return 6;
        break;
    }
}

QDate date;

int year;
int month;
int day;
int size;
int d_day[7] = {9,9,9,9,9,9,9};
int feb[12] = {31,28,31,30,31,30,31,31,30,31,30,31 };
int count;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    date = ui->dateEdit->date();
    year = date.year();
    month = date.month();
    day = date.day();

    if(ui->pbSun->isChecked()) {
        d_day[0] = 0;
    }
    if(ui->pbMon->isChecked()) {
        d_day[1] = 1;
    }
    if(ui->pbTue->isChecked()) {
        d_day[2] = 2;
    }
    if(ui->pbWed->isChecked()) {
        d_day[3] = 3;
    }
    if(ui->pbThu->isChecked()) {
        d_day[4] = 4;
    }
    if(ui->pbFri->isChecked()) {
        d_day[5] = 5;
    }
    if(ui->pbSat->isChecked()) {
        d_day[6] = 6;
    }

    count = ui->spinBox->value();

    //seting count
    while (count != 0) {

        int today = get_day_of_date(year, month, day);
        for (int i = 0; i < (sizeof(d_day)/sizeof(d_day[0])); i++) {
            if (today == d_day[i]) {
                count--;
            }
        }
        if (day == feb[month-1]) {
            if (month == 12) {
                year += 1;
                month = 1;
                day = 1;
            }
            else {
                month += 1;
                day = 1;
            }
        }
        else {
            day += 1;
        }
    }
    QMessageBox::about(this, "result", QString("End of date is [%1 - %2 - %3]").arg(year).arg(month).arg(day-1));
}

