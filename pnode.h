// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для узла
 * связанного списка.
 */

/**
 *  (PTL) Patriarch library : pnode.h
 */

#pragma once
#if !defined( _PTL_PNODE_H )
#define _PTL_PNODE_H

namespace ptl
  {
//////////////////////////////////////////////////////////////////////
  /*
   * Узел связанного списка данных.
   */
  template <typename _Tp> 
  class pnode
    {
    public:
      pnode( _Tp __data ) 
        : _M_data( __data ), _M_next( nullptr )
        { }

      _Tp          _M_data; // Значение, которое хранит узел.
      pnode<_Tp>*  _M_next; // Указатель на адрес следующего узла списка.
    };

  } // namespace ptl

#endif // _PTL_PNODE_H