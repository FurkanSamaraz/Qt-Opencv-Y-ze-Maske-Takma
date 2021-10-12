#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    QPixmap pix1("C:/Users/samar/source/repos/opencv4/opencv4/2.jpg");
    QPixmap pix2("C:/Users/samar/source/repos/opencv4/opencv4/3.jpg");
    QPixmap pix3("C:/Users/samar/source/repos/opencv4/opencv4/1.jpg");
    QPixmap pix4("C:/Users/samar/source/repos/opencv4/opencv4/9.jpg");
    QPixmap pix5("C:/Users/samar/source/repos/opencv4/opencv4/10.jpg");
    QPixmap pix6("C:/Users/samar/source/repos/opencv4/opencv4/11.jpg");

    ui->labelmaske1->setPixmap(pix1.scaled(70,70));
    ui->labelmaske1_2->setPixmap(pix2.scaled(70,70));
    ui->labelmaske1_3->setPixmap(pix3.scaled(70,70));
    ui->labelmaske1_4->setPixmap(pix4.scaled(70,70));
    ui->labelmaske1_5->setPixmap(pix5.scaled(70,70));
    ui->labelmaske1_6->setPixmap(pix6.scaled(70,70));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ekran_ac_clicked()
{
 kamera.open(0);
 if(!kamera.isOpened())
 {
     cout<<"Kamera Acilmadi!!!"<<endl;
 }
 else
    {
        cout<<"Kamera Acildi.."<<endl;

        connect(timer,SIGNAL(timeout()),this,SLOT(guncelle_windows()));
        timer->start(20);
    }
}

void MainWindow::on_ekran_kapa_clicked()
{
     disconnect(timer,SIGNAL(timeout()),this,SLOT(guncelle_windows()));
     kamera.release();

     gosterme(resim);

     cout<<"Kamera Kapandi."<<endl;
}

void MainWindow::putMask(Mat src, Point center, Size face_size)
{


    Mat mask1, src1;
    cv::resize(mask, mask1, face_size);
    Rect roi(center.x - face_size.width / 2, center.y - face_size.width / 2, face_size.width, face_size.width);
    src(roi).copyTo(src1);

    ///beyaz bölgeyi şeffaf yapmak için
    Mat mask2, m, m1;
    cvtColor(mask1, mask2, COLOR_BGR2GRAY);
    threshold(mask2, mask2, 230, 255, THRESH_BINARY_INV);

    vector<cv::Mat> maskChannels(3), result_mask(3);
    split(mask1, maskChannels);
    bitwise_and(maskChannels[0], mask2, result_mask[0]);
    bitwise_and(maskChannels[1], mask2, result_mask[1]);

    bitwise_and(maskChannels[2], mask2, result_mask[2]);
    merge(result_mask, m);

    mask2 = 255 - mask2;
    vector<cv::Mat> srcChannels(3);
    split(src1, srcChannels);
    bitwise_and(srcChannels[0], mask2, result_mask[0]);
    bitwise_and(srcChannels[1], mask2, result_mask[1]);
    bitwise_and(srcChannels[2], mask2, result_mask[2]);
    merge(result_mask, m1);

    addWeighted(m, 1, m1, 1, 0, m1);
    m1.copyTo(src(roi));
}

void MainWindow::guncelle_windows()
{
    kamera >> ekran;

    yuz.load("C:/OpencvQTt/opencv-3.4.3/source/data/haarcascades/haarcascade_frontalface_default.xml");

    yuz.detectMultiScale(ekran,cerceve,1.1,2, 0|CV_HAAR_SCALE_IMAGE,cv::Size(ekran.cols/4,ekran.rows/4));

    cvtColor(ekran,ekran,CV_BGR2RGB);

    for (size_t i = 0; i<cerceve.size() ;i++ )
    {
        kamera.retrieve(ekran);
       // rectangle(ekran,cerceve[i].tl(),cerceve[i].br(),cv::Scalar(12,50,255),3);
        cv::Point center(cerceve[i].x + cerceve[i].width * 0.5, cerceve[i].y + cerceve[i].height * 0.5);
         putMask(ekran,center,cv::Size(cerceve[i].width, cerceve[i].height));
    }
gosterme(ekran);
}

void MainWindow::gosterme(Mat &resim)
{
    cvtColor(resim,resim,CV_BGR2RGB);

    qt_resim = QImage((const unsigned char*)(resim.data),resim.cols,resim.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_resim));
    ui->label->resize(ui->label->pixmap()->size());
}




void MainWindow::on_maske1_clicked()
{
     mask = imread(maskeler.toStdString());
}


void MainWindow::on_maske2_clicked()
{
     mask = imread(maskeler2.toStdString());
}


void MainWindow::on_maske3_clicked()
{
     mask = imread(maskeler3.toStdString());
}


void MainWindow::on_maske5_clicked()
{
     mask = imread(maskeler5.toStdString());
}


void MainWindow::on_maske6_clicked()
{
     mask = imread(maskeler6.toStdString());
}


void MainWindow::on_maske7_clicked()
{
     mask = imread(maskeler7.toStdString());
}

