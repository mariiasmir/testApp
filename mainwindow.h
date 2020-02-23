#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void digits_numbers();

    void on_btnComma_clicked();

    void operations();

    void on_btnAllClean_clicked();

    void on_btnEquality_clicked();

    void math_operations();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
