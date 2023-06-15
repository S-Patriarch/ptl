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
#include <chrono>
#include <thread>

namespace ptl
{
  /*
   * Класс индикаторов выполнения.
   *
   * Конструкторы:
   *   - конструктор создания
   * Методы:
   *   - get_min()
   *   - get_max()
   *   - progress_bar()
   *
   * @code
   *   ptl::pbar pb;
   *   ptl::hcrs();
   *   for( ptl::__u32 __i{ pb.get_min() }; __i <= pb.get_max(); ++__i )
   *     {
   *       pb.progress_bar( __i );
   *       // Выполнение операций...
   *     }
   *   ptl::scrs();
   * @endcode
   */

  class pbar
  {
  private:
    __u32        _M_current_iteration;
    __u32        _M_total_iterations;
    __s32        _M_sleep;
    __u16        _M_bar_width;
    __u16        _M_bar_color;
    std::string  _M_bar;

  public:
    pbar()
    {
      _M_current_iteration = 0;
      _M_total_iterations  = 100;
      _M_sleep             = 50;
      _M_bar_width         = 30;
      _M_bar_color         = 1000;
      _M_bar               = "=";
    }

    ~pbar() noexcept
    { }

    auto
    get_min() -> __u32
    { return _M_current_iteration; }

    auto
    get_max() -> __u32
    { return _M_total_iterations; }

    auto
    progress_bar( __u32 __index ) -> void
    {
      float  __progress{ static_cast<float>( __index ) / _M_total_iterations };
      __u16  __completed_width{ static_cast<__u16>( __progress * _M_bar_width ) };

      pcolor c;

      std::cout << "[";

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
            std::cout << " " ;
        }

      std::cout << "] "
                << ptl::__u16( __progress * 100.0 )
                << "%"
                << '\r';
      std::cout.flush();

      std::this_thread::sleep_for( std::chrono::milliseconds( _M_sleep ) );
    }
  };

} // namespace ptl

#endif // _PTL_PBAR_H