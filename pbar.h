// -*- C++ -*-
//
// Copyright (c) S-Patriarch, 2023
// Индикаторы выполнения и работа с ними.
//
// (PTL) Patriarch library : pbar.h

#pragma once
#if !defined( __PTL_PBAR_H__ )
#define __PTL_PBAR_H__

#if !defined( __PTL_PTYPE_H__ )
#include "ptype.h"
#endif

#if !defined( __PTL_PCOLOR_H__ )
#include "pcolor.h"
#endif

#include <iostream>
#include <string>

// Методы:
//  - set_min() - установка минимальной процентной итерации
//  - set_max() - установка максимальной процентной итерации
//  - set_style() - установка стиля индикатора
//  - set_message() - установка сообщения индикатора
//  - set_brackets() - установка границ индикатора
//  - set_color() - установка цвета индикатора
//  - get_min() - получение минимальной процентной итерации
//  - get_max() - получение максимальной процентной итерации
//  - update() - обновление отрисовки индикатора выполнения
//
// @code
//   ptl::pBar pb;
//   ptl::hcrs();
//   for( ptl::__u32 i{ pb.get_min() }; i <= pb.get_max(); ++i )
//     {
//     pb.update( i );
//     // выполнение операций...
//     }
//   ptl::scrs();
// @endcode

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  class pBar
    {
    public:
      pBar();
      ~pBar() noexcept
        { }

      auto set_min( __u32 ) -> void;
      auto set_max( __u32 ) -> void;
      auto set_style( std::string, std::string ) -> void;
      auto set_style( std::string, std::string, std::string ) -> void;
      auto set_message( std::string ) -> void;
      auto set_brackets( std::string, std::string ) -> void;
      auto set_color( Color ) -> void;
      auto get_min() -> __u32;
      auto get_max() -> __u32;
      auto update( __u32 ) -> void;

    private:
      __u32        _M_minIterations;
      __u32        _M_maxIterations;
      __u16        _M_barWidth;
      Color        _M_barColor;
      std::string  _M_bar;
      std::string  _M_style;
      std::string  _M_percent;
      std::string  _M_message;
      std::string  _M_bracketLeft;
      std::string  _M_bracketRigth;
    };
//--------------------------------------------------------------------
// Конструктор.
//
  pBar::pBar()
    {
    _M_minIterations = 0;
    _M_maxIterations = 100;
    _M_barWidth      = 30;
    _M_barColor      = CURRENT;
    _M_bar           = "=";
    _M_style         = "complete";
    _M_percent       = "%";
    _M_message       = "";
    _M_bracketLeft   = "[";
    _M_bracketRigth  = "]";
    }
//--------------------------------------------------------------------
// Установка минимальной процентной итерации.
//
  auto
  pBar::set_min( __u32 _min ) -> void
    { _M_minIterations = _min; }
//--------------------------------------------------------------------
// Установка максимальной процентной итерации.
//
  auto
  pBar::set_max( __u32 _max ) -> void
    { _M_maxIterations = _max; }
//--------------------------------------------------------------------
// Установка стиля индикатора.
//
  auto
  pBar::set_style( std::string _style, 
                   std::string _percent ) -> void
    {
    _M_style   = _style;
    _M_percent = _percent;
    }
//--------------------------------------------------------------------
// Установка стиля индикатора.
//
  auto
  pBar::set_style( std::string _style, 
                   std::string _percent,
                   std::string _bar ) -> void
    {
    _M_style   = _style;
    _M_percent = _percent;
    _M_bar     = _bar;
    }
//--------------------------------------------------------------------
// Установка сообщения индикатора.
//
  auto
  pBar::set_message( std::string _message ) -> void
    { _M_message = _message; }
//--------------------------------------------------------------------
// Установка границ индикатора.
//
  auto
  pBar::set_brackets( std::string _bracketLeft,
                      std::string _bracketRigth ) -> void
    {
    _M_bracketLeft  = _bracketLeft;
    _M_bracketRigth = _bracketRigth;
    }
//--------------------------------------------------------------------
// Установка цвета индикатора.
//
  auto
  pBar::set_color( Color _color ) -> void
    { _M_barColor = _color; }
//--------------------------------------------------------------------
// Получение минимальной процентной итерации.
//
  auto
  pBar::get_min() -> __u32
    { return _M_minIterations; }
//--------------------------------------------------------------------
// Получение максимальной процентной итерации.
//
  auto
  pBar::get_max() -> __u32
    { return _M_maxIterations; }
//--------------------------------------------------------------------
// Обновление отрисовки индикатора выполнения.
//
  auto
  pBar::update( __u32 _index ) -> void
    {
    // вычисление процента выполнения
    float  _progress{ static_cast< float >( _index ) / _M_maxIterations };
    __u16  _completedWidth{ static_cast< __u16 >( _progress * _M_barWidth ) };

    pColor c;

    // вывод индикатора выполнения
    std::cout << _M_bracketLeft;

    for( __u16 i{ 0 }; i <= _M_barWidth; ++i )
      {
      if( i <= _completedWidth )
        {
        if( _M_barColor == CURRENT )
          {
          std::cout 
            << _M_bar;
          }
        else
          {
          std::cout 
            << c.esc_tb( _M_barColor )
            << _M_bar
            << c.esc_c();
          }
        }
      else
        {
        std::cout 
          << " ";
        }
      }

    std::cout 
      << _M_bracketRigth
      << " "
      << __u16( _progress * 100.0 )
      << _M_percent
      << " "
      << _M_message
      << "\r";

    std::cout.flush();
    }

  } // namespace ptl

#endif // __PTL_PBAR_H__