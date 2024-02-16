#ifndef CTUNES_H
#define CTUNES_H

#include <QMainWindow>
#include <string> // Add this line to include std::string

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void showSongs();

    int code(int codigo);

    void on_pushButton_6_clicked();

    // Change the parameters to std::string
    void addSong(QString name, QString artist, QString genre, double price);

    int getCodigo(long offset);

    void reviewSong(int code, int stars);

    void downloadSong(int codeSong, QString cliente);

    void songs(QString txtfile);

    void infoSong(int codeSong);

    int initializeSongsFile();

    int initializeCodeFile();

    int initializeDownloadsFile();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    double getSongPrice(int codeSong);

    int getDownloads(int codeSong);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    bool verifyCode(int code);

private:
    Ui::MainWindow *ui;
};
#endif // CTUNES_H

