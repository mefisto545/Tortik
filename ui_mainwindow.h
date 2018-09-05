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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *customPlot;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelImport;
    QLineEdit *lineEditImport;
    QPushButton *pushButtonImportFile;
    QPushButton *pushButtonRun;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelExportFileName;
    QLineEdit *lineEditExport;
    QPushButton *pushButtonExportFile;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelFreq;
    QLineEdit *lineEditFreq;
    QLabel *labelPhase;
    QLineEdit *lineEditPhase;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTrigg;
    QLineEdit *lineEditTrigg;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelW;
    QSpinBox *spinBoxW;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label;
    QSpinBox *spinBoxCycleNum;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_2;
    QLineEdit *lineEditSNR;
    QGroupBox *groupBox;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *lineEditRf;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEditW;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_10;
    QLineEdit *lineEditHeight;
    QCheckBox *checkBoxShowFitCurve;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBoxEnableFitParams;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEditMinError;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelNumOfSteps;
    QLineEdit *lineEditNumOfSteps;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QLineEdit *lineEditP;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QLineEdit *lineEditSmooth;
    QComboBox *comboBox;
    QCheckBox *checkBoxLine;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_5;
    QLineEdit *lineEditSlope;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QLineEdit *lineEditInter;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1297, 500);
        MainWindow->setMinimumSize(QSize(1, 1));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(670, 20, 621, 441));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 1, 651, 121));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(651, 121));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 20, 651, 101));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMaximumSize);
        labelImport = new QLabel(layoutWidget1);
        labelImport->setObjectName(QStringLiteral("labelImport"));

        horizontalLayout_6->addWidget(labelImport);

        lineEditImport = new QLineEdit(layoutWidget1);
        lineEditImport->setObjectName(QStringLiteral("lineEditImport"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditImport->sizePolicy().hasHeightForWidth());
        lineEditImport->setSizePolicy(sizePolicy1);
        lineEditImport->setMinimumSize(QSize(420, 0));
        lineEditImport->setSizeIncrement(QSize(10, 10));

        horizontalLayout_6->addWidget(lineEditImport);

        pushButtonImportFile = new QPushButton(layoutWidget1);
        pushButtonImportFile->setObjectName(QStringLiteral("pushButtonImportFile"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(21);
        sizePolicy2.setVerticalStretch(21);
        sizePolicy2.setHeightForWidth(pushButtonImportFile->sizePolicy().hasHeightForWidth());
        pushButtonImportFile->setSizePolicy(sizePolicy2);
        pushButtonImportFile->setMaximumSize(QSize(21, 21));
        pushButtonImportFile->setBaseSize(QSize(0, 0));

        horizontalLayout_6->addWidget(pushButtonImportFile);

        pushButtonRun = new QPushButton(layoutWidget1);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));

        horizontalLayout_6->addWidget(pushButtonRun);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        labelExportFileName = new QLabel(layoutWidget1);
        labelExportFileName->setObjectName(QStringLiteral("labelExportFileName"));

        horizontalLayout_5->addWidget(labelExportFileName);

        lineEditExport = new QLineEdit(layoutWidget1);
        lineEditExport->setObjectName(QStringLiteral("lineEditExport"));
        lineEditExport->setMinimumSize(QSize(420, 0));
        lineEditExport->setMaximumSize(QSize(420, 16777215));

        horizontalLayout_5->addWidget(lineEditExport);

        pushButtonExportFile = new QPushButton(layoutWidget1);
        pushButtonExportFile->setObjectName(QStringLiteral("pushButtonExportFile"));
        pushButtonExportFile->setMinimumSize(QSize(21, 21));
        pushButtonExportFile->setMaximumSize(QSize(21, 21));
        pushButtonExportFile->setSizeIncrement(QSize(0, 0));

        horizontalLayout_5->addWidget(pushButtonExportFile);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);

        horizontalLayout_5->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        labelFreq = new QLabel(layoutWidget1);
        labelFreq->setObjectName(QStringLiteral("labelFreq"));

        horizontalLayout_7->addWidget(labelFreq);

        lineEditFreq = new QLineEdit(layoutWidget1);
        lineEditFreq->setObjectName(QStringLiteral("lineEditFreq"));
        lineEditFreq->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_7->addWidget(lineEditFreq);

        labelPhase = new QLabel(layoutWidget1);
        labelPhase->setObjectName(QStringLiteral("labelPhase"));

        horizontalLayout_7->addWidget(labelPhase);

        lineEditPhase = new QLineEdit(layoutWidget1);
        lineEditPhase->setObjectName(QStringLiteral("lineEditPhase"));
        lineEditPhase->setMaximumSize(QSize(135, 16777215));

        horizontalLayout_7->addWidget(lineEditPhase);


        verticalLayout_4->addLayout(horizontalLayout_7);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(3, 129, 653, 338));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_5 = new QGroupBox(layoutWidget2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(320, 171));
        groupBox_5->setMaximumSize(QSize(16777215, 16777215));
        layoutWidget3 = new QWidget(groupBox_5);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 20, 320, 151));
        verticalLayout_8 = new QVBoxLayout(layoutWidget3);
        verticalLayout_8->setSpacing(5);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTrigg = new QLabel(layoutWidget3);
        labelTrigg->setObjectName(QStringLiteral("labelTrigg"));

        horizontalLayout_2->addWidget(labelTrigg);

        lineEditTrigg = new QLineEdit(layoutWidget3);
        lineEditTrigg->setObjectName(QStringLiteral("lineEditTrigg"));
        lineEditTrigg->setMinimumSize(QSize(192, 0));
        lineEditTrigg->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_2->addWidget(lineEditTrigg);


        verticalLayout_8->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelW = new QLabel(layoutWidget3);
        labelW->setObjectName(QStringLiteral("labelW"));

        horizontalLayout_3->addWidget(labelW);

        spinBoxW = new QSpinBox(layoutWidget3);
        spinBoxW->setObjectName(QStringLiteral("spinBoxW"));
        spinBoxW->setMinimumSize(QSize(192, 0));
        spinBoxW->setMaximumSize(QSize(192, 16777215));
        spinBoxW->setMinimum(1);
        spinBoxW->setMaximum(999);
        spinBoxW->setValue(50);

        horizontalLayout_3->addWidget(spinBoxW);


        verticalLayout_8->addLayout(horizontalLayout_3);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label = new QLabel(layoutWidget3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_15->addWidget(label);

        spinBoxCycleNum = new QSpinBox(layoutWidget3);
        spinBoxCycleNum->setObjectName(QStringLiteral("spinBoxCycleNum"));
        spinBoxCycleNum->setMinimumSize(QSize(192, 0));
        spinBoxCycleNum->setMaximumSize(QSize(192, 16777215));
        spinBoxCycleNum->setSizeIncrement(QSize(236, 0));
        spinBoxCycleNum->setMinimum(1);
        spinBoxCycleNum->setMaximum(25);
        spinBoxCycleNum->setValue(5);

        horizontalLayout_15->addWidget(spinBoxCycleNum);


        verticalLayout_8->addLayout(horizontalLayout_15);

        checkBox = new QCheckBox(layoutWidget3);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(true);
        checkBox->setMinimumSize(QSize(310, 0));
        checkBox->setMaximumSize(QSize(310, 16777215));
        checkBox->setChecked(false);

        verticalLayout_8->addWidget(checkBox);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_16->addWidget(label_2);

        lineEditSNR = new QLineEdit(layoutWidget3);
        lineEditSNR->setObjectName(QStringLiteral("lineEditSNR"));
        lineEditSNR->setEnabled(false);
        lineEditSNR->setMinimumSize(QSize(192, 0));
        lineEditSNR->setMaximumSize(QSize(192, 16777215));
        lineEditSNR->setSizeIncrement(QSize(236, 0));

        horizontalLayout_16->addWidget(lineEditSNR);


        verticalLayout_8->addLayout(horizontalLayout_16);


        verticalLayout_3->addWidget(groupBox_5);

        groupBox = new QGroupBox(layoutWidget2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(313, 111));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(2, 20, 321, 116));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 8, 5);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        lineEditRf = new QLineEdit(layoutWidget4);
        lineEditRf->setObjectName(QStringLiteral("lineEditRf"));
        lineEditRf->setMinimumSize(QSize(192, 0));
        lineEditRf->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_8->addWidget(lineEditRf);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(layoutWidget4);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        lineEditW = new QLineEdit(layoutWidget4);
        lineEditW->setObjectName(QStringLiteral("lineEditW"));
        lineEditW->setMinimumSize(QSize(192, 0));
        lineEditW->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_9->addWidget(lineEditW);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(0);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_10 = new QLabel(layoutWidget4);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_17->addWidget(label_10);

        lineEditHeight = new QLineEdit(layoutWidget4);
        lineEditHeight->setObjectName(QStringLiteral("lineEditHeight"));
        lineEditHeight->setMinimumSize(QSize(192, 0));
        lineEditHeight->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_17->addWidget(lineEditHeight);


        verticalLayout->addLayout(horizontalLayout_17);

        checkBoxShowFitCurve = new QCheckBox(layoutWidget4);
        checkBoxShowFitCurve->setObjectName(QStringLiteral("checkBoxShowFitCurve"));

        verticalLayout->addWidget(checkBoxShowFitCurve);


        verticalLayout_3->addWidget(groupBox);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_3 = new QGroupBox(layoutWidget2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(321, 111));
        groupBox_3->setMaximumSize(QSize(16777215, 16777215));
        layoutWidget5 = new QWidget(groupBox_3);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(0, 20, 321, 89));
        verticalLayout_5 = new QVBoxLayout(layoutWidget5);
        verticalLayout_5->setSpacing(5);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_5->setContentsMargins(5, 5, 5, 5);
        checkBoxEnableFitParams = new QCheckBox(layoutWidget5);
        checkBoxEnableFitParams->setObjectName(QStringLiteral("checkBoxEnableFitParams"));
        checkBoxEnableFitParams->setMinimumSize(QSize(311, 0));
        checkBoxEnableFitParams->setMaximumSize(QSize(311, 16777215));

        verticalLayout_5->addWidget(checkBoxEnableFitParams);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(layoutWidget5);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEditMinError = new QLineEdit(layoutWidget5);
        lineEditMinError->setObjectName(QStringLiteral("lineEditMinError"));
        lineEditMinError->setEnabled(false);
        lineEditMinError->setMinimumSize(QSize(192, 0));
        lineEditMinError->setMaximumSize(QSize(192, 16777215));

        horizontalLayout->addWidget(lineEditMinError);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        labelNumOfSteps = new QLabel(layoutWidget5);
        labelNumOfSteps->setObjectName(QStringLiteral("labelNumOfSteps"));

        horizontalLayout_10->addWidget(labelNumOfSteps);

        lineEditNumOfSteps = new QLineEdit(layoutWidget5);
        lineEditNumOfSteps->setObjectName(QStringLiteral("lineEditNumOfSteps"));
        lineEditNumOfSteps->setEnabled(false);
        lineEditNumOfSteps->setMinimumSize(QSize(192, 0));
        lineEditNumOfSteps->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_10->addWidget(lineEditNumOfSteps);


        verticalLayout_5->addLayout(horizontalLayout_10);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(layoutWidget2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(320, 217));
        groupBox_4->setMaximumSize(QSize(16777215, 16777215));
        layoutWidget6 = new QWidget(groupBox_4);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(0, 20, 320, 177));
        verticalLayout_6 = new QVBoxLayout(layoutWidget6);
        verticalLayout_6->setSpacing(5);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(layoutWidget6);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        lineEditP = new QLineEdit(layoutWidget6);
        lineEditP->setObjectName(QStringLiteral("lineEditP"));
        lineEditP->setMinimumSize(QSize(192, 0));
        lineEditP->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_11->addWidget(lineEditP);


        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(layoutWidget6);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_12->addWidget(label_8);

        lineEditSmooth = new QLineEdit(layoutWidget6);
        lineEditSmooth->setObjectName(QStringLiteral("lineEditSmooth"));
        lineEditSmooth->setMinimumSize(QSize(192, 0));
        lineEditSmooth->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_12->addWidget(lineEditSmooth);


        verticalLayout_6->addLayout(horizontalLayout_12);

        comboBox = new QComboBox(layoutWidget6);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(310, 0));
        comboBox->setMaximumSize(QSize(310, 16777215));

        verticalLayout_6->addWidget(comboBox);

        checkBoxLine = new QCheckBox(layoutWidget6);
        checkBoxLine->setObjectName(QStringLiteral("checkBoxLine"));

        verticalLayout_6->addWidget(checkBoxLine);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_5 = new QLabel(layoutWidget6);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_13->addWidget(label_5);

        lineEditSlope = new QLineEdit(layoutWidget6);
        lineEditSlope->setObjectName(QStringLiteral("lineEditSlope"));
        lineEditSlope->setEnabled(false);
        lineEditSlope->setMinimumSize(QSize(192, 0));
        lineEditSlope->setMaximumSize(QSize(192, 16777215));

        horizontalLayout_13->addWidget(lineEditSlope);


        verticalLayout_6->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_6 = new QLabel(layoutWidget6);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_14->addWidget(label_6);

        lineEditInter = new QLineEdit(layoutWidget6);
        lineEditInter->setObjectName(QStringLiteral("lineEditInter"));
        lineEditInter->setEnabled(false);
        lineEditInter->setMaximumSize(QSize(192, 16777215));
        lineEditInter->setSizeIncrement(QSize(192, 0));

        horizontalLayout_14->addWidget(lineEditInter);


        verticalLayout_6->addLayout(horizontalLayout_14);


        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout_4->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1297, 20));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "I / O", 0));
        labelImport->setText(QApplication::translate("MainWindow", "Import file name ", 0));
        lineEditImport->setText(QApplication::translate("MainWindow", "WH.dat", 0));
        pushButtonImportFile->setText(QApplication::translate("MainWindow", "...", 0));
        pushButtonRun->setText(QApplication::translate("MainWindow", "Run", 0));
        labelExportFileName->setText(QApplication::translate("MainWindow", "Export file name ", 0));
        lineEditExport->setText(QApplication::translate("MainWindow", "FitedData.txt", 0));
        pushButtonExportFile->setText(QApplication::translate("MainWindow", "...", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Save data", 0));
        labelFreq->setText(QApplication::translate("MainWindow", "Frequency column name", 0));
        lineEditFreq->setText(QApplication::translate("MainWindow", "Fgen", 0));
        labelPhase->setText(QApplication::translate("MainWindow", "Phase column name", 0));
        lineEditPhase->setText(QApplication::translate("MainWindow", "Theta", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Resonance detection", 0));
        labelTrigg->setText(QApplication::translate("MainWindow", "       Trigger", 0));
        lineEditTrigg->setText(QApplication::translate("MainWindow", "5", 0));
        labelW->setText(QApplication::translate("MainWindow", "  Noise selection", 0));
        label->setText(QApplication::translate("MainWindow", "Number of cycles", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Ignore resonances with low SNR", 0));
        label_2->setText(QApplication::translate("MainWindow", "Min. SNR", 0));
        lineEditSNR->setText(QApplication::translate("MainWindow", "10", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Resonance properties", 0));
        label_4->setText(QApplication::translate("MainWindow", "Central frequency", 0));
        label_9->setText(QApplication::translate("MainWindow", "Width", 0));
        label_10->setText(QApplication::translate("MainWindow", "Height", 0));
        checkBoxShowFitCurve->setText(QApplication::translate("MainWindow", "Show fit curve", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Fit parameters", 0));
        checkBoxEnableFitParams->setText(QApplication::translate("MainWindow", "Use custom fit parameters", 0));
        label_3->setText(QApplication::translate("MainWindow", "MinError", 0));
        lineEditMinError->setText(QApplication::translate("MainWindow", "1E-3", 0));
        labelNumOfSteps->setText(QApplication::translate("MainWindow", "Number of steps", 0));
        lineEditNumOfSteps->setText(QApplication::translate("MainWindow", "1E2", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Base Line", 0));
        label_7->setText(QApplication::translate("MainWindow", "p-parameter", 0));
        lineEditP->setText(QApplication::translate("MainWindow", "0.3", 0));
        label_8->setText(QApplication::translate("MainWindow", "Smoothness", 0));
        lineEditSmooth->setText(QApplication::translate("MainWindow", "1E7", 0));
        comboBox->setCurrentText(QString());
        checkBoxLine->setText(QApplication::translate("MainWindow", "Use custom straight line parameters", 0));
        label_5->setText(QApplication::translate("MainWindow", "Slope", 0));
        label_6->setText(QApplication::translate("MainWindow", "Interception", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
