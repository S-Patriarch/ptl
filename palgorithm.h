// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с алгоритмами.
 */

/**
 *  (PTL) Patriarch library : palgorithm.h
 */

#pragma once
#if !defined(_PTL_PALGORITHM)
#define _PTL_PALGORITHM

#include "ptype.h"
#include <utility>

/*
 * Функции:
 *   - get_max() - нахождение максимального элемента массива
 *   - swap() - обмен значениями двух объектов
 *   - quick_sort() - быстрая сортировка
 *   - bubble_sort() - пузырьковая сортировка
 */

namespace ptl
{
  /* 
   * Нахождение максимального элемента массива.
   */
  template <typename _Tp> 
    auto
    get_max(_Tp* __array, __u32 __size_array) -> _Tp
    {
      _Tp __max{ __array[0] };

      for (__u32 __i{0}; __i < __size_array; __i++)
        {
          if (__array[__i] > __max)
            {
              __max = __array[__i];
            }
        }

      return __max;
    }

  /* 
   * Обмен значениями двух объектов.
   * 
   * Эта функция включает в себя конструкцию копирования и две
   * операции присваивания, что может быть не самым эффективным
   * способом замены содержимого классов, хранящих большие объемы
   * данных, поскольку каждая из этих операций обычно работает в 
   * линейном времени над их размером.
   * 
   * Примечательно, что все стандартные контейнеры специализируются
   * таким образом, что вместо всего их содержимого меняются местами
   * только несколько внутренних указателей, что заставляет их
   * работать в реальном времени.
   * 
   * @code
   *   int x=10, y=20;                // x:10 y:20
   *   ptl::swap(x,y);                // x:20 y:10
   * 
   *   int foo[3];                    // foo: ?  ?  ?
   *   int bar[]={10,20,30};          // foo: ?  ?  ?   bar: 10 20 30
   *   ptl::swap(foo,bar);            // foo: 10 20 30  bar: ?  ?  ?
   * 
   *   std::cout << "foo contains:";
   *   for (int i: foo) std::cout << ' ' << i;
   *   std::cout << '\n';
   * @endcode
   */
  template <typename _Tp> 
    auto 
    swap(_Tp& __a, _Tp& __b) -> void
    { 
      _Tp __c{ std::move(__a) }; 
      __a = std::move(__b); 
      __b = std::move(__c); 
    }

  /*
   * Быстрая сортировка.
   * Данный алгоритм сортировки разработан Ч.Э.Р. Хоаром в 1960 году
   * 
   * @code
   *   ptl::quick_sort<int>(__array, 0, cst::_Size_Array-1);
   * @endcode
   */
  template <typename _Tp>
    auto
    quick_sort(_Tp* __array, __u32 __low, __u32 __high) -> void
    {
      __u32 __i{ __low };
      __u32 __j{ __high };
      _Tp   __y{ };
      _Tp   __z{ __array[(__low + __high) / 2] }; // Опорный элемент
      
      do
        {
          while (__array[__i] < __z) __i++;
          while (__array[__j] > __z) __j--;

          if (__i <= __j)
            {
              if (__array[__i] > __array[__j])
                {
                  __y = __array[__i];
                  __array[__i] = __array[__j];
                  __array[__j] = __y;
                }
              __i++;
              __j--;
            }
        }
      while (__i <= __j);

      // Рекурсия
      if (__low < __j)  quick_sort(__array, __low, __j);
      if (__i < __high) quick_sort(__array, __i, __high);
    }

  /*
   * Пузырьковая сортировка.
   * 
   * @code
   *   ptl::bubble_sort<int>(__array, cst::_Size_Array);
   * @endcode
   */
  template <typename _Tp>
    auto
    bubble_sort(_Tp* __array, __u32 __size_array) -> void
    {
      for (__u32 __i{ 0 }; __i < __size_array; __i++)
        {
          bool __flag{ true };

          for (__u32 __j{ 0 }; __j < __size_array - (__i+1); __j++)
            {
              if (__array[__j] > __array[__j+1])
                {
                  __flag = false;

                  _Tp __b{ __array[__j] };
                  __array[__j]   = __array[__j+1];
                  __array[__j+1] = __b;
                }
            }

          if (__flag) break;  
        }
    }

} // namespace ptl

#endif // _PTL_PALGORITHM