// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с консолью (терминалом).
 */

/**
 *  (PTL) Patriarch library : pconio.h
 */

#ifndef _PTL_PCONIO
#define _PTL_PCONIO 1

#include <iostream>
#include <clocale>

namespace ptl
{
  /* 
   * Очистка терминала и постановка курсора в 
   * верхний левый угол.
   */
  auto
  clear() -> void
  { std::cout << "\033[2J\033[1;1H"; }

  /* 
   * Локализация терминала ОС Windows 'Russian'.
   */ 
  auto
  setlocale_WIN32_rus() -> void
  {
    #ifdef _WIN32
      setlocale(LC_ALL, "Russian");
    #endif
  }

} // namespace ptl

#endif // _PTL_PCONIO