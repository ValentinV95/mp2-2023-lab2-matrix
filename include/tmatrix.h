﻿﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template <typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if ((sz==0)||(sz>MAX_VECTOR_SIZE))
            throw out_of_range("Vector size should be greater then zero and less than or equal to MAX_VECTOR_SIZE");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
        sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz) 
        {
            sz = v.sz;
            delete[] pMem;
            pMem = new T[sz]();
        }
        for (int i = 0; i < sz; i++) 
        {
            pMem[i] = v.pMem[i];
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (*this == v) 
            return *this;
        delete[] pMem;
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index should be less than size of the vector");
        else return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index should be less than size of the vector");
        else return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        for (int i = 0; i < sz; i++) 
        {
            if (pMem[i] != v.pMem[i])
                return false;
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors should have same sizes");
       TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors should have same sizes");
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors should have same sizes");
        T res = 0;
        for (int i = 0; i < sz; i++)
        {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        swap(lhs.sz, rhs.sz);
        swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if ((s == 0) || (s > MAX_MATRIX_SIZE))
            throw out_of_range("Matrix size should be greater than zero and less than or equal to MAX_MATRIX_SIZE");
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::size;

    T& at(size_t i, size_t j)
    {
        if ((i >= sz) || (j >= sz))
            throw out_of_range("Number of index should be less than size matrix size");
        return pMem[i][j];
    }

    const T& at(size_t i, size_t j) const
    {
        if ((i >= sz) || (j >= sz))
            throw out_of_range("Number of index should be less than size matrix size");
        return pMem[i][j];
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator!=(m);
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw invalid_argument("Matrix and vector should have same sizes");
        TDynamicVector<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res[i] = pMem[i] * v;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices should have same sizes");
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res[i] = pMem[i] + m[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices should have same sizes");
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++)
        {
            res[i] = pMem[i] - m[i];
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices should have same sizes");
        TDynamicMatrix<T> res(sz);
        for (int i = 0; i < sz; i++)
            for (int k = 0; k < sz; k++)
                for (int j = 0; j < sz; j++)
                    res[i][j] += pMem[i][k] * m.pMem[k][j];
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            for (size_t j = 0; j < v.sz; j++)
                istr >> v.pMem[i][j];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            for (size_t j = 0; j < v.sz; j++)
                ostr << v.pMem[i][j] << ' ';
            ostr << "\n";
        }
        return ostr;
    }
};

#endif

