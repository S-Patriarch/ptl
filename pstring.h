// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со строками 
 */

/**
 *  (PTL) Patriarch library : pstring.h
 */

#pragma once
#ifndef _PTL_PSTRING
#define _PTL_PSTRING

#include "ptype.h"
#include <iostream>
#include <utility>

namespace ptl
{
  /*
   * Класс строка.
   *
   * Конструкторы:
   *   - конструктор создания
   *   - конструктор создания пустой строки
   *   - конструктор копирования
   *   - конструктор присваения копирования
   *   - конструктор перемещения
   *   - конструктор присвоения перемещения
   * Методы:
   *   - at() - возвращает указатель на строку
   *   - size() - возвращает размер строки
   *   - s_len() - возвращает размер строки
   *   - s_cpy() - копирует строку
   *   - swap() - обмен значениями двух объектов
   */

  class pstring 
  {
  private:
    __u16  _M_size;   // Размер строки
    char*  _M_string; // Указатель на строку

  public:
    pstring(char const* __s)
    {
      _M_size   = s_len(__s);
      _M_string = new char[_M_size];

      s_cpy(_M_string, __s);
    }

    pstring()
    {
      _M_size = 1;
      _M_string = new char[_M_size];
      _M_string[0] = '\0';
    }

    pstring(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      s_cpy(_M_string, __other._M_string);
    }

    pstring& 
    operator=(const pstring& __other)
    {
      _M_string = new char[__other._M_size];
      _M_size   = __other._M_size;

      s_cpy(_M_string, __other._M_string);
    }

    /** Конструктор копирования перемещения.
     */
    pstring(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = nullptr;
      __other._M_size   = 0;
    }

    /** Конструктор присваивания перемещения.
     */
    pstring& 
    operator=(pstring&& __other) noexcept
    {
      _M_string = __other._M_string;
      _M_size   = __other._M_size;

      __other._M_string = nullptr;
      __other._M_size   = 0;

      return *this;
    }

    ~pstring() noexcept
    { delete[] _M_string; }

    /*
     * Метод, возвращает указатель на строку.
     */
    auto
    at() -> char*
    { return _M_string; }

    /*
     * Метод, возвращающий размер строки.
     */
    auto
    size() -> __u16
    { return _M_size; }

    /*
     * Метод, возвращающий размер строки без
     * использования библиотечной функции strlen().
     */
    auto
    s_len(char const* __s) -> __u16
    {
      __u16 __i;
      for (__i = 0; __s[__i] != '\0'; ++__i);
      return ++__i; 
    }

    /*
     * Метод, копирует строку __s2 в __s1 без
     * использования библиотечной функции strcpy().
     */
    auto
    s_cpy(char* __s1, char const* __s2) -> char*
    {
      for (__u16 __i{0}; __i < s_len(__s2); ++__i)
        __s1[__i] = __s2[__i];
      return __s1;
    }

    /*
     * Обмен значениями двух объектов.
     */
    auto
    swap(pstring& __a, pstring& __b) -> void
    {
      pstring __temp{ std::move(__a) };
      __a = std::move(__b);
      __b = std::move(__temp);
    }

//    friend ostream& 
//    operator<<(ostream& __os, const pstring& __s);
  };
/*
  ostream& 
  operator<<(ostream& __os, const pstring& __s)
  {
    __os << __s._M_string;
    return __os;
  }
*/
} // namespace ptl

#endif // _PTL_PSTRING