/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created: Tue Oct 11 21:48:18 2016
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_registerDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *idLineEdit;
    QLineEdit *pwdLineEdit;
    QLineEdit *rePwdLineEdit;
    QPushButton *confirmPushButton;
    QPushButton *cancelPushButton;
    QLabel *label_4;
    QLineEdit *nameLineEdit;

    void setupUi(QDialog *registerDialog)
    {
        if (registerDialog->objectName().isEmpty())
            registerDialog->setObjectName(QString::fromUtf8("registerDialog"));
        registerDialog->resize(352, 300);
        label = new QLabel(registerDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 72, 15));
        label_2 = new QLabel(registerDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 120, 72, 15));
        label_3 = new QLabel(registerDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 160, 72, 15));
        idLineEdit = new QLineEdit(registerDialog);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setGeometry(QRect(120, 50, 191, 21));
        pwdLineEdit = new QLineEdit(registerDialog);
        pwdLineEdit->setObjectName(QString::fromUtf8("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(120, 120, 191, 21));
        rePwdLineEdit = new QLineEdit(registerDialog);
        rePwdLineEdit->setObjectName(QString::fromUtf8("rePwdLineEdit"));
        rePwdLineEdit->setGeometry(QRect(120, 150, 191, 21));
        confirmPushButton = new QPushButton(registerDialog);
        confirmPushButton->setObjectName(QString::fromUtf8("confirmPushButton"));
        confirmPushButton->setGeometry(QRect(50, 200, 93, 28));
        cancelPushButton = new QPushButton(registerDialog);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));
        cancelPushButton->setGeometry(QRect(220, 200, 93, 28));
        label_4 = new QLabel(registerDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 80, 72, 15));
        nameLineEdit = new QLineEdit(registerDialog);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setGeometry(QRect(120, 80, 191, 21));

        retranslateUi(registerDialog);

        QMetaObject::connectSlotsByName(registerDialog);
    } // setupUi

    void retranslateUi(QDialog *registerDialog)
    {
        registerDialog->setWindowTitle(QApplication::translate("registerDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("registerDialog", "\350\264\246\346\210\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("registerDialog", "\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("registerDialog", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        confirmPushButton->setText(QApplication::translate("registerDialog", "\347\241\256 \350\256\244", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("registerDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("registerDialog", "\346\230\265\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class registerDialog: public Ui_registerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
