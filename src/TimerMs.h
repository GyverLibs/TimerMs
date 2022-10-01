/*
    Многофункциональный программный таймер на системном таймере millis() для Arduino
    Документация: 
    GitHub: https://github.com/GyverLibs/TimerMs
    Возможности:
    - Режим таймера и периодичного выполнения
    - Подключение функции-обработчика
    - Сброс/запуск/перезапуск/остановка/пауза/продолжение отсчёта
    - Возможность форсировать переполнение таймера
    - Возврат оставшегося времени в мс, а также условных единицах 8 и 16 бит
    - Несколько функций получения текущего статуса таймера
    - Алгоритм держит стабильный период и не боится переполнения millis()
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - добавил микросекундный режим
	v1.1.1 - небольшой фикс
    v1.2 - фикс функции stop
*/

#ifndef _TimerMs_h
#define _TimerMs_h
#include <Arduino.h>

class TimerMs {
public:
    // (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
    TimerMs(uint32_t prd = 1000, bool state = 0, bool mode = 0) {
        setTime(prd);
        if (state) start();
        _mode = mode;
    }
    
    // включить микросекундный режим (true)
    void setMicros(bool mode) {
        _us = mode;
    }
    
    // установить в режим таймера (остановится после срабатывания)
    void setTimerMode() {
        _mode = 1;
    }
    
    // установить в режим периода (перезапустится после срабатывания)
    void setPeriodMode() {
        _mode = 0;
    }
    
    // установить время
    void setTime(uint32_t prd) {
        _prd = (prd == 0) ? 1 : prd;
    }
    
    // подключить коллбэк
    void attach(void (*handler)()) {
        _handler = *handler;
    }
    
    // отключить коллбэк
    void detach() {
        _handler = nullptr;
    }

    // запустить/перезапустить таймер
    void start() {
        _state = true;  
        _tmr = uptime();
		_buf = 0;
    }
    
    // перезапустить
    void restart() {
        start();
    }
    
    // продолжить после остановки
    void resume() {
        if (!_state) _tmr = uptime() - _buf;
        _state = true;
    }
    
    // остановить/приостановить таймер
    void stop() {
        if (_state) _buf = uptime() - _tmr;
        _state = false;
    }
    
    // принудительно переполнить таймер
    void force() {
        _tmr = uptime() - _prd;
    }

    // в режиме периода однократно вернёт true при каждом периоде
    // в режиме таймера будет возвращать true при срабатывании
    bool tick() {
        if (_state) _buf = uptime() - _tmr;
        if (_state && _buf >= _prd) {
            if (!_mode) _tmr += _prd * (_buf / _prd);
            else stop();
            if (*_handler) _handler();
            _ready = 1;
            return true;
        }
        return false;
    }
    
    // однократно вернёт true при срабатывании (флаг)
    bool ready() {
        return _ready ? _ready = 0, 1 : 0;
    }
    
    // всегда возвращает true при срабатывании
    bool elapsed() {
        return (uptime() - _tmr >= _prd);
    }
    
    // работает ли таймер (start/resume)
    bool active() {
        return _state;
    }
    
    // elapsed+active: работает ли таймер + не сработал ли он  
    bool status() {
        return _state && !elapsed();
    }
    
    // остаток времени
    uint32_t timeLeft() {
        return max(long(_prd - _buf), 0L);
    }
    
    // остаток времени в 0-255
    uint8_t timeLeft8() {
        return max(255 - _buf * 255l / _prd, 0ul);
    }
    
    // остаток времени в 0-65535
    uint16_t timeLeft16() {
        return max(65535 - _buf * 65535l / _prd, 0ul);
    }
    
    // на случай использования в других фреймворках
    uint32_t uptime() {
        return _us ? micros() : millis();
    }

private:
    uint32_t _tmr = 0, _prd = 1000, _buf = 0;
    bool _state = 0, _mode = 0, _ready = 0, _us = 0;
    void (*_handler)() = nullptr;
};
#endif
