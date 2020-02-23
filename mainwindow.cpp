#include "mainwindow.h"
#include "ui_mainwindow.h"

static double numFirst;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //подключение кнопок с цифрами
    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    //подключение кнопок с операциями
    connect(ui->btnSignOfNumber,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->btnProcent,SIGNAL(clicked()), this, SLOT(operations()));
    //подключение кнопок с операциями над числами
    connect(ui->btnAddition,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->btnMultiplication,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->btnSubstraction,SIGNAL(clicked()),this,SLOT(math_operations()));
    connect(ui->btnForDivision,SIGNAL(clicked()),this,SLOT(math_operations()));

    ui->btnAddition->setCheckable(true);
    ui->btnMultiplication->setCheckable(true);
    ui->btnSubstraction->setCheckable(true);
    ui->btnForDivision->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    //создаем объект класса QPushButton
    QPushButton *button = static_cast<QPushButton *>(sender());
    //объявляем переменные
    double allNumbers;
    QString newLabel;
    //для ввода десятичных чисел, начинающихся с нуля
    if (ui->labelResult->text().contains(".") && button->text() == "0")
        newLabel = ui->labelResult->text() + button->text();
    else {
        //для ввода чисел с более чем одним разрядом
        allNumbers = (ui->labelResult->text() + button->text()).toDouble();
        //возможность вводить числа с 15-ю разрядами
        newLabel = QString::number(allNumbers, 'g', 15);
    }
    ui->labelResult->setText(newLabel);
}

void MainWindow::on_btnComma_clicked()
{
    //для возможности ввода только одной точки в числе
    if (!(ui->labelResult->text().contains(".")))
        ui->labelResult->setText(ui->labelResult->text() + ("."));
}

void MainWindow::operations()
{
    //коментарии смотри в функции digits_numbers()
    QPushButton *button = static_cast<QPushButton *>(sender());
    double allNumbers;
    QString newLabel;

    if (button->text() == "+/-") //перемена знакового разряда
    {
        allNumbers = (ui->labelResult->text()).toDouble();
        allNumbers = allNumbers * -1;
        newLabel = QString::number(allNumbers, 'g', 15);
        ui->labelResult->setText(newLabel);
    }
    else if (button->text() == "%")//перевод в проценты
    {
        allNumbers = (ui->labelResult->text()).toDouble();
        allNumbers = allNumbers * 0.01;
        newLabel = QString::number(allNumbers, 'g', 15);
        ui->labelResult->setText(newLabel);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button = static_cast<QPushButton *>(sender());
    numFirst = ui->labelResult->text().toDouble();
    //при нажатии на кнопку с операцией, очищаем label
    ui->labelResult->setText("");
    button->setChecked(true);
}

void MainWindow::on_btnAllClean_clicked()
{
    ui->btnAddition->setChecked(false);
    ui->btnMultiplication->setChecked(false);
    ui->btnForDivision->setChecked(false);
    ui->btnSubstraction->setChecked(false);

     ui->labelResult->setText("0");
}

void MainWindow::on_btnEquality_clicked()
{
    double labelNumber, numSecond;
    QString newLabel;

    numSecond = ui->labelResult->text().toDouble();

    if (ui->btnAddition->isChecked()) {
        labelNumber = numFirst + numSecond;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->labelResult->setText(newLabel);
        ui->btnAddition->setChecked(false);
    }
    else if (ui->btnMultiplication->isChecked()) {
        labelNumber = numFirst * numSecond;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->labelResult->setText(newLabel);
        ui->btnMultiplication->setChecked(false);
    }
    else if (ui->btnSubstraction->isChecked()) {
        labelNumber = numFirst - numSecond;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->labelResult->setText(newLabel);
        ui->btnSubstraction->setChecked(false);
    }
    else if (ui->btnForDivision->isChecked()) {
        if (int(numSecond) == 0)
            ui->labelResult->setText("0");
        else {
            labelNumber = numFirst / numSecond;
            newLabel = QString::number(labelNumber, 'g', 15);
            ui->labelResult->setText(newLabel);
        }
            ui->btnForDivision->setChecked(false);
    }
}
