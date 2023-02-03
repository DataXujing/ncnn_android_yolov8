#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QDebug>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>
#include <QCameraImageCapture>
#include <myvideosurface.h>
#include <QImage>
#include <QPainter>
#include <QScreen>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

void NV21_T_RGB(unsigned int width , unsigned int height , unsigned char *yuyv , unsigned char *rgb);

private:
    Ui::Widget *ui;
    QCamera *camera;
    QCameraImageCapture *capture;
    QCameraViewfinder *viewfinder;
    MyVideoSurface *mySurface;
    QImage videoImg;

public slots:
    void displayImage(int ,QImage image);
    void rcvFrame(QVideoFrame);                            //接收图像帧数据
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_label_linkHovered(const QString &link);
};

#endif // MAINWINDOW_H
