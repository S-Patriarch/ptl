// -*- C++ -*-

/*
 * Copyright (c) S-Patriarch, 2023
 *
 * Описание библиотеки для работы с консолью (терминалом).
 */

/**
 *  (PTL) Patriarch library : pconio.h
 */

#pragma once
#ifndef _PTL_PCONIO
#define _PTL_PCONIO

#include <iostream>

#ifdef _WIN32
#include <clocale>
#include <windows.h>
#endif

/*
 * Функции:
 *   - clear() - очистка терминала
 *   - setlocale_WIN32_rus() - локализация консоли ОС Windows для вывода
 *   - setconsole_WIN32_rus() - локализация консоли ОС Windows для ввода/вывода
 */

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
   * Локализация консоли ОС Windows для вывода
   * текста на русском языке.
   */ 
  auto
  setlocale_WIN32_rus() -> void
  {
    #ifdef _WIN32
      setlocale(LC_ALL, "Russian");
    #endif
  }

  /* 
   * Локализация консоли ОС Windows для ввода/вывода
   * текста на русском языке.
   */ 
  auto
  setconsole_WIN32_rus() -> void
  {
    #ifdef _WIN32
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
    #endif
  }

} // namespace ptl

#endif // _PTL_PCONIO