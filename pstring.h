// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со строками 
 */

/**
 *  (PTL) Patriarch library : pstring.h
 */

#ifndef _PTL_PSTRING
#define _PTL_PSTRING 1

#include "ptype.h"
#include <iostream>
#include <cstring>
#include <utility>

namespace ptl
{
  /*
   * Класс строка.
   *
   * Конструкторы:
   *   - явный конструктор создания
   *   - конструктор копирования
   *   - конструктор присваения копирования
   *   - конструктор перемещения
   *   - конструктор присвоения перемещения
   * Методы:
   *   - size() - возвращает размер строки
   *   - swap() - обмен значениями двух объектов
   */

  class pstring 
  {
  private:
    __u16  _M_size{ };   // Размер строки
    char*  _M_string{ }; // Указатель на строку

  public:
    explicit pstring(const char* __s)
    {
      _M_size   = strlen(__s) + 1;
      _M_string = new char[_M_size];

      strcpy(_M_string, __s);
    }

    pstring(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      strcpy(_M_string, __other._M_string);
    }

    pstring& 
    operator=(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      strcpy(_M_string, __other._M_string);
    }

    /** Конструктор копирования перемещения
     */
    pstring(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = mullptr;
      __other._M_size   = 0;
    }

    /** Конструктор присваивания перемещения
     */
    pstring& 
    operator=(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = mullptr;
      __other._M_size   = 0;

      return *this;
    }

    ~pstring() noexcept
    { delete[] _M_string; }

    /*
     * Метод, возвращающий размер строки
     */
    auto
    size() -> __u16
    { return _M_size; }

    /*
     * Обмен значениями двух объектов
     */
    auto
    swap(pstring& __a, pstring& __b) -> void
    {
      pstring __temp{ std::move(__a) };
      __a = std::move(__b);
      __b = std::move(__temp);
    }

    friend ostream& 
    operator<<(ostream& __os, const pstring& __s);
  };

  ostream& 
  operator<<(ostream& __os, const pstring& __s)
  {
    __os << __s._M_string;
    return __os;
  }

} // namespace ptl

#endif // _PTL_PSTRING