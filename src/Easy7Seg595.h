#pragma once
#include <Arduino.h>

class Easy7Seg595 {
public:
  Easy7Seg595(uint8_t sdi, uint8_t sclk, uint8_t load);

  void begin();
  void print(int number);  // 0..99; 0..9 is shown as " 0".." 9"

  void dotLeft(bool on);
  void dotRight(bool on);

  // Inputs are in A, B, C, D, E, F, G, DOT order.
  // 1 = segment ON, 0 = segment OFF.
  void rawLeft(bool a, bool b, bool c, bool d,
               bool e, bool f, bool g, bool dot);
  void rawRight(bool a, bool b, bool c, bool d,
                bool e, bool f, bool g, bool dot);

  void clear();

private:
  uint8_t _sdi, _sclk, _load;
  uint8_t _left;
  uint8_t _right;

  // This module is treated as common-anode / active-LOW:
  // bit7..bit0 = DP,G,F,E,D,C,B,A
  static uint8_t encodeRaw(bool a, bool b, bool c, bool d,
                           bool e, bool f, bool g, bool dot);
  static uint8_t encodeDigit(uint8_t digit);
  void writeDisplay();
};
