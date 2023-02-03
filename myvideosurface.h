#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H


#include <QAbstractVideoSurface>
#include <QDebug>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>

class MyVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    MyVideoSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const Q_DECL_OVERRIDE;
    bool isFormatSupported(const QVideoSurfaceFormat &) const Q_DECL_OVERRIDE;    //将视频流中像素格式转换成格式对等的图片格式，若无对等的格式，返回QImage::Format_Invalid
    bool start(const QVideoSurfaceFormat &) Q_DECL_OVERRIDE;                       //只要摄像头开，就会调用
    bool present(const QVideoFrame &) Q_DECL_OVERRIDE;                             //每一帧画面将回到这里处理
    void stop() Q_DECL_OVERRIDE;

signals:
    void frameAvailable(QVideoFrame cloneFrame);

};

#endif // MYVIDEOSURFACE_H
