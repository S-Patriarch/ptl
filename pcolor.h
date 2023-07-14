// -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Работа с цветовой esc-последовательностью в
// терминале (консоле).
//
// (PTL) Patriarch library : pcolor.h

#pragma once
#if !defined( __PTL_PCOLOR_H__ )
#define __PTL_PCOLOR_H__

#include <string>

// Методы:
//  - esc_c()  - сбрасывает цветовую esc-последовательность
//  - esc_tr() - устанавливает обычный цвет текста
//  - esc_tb() - устанавливает жирный цвет текста
//  - esc_br() - устанавливает обычный цвет фона
//  - esc_bb() - устанавливает жирный цвет фона

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  enum Color
    {
    BLACK   = 0, RED     = 1, GREEN = 2, YELLOW = 3,
    BLUE    = 4, MAGENTA = 5, CYAN  = 6, WHITE  = 7,
    CURRENT = 1000
    };
//////////////////////////////////////////////////////////////////////
  class pColor
    {
    public:
      pColor();

      virtual
      ~pColor() noexcept
        { 
        delete[] _M_textColorRegular;
        delete[] _M_textColorBold; 
        delete[] _M_backgroundColorRegular;
        delete[] _M_backgroundColorBold;
        }

      auto esc_c() -> std::string;
      auto esc_tr( Color ) -> std::string;
      auto esc_tb( Color ) -> std::string;
      auto esc_br( Color ) -> std::string;
      auto esc_bb( Color ) -> std::string;

    protected:
      unsigned short int  _M_sizeArray{ 8 };

      std::string*        _M_textColorRegular; 
      std::string*        _M_textColorBold;    
      std::string*        _M_backgroundColorRegular;
      std::string*        _M_backgroundColorBold;
      std::string         _M_colorClear;
    };
//--------------------------------------------------------------------
// Конструктор.
//
  pColor::pColor()
    { 
    _M_colorClear = "\033[0m";

    _M_textColorRegular = new std::string[ _M_sizeArray ]
      { 
      "\033[30m", "\033[31m", "\033[32m", "\033[33m", 
      "\033[34m", "\033[35m", "\033[36m", "\033[37m"
      };

    _M_textColorBold = new std::string[ _M_sizeArray ]
      { 
      "\033[30;1m", "\033[31;1m", "\033[32;1m", "\033[33;1m", 
      "\033[34;1m", "\033[35;1m", "\033[36;1m", "\033[37;1m"
      };

    _M_backgroundColorRegular = new std::string[ _M_sizeArray ]
      { 
      "\033[40m", "\033[41m", "\033[42m", "\033[43m", 
      "\033[44m", "\033[45m", "\033[46m", "\033[47m"
      };

    _M_backgroundColorBold = new std::string[ _M_sizeArray ]
      { 
      "\033[40;1m", "\033[41;1m", "\033[42;1m", "\033[43;1m", 
      "\033[44;1m", "\033[45;1m", "\033[46;1m", "\033[47;1m"
      };
    }
//--------------------------------------------------------------------
// Возвращает строку сброса цветовой esc-последовательности.
//
  auto
  pColor::esc_c() -> std::string
    { return _M_colorClear; }
//--------------------------------------------------------------------
// Устанавливает цвет текста.
// Возвращает строку цветовой esc-последовательности обычной
// насыщенности по заданному _index от 0 до 7 включительно.
//
  auto
  pColor::esc_tr( Color _index ) -> std::string
    { return _M_textColorRegular[ _index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет текста.
// Возвращает строку цветовой esc-последовательности жирной
// насыщенности по заданному _index от 0 до 7 включительно.
//
  auto
  pColor::esc_tb( Color _index ) -> std::string
    { return _M_textColorBold[ _index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет фона.
// Возвращает строку цветовой esc-последовательности обычной
// насыщенности по заданному _index от 0 до 7 включительно.
//
  auto
  pColor::esc_br( Color _index ) -> std::string
    { return _M_backgroundColorRegular[ _index ]; }
//--------------------------------------------------------------------
// Устанавливает цвет фона.
// Возвращает строку цветовой esc-последовательности жирной
// насыщенности по заданному _index от 0 до 7 включительно.
//
  auto
  pColor::esc_bb( Color _index ) -> std::string
    { return _M_backgroundColorBold[ _index ]; }

  } // namespace ptl

#endif // __PTL_PCOLOR_H__