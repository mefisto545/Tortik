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
    MainWindow::setWindowTitle("ResFinder_v1.0.2.3");
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
    // create graph for fit curve
    ui->customPlot->addGraph();
    // create graphs that show found resonances
    int resNum = 5, numOfRes = fittedData.size();
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
                if (!level(file->freqData, file->phaseData, &k, &y0, file->trigg))
                {
                    QMessageBox::about(this, "Error", "\tBaseline didn't converged.\nPlease, use bigger trigger value or curve baseline");
                    break;
                }
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

Resonance resFreq(double f, stack <Resonance> st, vector <double> &x)
{
    double h;
    while(!st.empty())
    {
        if(st.top().a == st.top().b)
        {
            h = (x[st.top().a] - x[st.top().a - 1]) / 2.;
            if (x[st.top().a] - h <= f && f <= x[st.top().a] + h)
                return st.top();
        }
        if(x[st.top().a] <= f && f <= x[st.top().b])
            return st.top();
        st.pop();
    }
    return { 0 };
}

void MainWindow::slotMousePress(QMouseEvent *event)
{
    double coordX = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    double xc = 0, width = 0, height = 0;
    Resonance locRes = resFreq(coordX, st, file->freqData);
    xc = locRes.xc;
    width = locRes.width;
    height = locRes.y0-locRes.yc;
    if(!st.empty())
    {
        if(xc >= 0)
        {
            QString xcStr = QString::number(xc,'g', 10);
            QString widthStr = QString::number(width, 'g', 6);
            QString heightStr = QString::number(height, 'g', 6);
            ui->lineEditRf->setText(xcStr);
            ui->lineEditW->setText(widthStr);
            ui->lineEditHeight->setText(heightStr);
            MainWindow::printFit(locRes);
        }
        else
        {
            ui->lineEditRf->setText("");
            ui->lineEditW->setText("");
        }
    }
}

void MainWindow::printFit(Resonance res)
{
    QVector<double> x, y;
    QVector<double> kek(0.0);
    QVector<double> kek1(0.0);
    ui->customPlot->graph(4)->setData(kek, kek1);
    ui->customPlot->replot();
    // cancel function after cleaning if special user doesn't need the fit curve
    if (!(ui->checkBoxShowFitCurve->isChecked())) return;
    ui->customPlot->graph(4)->setPen(QPen(Qt::black));
    double localParams[4];
    if (res.a == 0)
    {
        return;
    }
    localParams[0] = res.y0;
    localParams[1] = res.yc;
    localParams[2] = res.xc;
    localParams[3] = res.width;
    for(int i = res.xc - res.width*4.0; i < res.xc + res.width*4.0; i++)
    {
        x.append((double)i);
        y.append(ResFitter::lorentz((double)i,localParams));
    }
    ui->customPlot->graph(4)->addData(x, y);
    ui->customPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    string ExportFileName = ui->lineEditExport->text().toStdString();
    file->writeVectorToFile(ExportFileName, fitter->fittedData); // Write data of fitted resonances (with fit parameters) in txt file
    QMessageBox::about(this, "Done", "Saved");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    QStringList accepted_types;
    accepted_types << "txt" << "dat";
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fname = url.toLocalFile();
        QFileInfo info(fname);
        if(info.exists())
        {
            if(accepted_types.contains(info.suffix().trimmed(), Qt::CaseInsensitive));
            ui->lineEditImport->setText(url.path().remove(0,1));
            return;
        }
    }
}
