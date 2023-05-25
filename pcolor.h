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
#ifndef _PTL_COLOR
#define _PTL_COLOR

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

      _M_background_color_regular = new std::string[_M_size_array]
      { 
        "\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m", 
        "\x1b[44m", "\x1b[45m", "\x1b[46m", "\x1b[47m"
      };

      _M_background_color_bold = new std::string[_M_size_array]
      { 
        "\x1b[40;1m", "\x1b[41;1m", "\x1b[42;1m", "\x1b[43;1m", 
        "\x1b[44;1m", "\x1b[45;1m", "\x1b[46;1m", "\x1b[47;1m"
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

#endif // _PTL_COLOR