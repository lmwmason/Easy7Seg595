#pragma once
#include <Arduino.h>

class Easy7Seg595 {
public:
  Easy7Seg595(uint8_t sdi, uint8_t sclk, uint8_t load);

  void begin();

  // 0 ~ 99
  void print(int number);

  // Decimal point
  void dotLeft(bool on);
  void dotRight(bool on);

  // A, B, C, D, E, F, G, DOT
  // 1 = ON
  // 0 = OFF
  void rawLeft(
    bool a, bool b, bool c, bool d,
    bool e, bool f, bool g, bool dot
  );

  void rawRight(
    bool a, bool b, bool c, bool d,
    bool e, bool f, bool g, bool dot
  );

  // Temporarily turn the entire display off.
  // Current contents are preserved.
  void off();

  // Turn display back on and restore contents.
  void on();

  // Clear stored display contents.
  void clear();

private:
  uint8_t _sdi;
  uint8_t _sclk;
  uint8_t _load;

  uint8_t _left;
  uint8_t _right;

  bool _enabled;

  static uint8_t encodeRaw(
    bool a, bool b, bool c, bool d,
    bool e, bool f, bool g, bool dot
  );

  static uint8_t encodeDigit(uint8_t digit);

  void refresh();
  void writeBytes(uint8_t left, uint8_t right);
};
