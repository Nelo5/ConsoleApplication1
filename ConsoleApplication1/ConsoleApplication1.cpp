#include <iostream>
#include <string>
#include<csignal>
using namespace std;

//Проверка строки на соответствие шестнадцатеричной системе счисления
bool is_hex(string number) {
    for (int i = 0; i < number.length(); i++)
    {
        char c = toupper(number[i]);
        if (!((c > 47 && c < 58) || c > 64 && c < 71)) { return false; }
    }
    return true;
}
//Перевод двухзначного шестнадцатеричного числа в десятичное
int htoi(string num) {
    int res = 0;
    int counter = 0;
    for (char c : num) {
        res += (c > 57 ? (c - 55) * pow(16, 1 - counter) : (c - 48) * pow(16, 1 - counter));
        counter++;
    }
    return res;
}


//Перевод десятичного числа в двухзначное шестнадцатеричное
string itoh(int num) {
    string res = "";
    res += num / 16 > 9 ? char(num / 16) + 55 : char(num / 16) + 48;
    res += num % 16 > 9 ? char(num % 16) + 55 : char(num % 16) + 48;
    return res;
}

//Группировка значений массива относительно опорного (в нашем случае самого правого) элемента
int partition(string a[], int start, int end)
{
    int pivot = htoi(a[end]);
    int pIndex = start;
    for (int i = start; i < end; i++)
    {
        if ((htoi(a[i]) <= pivot))
        {
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
    swap(a[pIndex], a[end]);
    return pIndex;
}

//Алгоритм быстрой сортировки
void quicksort(string a[], int start, int end)
{
    if (start >= end) {
        return;
    }
    int pivot = partition(a, start, end);
    quicksort(a, start, pivot - 1);
    quicksort(a, pivot + 1, end);
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    signal(SIGINT, SIG_IGN);
    string matrix[4][4];
    string selector;
    string line;
    cout << "Введите 0, если хотите автоматически заполнить матрицу,"
        << "или 1 для самостятельного заполнения" << endl;
    getline(cin, selector);
    while (selector != "1" && selector != "0") {
        cout << "Введено некорректное значение" << endl;
        cin.clear();
        getline(cin, selector);
    }
    if (selector == "0") {
        for (int i = 0; i < 16; i++) { matrix[i / 4][i % 4] = itoh(rand() % (256)); }
    }
    else {
        cout << "Введите значения матрицы" << endl;
        for (int i = 0; i < 16; i++) {
            getline(cin, line);
            while (!is_hex(line) || line.length() != 2) {
                cout << "Ошибка ввода. Введите двухзначное шестнадцатеричное число" << endl;
                cin.clear();
                getline(cin, line);
            }
            matrix[i / 4][i % 4] = line;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        quicksort(matrix[i], 0, 3);
        if (i % 2 == 0) {
            swap(matrix[i][0], matrix[i][3]);
            swap(matrix[i][1], matrix[i][2]);
        }
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

