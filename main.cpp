#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QtGui>
#include<QFrame>
#include<QImage>

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//设置主题

    //CommonHelper::setStyle(":/style.qss");
    //CommonHelper::setStyle(":/black.qss");
    // CommonHelper::setStyle(":/white.qss");

MainWindow w;

//    QFrame *frame=new QFrame(MainWindow);
//    frame->resize(400,550);

//    QImage image1;
//    image1.load("C:\\Users\\ASUS\\Desktop\\SJH\\1.0_version\\3.jpg");
//    QImage image2=image1.scaled(400,550);

//    QPalette palette;
//    palette.setBrush(frame->backgroundRole(),QBrush(image2));
//    frame->setPalette(palette);
//    //frame->setMask(plxmap.mask());
//    frame->setAutoFillBackground(true);
//    frame->show();
w.show();
    return a.exec();
}
