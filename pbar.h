// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с индикаторами выполнения.
 */

/**
 *  (PTL) Patriarch library : pbar.h
 */

#pragma once
#if !defined( _PTL_PBAR_H )
#define _PTL_PBAR_H

#if !defined( _PTL_PTYPE_H )
#include "ptype.h"
#endif

#if !defined( _PTL_PCOLOR_H )
#include "pcolor.h"
#endif

#include <iostream>
#include <string>

/*
 * Класс индикаторов выполнения.
 *
 * Методы:
 *   - set_min() - установить минимальную процентную итерацию
 *   - set_max() - установить максимальную процентную итерацию
 *   - set_style() - установить стиль индикатора
 *   - set_message() - установить сообщение индикатора
 *   - set_brackets() - установить границы индикатора
 *   - set_color() - установить цвет индикатора
 *   - get_min() - получить минимальную процентную итерацию
 *   - get_max() - получить максимальную процентную итерацию
 *   - update() - обновить отрисовку индикатора
 *
 * @code
 *   ptl::pbar pb;
 *   ptl::hcrs();
 *   for( ptl::__u32 __i{ pb.get_min() }; __i <= pb.get_max(); ++__i )
 *     {
 *     pb.update( __i );
 *     // Выполнение операций...
 *     }
 *   ptl::scrs();
 * @endcode
 */

namespace ptl
  {

  class pbar
    {
    private:
      __u32        _M_min_iterations{ 0 };
      __u32        _M_max_iterations{ 100 };
      __u16        _M_bar_width{ 30 };
      __u16        _M_bar_color{ 1000 };
      std::string  _M_bar{ "=" };
      std::string  _M_style{ "complete" };
      std::string  _M_percent{ "%" };
      std::string  _M_message{ };
      std::string  _M_bracket_left{ "[" };
      std::string  _M_bracket_rigth{ "]" };

    public:
      pbar()
        { }

      ~pbar() noexcept
        { }

      auto
      set_min( __u32 __min ) -> void
        { _M_min_iterations = __min; }

      auto
      set_max( __u32 __max ) -> void
        { _M_max_iterations = __max; }

      auto
      set_style( std::string __style, 
                 std::string __percent ) -> void
        {
        _M_style   = __style;
        _M_percent = __percent;
        }

      auto
      set_style( std::string __style, 
                 std::string __percent,
                 std::string __bar ) -> void
        {
        _M_style   = __style;
        _M_percent = __percent;
        _M_bar     = __bar;
        }

      auto
      set_message( std::string __message ) -> void
        { _M_message = __message; }

      auto
      set_brackets( std::string __bracket_left,
                    std::string __bracket_rigth ) -> void
        {
        _M_bracket_left  = __bracket_left;
        _M_bracket_rigth = __bracket_rigth;
        }

      auto
      set_color( __u16 __color ) -> void
        { _M_bar_color = __color; }

      auto
      get_min() -> __u32
        { return _M_min_iterations; }

      auto
      get_max() -> __u32
        { return _M_max_iterations; }

      /*
       * Обновление отрисовки индикатора выполнения.
       */
      auto
      update( __u32 __index ) -> void
        {
        /** Вычисление процента выполнения.
         */
        float  __progress{ static_cast<float>( __index ) / _M_max_iterations };
        __u16  __completed_width{ static_cast<__u16>( __progress * _M_bar_width ) };

        pcolor c;

        /** Вывод индикатора выполнения.
         */
        std::cout << _M_bracket_left;

        for( ptl::__u16 __i{ 0 }; __i <= _M_bar_width; ++__i )
          {
          if( __i <= __completed_width )
            {
            if( _M_bar_color == 1000)
              std::cout << _M_bar;
            else
              std::cout << c.esc_tb( _M_bar_color )
                        << _M_bar
                        << c.esc_c();
            }
          else
            std::cout << " ";
          }

        std::cout << _M_bracket_rigth
                  << " "
                  << ptl::__u16( __progress * 100.0 )
                  << _M_percent
                  << " "
                  << _M_message
                  << "\r";

        std::cout.flush();
      }
    };

  } // namespace ptl

#endif // _PTL_PBAR_H