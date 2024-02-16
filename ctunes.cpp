#include "ctunes.h"
#include "./ui_ctunes.h"
#include <QFile>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("POP");
    ui->comboBox->addItem("ROCK");
    ui->comboBox->addItem("RAP");
    ui->comboBox->addItem("DANCE");
    ui->comboBox->addItem("REGGAE");
    ui->comboBox->addItem("ELECTRONICA");
    ui->comboBox->addItem("RANCHERA");
    QFile file("songs.itn");

    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        // Handle error opening file
        return 1;
    }

    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.

    // Close the file when done
    file.close();

    return 0;
    QFile file("codigos.itn");

    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        // Handle error opening file
        return 1;
    }

    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.

    // Close the file when done
    file.close();

    return 0;
    QFile file("downloads.itn");

    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        // Handle error opening file
        return 1;
    }

    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.

    // Close the file when done
    file.close();

    return 0;

}

int MainWindow::getCodigo(long offset)
{//codigo cancion
    if(offset==0){

    }
    //codigo download
    else if(offset==4){

    }
}
void MainWindow::addSong(String name,String artist,genero genre,double price)
{
    //getCodigo(0);
}
void MainWindow::reviewSong(int code,int stars)
{
    //add stars to song
}
void MainWindow::downloadSong(int codeSong,String cliente)
{

}
String MainWindow::songs(String txtfile)
{//Imprime info de la cancion: CODIGO-TITULO-CANTANTE-DURACION-PRECIO-RATING
    return txtfile;
}
String MainWindow::infoSong(int codeSong)
{
    //IMPRIMIR TODOS LOS DATOS INCLUYENDO EL NUMERO DE DOWNLOADS
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
    showSongs();
}


void MainWindow::on_pushButton_5_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}



int MainWindow::code(int codigo)
{
    return codigo;
}
void MainWindow::showSongs()
{//read file
    QString code;
    QString song;
    QString artist;

    double precioDouble;
    QString genero;
    int stars;
    int reviews;
    QFile file("songs.itn");
    if(!file.open(QIODevice::ReadOnly)){
        //Error
    }else{
        QDataStream in(&file);
        while(!file.atEnd()){
        in<<code;
        in<<song;
        ui->listWidget_2->addItem(song);
        in<<artist;
        in<<genero;
        in<<precioDouble;
        in<<stars;
        in<<reviews;
        }
        file.close();
    }


}


void MainWindow::on_pushButton_6_clicked()
{
    QString code = ui->plainTextEdit->toPlainText();
    QString song = ui->plainTextEdit_2->toPlainText();
    QString artist = ui->plainTextEdit_3->toPlainText();
    QString precio = ui->plainTextEdit_4->toPlainText();
    std::string str=precio.toStdString();
    double precioDouble= std::stod(str);
    QString genero= ui->comboBox->currentText();
    int stars=0;
    int reviews=0;
    //Write file
    QFile file("songs.itn");
    if(!file.open(QIODevice::WriteOnly)){
        //Error
    }
    else{
        QDataStream out(&file);
        out<<code;
        out<<song;
        out<<artist;
        out<<genero;
        out<<precioDouble;
        out<<stars;
        out<<reviews;

    }
}

