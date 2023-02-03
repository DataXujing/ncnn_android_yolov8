

#include "widget.h"
#include "ui_widget.h"
#include "yolo.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QTest>

extern Yolo * yolov8;
const float prob_threshold = 0.25f;
const float nms_threshold = 0.45f;

cv::Mat ChangeToMat(QImage image)
{

//    image = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat tmp(image.height(),image.width(),CV_8UC3,(uchar*)image.bits(),image.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cv::cvtColor(tmp, result, cv::COLOR_BGR2RGB);
        return result;
}

QImage ChangeToQIamge(cv::Mat mat)
{
    cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    QImage qim((const unsigned char*)mat.data, mat.cols, mat.rows, mat.step,
    QImage::Format_RGB888);
    return qim;
}



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    camera=new QCamera;//摄像头
    capture = new QCameraImageCapture(camera);
    viewfinder=new QCameraViewfinder(this);//取景器

    // static QMetaObject::Connection connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member,
    // Qt::ConnectionType = Qt::AutoConnection);
    //第一个参数sender为发送对象；第二个参数为发送对象里面的一个信号；第三个参数为接收对象；第四个参数为接收对象里面的槽函数。一般我们使用发送者触发信号，然后执行接收者的槽函数。
    QObject::connect(capture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));
    camera->setCaptureMode(QCamera::CaptureStillImage);
//    camera->setViewfinder(viewfinder);
    mySurface = new MyVideoSurface();
    camera->setViewfinder(mySurface);
    //处理myvideosurface中每一帧视频
    connect(mySurface, SIGNAL(frameAvailable(QVideoFrame)), this, SLOT(rcvFrame(QVideoFrame)), Qt::DirectConnection);

    camera->start(); //启动摄像头

    //获取摄像头支持的分辨率、帧率等参数
//    QList<QCameraViewfinderSettings > ViewSets = camera->supportedViewfinderSettings();
//    int i = 0;
//    qDebug() << "viewfinderResolutions sizes.len = " << ViewSets.length();
//    foreach (QCameraViewfinderSettings ViewSet, ViewSets) {
//        qDebug() << i++ <<" max rate = " << ViewSet.maximumFrameRate() << "min rate = "<< ViewSet.minimumFrameRate() << "resolution "<<ViewSet.resolution()<<\
//                    "Format="<<ViewSet.pixelFormat()<<""<<ViewSet.pixelAspectRatio();
//    }

    //设置摄像头参数
    QCameraViewfinderSettings camerasettings;
    camerasettings.setResolution(640,480);
    camerasettings.setPixelFormat(QVideoFrame::Format_NV21);
    camerasettings.setMaximumFrameRate(30);
    camerasettings.setMinimumFrameRate(30);

    camera->setViewfinderSettings(camerasettings);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::displayImage(int ,QImage image)
{
    image=image.convertToFormat(QImage::Format_RGB888);

    cv::Mat cv_image;
    cv_image = ChangeToMat(image);

    std::vector<Object> objects;
    yolov8->detect(cv_image, objects, prob_threshold, nms_threshold);
    yolov8->draw(cv_image, objects);

    QImage q_image = ChangeToQIamge(cv_image);

    ui->label->setPixmap(QPixmap::fromImage(q_image));
   //    qDebug() << image.size();

//    QTest::qSleep(5000);
//    ui->label->setPixmap(QPixmap(""));//清除图片

}

void Widget::rcvFrame(QVideoFrame m_currentFrame)
{
//    qDebug() << "received" << m_currentFrame.size();

    m_currentFrame.map(QAbstractVideoBuffer::ReadOnly);
//    unsigned char *pix_ptr = m_currentFrame.bits();
//    qDebug("%d %d %d %d", *pix_ptr, *(pix_ptr+1), *(pix_ptr+2), *(pix_ptr+3));
        //将视频帧转化成QImage,devicePixelRatio设备像素比，bytesPerLine一行的像素字节（1280*4=5120）

    videoImg = QImage(m_currentFrame.width(), m_currentFrame.height(), QImage::Format_RGB888);
    NV21_T_RGB(m_currentFrame.width(), m_currentFrame.height(), m_currentFrame.bits(), videoImg.bits());
//    videoImg =  QImage(m_currentFrame.bits(),
//                   m_currentFrame.width(),
//                   m_currentFrame.height(),
//                   QImage::Format_Grayscale8).copy();       //这里要做一个copy,因为char* pdata在emit后释放了
//    videoImg = videoImg.mirrored(true, false);                          //水平翻转，原始图片是反的

//    qDebug() <<  "image" << videoImg;  //可以看看输出啥东西
//    QString currentTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
//    QString savefile = QString("E:/study/QT/opencamera/opencamera/%1.jpg").arg(currentTime);
//    qDebug() << videoImg.save(savefile);
    m_currentFrame.unmap();                                         //释放map拷贝的内存
    QCameraInfo cameraInfo(*camera); // needed to get the camera sensor position and orientation

//    // Get the current display orientation
//    const QScreen *screen = QGuiApplication::primaryScreen();
//    const int screenAngle = screen->angleBetween(screen->nativeOrientation(), screen->orientation());

//    int rotation;
//    if (cameraInfo.position() == QCamera::BackFace) {
//        rotation = (cameraInfo.orientation() - screenAngle) % 360;
//    } else {
//        // Front position, compensate the mirror
//        rotation = (360 - cameraInfo.orientation() + screenAngle) % 360;
//    }

//    // Rotate the frame so it always shows in the correct orientation
    videoImg = videoImg.transformed(QTransform().rotate(90));

    QWidget::update();                                              //更新了，就会触发paintEvent画图
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    QRect rect(0, 0, 480, 640);
    //this->frameGeometry().width() << this->frameGeometry().height();
    QRect rect(5, 5, this->frameGeometry().width()-10, this->frameGeometry().height()-10);


    //设置画笔
    QPen pen;
    pen.setWidth(5);                    //线宽
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);        //实线
    pen.setCapStyle(Qt::FlatCap);       //线端点样式
    pen.setJoinStyle(Qt::BevelJoin);    //线连接点样式
    painter.setPen(pen);
    painter.drawRect(rect);

    //qDebug() <<  "image" << videoImg;     //第一次输出的QImage(null)
    //只要窗口启动，就会触发paintEvent，所以第一次是null,不可以画图。
    if(videoImg != QImage(nullptr)){
        painter.drawImage(rect, videoImg);
    }
}


void Widget::on_pushButton_clicked()
{
    capture->capture();

}

void Widget::NV21_T_RGB(unsigned int width , unsigned int height , unsigned char *yuyv , unsigned char *rgb)
{
    const int nv_start = width * height ;
    unsigned int i, j, index = 0, rgb_index = 0;
    unsigned char y, u, v;
    int r, g, b, nv_index = 0;

    for(i = 0; i < height; i++){
        for(j = 0; j < width; j ++){
            //nv_index = (rgb_index / 2 - width / 2 * ((i + 1) / 2)) * 2;
            nv_index = i / 2  * width + j - j % 2;

            y = yuyv[rgb_index];
            u = yuyv[nv_start + nv_index ];
            v = yuyv[nv_start + nv_index + 1];

            r = y + (140 * (v-128))/100;  //r
            g = y - (34 * (u-128))/100 - (71 * (v-128))/100; //g
            b = y + (177 * (u-128))/100; //b

            if(r > 255)   r = 255;
            if(g > 255)   g = 255;
            if(b > 255)   b = 255;
            if(r < 0)     r = 0;
            if(g < 0)     g = 0;
            if(b < 0)     b = 0;

            index = rgb_index % width + (height - i - 1) * width;
            //rgb[index * 3+0] = b;
            //rgb[index * 3+1] = g;
            //rgb[index * 3+2] = r;

            //颠倒图像
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 1] = b;
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 2] = g;
            //rgb[height * width * 3 - i * width * 3 - 3 * j - 3] = r;

            //正面图像
            rgb[i * width * 3 + 3 * j + 0] = b;
            rgb[i * width * 3 + 3 * j + 1] = g;
            rgb[i * width * 3 + 3 * j + 2] = r;

            rgb_index++;
        }
    }
//    return 0;
}


void Widget::on_label_linkHovered(const QString &link)
{

}
