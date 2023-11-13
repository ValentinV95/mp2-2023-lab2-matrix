﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
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
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Size should be greater than zero");
    else if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
      if (sz == 0)
          throw out_of_range("Size should be greater than zero");
      else if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[]pMem;
      pMem = nullptr;
      sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      if (sz != v.sz)
      {
          T* p = new T[v.sz];
          delete[]pMem;
          sz = v.sz;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
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
          throw out_of_range("This object doesn't contain the element you're trying to access");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("This object doesn't contain the element you're trying to access");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] += val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] -= val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] *= val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      TDynamicVector tmp(*this);
      if (sz != v.sz) throw invalid_argument("Impossible to add two objects with different sizes");
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] += v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("Impossible to subtract two objects with different sizes");
      TDynamicVector tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] -= v.pMem[i];
      return tmp;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("Impossible to multiply two objects with different sizes");
      T res=0;
      for (size_t i = 0; i < sz; i++)
          res+= pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz) ;
    std::swap(lhs.pMem, rhs.pMem);
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
      if (sz == 0)
          throw out_of_range("Matrix size should be greater than zero");
      else if (sz > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size should be less than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::operator=;
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;


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
  TDynamicMatrix<T> operator*(const T& val)
  {
      TDynamicMatrix tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = tmp.pMem[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) throw invalid_argument("Impossible to multiply matrix and vector with different sizes");
      TDynamicVector<T> tmp(sz);
          for (size_t i = 0; i < sz; i++)
              tmp[i] = pMem[i] * v;
          return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if(sz!=m.sz)
          throw invalid_argument("Impossible to add two matrices with different sizes");
      TDynamicMatrix tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = tmp.pMem[i] + m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Impossible to subtract two matrices with different sizes");
      TDynamicMatrix tmp(*this);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = tmp.pMem[i] - m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw invalid_argument("Impossible to multiply two matrices with different sizes");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t k = 0; k < sz; k++)
              for (size_t j = 0; j < sz; j++)
                  res[i][j] += pMem[i][k] * m.pMem[k][j];
      return res;

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << endl;
      return ostr;
  }
};

#endif
