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

void MainWindow::showGraph(const vector<double> &vectorx, const vector<double> &vectory, stack<struct Resonance> fittedData)
{
    // clear graphs data
    ui->customPlot->clearGraphs();

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    QVector<double> x = QVector<double>::fromStdVector(vectorx);
    QVector<double> y = QVector<double>::fromStdVector(vectory);
    ui->customPlot->graph(0)->setData(x, y);

    // create graphs that show finded resonances
    int resNum = 1;
    while(!fittedData.empty())
    {
        Resonance resonance = fittedData.top();

        ui->customPlot->addGraph();
        ui->customPlot->graph(resNum)->setPen(QPen(Qt::red));

        for (int k = resonance.a; k <= resonance.b; k++)
        {
            ui->customPlot->graph(resNum)->addData(vectorx[k], vectory[k]);
        }
        resNum++;
        fittedData.pop();
    }
    // give the axes appropriate labels:
    ui->customPlot->xAxis->setLabel("Freq");
    ui->customPlot->yAxis->setLabel("Theta");

    // set axes ranges, so we see all data:
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
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
    for (int i=0;  i < file.cycleNum; i++)
        level(file.freqData, file.phaseData, &k, &y0, file.trigg);
    trigger(file.freqData, file.phaseData, k, y0, file.trigg, file.w, &st);

    int maxNumberOfSteps = 1e2; //less steps is better
    double minError = 0.001, step = 0.1;
    ResFitter fitter(maxNumberOfSteps, minError, step,&file, y0, k);
    fitter.fitData(st);

    file.writeStackToFile(ExportFileName, fitter.fittedData); // Write data of fitted resonances (with fit parameters) in txt file
    MainWindow::showGraph(file.freqData, file.phaseData, fitter.fittedData);
    QMessageBox::about(this, "Result", "Done");
}
