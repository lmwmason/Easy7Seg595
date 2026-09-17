# Easy7Seg595

A tiny, dependency-free Arduino library for a **2-digit 7-segment display driven by two daisy-chained 74HC595 shift registers**.

Designed for modules exposing:

`VCC / GND / SDI / SCLK / LOAD`

No external 74HC595 library is required. Easy7Seg595 uses only Arduino core functions.

## Installation

### From GitHub ZIP

1. Open this repository on GitHub.
2. Select **Code -> Download ZIP**.
3. In Arduino IDE, open **Sketch -> Include Library -> Add .ZIP Library...**
4. Select the downloaded ZIP.

## Wiring example

| Display | Arduino UNO |
| --- | --- |
| VCC | 5V |
| GND | GND |
| SDI | D7 |
| SCLK | D6 |
| LOAD | D5 |

## Basic usage

```cpp
#include <Easy7Seg595.h>

Easy7Seg595 display(7, 6, 5); // SDI, SCLK, LOAD

void setup() {
  display.begin();
  display.print(42);
}

void loop() {}
```

## Decimal points

Decimal points can be changed without changing the currently displayed digit or raw pattern.

```cpp
display.print(42);

display.dotLeft(true);    // left decimal point ON
display.dotRight(false);  // right decimal point OFF
```

## Raw segment control

For custom shapes, control each segment directly.

Arguments are always:

`A, B, C, D, E, F, G, DOT`

and `1 = ON`, `0 = OFF`.

```cpp
// Display 0 on the left
display.rawLeft(1, 1, 1, 1, 1, 1, 0, 0);

// Display only the center segment on the right
display.rawRight(0, 0, 0, 0, 0, 0, 1, 0);
```

Segment naming:

```text
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D   DOT
```

## API

```cpp
display.begin();
display.print(42);

display.dotLeft(true);
display.dotRight(true);

display.rawLeft(A, B, C, D, E, F, G, DOT);
display.rawRight(A, B, C, D, E, F, G, DOT);

display.clear();
```

`print()` accepts values from 0 to 99. A one-digit number is shown on the right with the left digit blank.

## Hardware assumption

Version 1.0.0 targets the active-LOW segment mapping used by the original module:

`bit7..bit0 = DP G F E D C B A`

Because similar-looking 74HC595 modules can use different PCB routing, test the included Basic example after installation.

## License

MIT
