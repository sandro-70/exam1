#include "ctunes.h"
#include "./ui_ctunes.h"
#include <QFile>
#include <QDataStream>
#include "genero.h"
#include <QDir>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ Genero genre1= Genero::POP;
    Genero genre2= Genero::ROCK;
    Genero genre3= Genero::RAP;
    Genero genre4= Genero::DANCE;
    Genero genre5= Genero::REGGAE;
    Genero genre6= Genero::ELECTRONICA;
    Genero genre7= Genero::RANCHERA;
    ui->setupUi(this);
    ui->comboBox->addItem(enumToString(genre1));
    ui->comboBox->addItem(enumToString(genre2));
    ui->comboBox->addItem(enumToString(genre3));
    ui->comboBox->addItem(enumToString(genre4));
    ui->comboBox->addItem(enumToString(genre5));
    ui->comboBox->addItem(enumToString(genre6));
    ui->comboBox->addItem(enumToString(genre7));
    ui->dateEdit->setDate(QDate::currentDate());
    QString newpath= "C:/Users/ferna/OneDrive/Documentos/Examen1";
    QDir::setCurrent(newpath);
    qDebug()<< initializeSongsFile();
    qDebug()<< initializeCodeFile();
    qDebug()<< initializeDownloadsFile();
    qDebug() << "Current working directory:" << QDir::currentPath();


}
QString enumToString(Genero genre) {
    switch(genre) {
    case Genero::POP: return "POP";
    case Genero::ROCK: return "ROCK";
    case Genero::RAP: return "RAP";
    case Genero::DANCE: return "DANCE";
    case Genero::REGGAE: return "REGGAE";
    case Genero::ELECTRONICA: return "ELECTRONICA";
    case Genero::RANCHERA: return "RANCHERA";
    default: return "Unknown";
    }
}
int MainWindow::initializeSongsFile()
{
    QFile file("songs.itn");

    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // Handle error opening file
        return 1;
    }

    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.


    // Close the file when done
    file.close();

    return 0;
}
int MainWindow::initializeCodeFile()
{
    QFile file("codigos.itn");


    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // Handle error opening file
        return 1;
    }



    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.
    QDataStream out(&file);
    out <<1;
    out <<1;

    // Close the file when done
    file.close();

    return 0;
}
int MainWindow::initializeDownloadsFile()
{
    QFile file("downloads.itn");

    // Open the file in WriteOnly mode and in binary mode
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // Handle error opening file
        return 1;
    }

    // Now you can write binary data to the file using QFile methods like write(), writeData(), etc.

    // Close the file when done
    file.close();

    return 0;
}
int MainWindow::getCodigo(long offset) {
    QFile file("codigos.itn");

    if (!file.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open file for reading and writing!";
        return -1; // Return an error code or handle the error appropriately
    }

    int code;
    int dcode;

    if (offset == 0) { // Reading and writing for the first type of code
        QDataStream in(&file);
        in >> code; // Read the code from the file
        qDebug() << "Original code:" << code;

        // Increment the code
        ++code;
        qDebug() << "Updated code:" << code;

        // Seek to the beginning of the file
        file.seek(0);

        QDataStream out(&file);
        out << code; // Write the updated code to the file
        file.close();
        return code-=1;
    } else if (offset == 4) { // Reading and writing for the second type of code
        file.seek(4);
        QDataStream in(&file);
        in >> dcode; // Read the code from the file

        // Increment the code
        ++dcode;

        // Seek to the correct offset in the file
        file.seek(4);

        QDataStream out(&file);
        out << dcode; // Write the updated code to the file
        file.close();
        return dcode-=1;
    }



}

void MainWindow::addSong(QString name, QString artist, QString genre, double price) {
    QFile file("songs.itn");

    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDataStream out(&file);
    int codigo = getCodigo(0);
    out << codigo;
    out << name;
    out << artist;
    out << genre;
    out << price;
    out << 0;
    out << 0;
    file.close();
}

void MainWindow::reviewSong(int code, int stars) {
    if (stars >= 0 && stars <= 5) {
        QFile file("songs.itn");
        if (!file.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open file for reading and writing!";
            // Handle the error appropriately
        }

        QDataStream in(&file);
        QDataStream out(&file);
        int codigo;
        QString name;
        QString artist;
        QString genre;
        double price;
        int starsRead;
        int reviews;

        while (!in.atEnd()) {
            // Read the record from the file
            in >> codigo >> name >> artist >> genre >> price >> starsRead >> reviews;

            if (codigo == code) {
                // Modify the stars value
                starsRead = stars;
            }

            // Write the record back to the file
            out << codigo << name << artist << genre << price << starsRead << reviews;
        }

        // Close the file
        file.close();
    }
}

void MainWindow::downloadSong(int codeSong,QString cliente)
{        QFile file("downloads.itn");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDate date=QDate::currentDate();
    QString dateString=date.toString("yyyy-MM-dd");
    qDebug() << "Current date string:" << dateString;
    int dcode= getCodigo(4);
    double precio=getSongPrice(codeSong);

    QDataStream out(&file);
    out << dcode;
    out << dateString;
    out << codeSong;
    out << cliente;
    out << precio;


}
double MainWindow::getSongPrice(int codeSong)
{
    QFile file("songs.itn");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDataStream in(&file);
    int codigo;
    QString name;
    QString artist;
    QString genre;
    double price;
    int starsRead;
    int reviews;

    while (!in.atEnd()) {
        // Read the record from the file
        in >> codigo >> name >> artist >> genre >> price >> starsRead >> reviews;

        if (codigo == codeSong) {
            // Modify the stars value
            return price;
        }


}
}
void MainWindow::songs(QString txtfile) {
    QFile file("songs.itn");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDataStream in(&file);
    int codigo;
    QString name;
    QString artist;
    QString genre;
    double price;
    int starsRead;
    int reviews;

    while (!in.atEnd()) {
        // Read the record from the file
        in >> codigo >> name >> artist >> genre >> price >> starsRead >> reviews;
        txtfile = "CODIGO: " + QString::number(codigo) +
                  " TITULO: " + name +
                  " CANTANTE: " + artist +
                  " GENERO: " + genre +
                  " PRECIO: " + QString::number(price) +
                  " RATING: " + QString::number(starsRead/reviews) +
                  " REVIEWS: " + QString::number(reviews);
        ui->listWidget_2->addItem(txtfile);
    }
}

void MainWindow::infoSong(int codeSong) {
    //IMPRIMIR TODOS LOS DATOS INCLUYENDO EL NUMERO DE DOWNLOADS
    QFile file("songs.itn");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDataStream in(&file);
    int codigo;
    QString name;
    QString artist;
    QString genre;
    double price;
    int starsRead;
    int reviews;

    while (!in.atEnd()) {
        // Read the record from the file
        in >> codigo >> name >> artist >> genre >> price >> starsRead >> reviews;
        if (codigo == codeSong) {
            QString info = "CODIGO: " + QString::number(codigo) +
                           " TITULO: " + name +
                           " CANTANTE: " + artist +
                           " GENERO: " + genre +
                           " PRECIO: " + QString::number(price) +
                           " RATING: " + QString::number(starsRead/reviews) +
                           " REVIEWS: " + QString::number(reviews) +
                           " DOWNLOADS: " + QString::number(getDownloads(codeSong));
            ui->listWidget->addItem(info);

        }
    }
}
int MainWindow::getDownloads(int codeSong)
{
    QFile file("downloads.itn");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    int dcode;
    QString dateString;
    int code;
    QString cliente;
    double precio;
    int cont=0;
    QDataStream in(&file);
    while(!in.atEnd()){
    in  << dcode << dateString << code << cliente << precio;
        if(codeSong==code){
        cont+=1;
    }
    } return cont;

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QString code=QString::number(getCodigo(0));
    ui->plainTextEdit->setPlainText(code);

}


void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
    ui->label_17->hide();
     ui->plainTextEdit_10->hide();

}


void MainWindow::on_pushButton_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
    ui->listWidget->hide();

}


void MainWindow::on_pushButton_5_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
    QString txtFile="";
    songs(txtFile);
}



int MainWindow::code(int codigo)
{
    return codigo;
}
void MainWindow::showSongs()
{//read file
    QString code;
    QString name;
    QString artist;

    double precioDouble;
    QString genre;
    int stars;
    int reviews;
    QFile file("songs.itn");
    if(!file.open(QIODevice::ReadOnly)){
        //Error
    }else{
        QDataStream in(&file);
        while(!file.atEnd()){
        in>>code;
        in>>name;
        ui->listWidget_2->addItem(name);
        in>>artist;
        in>>genre;
        in>>precioDouble;
        in>>stars;
        in>>reviews;
        }
        file.close();
    }


}


void MainWindow::on_pushButton_6_clicked()
{
    QString name= ui->plainTextEdit_2->toPlainText();
    QString artist= ui->plainTextEdit_3->toPlainText();
    QString genre= ui->comboBox->currentText();
    QString price= ui->plainTextEdit_4->toPlainText();
    bool ok;
    addSong(name,artist,genre,price.toDouble(&ok));
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_lineEdit_editingFinished()
{
    //Mostrar precio de la cancion ui->plainTextEdit_9->setPlainText(precio)

}


void MainWindow::on_lineEdit_2_editingFinished()
{
    //Show rating field and go back button
    ui->label_17->show();
    ui->plainTextEdit_10->show();

}


void MainWindow::on_lineEdit_3_editingFinished()
{
    ui->listWidget->show();
    QString codeSong=ui->lineEdit_3->text();
    bool ok;
    infoSong(codeSong.toInt(&ok));
}



void MainWindow::on_pushButton_7_clicked()
{   QString codeSong=ui->lineEdit->text();
    QString cliente= ui->plainTextEdit_9->toPlainText();
    bool ok;
    qDebug() << ok;
    if(verifyCode(codeSong.toInt(&ok)))
{
    downloadSong(codeSong.toInt(&ok),cliente);
}
}


void MainWindow::on_pushButton_8_clicked()
{   QString code=ui->lineEdit_2->text();
    bool ok;
    qDebug() << ok;
    QString stars=ui->plainTextEdit_10->toPlainText();
    reviewSong(code.toInt(&ok),stars.toInt(&ok));
}
bool MainWindow::verifyCode(int code)
{
    QFile file("songs.itn");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading and writing!";
        // Handle the error appropriately
    }
    QDataStream in(&file);
    int codigo;
    QString name;
    QString artist;
    QString genre;
    double price;
    int starsRead;
    int reviews;

    while (!in.atEnd()) {
        // Read the record from the file
        in >> codigo >> name >> artist >> genre >> price >> starsRead >> reviews;

        if (codigo == code) {
            // Modify the stars value
            return true;
        }


    }
    return false;
}

