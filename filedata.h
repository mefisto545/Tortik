#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

class FileData
{
    string filePath;                                                               // Путь к файлу
    string freqColName;                                                      // Название столбца со значениями Частот
    string phaseColName;                                                   // Название столбца со значениями Фазы
    int freqColNum;                                                                   // Номер столбца со значениями Частот
    int phaseColNum;                                                                // Номер столбца со значениями Фазы

public:
    vector<double> freqData;                                             // Вектор с частотами
    vector<double> phaseData;                                          // Вектор со значениями фазы
    double trigg;                                                       // half-wight of non-resonance zone
    int w;                                                              // half-wight of noise research area
    int cycleNum;                                                       // number of cycles in median parameters calculation
    FileData(const string &path, const string &freqName, const string &phaseName);// Конструктор с путём к файлу, названиями столбцов
    double minSNR;
    int readRows();                                                                  // Чтение столбцов с названиями из row
    void writeRows(const string &path, const string *rowNames, const vector<double> *arrays, int size); //Запись столбцов в файл
    void writeFreqAndTheta();
    void writeStackToFile(const string &path, stack <struct Resonance> stack);
    void writeVectorToFile(const string &path, const vector <struct Resonance> &data);

private:
};

inline double median(double f,double k, double y0)
{
    return f*k + y0;
}
struct Resonance
{
    int a;
    int b;
    double y0;
    double width;
    double yc;
    double xc;
    double snr;
    double mse;
};
bool level(vector <double> &x, vector <double> &y, double* k, double* y0, double trigg);
void trigger(vector <double> &x, vector <double> &y, vector <double> &baseline, double trigg, int w,
             bool SNRmatter, double minSNR, stack <struct Resonance> *Stack);
double SNR(vector <double> &y, int a, int b, double median, double trigg, int w);

#endif // FILEDATA_H
