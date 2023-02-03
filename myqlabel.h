#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QObject>
#include <QLabel>
#include <QMessageBox>


class myqlabel : public QLabel
{
    Q_OBJECT
public:
    myqlabel(const QString &Titter,QWidget *parent=0);
    ~myqlabel();
signals:
    //点击信号
    void clicked();
public slots:
    //点击信号响应槽
    void slotClicked();
protected:
    //鼠标按下事件
    void mousePressEvent(QMouseEvent*/* event*/);
};


#endif // MYQLABEL_H
