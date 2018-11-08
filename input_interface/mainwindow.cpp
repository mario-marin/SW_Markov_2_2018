#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTime>
#include <QTextStream>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MatrizP = new QStandardItemModel (this);
    VectorInicial = new QStandardItemModel (this);
    ui->tableView->setModel(MatrizP);
    ui->tableView_2->setModel(VectorInicial);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}
int MainWindow::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    QString filename =QFileDialog::getOpenFileName(
                this,
                tr("Abrir Archivo"),
                "C://",
                "Archivo de texto (*.txt)");
   ui->lineEdit_2->setText(filename);
}

void MainWindow::on_radioButton_pressed()
{
    ui->frame->setEnabled(true);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->frame->setEnabled(false);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    MatrizP->setColumnCount(arg1);
    MatrizP->setRowCount(arg1);
    VectorInicial->setColumnCount(arg1);
    VectorInicial->setRowCount(1);
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->radioButton_2->isChecked()){
        const int rowCount = MatrizP->rowCount();
        for (int ix=0; ix<rowCount; ix++){
            int n=10000;
            for (int jy=0; jy<rowCount; jy++){
                double probabilidad;
                if(jy==rowCount-1){
                    probabilidad=(n+ 0.0)/10000;
                }
                else{
                     int val=randInt(0,n);
                    n-=val;
                    probabilidad=(val+ 0.0)/10000;
                }
                QString Value = QString::number(probabilidad);

                MatrizP->setItem(ix,jy,new QStandardItem (Value));
            }
        }
    }
    else if (ui->radioButton->isChecked()){

        const int rowCount = MatrizP->rowCount();
        for (int ix=0; ix<rowCount; ix++){
            int n=40;

            for (int jy=0; jy<rowCount; jy++){
                int val=randInt(0,n);
                QString Value = QString::number(val);
                MatrizP->setItem(ix,jy,new QStandardItem (Value));
            }
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableView->setEnabled(true);
    ui->spinBox->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile archivo("input.txt");
        QString cantidadNodos = QString::number(ui->spinBox->value());
        QString v_inicial;
        QString separador = "-------------";
        if(archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream datosArchivo(&archivo);
            datosArchivo << cantidadNodos <<endl;
            const int rowCount = MatrizP->rowCount();
            for (int jy=0; jy<rowCount; jy++){
                v_inicial+= VectorInicial->item(0,jy)->text() + " ";
            }
            datosArchivo << v_inicial <<endl;
            datosArchivo << separador << endl;
            for (int ix=0; ix<rowCount; ix++){
                for (int jy=0; jy<rowCount; jy++){
                    QString linea = QString::number(ix)+" "+QString::number(jy)+" "+MatrizP->item(ix,jy)->text();
                    datosArchivo << linea << endl;
                }
            }

        }
        archivo.close();

        bool esContinua = ui->radioButton->isChecked();
        if (esContinua){
            bool q_matrix = ui->radioButton_3->isChecked();
            bool p_matrix = ui->radioButton_4->isChecked();
            double delta_T = ui->lineEdit_2->text().toDouble();
            if(q_matrix){
                //se calcula con la matriz q
            }
            if(p_matrix){
                //se calcula con la matriz p
            }
            else{
                // se calcula con el metodo clasico
            }
        }

        else{

            //aqui se debe llamar a la funcion que realiza los calculos para la Variable discreta.
        }
}

