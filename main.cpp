#include "widget.h"

#include "yolo.h"

#include <QApplication>
#include <QFile>

Yolo *yolov8 = new Yolo();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载QSS

    QFile qss_(":/assets/ManjaroMix.qss");
    if( qss_.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss_.readAll());
        a.setStyleSheet(style);
        qss_.close();
    }
    else{
       qDebug("Open failed");
    }

    int target_size = 640;
        float norm_vals[3] = { 1 / 255.f, 1 / 255.f, 1 / 255.f };
        float mean_vals[3] = { 103.53f, 116.28f, 123.675f };

        yolov8->load(target_size, mean_vals,norm_vals);



    Widget w;
    w.show();
    return a.exec();
}
