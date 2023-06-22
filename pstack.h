// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со стеком.
 */

/**
 *  (PTL) Patriarch library : pstack.h
 */

#pragma once
#if !defined( _PTL_PSTACK_H )
#define _PTL_PSTACK_H

#if !defined( _PTL_PNODE_H )
#include "pnode.h"
#endif

#if !defined( _PTL_PTYPE_H )
#include "ptype.h"
#endif

#if !defined(_PTL_PEXCEPT_H)
#include "pexcept.h"
#endif

/*
 * Стек.
 * Реализован посредствам связанного списка.
 *
 * Методы:
 *   - is_empty() - проверяет стек на пустату (true - пуст, false - нет)
 *   - push() - добавляет элемент на вершину стека
 *   - pop() - удаляет элемент с вершины стека и возращает его значение
 *   - peek() - выводит значение элемента с вершины стека
 */

namespace ptl
  {

  template <typename _Tp> 
  class pstack
    {
    private:
      pnode<_Tp>*  _M_top; // Указатель на вершину стека.

    public:
      pstack()
        : _M_top( nullptr )
        { }

      ~pstack() noexcept
        {
        while( _M_top )
          {
          pnode<_Tp>* 
          temp = _M_top;

          _M_top = _M_top->_M_next;

          delete temp;
          }
        }

      auto
      is_empty() -> bool
        { return _M_top == nullptr; }

      auto
      push( const _Tp& __data ) -> void
        {
        pnode<_Tp>* 
        temp = new pnode<_Tp>( __data );
        
        temp->_M_next = _M_top;
        _M_top = temp;
        }

      auto
      pop() -> _Tp
        {
        if( is_empty() )
          throw 
          pexception("E: Стек пуст.");

        _Tp  __result = _M_top->_M_data;

        pnode<_Tp>* 
        temp = _M_top;

        _M_top = _M_top->_M_next;

        delete temp;
        return __result;
        }

      auto
      peek() -> _Tp
        {
        if( is_empty() )
          throw 
          pexception("E: Стек пуст.");

        return _M_top->_M_data;
        }
    };

  } // namespace ptl

#endif // _PTL_PSTACK_H