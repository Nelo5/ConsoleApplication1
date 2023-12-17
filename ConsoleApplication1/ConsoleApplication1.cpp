#include <iostream>
#include <string>
#include <cmath>
#include<csignal>
using namespace std;

//Проверка строки на соответствие шестнадцатеричной системе счисления
bool is_hex(string number) 
{
    if (number.length() != 2) { return false; }          //Если обрабатывается не двузначное число, фунция сразу же возвращает false
    bool check = true;                                   //Объявление переменной для отслеживания нешестнадцатеричных символов
    for (int i = 0; i < 2; i++)                          
    {                                                    
        char c = toupper(number[i]);                     //Для удобства проверки приводим символ к верхнему регистру
        if (!((c > 47 && c < 58) || c > 64 && c < 71))   //Если i-ый символ не является шестнадцатеричным
        { 
            check=false;                                 //check принимает значение false         
        } 
    }
    return check;                                        //Возвращение значения переменной check            
}

//Перевод двузначного шестнадцатеричного числа в десятичное
int htoi(string num)
{
    int res = 0;
    res += (num[0] > 57 ? (num[0] - 55) * pow(16, 1) : (num[0] - 48) * pow(16, 1));
    res += (num[1] > 57 ? (num[1] - 55) * pow(16, 0) : (num[1] - 48) * pow(16, 0));
  
    return res;
}

//Перевод десятичного числа в двузначное шестнадцатеричное
string itoh(int num) 
{
    string res = "";
    res += num / 16 > 9 ? char(num / 16) + 55 : char(num / 16) + 48;
    res += num % 16 > 9 ? char(num % 16) + 55 : char(num % 16) + 48;
    return res;
}

//Группировка значений массива относительно опорного (в нашем случае самого правого) элемента
int partition(string a[], int start, int end)
{
    int pivot = htoi(a[end]);                                             //Берём последний элемент списка за опорный
    int pindex = start;                                                   //Берём начальный индекс за опорный индекс
    for (int i = start; i < end; i++)                                     
    {                                                                     
        int t = htoi(a[i]);                                               
        if ((t <= pivot))                                                 //Если значение i-ого элемента больше опорного
        {                                                                 
            swap(a[i], a[pindex]);                                        //Меняем местами i-ый элемент и элемент с опорным индексом
            pindex++;                                                     
        }                                                                 
    }                                                                     
    swap(a[pindex], a[end]);                                              //Меняем местами опорный элемент и элемент с опорным индексом 
    return pindex;                                                        //Возвращает опорный индекс, слева от него находятся элементы меньшие опорного
                                                                          // а справа - элементы большие опорного
}

//Алгоритм быстрой сортировки
void quicksort(string a[], int start, int end)
{
    if (start >= end) {
        return;                                                           //Выход из рекурсии
    }
    int pivot = partition(a, start, end);                                 //Нахождение индекса опорного элемента и группировка массива 
    quicksort(a, start, pivot - 1);                                       //Быстрая сортировка элементов, меньших опорного
    quicksort(a, pivot + 1, end);                                         //Быстрая сортировка элементов, меньших опорного
}

int main()
{
    srand(time(NULL));                                                     //За семя рандома берём текущее время системы
    setlocale(LC_ALL, "RU");                                               //Настройка консоли для работы с русским языком
    signal(SIGINT, SIG_IGN);                                               //Блокировка ctrl+z и ctrl+c
    string matrix[4][4];                                                   //Инициализация матрицы 4 x 4
    string selector;                                                       //Инициализация переменных для ввода данных
    string line;
    cout << "Введите 0, если хотите автоматически заполнить матрицу, или 1 для самостятельного заполнения" << endl;
    cout << "Если введёте ctrl+z после каких-либо символов, дважды нажмите Enter" << endl;
    getline(cin, selector);
    while (selector != "1" && selector != "0") 
    {
        cout << "Неверный ввод. Введите 0 или 1" << endl;
        cin.clear();
        getline(cin, selector);
    }
    if (selector == "0")                                                   //Заолнение матрицы случайными значениями
    {
        for (int i = 0; i < 16; i++) { matrix[i / 4][i % 4] = itoh(rand() % 256); }
    }
    else                                                                   //Ручное заполнение матрицы
    {
        cout << "Введите значения матрицы" << endl;
        for (int i = 0; i < 16; i++) 
        {
            getline(cin, line);
            while (!is_hex(line)) 
            {
                cout << "Ошибка ввода. Введите двузначное шестнадцатеричное число" << endl;
                cin.clear();
                getline(cin, line);
            }
            matrix[i / 4][i % 4] = line;
        }
    }
    cout << endl;
    for (int i = 0; i < 4; i++)                                                                                    
    {
        for (int j = 0; j < 4; j++) 
        {
            cout << matrix[i][j] << " ";                                   //Вывод значений матрицы 
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 4; i++)                                            
    {
        quicksort(matrix[i], 0, 3);                                        //Сортировка строк матрицы
        if (i % 2 == 0)                                                    //Сортировка по убыванию нечётных строк матрицы
        {
            swap(matrix[i][0], matrix[i][3]);
            swap(matrix[i][1], matrix[i][2]);
        }
        for (int j = 0; j < 4; j++) {                                       
            cout << matrix[i][j] << " ";                                   //Вывод значений матрицы 
        }
        cout << endl;
    }
}

