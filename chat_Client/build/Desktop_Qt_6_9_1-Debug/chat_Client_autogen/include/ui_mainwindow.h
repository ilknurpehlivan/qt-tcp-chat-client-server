/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser_receivedMessages;
    QLineEdit *lineEdit_message;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_sendMessage;
    QPushButton *pushButton_sendAttachment;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setAcceptDrops(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 50, 451, 461));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser_receivedMessages = new QTextBrowser(layoutWidget);
        textBrowser_receivedMessages->setObjectName("textBrowser_receivedMessages");

        verticalLayout->addWidget(textBrowser_receivedMessages);

        lineEdit_message = new QLineEdit(layoutWidget);
        lineEdit_message->setObjectName("lineEdit_message");

        verticalLayout->addWidget(lineEdit_message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_sendMessage = new QPushButton(layoutWidget);
        pushButton_sendMessage->setObjectName("pushButton_sendMessage");

        horizontalLayout->addWidget(pushButton_sendMessage);

        pushButton_sendAttachment = new QPushButton(layoutWidget);
        pushButton_sendAttachment->setObjectName("pushButton_sendAttachment");

        horizontalLayout->addWidget(pushButton_sendAttachment);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "dinleyici", nullptr));
        lineEdit_message->setPlaceholderText(QCoreApplication::translate("MainWindow", "Mesaj\304\261n\304\261z\304\261 yaz\304\261n...", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send Message", nullptr));
        pushButton_sendAttachment->setText(QCoreApplication::translate("MainWindow", "Send Attachment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
