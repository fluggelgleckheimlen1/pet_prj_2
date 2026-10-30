# pet_prj_2 (Hash Calculator)

[English](#english) | [Русский](#russian)

<a name="english"></a>
## Overview

A console utility written in pure **C** for Windows (XP+) operating system, designed for interactive calculation of cryptographic hash sums of text data using the native **Windows CryptoAPI**.

The project is built with a focus on a custom text-based user interface (TUI) without relying on heavy third-party libraries.

### Key Features
* **Interactive TUI Menu:** navigation via arrow keys (`Up`, `Down`) with visual highlighting of the selected item
* **Supported Hash Algorithms:**
  * MD5, SHA-1, SHA-256, SHA-384, SHA-512
* **Native Integration:** operates directly through Windows CryptoAPI utilizing standard cryptographic providers

### Controls
* **`↑` / `↓`** — Navigate menu items.
* **`Enter`** — Confirm selection and proceed to text input.
* **`ESC`** — Exit the program.

### Requirements & Building
* **OS:** Microsoft Windows (XP+).
* **Compiler:** Microsoft Visual Studio (MSVC) or any Windows-compatible compiler supporting Windows SDK (ensure Windows system libraries such as `advapi32.lib` are linked).

## License
This project is distributed for educational and personal purposes.

---
<a name="russian"></a>
## Описание

Консольная утилита на чистом Си для ОС Windows (XP+), предназначенная для интерактивного вычисления криптографических хеш-сумм текстовых данных с использованием нативного **Windows CryptoAPI**.

Проект разработан с упором на кастомный консольный интерфейс (TUI) без использования сторонних тяжелых библиотек.

### Основные возможности

* **Интерактивное консольное меню:** Управление выбором алгоритма с помощью стрелок (`Up`, `Down`) с визуальной подсветкой выбранного пункта.
* **Поддерживаемые алгоритмы хеширования:**
  * MD5, SHA-1, SHA-256, SHA-384, SHA-512

* **Нативная интеграция:** Работает напрямую через Windows CryptoAPI, используя системные криптографические провайдеры.

### Управление в программе
* **`↑` / `↓**` — Навигация по пунктам меню.
* **`Enter`** — Выбор алгоритма и переход к вводу текста.
* **`ESC`** — Выход из программы.

### Требования и сборка
* **Операционная система:** Microsoft Windows (XP+).
* **Компилятор:** Microsoft Visual Studio (MSVC) или любой другой совместимый компилятор под Windows с поддержкой Windows SDK (убедитесь, что линковщик подключил стандартные библиотеки Windows, при необходимости `advapi32.lib`).

## Лицензия
Проект распространяется в учебных и личных целях.
