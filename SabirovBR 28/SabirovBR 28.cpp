


#include <iostream> 
#include <Windows.h> 
#include <iomanip> 
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct MyDate {
    unsigned short Day;
    unsigned short Month;
    unsigned short Year;
};

struct Record
{
    char Name[9];
    char Type[3];
    int Square;
    int Count;
    struct MyDate Date;

};

void printDate(unsigned short Day, unsigned short Month, unsigned short Year, int wLine) {
    int w = 10;
    int delta = (wLine - w) / 2 + 1;
    cout << left;
    cout.width(delta); cout << " ";
    if (Day > 9) cout << Day; else cout << "0" << Day;
    cout << ".";
    if (Month > 9) cout << Month; else cout << "0" << Month;
    cout << ".";
    cout << Year;
    cout.width(delta); cout << " " << right << " |" << endl;


}

void OutTableEntry(struct Record* A, int i) {
    using std::cout;
    cout << A[i].Name << endl;
}


void printDate1(struct MyDate date1, int wLine) {
    printDate(date1.Day, date1.Month, date1.Year, wLine);
}

void Draw(struct Record* Table, int RowCount)
{
    cout << endl; cout << "|"; cout.width(100); cout.fill('-'); cout << "|" << endl;
    cout.fill(' '); cout.width(100); cout << left << "|Сельскохозяйственные предприятия"; cout << "|" << endl;
    cout.width(100); cout.fill('-'); cout << "|" << "|" << endl;
    cout.fill(' ');

    cout.width(20); cout << "|Название ";
    cout.width(20); cout << "|Вид собственности ";
    cout.width(20); cout << "|Площадь земли (га) ";
    cout.width(20); cout << "|Кол.работников ";
    cout.width(20); cout << "|Дата документа ";
    cout << "|" << endl;
    cout.width(100); cout.fill('-'); cout << "|" << "|" << endl;
    cout.fill(' ');

    for (int i = 0; i < RowCount; i++) {
        cout << "|"; cout << setw(19) << left << Table[i].Name;
        cout << "|";
        cout.width(19); cout << left << Table[i].Type;
        cout << "|";
        cout.width(19); cout << left << Table[i].Square;
        cout << "|";
        cout << setw(19); cout << right << Table[i].Count;
        cout << "|";

        printDate1(Table[i].Date, 17);
    }
    cout << "|";
    cout.width(100); cout.fill('-'); cout << "|" << endl;
    cout.width(100); cout.fill(' '); cout << left << "|Вид собственности : Д - государственная, Ч - частная, К - кооперативная" << right << "|" << endl << "|";
    cout.width(100); cout.fill('-'); cout << "|" << endl;
}

int main() {

    using namespace std;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct Record Table[10] = { { "Заря", "Д", 300, 120, {7,3,2022} } ,{ "Росинка", "К", 174, 27, {3,7,2022} } ,{ "Петренко","Ч",56, 6, {8,8,2021} } };

    cout << "Начальная таблица\n";

    Draw(Table, 3);

 /*   // 2 практика

    Record* A;//А - указатель на массив, элементы которого - структура Record (указатель = нулевой элемент массива(начало))
    Record** B;
    int ElementCount = 3;
    int ExtendedElementCount = 10;//Кол-во элементов

    A = (Record*)malloc(ElementCount * sizeof(Record)); // Выделяем память размером кол-во элементов * размер одного элемента и преобразуем в Record*

    for (int i = 0; i < ElementCount; i++) {
        strcpy_s(A[i].Name, Table[i].Name);
        A[i].Type = Table[i].Type;
        A[i].Square = Table[i].Square;
        A[i].Count = Table[i].Count;
        A[i].Date = Table[i].Date;
    }

    A = (Record*)realloc(A, 3 * sizeof(Record)); // Увеличиваем память для 10 элементов

    B = (Record**) new Record * [ExtendedElementCount];

    for (int i = 0; i < ExtendedElementCount; i++) {
        B[i] = (Record*) new Record;
        *(B[i]) = A[i];
    }



    for (int i = 0; i < ExtendedElementCount; i++) {
        cout << "Адрес A[i] " << &A[i] << " Значение А[i] " << A[i].Name << ' ' << A[i].Type << ' ' << A[i].Square << ' ' << A[i].Count << ' ' << A[i].Date.Day << ' ' << A[i].Date.Month << ' ' << A[i].Date.Year << endl;

    }
    cout << endl;
    for (int i = 0; i < ExtendedElementCount; i++) {
        cout << "Адрес B[i] " << &B[i] << " Значение B[i] " << (*B[i]).Name << endl;
    }
    delete[]B;
    free(A); */


    // 4 практика

    FILE* TextFile;

    fopen_s(&TextFile, "DataText.txt", "w+");

    for (int i = 0; i < 3; i++) {
        fprintf(TextFile, "%s %s %d %d %d %d %d", \
            Table[i].Name, \
            Table[i].Type, \
            Table[i].Square, \
            Table[i].Count, \
            Table[i].Date.Day, Table[i].Date.Month, Table[i].Date.Year);
    }

    fclose(TextFile); //Открыли(создали) тхт файл, записали таблицу, закрыли файл.


    fopen_s(&TextFile, "DataText.txt", "r");

    Record ReadedTable[4];

    for (int i = 0; i < 3; i++) {
        fscanf_s(TextFile, "%s", &ReadedTable[i].Name, _countof(ReadedTable[i].Name));
        fscanf_s(TextFile, "%s", &ReadedTable[i].Type, _countof(ReadedTable[i].Type));
        fscanf_s(TextFile, "%d", &ReadedTable[i].Square);
        fscanf_s(TextFile, "%d", &ReadedTable[i].Count);
        fscanf_s(TextFile, "%d", &ReadedTable[i].Date.Day);
        fscanf_s(TextFile, "%d", &ReadedTable[i].Date.Month);
        fscanf_s(TextFile, "%d", &ReadedTable[i].Date.Year);
    }

    fclose(TextFile);

    cout << "\nТаблица в текстовом формате из файла\n";

    Draw(ReadedTable, 3); // Прочитали файл, вывели таблицу новую, закрыли файл.

    // Записываем в файл в бинарке

    FILE* BinaryFile;
    fopen_s(&BinaryFile, "DataBin.bin", "w");
    fwrite(Table, sizeof(Table), 1, BinaryFile);
    fclose(BinaryFile);

    //Считали с файла, вывели таблицу

    fopen_s(&BinaryFile, "DataBin.bin", "rb");
    fread_s(ReadedTable, sizeof(ReadedTable), sizeof(ReadedTable), 1, BinaryFile);
    fclose(BinaryFile);

    cout << "\nТаблица в текстовом формате из бинарного файла\n";

    Draw(ReadedTable,3);



    //Добавляем 4 запись
    Record NewTable[4];

    for (int i = 0; i < 3; i++) { NewTable[i] = Table[i]; }; // Скопировали 3 старых записи

    cout << "\nВведите данные для новой записи\n";
    cin >> NewTable[3].Name >> NewTable[3].Type >> NewTable[3].Square >> NewTable[3].Count >> NewTable[3].Date.Day >> NewTable[3].Date.Month >> NewTable[3].Date.Year;

    fopen_s(&TextFile, "DataText.txt", "w+");
    fwrite(NewTable, sizeof(NewTable), 1, TextFile);
    fclose(TextFile);                                        // Переписали файл, но уже с новой записью

    fopen_s(&TextFile, "DataText.txt", "r");
    fread_s(NewTable, sizeof(NewTable),sizeof(NewTable), 1, TextFile);
    fclose(TextFile);                                        //Считали файл с новой записью

    cout << "\n Таблица с новой записью \n";
    Draw(NewTable, 4);

    //Выполнение задания 2 (Поменять местами строковые значения в 3 и 4 записях файла. Данные считываются из текстового файла)

    fopen_s(&TextFile, "DataText.txt", "r");
    swap(NewTable[2].Name, NewTable[3].Name);
    swap(NewTable[2].Type, NewTable[3].Type);
    fclose(TextFile);                           //Открыли файл, поменяли строковые значения

    fopen_s(&TextFile, "DataText.txt", "w+");
    fread_s(NewTable, sizeof(NewTable), sizeof(NewTable), 1, TextFile);
    fclose(TextFile);                           //Перезаписали файл

    cout << "\nТаблица с выполненным заданием\n";
    Draw(NewTable, 4);                         // Вывели таблицу с заданием


}