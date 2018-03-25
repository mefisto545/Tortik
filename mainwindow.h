#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <stack>
#include "resfitter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showGraph(const std::vector<double> &vectorx, const std::vector<double> &vectory,
                   std::vector<struct Resonance> fittedData);
    void showGraphBaseline(const vector<double> &vectorx,const vector <double> &baseline, bool straight, double trigg);
    stack <struct Resonance> st;
    FileData *file;
    ResFitter *fitter;
    vector <double> baseline;
    ~MainWindow();

private slots:
    void on_pushButtonRun_clicked();
    void on_checkBox_clicked(bool checked);

    void on_checkBoxEnableFitParams_clicked(bool checked);

    void on_pushButtonImportFile_clicked();

    void on_pushButtonExportFile_clicked();

    void slotMousePress(QMouseEvent *event);
    void on_pushButton_clicked();

    void on_checkBoxLine_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
