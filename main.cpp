#include "mainwindow.h"
#include "filedata.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileData file("WH.dat","Fgen","Theta"); //Example of creating file class
    file.readRows(); //Reading two rows from file
    double k, y0;
    stack <struct AB> st;
    file.trigg = 1;
    level(file.freqData, file.phaseData, &k, &y0);
    trigger(file.freqData, file.phaseData, k, y0, file.trigg, &st);
    file.writeStackToFile("StackData.txt", st);

    file.writeFreqAndTheta(); //Write Readed data to file FreqAndTheta.txt
    string names[] = {"Frequency", "Theta"}; //Names of the rows
    vector<double> data[] = {file.freqData, file.phaseData}; //Vectors with data
    file.writeRows("1.txt", names, data, 2); //Write data rows in file and name them as strings from name[]


    return a.exec();
}
