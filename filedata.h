#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

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
    FileData(const string &path, const string &freqName, const string &phaseName);// Конструктор с путём к файлу, названиями столбцов
    bool readRows();                                                                  // Чтение столбцов с названиями из row
    void writeRows(const string &path, const string *rowNames, const vector<double> *arrays, int size); //Запись столбцов в файл
    void writeFreqAndTheta();
    void writeStackToFile(const string &path, stack <struct AB> stack);

private:
};

inline double median(double f,double k, double y0);
struct AB
{
    int a;
    int b;
    double snr;
};
void level(vector <double> &x, vector <double> &y, double* k, double* y0);
void trigger(vector <double> &x, vector <double> &y, double k, double y0, double trigg, int w, stack <struct AB> *Stack);
double SNR(vector <double> &y, int a, int b, double median, double trigg, int w);

#endif // FILEDATA_H
