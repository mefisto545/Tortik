#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <stack>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showGraph(const std::vector<double> &vectorx, const std::vector<double> &vectory,
                   std::stack<struct Resonance> fittedData, double k, double y0, double trigg);
    ~MainWindow();

private slots:
    void on_pushButtonRun_clicked();
    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
