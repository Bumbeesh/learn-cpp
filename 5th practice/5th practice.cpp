#include <iostream> 
#include <Windows.h> 
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <string>

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

class clDate
{
private:

    unsigned short year;
    unsigned short month;
    unsigned short day;

public:

    char delimiter = '.';

    clDate()
    {
        setDate(1, 1, 1970);
    }

    clDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        setDate(_day, _month, _year);
    }

    MyDate getDate()
    {
        struct MyDate MD;
        MD.Year = year;
        MD.Month = month;
        MD.Day = day;
    }

    void setDate(MyDate _mD)
    {
        setDate(_mD.Day, _mD.Month, _mD.Year);
    }

    void setDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        this->day = _day;
        this->month = _month;
        this->year = _year;
    }

    void PrintDate()
    {
        if (this->day > 0 and this->day < 10)
            cout << "0";
        cout << day << this->delimiter;
        if (this->month > 0 and this->month < 10)
            cout << "0";
        cout << month << this->delimiter;
        cout << year << endl;
    }
};


struct Node {
    Record Data;
    struct Node* Next;
}; //структура список - хранится структура record и указатель на следующий элемент списка

struct Node* Head; // голова списка(начало?)
int CountItem = 0; // кол-во элементов в списке

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
        cout << "|"; cout << cout.width(19) << left << Table[i].Name;
        cout << "|";
        cout.width(19); cout << left << Table[i].Type;
        cout << "|";
        cout.width(19); cout << left << Table[i].Square;
        cout << "|";
        cout << cout.width(19); cout << right << Table[i].Count;
        cout << "|";

        printDate1(Table[i].Date, 17);
    }
    cout << "|";
    cout.width(100); cout.fill('-'); cout << "|" << endl;
    cout.width(100); cout.fill(' '); cout << left << "|Вид собственности : Д - государственная, Ч - частная, К - кооперативная" << right << "|" << endl << "|";
    cout.width(100); cout.fill('-'); cout << "|" << endl;
}

// FindIndex функция//

void AddItem(Record Data)
{
    struct Node* newItem = new Node(); // создали новую структуру(выделили память? из кучи)
    newItem->Data = Data; //присвоили ей данный аргумента, переданного в функцию
    if (CountItem == 0) {
        newItem->Next = NULL; //если это нулевой элемент(первый) то это конец списка(нет указателя на следующий)

    }
    else
    {
        newItem->Next = Head; //если элементов больше 0 - будет указатель аргумента(разобраться как работает)
    }
    Head = newItem; //указываем на адрес первого элемента
    CountItem++; // увеличиваем кол-во элементов в д.списке
}

void InsertItem(int Index, Record Data) {
    if (not (Index >= 0 and Index <= CountItem and CountItem >= 0))
        return;
    if (Index == 0)
    {
        AddItem(Data); //Если это будет нулевой элемент, то просто добавляем, а не вставляем
    }
    else
    {
        struct Node* Current = Head; // 
        for (int i = 0; i < Index - 1; i++)
        {
            Current = Current->Next; // каждому элементу присваиваем указатель на следующий (раздвигаем место для вставки)
        }
        struct Node* newItem = new Node(); // создаём новую структуру для вставки
        newItem->Data = Data; // передаём ему данные аргумента
        newItem->Next = Current->Next; // в качестве указателя будет указатель на тот, который сдвинули самым первым
        Current->Next = newItem; // не понял разобраться
        CountItem++;
    }
}

void EditItem(int Index, Record Data)
{
    if (Index >= 0 and Index < CountItem and CountItem > 0)
    {
        struct Node* Current = Head;
        for (int i = 0; i < Index; i++)
        {
            Current = Current->Next;

        }
        Current->Data = Data;
    }
    else
    {
        cout << endl << "Ошибка : индекс вне диапазона.";
    }
}

void DeleteItem(int Index)
{
    if (Index >= 0 and Index < CountItem and CountItem > 0)
    {
        struct Node* Current = Head;
        struct Node* Old;
        if (Index == 0)
        {
            Old = Head;
            Head = Current->Next;
            delete Old;
            CountItem--;
        }
        else
        {
            int i = 0;
            while (Current)
            {
                if (i == Index - 1)
                {
                    Old = Current->Next->Next;
                    delete Current->Next;
                    Current->Next = Old;
                    CountItem--;
                    break;
                }
                i++;
                Current = Current->Next;

            }
        }
    }
}

int  findIndex(struct Record* Table) {
    int ind = -1;
    int IntIndex;
    cin >> IntIndex;
    for (int i = 0; i < 3; i++) {
        if (Table[i].Count == IntIndex)
            ind = i;
    }
    return ind;
};

void PrintMyList()
{
    struct Node* Current = Head;
    cout << endl;
    while (Current) {
        cout << " " << Current->Data.Name;
        Current = Current->Next;

    }
}

void DrawWthList()
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
    struct Node* Current = Head;
    while (Current)
    {
        cout << "|"; cout << cout.width(19) << left << Current->Data.Name;
        cout << "|";
        cout.width(19); cout << left << Current->Data.Type;
        cout << "|";
        cout.width(19); cout << left << Current->Data.Square;
        cout << "|";
        cout << cout.width(19); cout << right << Current->Data.Count;
        cout << "|";

        printDate1(Current->Data.Date, 17);

        Current = Current->Next;
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

   /* cout << "Третья практика" << endl;

    AddItem(Table[0]);
    AddItem(Table[1]);
    AddItem(Table[2]);
    DrawWthList();
    struct Record newTable = { "Сабир", "B", 228, 1337, {14,05,2004} };
    InsertItem(1, newTable);
    DrawWthList();
    DeleteItem(3);
    struct Record EditTable = { "Мер", "B", 111, 1222, {14,1,2023} };
    EditItem(1, EditTable);
    DrawWthList(); */
    //3 практика задание 2 - Найти элементы списка, по целому числу, введенному с клавиатуры, и удалить найденные элементы списка. 

    // 5 практика
    class clDate date1;
    date1.PrintDate();

}