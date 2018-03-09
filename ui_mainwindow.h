/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *lineEditTrigg;
    QLabel *labelW;
    QLineEdit *lineEditW;
    QLabel *labelTrigg;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonRun;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBoxCycleNum;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 306);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 140, 160, 51));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lineEditTrigg = new QLineEdit(formLayoutWidget);
        lineEditTrigg->setObjectName(QStringLiteral("lineEditTrigg"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditTrigg);

        labelW = new QLabel(formLayoutWidget);
        labelW->setObjectName(QStringLiteral("labelW"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelW);

        lineEditW = new QLineEdit(formLayoutWidget);
        lineEditW->setObjectName(QStringLiteral("lineEditW"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditW);

        labelTrigg = new QLabel(formLayoutWidget);
        labelTrigg->setObjectName(QStringLiteral("labelTrigg"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelTrigg);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(270, 210, 111, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonRun = new QPushButton(horizontalLayoutWidget);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout->addWidget(pushButtonRun);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(220, 120, 160, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        spinBoxCycleNum = new QSpinBox(horizontalLayoutWidget_2);
        spinBoxCycleNum->setObjectName(QStringLiteral("spinBoxCycleNum"));
        spinBoxCycleNum->setMinimum(1);
        spinBoxCycleNum->setMaximum(5);

        horizontalLayout_2->addWidget(spinBoxCycleNum);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lineEditTrigg->setText(QApplication::translate("MainWindow", "1", 0));
        labelW->setText(QApplication::translate("MainWindow", "W", 0));
        lineEditW->setText(QApplication::translate("MainWindow", "50", 0));
        labelTrigg->setText(QApplication::translate("MainWindow", "trigg", 0));
        pushButtonRun->setText(QApplication::translate("MainWindow", "Run", 0));
        label->setText(QApplication::translate("MainWindow", "cycleNum", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
