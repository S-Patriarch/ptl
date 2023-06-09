// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с цветовой схемой терминала
 */

/**
 *  (PTL) Patriarch library : pcolor.h
 */

#pragma once
#if !defined(_PTL_COLOR_H)
#define _PTL_COLOR_H

#if !defined(_PTL_PTYPE_H)
#include "ptype.h"
#endif
#if !defined(_PTL_PEXCEPT_H)
#include "pexcept.h"
#endif

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
   *   - esc_c()  - сбрасывает цветовую esc-последовательность
   *   - esc_tr() - устанавливает обычный цвет текста
   *   - esc_tb() - устанавливает жирный цвет текста
   *   - esc_br() - устанавливает обычный цвет фона
   *   - esc_bb() - устанавливает жирный цвет фона
   */

  class pcolor
  {
  protected:
    __u16         _M_size_array{ 8 }; // Размер массива строк

    std::string*  _M_text_color_regular; 
    std::string*  _M_text_color_bold;    
    std::string*  _M_background_color_regular;
    std::string*  _M_background_color_bold;
    std::string   _M_color_clear;

  public:
    pcolor()
    { 
      _M_color_clear = "\033[0m";

      _M_text_color_regular = new std::string[_M_size_array]
      { 
        "\033[30m", "\033[31m", "\033[32m", "\033[33m", 
        "\033[34m", "\033[35m", "\033[36m", "\033[37m"
      };

      _M_text_color_bold = new std::string[_M_size_array]
      { 
        "\033[30;1m", "\033[31;1m", "\033[32;1m", "\033[33;1m", 
        "\033[34;1m", "\033[35;1m", "\033[36;1m", "\033[37;1m"
      };

      _M_background_color_regular = new std::string[_M_size_array]
      { 
        "\033[40m", "\033[41m", "\033[42m", "\033[43m", 
        "\033[44m", "\033[45m", "\033[46m", "\033[47m"
      };

      _M_background_color_bold = new std::string[_M_size_array]
      { 
        "\033[40;1m", "\033[41;1m", "\033[42;1m", "\033[43;1m", 
        "\033[44;1m", "\033[45;1m", "\033[46;1m", "\033[47;1m"
      };
    }

    virtual
    ~pcolor() noexcept
    { 
      delete[] _M_text_color_regular;
      delete[] _M_text_color_bold; 
      delete[] _M_background_color_regular;
      delete[] _M_background_color_bold;
    }

    /*
     * Возвращает строку сброса цветовой esc-последовательности.
     */
    auto
    esc_c() -> std::string
    { return _M_color_clear; }

    /*
     * Устанавливает цвет текста.
     * Возвращает строку цветовой esc-последовательности обычной
     * насыщенности по заданному __index от 0 до 7 включительно.
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
     * Устанавливает цвет текста.
     * Возвращает строку цветовой esc-последовательности жирной
     * насыщенности по заданному __index от 0 до 7 включительно.
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

    /*
     * Устанавливает цвет фона.
     * Возвращает строку цветовой esc-последовательности обычной
     * насыщенности по заданному __index от 0 до 7 включительно.
     */
    auto
    esc_br(__u16 __index) -> std::string
    {
      /** Проверяем __index на одекватность.
       */
      if (__index < 0 || __index >= _M_size_array)
        throw
        pexception("E: Индекс цвета не приемлем.");

      return _M_background_color_regular[__index];
    }

    /*
     * Устанавливает цвет фона.
     * Возвращает строку цветовой esc-последовательности жирной
     * насыщенности по заданному __index от 0 до 7 включительно.
     */
    auto
    esc_bb(__u16 __index) -> std::string
    {
      /** Проверяем __index на одекватность.
       */
      if (__index < 0 || __index >= _M_size_array)
        throw
        pexception("E: Индекс цвета не приемлем.");

      return _M_background_color_bold[__index];
    }
  };

} // namespace ptl

#endif // _PTL_COLOR_H