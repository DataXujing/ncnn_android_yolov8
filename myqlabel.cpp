#include "myqlabel.h"

myqlabel::myqlabel(const QString &Titter, QWidget *parent)
    :QLabel(parent)
{
     this->setText(Titter);
     connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

myqlabel::~myqlabel()
{

}

void myqlabel::slotClicked()
{
    this->setPixmap(QPixmap(""));

}
void myqlabel::mousePressEvent(QMouseEvent*)
{
    emit clicked();
}

