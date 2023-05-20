// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с цветовой схемой терминала
 */

/**
 *  (PTL) Patriarch library : pcolor.h
 */

#ifndef _PTL_COLOR
#define _PTL_COLOR 1

#include "ptype.h"
#include "pexcept.h"
#include <string>

namespace ptl
{
  /*
   * Класс описывает работу с цветовой esc-последовательностью в 
   * терминале (консоле)
   * 
   * Конструкторы:
   *   - конструктор создания
   * Методы:
   *   - esc_c()  - возвращает строку сброса цветовой esc-последовательности
   *   - esc_tr() - возвращает строку обычной цветовой esc-последовательности
   *   - esc_tb() - возвращает строку жирной цветовой esc-последовательности
   */

  class pcolor
  {
  protected:
    __u16         _M_size_array{ 8 };    // Размер массива строк
    std::string*  _M_text_color_regular; // Указатель на массив строк
    std::string*  _M_text_color_bold;    // Указатель на массив строк
    std::string   _M_color_clear;

  public:
    pcolor()
    { 
      _M_color_clear = "\x1b[0m";

      _M_text_color_regular = new std::string[_M_size_array]
      { 
        "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m", 
        "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m"
      };

      _M_text_color_bold = new std::string[_M_size_array]
      { 
        "\x1b[30;1m", "\x1b[31;1m", "\x1b[32;1m", "\x1b[33;1m", 
        "\x1b[34;1m", "\x1b[35;1m", "\x1b[36;1m", "\x1b[37;1m"
      };
    }

    virtual
    ~pcolor() noexcept
    { 
      delete[] _M_text_color_regular;
      delete[] _M_text_color_bold; 
    }

    /*
     * Возвращает строку сброса цветовой esc-последовательности.
     */
    auto
    esc_c() -> std::string
    { return _M_color_clear; }

    /*
     * Возвращает строку цветовой esc-последовательности обычной
     * насыщенности по заданному __index от 0 до 7 включительно.
     * __index{8} - это терминирующий цвет esc-последовательности.
     */
    auto
    esc_tr(__u16 __index) -> std::string
    {
      /** Проверяем __index на одекватность.
       */
      if (__index < 0 || __index >= _M_size_array)
        throw
        pexception("E: Индекс цвета не приемлем.");

      return _M_text_color_regular[__index];
    }

    /*
     * Возвращает строку цветовой esc-последовательности жирной
     * насыщенности по заданному __index от 0 до 7 включительно.
     * __index{8} - это терминирующий цвет esc-последовательности.
     */
    auto
    esc_tb(__u16 __index) -> std::string
    {
      /** Проверяем __index на одекватность.
       */
      if (__index < 0 || __index >= _M_size_array)
        throw
        pexception("E: Индекс цвета не приемлем.");

      return _M_text_color_bold[__index];
    }
  };

} // namespace ptl

#endif // _PTL_COLOR