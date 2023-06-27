// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для очереди.
 */

/**
 *  (PTL) Patriarch library : pqueue.h
 */

#pragma once
#if !defined( _PTL_PQUEUE_H )
#define _PTL_PQUEUE_H

#if !defined( _PTL_PNODE_H )
#include "pnode.h"
#endif

#if !defined(_PTL_PEXCEPT_H)
#include "pexcept.h"
#endif

#include <iostream>

/*
 * Очередь. 
 *
 * Методы:
 *   - is_empty() - проверка, пуста ли очередь (true - пуста, false - нет)
 *   - en_queue() - добавление элемента в конец очереди
 *   - de_queue() - удаление элемента с конца очереди
 *   - peek() - просмотр элемента начала очереди
 *   - show() - вывод содержимого очереди через пробел
 *
 * @code
 *   ptl::pqueue<ptl::__s32> queue;
 *   queue. ...;
 * @endcode
 */

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  /*
   * Очередь.
   * Реализован посредствам связанного списка.
   * (первый пришел, первый ушел)
   */
  template <typename _Tp> 
  class pqueue
    {
    private:
      pnode<_Tp>*  _M_front; // Начало очереди.
      pnode<_Tp>*  _M_rear;  // Конец очереди.

    public:
      pqueue() 
        : _M_front( nullptr ), _M_rear( nullptr )
        { }

      ~pqueue() noexcept
        { }
//--------------------------------------------------------------------
    auto
    is_empty() -> bool
      { return _M_front == nullptr; }
//--------------------------------------------------------------------
    auto
    en_queue( const _Tp& __data ) -> void
      {
      pnode<_Tp>* 
      temp = new pnode( __data );

      if( _M_rear == nullptr )
        {
        _M_front = temp;
        _M_rear  = temp;
        return;
        }

      _M_rear->_M_next = temp;
      _M_rear = temp;
      }
//--------------------------------------------------------------------
    auto
    de_queue() -> void
      {
      if( is_empty() )
        throw 
        pexception("W: Очередь пуста.");

      // Удаляем первый узел в очереди.
      pnode<_Tp>* temp = _M_front;
      _M_front = _M_front->_M_next;

      // Если очередь пуста, необходимо обновить значение _M_rear.
      if( _M_front == nullptr )
        _M_rear = nullptr;

      delete temp;
      }
//--------------------------------------------------------------------
    auto
    peek() -> _Tp
      {
      if( is_empty() )
        throw 
        pexception("W: Очередь пуста.");

      return _M_front->_M_data;
      }
//--------------------------------------------------------------------
    auto
    show() -> void
      {
      if( is_empty() )
        throw 
        pexception("W: Очередь пуста.");

      pnode<_Tp>* temp = _M_front;

      while( temp != nullptr )
        {
        std::cout << temp->_M_data
                  << " ";
        temp = temp->_M_next;
        }
      }
    };

  } // namespace ptl

#endif // _PTL_PQUEUE_H