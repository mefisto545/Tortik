#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedata.h"
#include "resfitter.h"
#include <QApplication>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGraph(const vector<double> &vectorx, const vector<double> &vectory,
                           vector<struct Resonance> fittedData, double k, double y0, double trigg)
{
    // clear graphs data
    ui->customPlot->clearGraphs();

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    QVector<double> x = QVector<double>::fromStdVector(vectorx);
    QVector<double> y = QVector<double>::fromStdVector(vectory);
    ui->customPlot->graph(0)->setData(x, y);
    int size = vectorx.size();
    // create graphs for linear approximation and 2 trigger lines
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::green));
    ui->customPlot->graph(1)->addData(vectorx[0], y0+k*vectorx[0]);
    ui->customPlot->graph(1)->addData(vectorx[size-1], y0+k*vectorx[size-1]);
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::gray));
    ui->customPlot->graph(2)->addData(vectorx[0], trigg+y0+k*vectorx[0]);
    ui->customPlot->graph(2)->addData(vectorx[size-1], trigg+y0+k*vectorx[size-1]);
    ui->customPlot->addGraph();
    ui->customPlot->graph(3)->setPen(QPen(Qt::gray));
    ui->customPlot->graph(3)->addData(vectorx[0], y0-trigg+k*vectorx[0]);
    ui->customPlot->graph(3)->addData(vectorx[size-1], y0-trigg+k*vectorx[size-1]);
    // create graphs that show found resonances
    int resNum = 4, numOfRes = fittedData.size();
    for(int i = 0; i < numOfRes; i++)
    {
        Resonance resonance = fittedData[i];

        ui->customPlot->addGraph();
        ui->customPlot->graph(resNum)->setPen(QPen(Qt::red));

        for (int k = resonance.a; k <= resonance.b; k++)
        {
            ui->customPlot->graph(resNum)->addData(vectorx[k], vectory[k]);
        }
        if(resonance.a == resonance.b)
        {
            ui->customPlot->graph(resNum)->addData(vectorx[resonance.a-1], vectory[resonance.a-1]);
            ui->customPlot->graph(resNum)->addData(vectorx[resonance.a+1], vectory[resonance.a+1]);
        }
        resNum++;
    }
    // give the axes appropriate labels:
    ui->customPlot->xAxis->setLabel("Freq");
    ui->customPlot->yAxis->setLabel("Theta");

    // set axes ranges, so we see all data:
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->replot();
}

void MainWindow::on_pushButtonRun_clicked()
{
    string ImportFileName = ui->lineEditImport->text().toStdString();
    string FreqColumnName = ui->lineEditFreq->text().toStdString();
    string PhaseColumnName = ui->lineEditPhase->text().toStdString();
    string ExportFileName = ui->lineEditExport->text().toStdString();

    FileData file(ImportFileName,FreqColumnName, PhaseColumnName); //Example of creating file class
    switch(file.readRows()) //Reading two rows from file
    {
        case 1:
            QMessageBox::about(this, "Error", "File is empty or doesn't exist");
            return;
        case 2:
            QMessageBox::about(this, "Error", "Cannot find frequency column");
            return;
        case 3:
            QMessageBox::about(this, "Error", "Cannot find phase column");
            return;
    }
    double k = 0, y0 = 0;
    stack <struct Resonance> st;
    file.trigg = ui->lineEditTrigg->text().toDouble();
    file.w = ui->spinBoxW->value();
    file.cycleNum = ui->spinBoxCycleNum->value();
    file.minSNR = ui->lineEditSNR->text().toDouble();
    for (int i=0;  i < file.cycleNum; i++)
        level(file.freqData, file.phaseData, &k, &y0, file.trigg);
    trigger(file.freqData, file.phaseData, k, y0, file.trigg, file.w, ui->checkBox->isChecked(), file.minSNR, &st);

    int maxNumberOfSteps = ui->lineEditNumOfSteps->text().toDouble(); //less steps is better
    double minError = ui->lineEditMinError->text().toDouble(), step = ui->lineEditFitStep->text().toDouble();
    ResFitter fitter(maxNumberOfSteps, minError, step,&file, y0, k);
    fitter.fitData(st);

    file.writeVectorToFile(ExportFileName, fitter.fittedData); // Write data of fitted resonances (with fit parameters) in txt file
    MainWindow::showGraph(file.freqData, file.phaseData, fitter.fittedData, k, y0, file.trigg);
    QMessageBox::about(this, "Result", "Done");
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked == true)
        ui->lineEditSNR->setEnabled(true);
    else
        ui->lineEditSNR->setEnabled(false);
}
