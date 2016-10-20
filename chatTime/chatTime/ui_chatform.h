/********************************************************************************
** Form generated from reading UI file 'chatform.ui'
**
** Created: Tue Oct 11 21:48:18 2016
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATFORM_H
#define UI_CHATFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatForm
{
public:
    QFrame *frame;
    QListWidget *displayListWidget;
    QFrame *frame_2;
    QTextEdit *inputTextEdit;
    QPushButton *sendButton;

    void setupUi(QWidget *chatForm)
    {
        if (chatForm->objectName().isEmpty())
            chatForm->setObjectName(QString::fromUtf8("chatForm"));
        chatForm->resize(364, 355);
        frame = new QFrame(chatForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 20, 371, 161));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        displayListWidget = new QListWidget(frame);
        displayListWidget->setObjectName(QString::fromUtf8("displayListWidget"));
        displayListWidget->setGeometry(QRect(10, 10, 341, 141));
        frame_2 = new QFrame(chatForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 180, 371, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        inputTextEdit = new QTextEdit(frame_2);
        inputTextEdit->setObjectName(QString::fromUtf8("inputTextEdit"));
        inputTextEdit->setGeometry(QRect(10, 10, 341, 91));
        sendButton = new QPushButton(chatForm);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(250, 300, 98, 27));

        retranslateUi(chatForm);

        QMetaObject::connectSlotsByName(chatForm);
    } // setupUi

    void retranslateUi(QWidget *chatForm)
    {
        chatForm->setWindowTitle(QApplication::translate("chatForm", "Form", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("chatForm", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chatForm: public Ui_chatForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATFORM_H
