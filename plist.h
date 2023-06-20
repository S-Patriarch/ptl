// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы со 
 * связанным списком данных.
 */

/**
 *  (PTL) Patriarch library : plist.h
 */

#pragma once
#if !defined( _PTL_PLIST_H )
#define _PTL_PLIST_H

#if !defined( _PTL_PTYPE_H )
#include "ptype.h"
#endif

#include <iostream>

namespace ptl
  {

  /*
   * Связанный список данных. 
   *
   * Методы:
   *   - push_back() - вставка в конец списка
   *   - push_front() - вставка в начало списка
   *   - insert() - вставка в середину списка
   *   - delete_node() - удаление узла списка по значению
   *   - delete_pos() - удаление узла списка по позиции
   *   - show() - вывод содержимого списка через пробел
   *   - clear() - удаление всего списка
   *
   * @code
   *   ptl::plist<ptl::__s32> list;
   *   list. ...;
   * @endcode
   */

  /*
   * Узел связанного списка данных.
   */
  template <typename _Tp> 
  class pnode
    {
    public:
      pnode( _Tp __data ) : _M_data( __data ), _M_next( nullptr )
        { }

      _Tp          _M_data; // Значение, которое хранит узел.
      pnode<_Tp>*  _M_next; // Указатель на адрес следующего узла списка.
    };

  /*
   * Связанный список, который хранит узлы, а также 
   * предоставляет методы для управления данными.
   */
  template <typename _Tp> 
  class plist
    {
    private:
      pnode<_Tp>*  _M_head; // Начало связанного списка данных.

    public:
      plist() : _M_head( nullptr )
        { }
      
      auto
      push_back( _Tp __data ) -> void
        {
        /** Создаем новый узел.
         */
        pnode<_Tp>* node = new pnode<_Tp>( __data );

        /** Если список пуст, то возвращаем узел.
         */
        if( _M_head == nullptr )
          {
          _M_head = node;
          return;
          }

        /** Ищем последний элемент списка.
         */
        pnode<_Tp>* last = _M_head;
        while( last->_M_next != nullptr )
          {
          last = last->_M_next;
          }

        /** Обновляем указатель _M_next последнего узла на 
         *  указатель на новый узел.
         */
        last->_M_next = node;
        return;
        }

      auto
      push_front( _Tp __data ) -> void
        {
        pnode<_Tp>* node = new pnode<_Tp>( __data );
        node->_M_next = _M_head;
        _M_head = node;
        }

      auto
      insert( __u32 __position, _Tp __data ) -> void
        {
        /** Создаем новый узел.
         */
        pnode<_Tp>* new_node = new pnode<_Tp>( __data );

        /** Если список пуст, то новый узел и будет началом списка.
         */
        if( _M_head == nullptr )
          {
          _M_head = new_node;
          return;
          }

        if( __position == 0)
          {
          /** Крайний случай - вставка в начало списка.
           */
          new_node->_M_next = _M_head;
          _M_head = new_node;
          return;
          }

        __u32  __curr_pos{ 0 };

        pnode<_Tp>* current = _M_head;

        /** Идем по списку, пока список не кончится, или
         *  пока не дойдем до позиции.
         */
        while( __curr_pos < __position - 1 && current->_M_next != nullptr )
          {
          current = current->_M_next;
          __curr_pos++;
          }

        /** Меняем указатель на следующий узел на
         *  указатель на новый узел.
         */
        pnode<_Tp>* next = current->_M_next;
        current->_M_next = new_node;

        /** Связываем список обратно, меняем указатель на узел,
         *  следующий после нового узла, на указатель на узел,
         *  следующий за current.
         */
        new_node->_M_next = next;
        }

      auto
      delete_node( _Tp __data ) -> void
        {
        pnode<_Tp>* temp = _M_head;
        pnode<_Tp>* prev = nullptr;

        /** Крайний случай - удаляем начало списка.
         */
        if( temp && temp->_M_data == __data )
          {
          _M_head = temp->_M_next;
          delete temp;
          return;
          }

        /** Идем по списку, пока не найдем узел со
         *  значением данных, равных ключу.
         */
        while( temp && temp->_M_data != __data )
          {
          prev = temp;
          temp = temp->_M_next;
          }

        /** Если узел не найден, возвращаем.
         */
        if( !temp )
          return;

        /** Меняем указатель следующего узла для предыдущего узла на 
         *  узел, следующий за удаляемым узлом, и удаляем узел с
         *  данными.
         */
        prev->_M_next = temp->_M_next;
        delete temp;
        }

      auto
      delete_pos( __u32 __position ) -> void
        {
        pnode<_Tp>* temp = _M_head;
        pnode<_Tp>* prev = nullptr;

        /** Крайний случай - удаляем начало списка.
         */
        if( __position == 0 )
          {
          _M_head = temp->_M_next;
          delete temp;
          return;
          }

        __u32  __curr_pos{ 0 };

        while( __curr_pos < __position && temp->_M_next != nullptr )
          {
          prev = temp;
          temp = temp->_M_next;
          __curr_pos++;
          }

        /** Если узел не найден, возвращаем.
         */
        if( !temp )
          return;

        /** Меняем указатель следующего узла для предыдущего узла на 
         *  узел, следующий за удаляемым узлом, и удаляем узел с
         *  данными.
         */
        prev->_M_next = temp->_M_next;
        delete temp;
        }

      auto
      show() -> void
        {
        pnode<_Tp>* currend = _M_head;

        while( currend != nullptr )
          {
          std::cout << currend->_M_data
                    << " ";
          currend = currend->_M_next;
          }
        }

      auto
      clear() -> void
        {
        pnode<_Tp>* currend = _M_head;

        while( currend != nullptr )
          {
          pnode<_Tp>* temp = currend->_M_next;
          delete currend;
          currend = temp;
          }

        _M_head = nullptr;
        }
    };

  } // namespace ptl

#endif // _PTL_PLIST_H