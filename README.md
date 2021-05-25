![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
# TimerMs
Многофункциональный программный таймер на системном таймере millis() для Arduino
- Режим таймера и периодичного выполнения
- Подключение функции-обработчика
- Сброс/запуск/перезапуск/остановка/пауза/продолжение отсчёта
- Возможность форсировать переполнение таймера
- Возврат оставшегося времени в мс, а также условных единицах 8 и 16 бит
- Несколько функций получения текущего статуса таймера
- Алгоритм держит стабильный период и не боится переполнения millis()

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **TimerMs** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/TimerMs/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
// (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
TimerMs tmr;                                        // время 1000мс, не запущен, режим периода
TimerMs tmr(uint32_t prd);                          // время prd, не запущен, режим периода
TimerMs tmr(uint32_t prd, bool state);              // время prd, state статус, режим периода
TimerMs tmr(uint32_t prd, bool state, bool mode);   // время prd, state статус, mode: 0 период / 1 таймер
```

<a id="usage"></a>
## Использование
```cpp
void setTimerMode();            // установить в режим таймера (остановится после срабатывания)
void setPeriodMode();  			// установить в режим периода (перезапустится после срабатывания)
void setTime(uint32_t prd);     // установить время
void attach(void (*handler)()); // подключить коллбэк
void detach();                  // отключить коллбэк
void start();                   // запустить/перезапустить таймер
void resume();                  // продолжить после остановки
void stop();                    // остановить/приостановить таймер
void force();                   // принудительно переполнить таймер

// в режиме периода однократно вернёт true при каждом периоде
// в режиме таймера будет возвращать true при срабатывании
bool tick();

bool ready();           // однократно вернёт true при срабатывании (флаг)
bool elapsed();         // всегда возвращает true при срабатывании
bool active();          // работает ли таймер (start/resume)
bool status();          // elapsed+active: работает ли таймер + не сработал ли он

uint32_t timeLeft();    // остаток времени в мс
uint8_t timeLeft8();    // остаток времени в 0-255
uint16_t timeLeft16();  // остаток времени в 0-65535
```

<a id="example"></a>
## Пример
```cpp
#include <TimerMs.h>
// (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
TimerMs tmr(2000, 1, 1);

void setup() {
  Serial.begin(9600);
  //tmr.setTimerMode();
  tmr.setPeriodMode();
}

void loop() {
  if (tmr.tick()) Serial.println("finish");
}
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!