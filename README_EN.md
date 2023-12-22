This is an automatic translation, may be incorrect in some places. See sources and examples!

# Timerms
A multifunctional software timer on the Millis () system timer for Arduino
- timer mode and periodic execution
- Connection of a processing function
- reset/launch/restart/stop/pause/Continuation of the reference
- the ability to force the timer overflow
- Return of the remaining time in the MS, as well as conditional units 8 and 16 bits
- several functions of obtaining the current timer status
- the algorithm holds a stable period and is not afraid of overflowing Millis ()

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** Timerms ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/timerms/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
// (period, ms), (0 not launched / 1 launched), (mode: 0 period / 1 timer)
Timerms TMR;// time 1000ms, not launched, the mode of the period
Timerms TMR (Uint32_T PRD);// PRD time, not launched, the period of the period
Timerms TMR (Uint32_T PRD, Bool State);// PRD time, state status, period of the period
Timerms TMR (Uint32_T PRD, BOOL STATE, BOLOL MODE);// PRD time, state status, mode: 0 period / 1 timer
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID setmicros (Bool Mode);// Turn on the microsecond mode (True)
VOID settimermode ();// install in the timer mode (stop after the trigger)
VOID setperiodmode ();// install in the period of the period (restart after the trigger)
VOID settime (Uint32_T PRD);// set the time
VOID attach (VOID (*handler) ());// Connect collback
VOID Detach ();// Disconnect the collback
VOID Start ();// Launch/restart the timer
VOID Resume ();// Continue after stopping
VOID Stop ();Cranberries // Stop/suspend the timer
VOID form ();// forcibly overfill the timer

// in the mode of the period will once return True at every period
// in the timer mode will return True when triggered
Bool Tick ();

Bool Ready ();// will return True once when triggered (flag)
Bool ElapSed ();// always returns True when triggered
Bool Active ();// Does the Timer work (Start/Resume)
Bool Status ();// ELAPSED + Active: Is the timer working + WIT

uint32_t timeleft ();// The rest of the time in MS
uint8_t timeleft8 ();// The rest of the time at 0-255
uint16_t timeleft16 ();// The rest of the time is 0-65535
`` `

<a id="EXAMPLE"> </a>
## Example
`` `CPP
#include <timerms.h>
// (period, ms), (0 not launched / 1 launched), (mode: 0 period / 1 timer)
Timerms TMR (2000, 1, 1);

VOID setup () {
  Serial.Begin (9600);
  //tmr.settimermode ();
  TMR.Setperiodmode ();
}

VOID loop () {
  if (tmr.tick ()) serial.println ("finish");
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - added a microsecond mode
- v1.1.1 - Small fix
- V1.2 - Fix of the Stop function

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code