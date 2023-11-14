﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
#include <string>
//---------------------------------------------------------------------------

template<typename T>
void Asker(TDynamicMatrix<T> &to) {
    int buf;
    cin >> buf;
    if (cin.fail()) {
        throw invalid_argument("Not number");
    }
    to = TDynamicMatrix<T>(buf);
    cout << "Введите элементы матрицы слева направо сверху вниз: " << endl;
    cin >> to;
}

void main()
{
    TDynamicMatrix<int> a; TDynamicMatrix<int> b;
    TDynamicMatrix<int> c;
    setlocale(LC_ALL, "Russian");
    char buf = '\0';
    string err_bufer;
    char ops;
    cout << "Тестирование класс работы с матрицами" << endl;
    do {
        try {
            cout << "Введите размер матрицы A: " << endl;
            Asker(a);
            cout << "Введите размер матрицы B: " << endl;
            Asker(b);
        }
        catch (const out_of_range &e) {
            cout << "Exception: " << e.what() << endl;
            continue;
        }
        catch (const invalid_argument &e) {
            cout << "Exception: " << e.what() << endl;
            cin.clear();
            getline(cin, err_bufer);
            continue;
        }
        cout << "Matrix a = " << endl << a;
        cout << "Matrix b = " << endl << b;
        cout << "Введите операцию (+, -, *): " << endl;
        cin >> ops;
        try {
            switch (ops) {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            default:
                throw invalid_argument("Неверный ввод.");
            }
        }
        catch (const exception &e) {
            cout << "Exception: " << e.what() << endl;
            continue;
        }
        cout << "Matrix c = a " << ops << " b:" << endl << c;
        cout << "Продолжить? (Нет - n/N)" << endl;
        cin >> buf;
        cin.clear();
        getline(cin, err_bufer);
    } while (buf != 'n' && buf != 'N');
}
//---------------------------------------------------------------------------
