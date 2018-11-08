#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_radioButton_pressed();

    void on_radioButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_spinBox_valueChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *MatrizP;
    QStandardItemModel *VectorInicial;
    int randInt(int low, int high);
};

#endif // MAINWINDOW_H
