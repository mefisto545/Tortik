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
#include <QtWidgets/QCheckBox>
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
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *labelImport;
    QLineEdit *lineEditImport;
    QLabel *labelFreq;
    QLineEdit *lineEditFreq;
    QLabel *labelPhase;
    QLineEdit *lineEditPhase;
    QLabel *labelExportFileName;
    QLineEdit *lineEditExport;
    QFormLayout *formLayout;
    QLabel *labelTrigg;
    QLineEdit *lineEditTrigg;
    QLabel *labelW;
    QSpinBox *spinBoxW;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBoxCycleNum;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEditSNR;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonRun;
    QFormLayout *formLayout_2;
    QLabel *labelFitStep;
    QLineEdit *lineEditFitStep;
    QLabel *label_3;
    QLineEdit *lineEditMinError;
    QLabel *labelNumOfSteps;
    QLineEdit *lineEditNumOfSteps;
    QCheckBox *checkBoxEnableFitParams;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(550, 520);
        MainWindow->setMinimumSize(QSize(500, 520));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 210, 531, 271));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 525, 191));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelImport = new QLabel(widget);
        labelImport->setObjectName(QStringLiteral("labelImport"));

        verticalLayout->addWidget(labelImport);

        lineEditImport = new QLineEdit(widget);
        lineEditImport->setObjectName(QStringLiteral("lineEditImport"));

        verticalLayout->addWidget(lineEditImport);

        labelFreq = new QLabel(widget);
        labelFreq->setObjectName(QStringLiteral("labelFreq"));

        verticalLayout->addWidget(labelFreq);

        lineEditFreq = new QLineEdit(widget);
        lineEditFreq->setObjectName(QStringLiteral("lineEditFreq"));

        verticalLayout->addWidget(lineEditFreq);

        labelPhase = new QLabel(widget);
        labelPhase->setObjectName(QStringLiteral("labelPhase"));

        verticalLayout->addWidget(labelPhase);

        lineEditPhase = new QLineEdit(widget);
        lineEditPhase->setObjectName(QStringLiteral("lineEditPhase"));

        verticalLayout->addWidget(lineEditPhase);

        labelExportFileName = new QLabel(widget);
        labelExportFileName->setObjectName(QStringLiteral("labelExportFileName"));

        verticalLayout->addWidget(labelExportFileName);

        lineEditExport = new QLineEdit(widget);
        lineEditExport->setObjectName(QStringLiteral("lineEditExport"));

        verticalLayout->addWidget(lineEditExport);


        horizontalLayout_4->addLayout(verticalLayout);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelTrigg = new QLabel(widget);
        labelTrigg->setObjectName(QStringLiteral("labelTrigg"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelTrigg);

        lineEditTrigg = new QLineEdit(widget);
        lineEditTrigg->setObjectName(QStringLiteral("lineEditTrigg"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditTrigg);

        labelW = new QLabel(widget);
        labelW->setObjectName(QStringLiteral("labelW"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelW);

        spinBoxW = new QSpinBox(widget);
        spinBoxW->setObjectName(QStringLiteral("spinBoxW"));
        spinBoxW->setMinimum(1);
        spinBoxW->setMaximum(999);
        spinBoxW->setValue(50);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxW);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        spinBoxCycleNum = new QSpinBox(widget);
        spinBoxCycleNum->setObjectName(QStringLiteral("spinBoxCycleNum"));
        spinBoxCycleNum->setMinimum(1);
        spinBoxCycleNum->setMaximum(10);

        horizontalLayout_2->addWidget(spinBoxCycleNum);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, 0, -1);
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(true);
        checkBox->setChecked(false);

        verticalLayout_2->addWidget(checkBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEditSNR = new QLineEdit(widget);
        lineEditSNR->setObjectName(QStringLiteral("lineEditSNR"));
        lineEditSNR->setEnabled(false);

        horizontalLayout_3->addWidget(lineEditSNR);


        verticalLayout_2->addLayout(horizontalLayout_3);


        formLayout->setLayout(3, QFormLayout::SpanningRole, verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonRun = new QPushButton(widget);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout->addWidget(pushButtonRun);


        formLayout->setLayout(4, QFormLayout::SpanningRole, horizontalLayout);


        horizontalLayout_4->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        labelFitStep = new QLabel(widget);
        labelFitStep->setObjectName(QStringLiteral("labelFitStep"));
        labelFitStep->setAlignment(Qt::AlignCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, labelFitStep);

        lineEditFitStep = new QLineEdit(widget);
        lineEditFitStep->setObjectName(QStringLiteral("lineEditFitStep"));
        lineEditFitStep->setEnabled(false);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEditFitStep);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_3);

        lineEditMinError = new QLineEdit(widget);
        lineEditMinError->setObjectName(QStringLiteral("lineEditMinError"));
        lineEditMinError->setEnabled(false);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEditMinError);

        labelNumOfSteps = new QLabel(widget);
        labelNumOfSteps->setObjectName(QStringLiteral("labelNumOfSteps"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, labelNumOfSteps);

        lineEditNumOfSteps = new QLineEdit(widget);
        lineEditNumOfSteps->setObjectName(QStringLiteral("lineEditNumOfSteps"));
        lineEditNumOfSteps->setEnabled(false);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lineEditNumOfSteps);

        checkBoxEnableFitParams = new QCheckBox(widget);
        checkBoxEnableFitParams->setObjectName(QStringLiteral("checkBoxEnableFitParams"));

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, checkBoxEnableFitParams);


        horizontalLayout_4->addLayout(formLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 550, 20));
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
        labelImport->setText(QApplication::translate("MainWindow", "Import file name", 0));
        lineEditImport->setText(QApplication::translate("MainWindow", "WH.dat", 0));
        labelFreq->setText(QApplication::translate("MainWindow", "Frequency column name", 0));
        lineEditFreq->setText(QApplication::translate("MainWindow", "Fgen", 0));
        labelPhase->setText(QApplication::translate("MainWindow", "Phase column name", 0));
        lineEditPhase->setText(QApplication::translate("MainWindow", "Theta", 0));
        labelExportFileName->setText(QApplication::translate("MainWindow", "Export File Name", 0));
        lineEditExport->setText(QApplication::translate("MainWindow", "FitedData.txt", 0));
        labelTrigg->setText(QApplication::translate("MainWindow", "       Trigger", 0));
        lineEditTrigg->setText(QApplication::translate("MainWindow", "1", 0));
        labelW->setText(QApplication::translate("MainWindow", "  Noise selection", 0));
        label->setText(QApplication::translate("MainWindow", "Number of cycles", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Ignore resonances with low SNR", 0));
        label_2->setText(QApplication::translate("MainWindow", "Min. SNR", 0));
        lineEditSNR->setText(QApplication::translate("MainWindow", "10", 0));
        pushButtonRun->setText(QApplication::translate("MainWindow", "Run", 0));
        labelFitStep->setText(QApplication::translate("MainWindow", "Fit step", 0));
        lineEditFitStep->setText(QApplication::translate("MainWindow", "0.5", 0));
        label_3->setText(QApplication::translate("MainWindow", "MinError", 0));
        lineEditMinError->setText(QApplication::translate("MainWindow", "1e-3", 0));
        labelNumOfSteps->setText(QApplication::translate("MainWindow", "Number of steps", 0));
        lineEditNumOfSteps->setText(QApplication::translate("MainWindow", "1e2", 0));
        checkBoxEnableFitParams->setText(QApplication::translate("MainWindow", "Change fit parameters", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
