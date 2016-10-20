#include <QtGui/QApplication>
#include <QTextCodec>

#include "mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    loginDialog loginDlg;
    //registerDialog registerDlg;
    //w.show();
    loginDlg.show();

    return a.exec();
}
