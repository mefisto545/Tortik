#include "filedata.h"

FileData::FileData(char *path, char *freqName, char *phaseName)
{
    filePath = string(path);                                       // Объявление пути к файлу
    freqColName = string(freqName);                     // Инициализация названия колонки с частотами
    phaseColName = string(phaseName);               //  Инициализация названия колонки с фазой
    phaseColNum = -1;                                                   // Инициализация начальных значений номеров колонок
    freqColNum = -1;                                                      // отрицательной единицей
}

bool FileData::readRows()
{
    ifstream fileStream(filePath);                                // Создание потока и подключение к файлу с данными
    string localWord;                                                   // Локальная переменная на отдельного названия столбца/ Отдельного значения
    string localLine;                                                     // Локальная переменная для считываемой строки
    stringstream ss;                                                    // Поток для подключения к строкам для деления их на составляющие элементы
    int numWord = 0;                                                        // Итератор для элементов в строке
    int numLine = 1;                                                          // Итератор для строк

    getline(fileStream, localLine);                               // Получение и запись первой строки с заголовками
    ss = stringstream(localLine);                                //Подключение к нему потока

    while (ss >> localWord)
    {
        if (localWord == phaseColName) phaseColNum = numWord;              // Нахождение
        if (localWord == freqColName) freqColNum = numWord;                   // номеров
        numWord++;                                                                                        // столбцов, интересных нам
    }
    numWord = 0;                                                                                          // Обнуление итератора после прохождение 1 строки

    if (phaseColNum < 0 || freqColNum < 0) return false;                           // Если не нашли один из столбцов, завершаем работу=(

    while (!fileStream.eof())                                                                          // Читаем, пока файл не закончится
    {
        getline( fileStream, localLine);                                                     // Получение очередной строки из потока
        ss = stringstream(localLine);                                                       // Подключение к ней потока
        while (ss >> localWord)                                                                     // Читаем из потока до конца
        {
            if (numWord == phaseColNum)                                                    // При совпадении номеров записываем
            {
                phaseData.push_back(atof(localWord.c_str()));                      // нужные нам числа
            }
            if (numWord == freqColNum)
            {
                freqData.push_back(atof(localWord.c_str()));                        // в соответствующие переменные
            }
            numWord++;
        }
        numWord = 0;
        numLine++;
    }
    return 0;
}
