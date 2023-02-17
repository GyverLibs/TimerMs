This is an automatic translation, may be incorrect in some places. See sources and examples!

# TimerMs
Multifunctional software timer on millis() system timer for Arduino
- Timer and periodic execution mode
- Connecting a handler function
- Reset/Start/Restart/Stop/Pause/Resume
- Ability to force timer overflow
- Ability to stop automatically after certain executions in the period mode
- Return of the remaining time in ms, as well as arbitrary units of 8 and 16 bits
- Several functions to get the current timer status
- The algorithm keeps a stable period and is not afraid of millis() overflow

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **TimerMs** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/TimerMs/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Chitaand more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
// (period, ms), (0 not running / 1 running), (mode: 0 period / 1 timer)
TimerMs tmr; // time 1000ms, not running, period mode
TimerMs tmr(uint32_tprd); // time prd, not running, period mode
TimerMs tmr(uint32_t prd, bool state); // time prd, state status, period mode
TimerMs tmr(uint32_t prd, bool state, bool mode); // time prd, state status, mode: 0 period / 1 timer
```

<a id="usage"></a>
## Usage
```cpp
void setMicros(bool mode); // enable microsecond mode (true)
void setTimerMode(); // set to timer mode (stop after firing)
void setPeriodMode(); // set to period mode (restart after firing)
void setTime(uint32_tprd); // set the time
void setLimit(unit8_t limit); // set maximum number of executions in the period mode
void attach(void (*handler)()); // connect callback
void detach(); // disable callback
void start(); // start/restart the timer
void resume(); // continue after stop
void stop(); // stop/pause the timer
voidforce(); // force the timer to overflow

// in period mode will return true once for each period
// in timer mode will return true when triggered
bool tick();

bool ready(); // returns true once when triggered (flag)
bool elapsed(); // always returns true when triggered
bool active(); // is the timer running (start/resume)
bool status(); // elapsed+active: is the timer running + has it not fired

uint32_ttimeLeft(); // remaining time in ms
uint8_ttimeLeft8(); // remaining time in 0-255
uint16_t timeLeft16(); // remaining timeCranberries in 0-65535
```

<a id="example"></a>
## Example
```cpp
#include <TimerMs.h>
// (period, ms), (0 not running / 1 running), (mode: 0 period / 1 timer)
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
## Versions
- v1.0
- v1.1 - added microsecond mode
- v1.2 - stop function fixed
- v1.3 - added limited executions in the period mode

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!