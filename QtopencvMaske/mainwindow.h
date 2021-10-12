#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <QImage>
#include <vector>
#include <iostream>
#include <QTimer>
using namespace cv;
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void guncelle_windows();
    void gosterme(Mat &resim);

    void on_ekran_ac_clicked();

    void on_ekran_kapa_clicked();

    void putMask(Mat src,Point center,Size face_size);



    void on_maske1_clicked();

    void on_maske2_clicked();

    void on_maske3_clicked();

    void on_maske5_clicked();

    void on_maske6_clicked();

    void on_maske7_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    VideoCapture kamera;
    Mat ekran;
    Mat resim;
    QImage qt_resim;
    std::vector<cv::Rect> cerceve;
    CascadeClassifier yuz;
    QString maskeler = "C:/Users/samar/source/repos/opencv4/opencv4/2.jpg";
    QString maskeler2 = "C:/Users/samar/source/repos/opencv4/opencv4/3.jpg";
    QString maskeler3 = "C:/Users/samar/source/repos/opencv4/opencv4/1.jpg";
    QString maskeler5 = "C:/Users/samar/source/repos/opencv4/opencv4/9.jpg";
    QString maskeler6 = "C:/Users/samar/source/repos/opencv4/opencv4/10.jpg";
    QString maskeler7 = "C:/Users/samar/source/repos/opencv4/opencv4/11.jpg";
    Mat mask ;

};
#endif // MAINWINDOW_H
