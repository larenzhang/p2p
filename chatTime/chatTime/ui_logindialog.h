/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created: Tue Oct 11 21:48:18 2016
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *loginPushButton;
    QPushButton *registerPushButton;
    QPushButton *setPushButton;
    QPushButton *confirmPushButton;
    QPushButton *cancelPushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *idLineEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *pwLineEdit;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *ipLineEdit;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *portLineEdit;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(400, 280);
        label = new QLabel(loginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 72, 15));
        label_2 = new QLabel(loginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 50, 311, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(14);
        label_2->setFont(font);
        loginPushButton = new QPushButton(loginDialog);
        loginPushButton->setObjectName(QString::fromUtf8("loginPushButton"));
        loginPushButton->setGeometry(QRect(90, 230, 93, 28));
        registerPushButton = new QPushButton(loginDialog);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));
        registerPushButton->setGeometry(QRect(230, 230, 93, 28));
        setPushButton = new QPushButton(loginDialog);
        setPushButton->setObjectName(QString::fromUtf8("setPushButton"));
        setPushButton->setGeometry(QRect(340, 230, 51, 28));
        confirmPushButton = new QPushButton(loginDialog);
        confirmPushButton->setObjectName(QString::fromUtf8("confirmPushButton"));
        confirmPushButton->setGeometry(QRect(90, 360, 93, 28));
        cancelPushButton = new QPushButton(loginDialog);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));
        cancelPushButton->setGeometry(QRect(230, 360, 93, 28));
        widget = new QWidget(loginDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 120, 301, 23));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        idLineEdit = new QLineEdit(widget);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));

        horizontalLayout->addWidget(idLineEdit);

        widget1 = new QWidget(loginDialog);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(50, 170, 301, 23));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        pwLineEdit = new QLineEdit(widget1);
        pwLineEdit->setObjectName(QString::fromUtf8("pwLineEdit"));

        horizontalLayout_2->addWidget(pwLineEdit);

        widget2 = new QWidget(loginDialog);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(50, 290, 301, 23));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        ipLineEdit = new QLineEdit(widget2);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));

        horizontalLayout_3->addWidget(ipLineEdit);

        widget3 = new QWidget(loginDialog);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(50, 330, 301, 23));
        horizontalLayout_4 = new QHBoxLayout(widget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(widget3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        portLineEdit = new QLineEdit(widget3);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

        horizontalLayout_4->addWidget(portLineEdit);


        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QApplication::translate("loginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("loginDialog", "ChatTime", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("loginDialog", "Let's enjoy the chat time!", 0, QApplication::UnicodeUTF8));
        loginPushButton->setText(QApplication::translate("loginDialog", "\347\231\273 \345\275\225", 0, QApplication::UnicodeUTF8));
        registerPushButton->setText(QApplication::translate("loginDialog", "\346\263\250 \345\206\214", 0, QApplication::UnicodeUTF8));
        setPushButton->setText(QApplication::translate("loginDialog", "\350\256\276\347\275\256^", 0, QApplication::UnicodeUTF8));
        confirmPushButton->setText(QApplication::translate("loginDialog", "\347\241\256 \350\256\244", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("loginDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("loginDialog", "\350\264\246\346\210\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("loginDialog", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("loginDialog", "IP:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("loginDialog", "PORT:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
