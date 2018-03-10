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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *lineEditTrigg;
    QLabel *labelTrigg;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBoxCycleNum;
    QLabel *label;
    QSpinBox *spinBoxW;
    QLabel *labelW;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonRun;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelImport;
    QLineEdit *lineEditImport;
    QLabel *labelFreq;
    QLineEdit *lineEditFreq;
    QLabel *labelPhase;
    QLineEdit *lineEditPhase;
    QLabel *labelExportFileName;
    QLineEdit *lineEditExport;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(409, 307);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(230, 70, 160, 76));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        lineEditTrigg = new QLineEdit(formLayoutWidget);
        lineEditTrigg->setObjectName(QStringLiteral("lineEditTrigg"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditTrigg);

        labelTrigg = new QLabel(formLayoutWidget);
        labelTrigg->setObjectName(QStringLiteral("labelTrigg"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelTrigg);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        spinBoxCycleNum = new QSpinBox(formLayoutWidget);
        spinBoxCycleNum->setObjectName(QStringLiteral("spinBoxCycleNum"));
        spinBoxCycleNum->setMinimum(1);
        spinBoxCycleNum->setMaximum(5);

        horizontalLayout_2->addWidget(spinBoxCycleNum);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        spinBoxW = new QSpinBox(formLayoutWidget);
        spinBoxW->setObjectName(QStringLiteral("spinBoxW"));
        spinBoxW->setMinimum(1);
        spinBoxW->setMaximum(999);
        spinBoxW->setValue(50);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxW);

        labelW = new QLabel(formLayoutWidget);
        labelW->setObjectName(QStringLiteral("labelW"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelW);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(250, 180, 111, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonRun = new QPushButton(horizontalLayoutWidget);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout->addWidget(pushButtonRun);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 50, 191, 176));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelImport = new QLabel(verticalLayoutWidget);
        labelImport->setObjectName(QStringLiteral("labelImport"));

        verticalLayout->addWidget(labelImport);

        lineEditImport = new QLineEdit(verticalLayoutWidget);
        lineEditImport->setObjectName(QStringLiteral("lineEditImport"));

        verticalLayout->addWidget(lineEditImport);

        labelFreq = new QLabel(verticalLayoutWidget);
        labelFreq->setObjectName(QStringLiteral("labelFreq"));

        verticalLayout->addWidget(labelFreq);

        lineEditFreq = new QLineEdit(verticalLayoutWidget);
        lineEditFreq->setObjectName(QStringLiteral("lineEditFreq"));

        verticalLayout->addWidget(lineEditFreq);

        labelPhase = new QLabel(verticalLayoutWidget);
        labelPhase->setObjectName(QStringLiteral("labelPhase"));

        verticalLayout->addWidget(labelPhase);

        lineEditPhase = new QLineEdit(verticalLayoutWidget);
        lineEditPhase->setObjectName(QStringLiteral("lineEditPhase"));

        verticalLayout->addWidget(lineEditPhase);

        labelExportFileName = new QLabel(verticalLayoutWidget);
        labelExportFileName->setObjectName(QStringLiteral("labelExportFileName"));

        verticalLayout->addWidget(labelExportFileName);

        lineEditExport = new QLineEdit(verticalLayoutWidget);
        lineEditExport->setObjectName(QStringLiteral("lineEditExport"));

        verticalLayout->addWidget(lineEditExport);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 409, 21));
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
        labelTrigg->setText(QApplication::translate("MainWindow", "Trigger", 0));
        label->setText(QApplication::translate("MainWindow", "Number of cycles", 0));
        labelW->setText(QApplication::translate("MainWindow", "Noise wight", 0));
        pushButtonRun->setText(QApplication::translate("MainWindow", "Run", 0));
        labelImport->setText(QApplication::translate("MainWindow", "Import file name", 0));
        lineEditImport->setText(QApplication::translate("MainWindow", "WH.dat", 0));
        labelFreq->setText(QApplication::translate("MainWindow", "Frequency column name", 0));
        lineEditFreq->setText(QApplication::translate("MainWindow", "Fgen", 0));
        labelPhase->setText(QApplication::translate("MainWindow", "Phase column name", 0));
        lineEditPhase->setText(QApplication::translate("MainWindow", "Theta", 0));
        labelExportFileName->setText(QApplication::translate("MainWindow", "Export File Name", 0));
        lineEditExport->setText(QApplication::translate("MainWindow", "FitedData.txt", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
