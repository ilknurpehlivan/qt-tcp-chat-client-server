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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox_receiver;
    QTextEdit *textEdit;
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
        MainWindow->resize(772, 615);
        MainWindow->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(170, 40, 451, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox_receiver = new QComboBox(layoutWidget);
        comboBox_receiver->setObjectName("comboBox_receiver");

        verticalLayout->addWidget(comboBox_receiver);

        textEdit = new QTextEdit(layoutWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        lineEdit_message = new QLineEdit(layoutWidget);
        lineEdit_message->setObjectName("lineEdit_message");
        lineEdit_message->setCursor(QCursor(Qt::CursorShape::SizeFDiagCursor));
        lineEdit_message->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

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
        menubar->setGeometry(QRect(0, 0, 772, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gonderici", nullptr));
        lineEdit_message->setText(QString());
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
