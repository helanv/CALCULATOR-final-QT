#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

double num_first;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    // Активация +/-, %
    connect(ui->pushButton_plus_minus,SIGNAL(clicked()),this,SLOT(mathOperations()));
    connect(ui->pushButton_procent,SIGNAL(clicked()),this,SLOT(mathOperations()));

    // Активация +, -, /, x
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(calculateOperations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(calculateOperations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(calculateOperations()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(calculateOperations()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// цифры ( нажатие )
void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();

    double allNumbers;
    QString stringForNumbers;

    // реализация нуля после точки
    if(ui->result_show->text().contains(".") && button->text() == "0"){
        stringForNumbers = ui->result_show->text() + button->text();
    } else {
        allNumbers = (ui->result_show->text() + button->text()).toDouble();
        stringForNumbers = QString::number(allNumbers, 'g', 15);
    }

    ui->result_show->setText(stringForNumbers);
}

// кнопка точки
void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_show->text().contains('.'))) // проверка, есть ли точка? только 1 точка используется
    ui->result_show->setText(ui->result_show->text() + "."); // выводим точку
}

// математические операции
void MainWindow::mathOperations()
{
    QPushButton *button = (QPushButton *)sender();

    double allNumbers;
    QString stringForNumbers;

    if(button->text() == "+/-"){
        allNumbers = (ui->result_show->text()).toDouble();
        allNumbers = allNumbers * -1; // применение +/- в калькуляторе
        stringForNumbers = QString::number(allNumbers, 'g', 15);

        ui->result_show->setText(stringForNumbers);
   } else if(button->text() == "%"){
        allNumbers = (ui->result_show->text()).toDouble();
        allNumbers = allNumbers * 0.01; // применение +/- в калькуляторе
        stringForNumbers = QString::number(allNumbers, 'g', 15);

        ui->result_show->setText(stringForNumbers);
   }
}

// реализация счета - +,  -,  /,  x
void MainWindow::calculateOperations()
{
    QPushButton *button = (QPushButton *)sender();

    num_first = ui->result_show->text().toDouble();
    ui->result_show->setText("");

    button->setChecked(true);
}

// очиста калькулятора, клавиша AC
void MainWindow::on_pushButton_reset_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    ui->result_show->setText("0");
}

// сумма, клавиша =
void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, num_second;
    QString stringForNumbers;

    num_second = ui->result_show->text().toDouble();

        //плюс
    if(ui->pushButton_plus->isChecked()){
        labelNumber = num_first + num_second;
        stringForNumbers = QString::number(labelNumber, 'g', 15);

        ui->result_show->setText(stringForNumbers);
        ui->pushButton_plus->setChecked(false);

        //минус
    } else if(ui->pushButton_minus->isChecked()){
        labelNumber = num_first - num_second;
        stringForNumbers = QString::number(labelNumber, 'g', 15);

        ui->result_show->setText(stringForNumbers);
        ui->pushButton_minus->setChecked(false);

        //деление
    } else if(ui->pushButton_divide->isChecked()){
        if(num_second == 0){
            ui->result_show->setText("Error");  // проверка деления на ноль
        } else {
            labelNumber = num_first / num_second;
            stringForNumbers = QString::number(labelNumber, 'g', 15);

            ui->result_show->setText(stringForNumbers);
        }

        ui->pushButton_divide->setChecked(false);

        //умножение
    } else if(ui->pushButton_mult->isChecked()){
        labelNumber = num_first * num_second;
        stringForNumbers = QString::number(labelNumber, 'g', 15);

        ui->result_show->setText(stringForNumbers);
        ui->pushButton_mult->setChecked(false);
    }
}
