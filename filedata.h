#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <vector>
#include <QFile>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class FileData
{
public:
    vector<double> freqData;                                             // Вектор с частотами
    vector<double> phaseData;                                          // Вектор со значениями фазы
    string filePath;                                                               // Путь к файлу
    string freqColName;                                                      // Название столбца со значениями Частот
    string phaseColName;                                                   // Название столбца со значениями Фазы
    int freqColNum;                                                                   // Номер столбца со значениями Частот
    int phaseColNum;                                                                // Номер столбца со значениями Фазы

    FileData(char *path, char *freqName, char *phaseName);// Конструктор с путём к файлу, названиями столбцов
    bool readRows();                                                                  // Чтение столбцов с названиями из row
    //void writeRows(char* rowNames[]); //Запись столбцов в файл

private:
};

#endif // FILEDATA_H
