# Easy7Seg595

A simple, dependency-free Arduino library for controlling a **2-digit 7-segment display using two daisy-chained 74HC595 shift registers**.

Easy7Seg595 is designed to make these displays easy to use without manually writing segment bit patterns or dealing with `shiftOut()` every time.

## Features

- Display numbers from `0` to `99`
- Independent left and right decimal point control
- Direct control of every segment
- Simple `1 = ON`, `0 = OFF` raw segment API
- Turn the entire display on or off
- `off()` preserves the current display state
- `clear()` completely clears the display contents
- No external dependencies
- Uses only 3 Arduino GPIO pins

## Wiring

The display uses three control signals:

| Display | Arduino |
|---|---|
| SDI | Any digital pin |
| SCLK | Any digital pin |
| LOAD | Any digital pin |
| VCC | Power |
| GND | GND |

Example:

```text
SDI  -> D7
SCLK -> D6
LOAD -> D5
```

Then create the display object:

```cpp
Easy7Seg595 display(7, 6, 5);
```

The constructor order is:

```cpp
Easy7Seg595(SDI, SCLK, LOAD);
```

## Installation

### Arduino IDE

Download this repository as a ZIP file.

In Arduino IDE:

```text
Sketch
→ Include Library
→ Add .ZIP Library...
```

Select the downloaded ZIP file.

Then include the library:

```cpp
#include <Easy7Seg595.h>
```

## Basic Usage

```cpp
#include <Easy7Seg595.h>

Easy7Seg595 display(7, 6, 5);

void setup() {
  display.begin();

  display.print(42);
}

void loop() {
}
```

The display will show:

```text
42
```

## API

### `begin()`

Initializes the display.

```cpp
display.begin();
```

Call this once inside `setup()`.

---

### `print(number)`

Displays a number from `0` to `99`.

```cpp
display.print(42);
```

Displays:

```text
42
```

Single-digit numbers are displayed on the right digit:

```cpp
display.print(7);
```

Displays:

```text
 7
```

Values are constrained to the range `0` to `99`.

---

### `dotLeft(on)`

Controls the decimal point on the left digit.

```cpp
display.print(42);
display.dotLeft(true);
```

Displays:

```text
4.2
```

Turn it off:

```cpp
display.dotLeft(false);
```

---

### `dotRight(on)`

Controls the decimal point on the right digit.

```cpp
display.print(42);
display.dotRight(true);
```

Turn it off:

```cpp
display.dotRight(false);
```

Both decimal points can also be enabled:

```cpp
display.dotLeft(true);
display.dotRight(true);
```

---

### `rawLeft(...)`

Directly controls every segment of the left digit.

Arguments are always given in this order:

```text
A, B, C, D, E, F, G, DOT
```

Each argument uses:

```text
1 = ON
0 = OFF
```

For example, display `0`:

```cpp
display.rawLeft(
  1, 1, 1, 1,
  1, 1, 0, 0
);
```

Display only the center segment:

```cpp
display.rawLeft(
  0, 0, 0, 0,
  0, 0, 1, 0
);
```

This produces:

```text
-
```

---

### `rawRight(...)`

Works exactly like `rawLeft()`, but controls the right digit.

```cpp
display.rawRight(
  1, 1, 1, 1,
  1, 1, 0, 0
);
```

This displays `0` on the right digit.

The argument order is:

```text
A, B, C, D, E, F, G, DOT
```

---

### `off()`

Temporarily turns the entire display off.

```cpp
display.print(42);

display.off();
```

The display becomes blank, but `42` is still stored internally.

---

### `on()`

Turns the display back on.

```cpp
display.on();
```

If the display contained `42` before calling `off()`, it will display `42` again.

For example:

```cpp
display.print(42);

display.off();
delay(1000);

display.on();
```

The sequence is:

```text
42
blank
42
```

---

### `clear()`

Clears both digits and removes the currently stored display contents.

```cpp
display.clear();
```

This is different from `off()`.

```cpp
display.print(42);

display.off();
display.on();
```

Restores:

```text
42
```

But:

```cpp
display.print(42);

display.clear();
```

Clears the stored display contents.

## Raw Segment Layout

The raw API follows the standard 7-segment naming convention:

```text
     A
    ---
 F |     | B
   |  G  |
    ---
 E |     | C
   |     |
    ---   • DOT
     D
```

The argument order is:

```cpp
display.rawLeft(
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  DOT
);
```

For example:

```cpp
display.rawLeft(
  1, // A
  1, // B
  1, // C
  1, // D
  1, // E
  1, // F
  0, // G
  0  // DOT
);
```

produces `0`.

## Complete Example

```cpp
#include <Easy7Seg595.h>

Easy7Seg595 display(7, 6, 5);

void setup() {
  display.begin();

  // Display a number
  display.print(42);
  delay(1000);

  // Left decimal point
  display.dotLeft(true);
  delay(1000);

  display.dotLeft(false);

  // Right decimal point
  display.dotRight(true);
  delay(1000);

  display.dotRight(false);

  // Temporarily turn everything off
  display.off();
  delay(1000);

  // Restore previous display
  display.on();
  delay(1000);

  // Custom left pattern: "-"
  display.rawLeft(
    0, 0, 0, 0,
    0, 0, 1, 0
  );

  // Custom right pattern: "0"
  display.rawRight(
    1, 1, 1, 1,
    1, 1, 0, 0
  );

  delay(1000);

  // Clear everything
  display.clear();
}

void loop() {
}
```

## Function Reference

| Function | Description |
|---|---|
| `begin()` | Initialize the display |
| `print(number)` | Display a number from 0 to 99 |
| `dotLeft(bool)` | Control the left decimal point |
| `dotRight(bool)` | Control the right decimal point |
| `rawLeft(...)` | Directly control all segments of the left digit |
| `rawRight(...)` | Directly control all segments of the right digit |
| `off()` | Turn the display off while preserving its contents |
| `on()` | Turn the display on and restore its contents |
| `clear()` | Clear both digits and stored contents |

## Requirements

- Arduino-compatible board
- 2-digit 7-segment display
- Two daisy-chained 74HC595 shift registers

No additional Arduino libraries are required.

## License

MIT
