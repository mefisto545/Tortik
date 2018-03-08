#include "mainwindow.h"
#include "filedata.h"
#include "resfitter.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileData file("WH.dat","Fgen","Theta"); //Example of creating file class
    file.readRows(); //Reading two rows from file
    double k = 0, y0 = 0;
    stack <struct Resonance> st;
    file.trigg = 2;
    file.w = 50;
    int cycleNum = 1;
    for (int i=0;  i <cycleNum; i++)
        level(file.freqData, file.phaseData, &k, &y0, file.trigg);
    trigger(file.freqData, file.phaseData, k, y0, file.trigg, file.w, &st);
    file.writeStackToFile("StackData.txt", st);

    int maxNumberOfSteps = 1e2; //less steps is better
    double minError = 0.01, step = 0.1;
    ResFitter fitter(maxNumberOfSteps, minError, step,&file, y0, k);
    fitter.fitData(st);

    file.writeStackToFile("FitedData.txt", fitter.fittedData); // Write data of fitted resonances (with fit parameters) in txt file

    return a.exec();
}
