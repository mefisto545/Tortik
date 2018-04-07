#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedata.h"
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include "als.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("ResFinder");
    connect(ui->customPlot, &QCustomPlot::mousePress, this, &MainWindow::slotMousePress);
    QStringList List;
    List.push_back("Use straight baseline");
    List.push_back("Use curve baseline");
    ui->comboBox->addItems(List);
    List.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGraph(const vector<double> &vectorx, const vector<double> &vectory,
                           vector<struct Resonance> fittedData, const vector <double> &baseline)
{
    // clear graphs data
    ui->customPlot->clearGraphs();

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    QVector<double> x = QVector<double>::fromStdVector(vectorx);
    QVector<double> y = QVector<double>::fromStdVector(vectory);
    ui->customPlot->graph(0)->setData(x, y);
    // create graphs for baseline and 2 trigger lines
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
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
        else
        //resonance display correction
            if(resonance.a > 0 && resonance.b - 1 < vectorx.size())
            {
                if(resonance.yc - resonance.y0 > 0)
                {
                    if(vectory[resonance.a - 1] < baseline[resonance.a - 1])
                        ui->customPlot->graph(resNum)->addData(vectorx[resonance.a-1], vectory[resonance.a-1]);
                    if(vectory[resonance.b - 1] < baseline[resonance.b - 1])
                        ui->customPlot->graph(resNum)->addData(vectorx[resonance.b+1], vectory[resonance.b+1]);
                }
                else
                {
                    if(vectory[resonance.a - 1] > baseline[resonance.a - 1])
                        ui->customPlot->graph(resNum)->addData(vectorx[resonance.a-1], vectory[resonance.a-1]);
                    if(vectory[resonance.b - 1] > baseline[resonance.b - 1])
                        ui->customPlot->graph(resNum)->addData(vectorx[resonance.b+1], vectory[resonance.b+1]);
                }
            }
        //resonance display correction
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
void MainWindow::showGraphBaseline(const vector<double> &vectorx,const vector <double> &baseline, bool straight, double trigg)
{
    int size = vectorx.size();
    if(straight)
    {
        ui->customPlot->graph(1)->setPen(QPen(Qt::green));
        ui->customPlot->graph(1)->addData(vectorx[0],baseline[0]);
        ui->customPlot->graph(1)->addData(vectorx[size-1], baseline[size-1]);
        ui->customPlot->graph(2)->setPen(QPen(Qt::gray));
        ui->customPlot->graph(2)->addData(vectorx[0], trigg+baseline[0]);
        ui->customPlot->graph(2)->addData(vectorx[size-1], trigg+baseline[size-1]);
        ui->customPlot->graph(3)->setPen(QPen(Qt::gray));
        ui->customPlot->graph(3)->addData(vectorx[0], -trigg+baseline[0]);
        ui->customPlot->graph(3)->addData(vectorx[size-1], -trigg+baseline[size-1]);
    }
    else
    {
        ui->customPlot->graph(1)->setPen(QPen(Qt::green));
        ui->customPlot->graph(1)->setData(QVector<double>::fromStdVector(vectorx), QVector<double>::fromStdVector(baseline));
        ui->customPlot->graph(2)->setPen(QPen(Qt::gray));
        ui->customPlot->graph(3)->setPen(QPen(Qt::gray));
        for(int i = 0; i < size; i++)
        {
            ui->customPlot->graph(2)->addData(vectorx[i], trigg+baseline[i]);
            ui->customPlot->graph(3)->addData(vectorx[i], -trigg+baseline[i]);
        }
    }
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
    double p = ui->lineEditP->text().toDouble();
    double smooth = ui->lineEditSmooth->text().toDouble();
    baseline = file->phaseData;
    if (ui->comboBox->currentText() == "Use straight baseline")
    {
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
        for(unsigned int i = 0; i < baseline.size(); i++)
            baseline[i] = median(file->freqData[i], k, y0);
    }
    else
    {
        mainals(baseline, p, smooth, file->cycleNum);
    }
    trigger(file->freqData, file->phaseData, baseline, file->trigg, file->w, ui->checkBox->isChecked(), file->minSNR, &st);

    int maxNumberOfSteps;
    double minError;
    if (ui->checkBoxEnableFitParams->isChecked())
    {
        maxNumberOfSteps = ui->lineEditNumOfSteps->text().toDouble();
        minError = ui->lineEditMinError->text().toDouble();
    }
    else
    {
        maxNumberOfSteps = DEF_MAX_STEPS;
        minError = DEF_MIN_ERROR;
    }
    fitter = new ResFitter(maxNumberOfSteps, minError, file);
    fitter->fitData(st, baseline);

    MainWindow::showGraph(file->freqData, file->phaseData, fitter->fittedData, baseline);
    MainWindow::showGraphBaseline(file->freqData, baseline, ui->comboBox->currentText() == "Use straight baseline",
                              file->trigg);
    QMessageBox::about(this, "Done", "Found " + QString::number(fitter->fittedData.size()) + " resonances   ");

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
            QString str = QString::number(xc,'g', 10);
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
