#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedata.h"
#include <QApplication>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("ResFinder");
    connect(ui->customPlot, &QCustomPlot::mousePress, this, &MainWindow::slotMousePress);
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
    ui->customPlot->xAxis->setLabel("Frequency");
    ui->customPlot->yAxis->setLabel("Phase");

    // set axes ranges, so we see all data:
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->replot();
}

void MainWindow::on_pushButtonRun_clicked()
{
    while(!st.empty())
    {
        st.pop();
    }
    string ImportFileName = ui->lineEditImport->text().toStdString();
    string FreqColumnName = ui->lineEditFreq->text().toStdString();
    string PhaseColumnName = ui->lineEditPhase->text().toStdString();
    file = new FileData(ImportFileName,FreqColumnName, PhaseColumnName); //Example of creating file class
    switch(file->readRows()) //Reading two rows from file
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
    file->trigg = ui->lineEditTrigg->text().toDouble();
    file->w = ui->spinBoxW->value();
    file->cycleNum = ui->spinBoxCycleNum->value();
    file->minSNR = ui->lineEditSNR->text().toDouble();
    if(ui->checkBoxLine->isChecked())
    {
        k = ui->lineEditSlope->text().toDouble();
        y0 = ui->lineEditInter->text().toDouble();
    }
    else
    {
        for (int i=0;  i < file->cycleNum; i++)
            level(file->freqData, file->phaseData, &k, &y0, file->trigg);
        ui->lineEditSlope->setText(QString::number(k));
        ui->lineEditInter->setText(QString::number(y0));
    }

    trigger(file->freqData, file->phaseData, k, y0, file->trigg, file->w, ui->checkBox->isChecked(), file->minSNR, &st);

    int maxNumberOfSteps;
    double minError, step;
    if (ui->checkBoxEnableFitParams->isChecked())
    {
        maxNumberOfSteps = ui->lineEditNumOfSteps->text().toDouble();
        minError = ui->lineEditMinError->text().toDouble();
        step = ui->lineEditFitStep->text().toDouble();
    }
    else
    {
        maxNumberOfSteps = DEF_MAX_STEPS;
        minError = DEF_MIN_ERROR;
        step = DEF_STEP;
    }
    fitter = new ResFitter(maxNumberOfSteps, minError, step, file, y0, k);
    fitter->fitData(st);

    MainWindow::showGraph(file->freqData, file->phaseData, fitter->fittedData, k, y0, file->trigg);
    QString N = QString::number(fitter->fittedData.size());
    QMessageBox::about(this, "Done", "Found " + N + " resonances   ");
    for(unsigned int i=0; i < fitter->fittedData.size(); i++)
    {
        st.push(fitter->fittedData[i]);
    }
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_checkBox_clicked(bool checked)
{
        ui->lineEditSNR->setEnabled(checked);
}

void MainWindow::on_checkBoxLine_clicked(bool checked)
{
        ui->lineEditSlope->setEnabled(checked);
        ui->lineEditInter->setEnabled(checked);
}

void MainWindow::on_checkBoxEnableFitParams_clicked(bool checked)
{
        ui->lineEditFitStep->setEnabled(checked);
        ui->lineEditMinError->setEnabled(checked);
        ui->lineEditNumOfSteps->setEnabled(checked);
}

void MainWindow::on_pushButtonImportFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File with Data"), "",
            tr("Data Files (*.dat);; Text Files (*.txt)"));
    ui->lineEditImport->setText(fileName);
}

void MainWindow::on_pushButtonExportFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt)"));
    ui->lineEditExport->setText(fileName);
}

double resFreq(double f, stack <Resonance> st, vector <double> &x)
{
    double h;
    while(!st.empty())
    {
        if(st.top().a == st.top().b)
        {
            h = (x[st.top().a] - x[st.top().a - 1]) / 2.;
            if (x[st.top().a] - h <= f && f <= x[st.top().a] + h)
                return st.top().xc;
        }
        if(x[st.top().a] <= f && f <= x[st.top().b])
            return st.top().xc;
        st.pop();
    }
    return -1;
}

void MainWindow::slotMousePress(QMouseEvent *event)
{
    double coordX = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double xc = resFreq(coordX, st, file->freqData);
    if(!st.empty())
    {
        if(xc >= 0)
        {
            QString str = QString::number(xc);
            ui->lineEditRf->setText(str);
        }
        else
            ui->lineEditRf->setText("");
    }
}


void MainWindow::on_pushButton_clicked()
{
    string ExportFileName = ui->lineEditExport->text().toStdString();
    file->writeVectorToFile(ExportFileName, fitter->fittedData); // Write data of fitted resonances (with fit parameters) in txt file
    QMessageBox::about(this, "Done", "Saved");
}
