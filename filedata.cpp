#include "filedata.h"

FileData::FileData(const string &path, const string &freqName, const string &phaseName)
{
    filePath = string(path);                                       // Объявление пути к файлу
    freqColName = string(freqName);                     // Инициализация названия колонки с частотами
    phaseColName = string(phaseName);               //  Инициализация названия колонки с фазой
    phaseColNum = -1;                                                 // Инициализация начальных значений номеров колонок
    freqColNum = -1;                                                      // отрицательной единицей
}

int FileData::readRows()
{
    ifstream fileStream(filePath);                                // Создание потока и подключение к файлу с данными
    string localWord;                                                   // Локальная переменная на отдельного названия столбца/ Отдельного значения
    string localLine;                                                     // Локальная переменная для считываемой строки
    stringstream ss;                                                    // Поток для подключения к строкам для деления их на составляющие элементы
    int numWord = 0;                                                        // Итератор для элементов в строке
    int numLine = 1;                                                          // Итератор для строк

    getline(fileStream, localLine);                               // Получение и запись первой строки с заголовками
    ss = stringstream(localLine);                                //Создание потока этой строки
    if(fileStream.peek() == std::ifstream::traits_type::eof())
        return 1;
    while (ss >> localWord)
    {
        if (localWord == phaseColName) phaseColNum = numWord;              // Нахождение
        if (localWord == freqColName) freqColNum = numWord;                   // номеров
        numWord++;                                                                                        // столбцов, интересных нам
    }
    numWord = 0;                                                                                          // Обнуление итератора после прохождение 1 строки
    // Если не нашли один из столбцов, завершаем работу=(
    if (freqColNum < 0)
        return 2;
    if (phaseColNum < 0)
        return 3;

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

void  FileData::writeRows(const string &path , const string *rowNames,const vector<double> *arrays, int size)
{
    int colIterator = 0, rowIterator = 0;

    int maxVectSize = 0;
    ofstream fileStream(path, ofstream::app);

    for (colIterator = 0; colIterator < size; colIterator ++)
    {
        fileStream << rowNames[colIterator] << "\t";
        int locSize = arrays[colIterator].size();
        if (locSize > maxVectSize) maxVectSize = locSize;
    }
    fileStream << "\n";

    for (rowIterator = 0; rowIterator < maxVectSize; rowIterator++)
    {
        for (colIterator = 0; colIterator < size; colIterator ++)
        {
            int locSize = arrays[colIterator].size();
            if (locSize > rowIterator)
            {
                fileStream << arrays[colIterator][rowIterator] << "\t";
            }
            else
            {
                fileStream << "\t";
            }
        }
        fileStream << "\n";
    }
    fileStream.flush();
    fileStream.close();
}

void FileData::writeFreqAndTheta()
{
    if (phaseColNum < 0 || freqColNum < 0) return;
    int size = this->freqData.size();
    int i = 0;
    ofstream fileStream("FrequencyAndTheta.txt");

    fileStream << "Freq\t" << "Theta\n";

    for (i =0; i < size; i++)
    {
        fileStream << freqData[i] << "\t" << phaseData[i] << "\n";
    }
    fileStream.close();
}

void FileData::writeStackToFile(const string &path, stack<struct Resonance> st)
{
    ofstream fileStream(path);
    fileStream << "№Fa\t" << "№Fb\t" << "SNR\t" << "y0\t" << "yc\t" << "xc\t" << "width\t" << "mse\n";
    while (!st.empty())
    {
        fileStream << st.top().a << "\t"
                   << st.top().b << "\t"
                   << st.top().snr << "\t"
                   << st.top().y0 << "\t"
                   << st.top().yc << "\t"//
                   << st.top().xc << "\t"
                   << st.top().width << "\t"
                   << st.top().mse << "\n";
        st.pop();
    }
    fileStream.close();
}
