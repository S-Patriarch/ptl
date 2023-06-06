// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с контейнером данных.
 */

/**
 *  (PTL) Patriarch library : pvector.h
 */

#pragma once
#if !defined(_PTL_PVECTOR)
#define _PTL_PVECTOR

#include "ptype.h"
#include "pexcept.h"

namespace ptl
{
  /*
   * Контейнер данных.
   *
   * Конструкторы:
   *   - конструктор создания
   *   - конструктор создания заданного размера
   *   - конструктор создания заданного размера и запалняет его заданным 
   *     значением
   *   - конструктор копирования
   *   - конструктор присваения копирования
   *   - конструктор перемещения
   *   - конструктор присвоения перемещения
   *   - конструктор дорступа к элеменнтам контейнера
   * Методы:
   *   - size() - возвращает размер контейнера
   *   - at() - возвращает значение элемента контейнера по заданному индексу
   *   - find_item() - ищет элемент контейнера по значению
   *   - clear() - стирает контейнер и устанавливает длину равную 0
   *   - insert() - вставлет заданное значение в заданный элемент контейнера
   *   - insert_in_beginning() - вставляет элемент в начало контейнера
   *   - insert_in_end() - вставляет элемент в конец контейнера
   *   - insert_vector() - вставляет в заданное место контейнера заданный 
   *     диапазон значений другого контейнера
   *   - erase() - удаляет элемент контейнера
   *   - reallocate() - изменяет размер контейнера с уничтожением всех элементов
   *   - resize() - изменяет размер контейнера с сохранением всех элементов
   *   - swap() - меняет местами элементы контейнера по заданным индексам
   *   - empty() - определяет, пустой ли контейнер
   *   - doubles() - вычисляет, есть ли в контейнере дубли
   *   - unique() - находит и возращает элемент контейнера, имеющий
   *     наибольшее количество повторений в контейнере
   * 
   * Варианты инициализации контейнера:
   * @code
   *   // пустой контейнер строк
   *   ptl::pvector<std::string> __array();
   *
   *   // контейнер из 3-х пустых строк
   *   ptl::pvector<std::string> __array(3);
   *
   *   // контейнер из 3-х строк "hello"
   *   ptl::pvector<std::string> __array(3, "hello");
   * @endcode
   */

  template <typename _Tp> 
  class pvector 
  {
  private:
    __u32  _M_lenght{ }; // Размер контейнера
    _Tp*   _M_data{ };   // Указатель на хранилище контейнера

  public:
    /*
     * Конструкторы.
     */

    /** Конструктор, который строит пустой контейнер.
     */
    pvector() = default;

    /** Конструктор, который строит пустой контейнер заданного размера.
     */
    pvector(__u32 __lenght)
    : _M_lenght{ __lenght }
    {
      if (__lenght <= 0)
        throw 
        pexception("E: Размер контейнера не приемлем.");

      if (__lenght > 0)
        _M_data = new _Tp[__lenght] { };
    }

    /** Конструктор, который строит контейнер заданного размера и
     *  заполняет его заданным значением.
     */
    pvector(__u32 __lenght, _Tp __value)
    : _M_lenght{ __lenght }
    {
      if (__lenght <= 0)
        throw 
        pexception("E: Размер контейнера не приемлем.");

      if (__lenght > 0)
        _M_data = new _Tp[__lenght] { };

      for (__u32 __index{ 0 }; __index < _M_lenght; ++__index)
        _M_data[__index] = __value;
    }

    /** Конструктор копирования.
     */
    pvector(pvector& __a) = delete;

    /** Конструктор перемещения.
     */
    pvector(pvector&& __a) noexcept
    : _M_lenght{ __a._M_lenght }, _M_data{ __a._M_data }
    {
      __a._M_lenght = 0;
      __a._M_data   = nullptr;
    }

    /*
     * Деструктор, который освобождает любые динамически выделенные
     * данные.
     */
    ~pvector() noexcept
    {
      /** Здесь не нужно устанавливать _M_data равный nullptr или 
       *  _M_lenght равный 0, поскольку объект в любом случае будет 
       *  уничтожен сразу после выполнения этого деструктора.
       */
      delete[] _M_data;
    }

    /*
     * Метод, возвращающий размер контейнера.
     */
    auto
    size() -> __u32
    { return _M_lenght; }

    /*
     * Метод возвращает значение элемента контейнера по заданному 
     * индексу контейнера.
     */
    auto
    at(__u32 __index) -> _Tp
    { return _M_data[__index]; }

    /*
     * Перегрузка оператора [] для получения доступа к элементам
     * контейнера.
     */
    _Tp& 
    operator[](__u32 __index)
    {
      if (__index < 0 || __index >= _M_lenght)
        throw 
        pexception("E: Значение индекса контейнера не приемлемо.");
  
      return _M_data[__index];
    }

    /*
     * Перегрузка оператора =, чтобы мы могли скопировать контейнер.
     */ 
    pvector& 
    operator=(pvector& __a) = delete;

    /*
     * Перегрузка оператора =, чтобы мы могли переместить контейнер.
     */ 
    pvector& 
    operator=(pvector&& __a) noexcept
    {
      /** Проверка самоназначения.
       */
      if (&__a == this)
        return *this;
     
      delete[] _M_data;

      _M_lenght = __a._M_lenght;
      _M_data   = __a._M_data;

      __a._M_lenght = 0;
      __a._M_data   = nullptr;

      return *this;
    }

    /*
     * Метод поиска элемента контейнера по значению.
     * Возвращает индекс, под которым находится искомый элемент 
     * контейнера.
     */
    auto
    find_item(_Tp __value) -> __u32
    {
      /** Перебираем каждый элемент контейнера, сравнивая его с заданным
       *  значением. Если присутствует совпадение, то возвращаем индекс,
       *  под которым распологается в контейнере заданное значение.
       */
      for (__u32 __index{ 0 }; __index < _M_lenght; ++__index)
        if (_M_data[__index] == __value)
          return __index;

      throw 
      pexception("E: Заданное значение в контейнере не найдено.");
    }

    /*
     * Метод стирающий контейнер и устанавливающий длину равную 0.
     */
    auto
    clear() -> void
    {
      delete[] _M_data;

      /** Нам нужно убедиться, что мы установили _M_data в nullptr, 
       *  иначе он останется указывающим на освобожденную память.
       */
      _M_lenght = 0;
      _M_data   = nullptr;
    }

    /*
     * Метод вставлет заданное значение в элемент контейнера 
     * под заданным индексом.
     */
    auto
    insert(_Tp __value, __u32 __index) -> void
    {
      /** Проверка значения индекса на вменяемость.
       */
      if (__index < 0 || __index > _M_lenght)
        throw 
        pexception("E: Значение индекса контейнера не приемлемо.");

      /** Создаем новый контейнер на 1-н элемент больше чем старый 
       *  контейнер.
       */
      _Tp* 
      __data{ new _Tp[_M_lenght+1] };

      /** Копируем все элементы вплоть до индекса.
       */
      for (__u32 __before{ 0 }; __before < __index; ++__before)
        __data[__before] = _M_data[__before];

      /** Вставляем новый элемент в новый контейнер.
       */
      __data[__index] = __value;

      /** Копируем все значения после вставленного элемента.
       */
      for (__u32 __after{ __index }; __after < _M_lenght; ++__after)
        __data[__after+1] = _M_data[__after];

      /** Удаляем старый контейнер и используем вместо него новый 
       *  контейнер.
       */
      delete[] _M_data;

      ++_M_lenght;
      _M_data = __data;
    }

    /*
     * Метод вставляет элемент в начало контейнера.
     */
    auto
    insert_in_beginning(_Tp __value) -> void
    { insert(__value, 0); }

    /*
     * Метод вставляет элемент в конец контейнера.
     */
    auto
    insert_in_end(_Tp __value) -> void
    { insert(__value, _M_lenght); }

    /*
     * Метод удаляет элемент контейнера.
     */
    auto
    erase(__u32 __index) -> void
    {
      /** Проверка значения индекса на вменяемость.
       */
      if (__index < 0 || __index >= _M_lenght)
        throw 
        pexception("E: Значение индекса контейнера не приемлемо.");

      /** Если это последний оставшийся элемент в контейнере, то 
       *  устанавливаем для контейнера значение empty и извлекаем его.
       */
      if (_M_lenght == 1)
        {
          clear();
          return;
        }

      /** Создаем новый контейнер на один элемент меньше чем старый 
       *  контейнер.
       */
      _Tp* 
      __data{ new _Tp[_M_lenght-1] };

      /** Копируем все элементы вплоть до индекса.
       */
      for (__u32 __before{ 0 }; __before < __index; ++__before)
        __data[__before] = _M_data[__before];

      /** Копируем все значения после удаленного элемента.
       */
      for (__u32 __after{ __index+1 }; __after < _M_lenght; ++__after)
        __data[__after-1] = _M_data[__after];

      /** Удаляем старый контейнер и используем вместо него новый 
       *  контейнер.
       */
      delete[] _M_data;

      --_M_lenght;
      _M_data = __data;
    }

    /*
     * Изменяет размер контейнера.
     * Все существующие элементы контейнера будут уничтожены.
     */
    auto
    reallocate(__u32 __new_lenght) -> void
    {
      /** Удалаяем все существующие элементы.
       */
      clear();

      /** Если контейнер пустой, то возвращаемся сюдаже.
       */
      if (__new_lenght <= 0)
        return;

      /** Выделяем новые элементы.
       */
      _M_lenght = __new_lenght;
      _M_data   = new _Tp[__new_lenght];
    }

    /*
     * Изменяет размер контейнера.
     * Все существующие элементы контейнера будут сохранены.
     */
    auto
    resize(__u32 __new_lenght) -> void
    {
      /** Если контейнер уже имеет нужную длинну, то заканчиваем.
       */
      if (__new_lenght == _M_lenght)
        return;

      /** Если изменяется размер до пустого контейнера, то 
       *  сделаем это и заканчиваем.
       */
      if (__new_lenght <= 0)
        {
          clear();
          return;
        }

      /** Теперь мы можем предположить, что __new_lenght - это, как 
       *  минимум, 1-н элемент.
       *  Этот алгоритм работаеи следующим образом:
       *  Сначало мы выделяем новый контейнер. Затем мы копируем элементы 
       *  из существующего контейнера в новый контейнер. Как только это 
       *  будет сделано, мы можем уничтожить старый контейнер и заставить 
       *  _M_data указывать на новый контейнер.
       */

      /** Выделяем новый контейнер.
       */
      _Tp* 
      __data{ new _Tp[__new_lenght] };

      /** Затем мы должны выяснить, сколько элементов скопировать из
       *  существующего контейнера в новый контейнер. Мы хотим скопировать
       *  столько элементов, сколько есть в меньшем из двух контейнеров.
       */
      if (_M_lenght > 0)
        {
          __u32 
          __elements_to_copy
          { (__new_lenght > _M_lenght) ? _M_lenght : __new_lenght };

          /** Теперь скопируем элементы один за другим.
           */
          for (__u32 __index{ 0 }; __index < __elements_to_copy; ++__index)
            __data[__index] = _M_data[__index];
        }

      /** Теперь мы можем удалить старый контейнер, потому что
       *  он нам больше не нужен.
       */
      delete[] _M_data;

      /** Используем вместо старого контейнера новый контейнер.
       *  Это приводит к тому, что _M_data указывает на тот же адрес, 
       *  что и новый контейнер. Потому что данные были распределены 
       *  динамически, они не будут уничтожены, когда выйдут за пределы 
       *  области видимости.
       */
      _M_lenght = __new_lenght;
      _M_data   = __data;
    }

    /*
     * Меняет местами значения элементов контейнера по заданным 
     * индексам.
     */
    auto
    swap(__u32 __index_1, __u32 __index_2) -> void
    {
      /** Проверяем __index_1 и __index_2 на вменяемость.
       */
      if (__index_1 < 0 || __index_1 >= _M_lenght)
        throw
        pexception("E: Значение индекса контейнера не приемлемо.");

      if (__index_2 < 0 || __index_2 >= _M_lenght)
        throw
        pexception("E: Значение индекса контейнера не приемлемо.");

      /** Создаем временный элемент-буфер для обмена.
       */
      _Tp __element_temp{ _M_data[__index_1] };

      /** Меняем местами элементы контейнера.
       */
      _M_data[__index_1] = _M_data[__index_2];
      _M_data[__index_2] = __element_temp;
    }

    /*
     * Определяет, пустой ли контейнер.
     */
    auto
    empty() -> bool
    {
      /** Возвращает:
       *    true  - контейнер пустой
       *    false - контейнер не пустой
       */

      if (_M_lenght == 0 || _M_data == nullptr) 
        return true;

      return false;
    }

    /*
     * Вставляет в заданное место контейнера заданный диапазон значений 
     * другого контейнера.
     */
    auto
    insert_vector(_Tp* __vector, 
    __u32 __index_1, __u32 __index_2, __u32 __index) -> void
    {
      /** Передаваемые аргументы:
       *    __vector  - указатель на контейнер донор
       *    __index_1 - начальный индех контейнера донора
       *    __index_2 - конечный индех контейнера донора
       *    __index   - индекс исходного контейнера с которого
       *                будут вставлены элементы контейнера донора
       */

      if (__index < 0 || __index >= _M_lenght)
        throw 
        pexception("E: Значение индекса контейнера не приемлемо.");

      /** Определяем, сколько элементов копировать.
       */
      __u32
      __elements_to_copy{ (__index_2 - __index_1) + 1 };

      /** Создаем новый контейнер на __element_to_copy элементов 
       *  больше чем старый контейнер.
       */
      _Tp* 
      __data{ new _Tp[_M_lenght + __elements_to_copy] };

      /** Копируем все элементы вплоть до индекса.
       */
      for (__u32 __before{ 0 }; __before < __index; ++__before)
        __data[__before] = _M_data[__before];

      /** Вставляем новые элементы в новый контейнер.
       */
      for (__u32 __after{ __index }; 
           __after < (__index + __elements_to_copy); ++__after)
        __data[__after] = __vector[__index_1++];

      /** Копируем все значения после вставленных новых элементов.
       */
      for (__u32 __after{ __index }; __after < _M_lenght; ++__after)
        __data[(__index++) + __elements_to_copy] = _M_data[__after];

      /** Удаляем старый контейнер и используем вместо него новый 
       *  контейнер.
       */
      delete[] _M_data;

      _M_lenght += __elements_to_copy;
      _M_data    = __data;
    } 

    /*
     * Вычисляет, есть ли в контейнере дубли.
     * Возвращает true, если есть и false, если нет.
     */
    auto
    doubles() -> bool
    {
      for (__u32 __i{0}; __i < size(); __i++)
        {
          for (__u32 __j{0}; __j < size(); __j++)
            {
              if (__i != __j && _M_data[__i] == _M_data[__j])
                return true;
            }
        }
      return false;
    }

    /*
     * Находит и возращает элемент контейнера, имеющий
     * наибольшее количество повторений в контейнере.
     */
    auto
    unique() -> _Tp
    {
      /** Массив количества каждого  элемента.
       */
      __u32* 
      __unique_counts = new __u32[size()];

      /** Массив уникальных элементов.
       */
      _Tp*
      __unique_elements = new _Tp[size()];

      /** Счетчик уникальных элементов.
       */
      __u32 __unique_counter{ 0 };

      /** Реализация первой части алгоритма, ищем количество повторений
       *  для каждого уникального элемента.
       */

      for (__u32 __i{0}; __i < size(); __i++)
        {
          /** Переменная для запоминания индекса найденного элемента.
           */
          __s32 __existing_index{-1};

          for (__u32 __j{0}; __j < __unique_counter; __j++)
            {
              /** Поиск __i-ого элемента среди уже 
               *  обработанных элементов.
               */
              if (__unique_elements[__j] == _M_data[__i])
                {
                  __existing_index = __j;

                  /** Увеличили количество повторений на 1.
                   */
                  __unique_counts[__j]++; 
                  break;
                }
            }

            if (__existing_index == -1)
              {
                /** Если элемент еще не встречался, то запомним его.
                 */
                __unique_elements[__unique_counter] = _M_data[__i];
                __unique_counts[__unique_counter] = 1;
                __unique_counter++;
              }
        }

      __u32 
      __max_unique_count_index{ 0 };

      __u32
      __max_unique_count = __unique_counts[0];

      /** Реализация второй части алгоритма, среди посчитанных
       *  повторений ищем максимальное.
       */

      for (__u32 __i{0}; __i < __unique_counter; __i++)
        {
          if (__max_unique_count < __unique_counts[__i])
            {
              __max_unique_count_index = __i;
            }
        }

      _Tp
      __return_elements = __unique_elements[__max_unique_count_index];

      delete[] __unique_counts;
      delete[] __unique_elements;

      return __return_elements;
    }

  };

} // namespace ptl

#endif // _PTL_PVECTOR