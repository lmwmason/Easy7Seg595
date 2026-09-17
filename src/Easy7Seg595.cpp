#include "Easy7Seg595.h"

Easy7Seg595::Easy7Seg595(uint8_t sdi, uint8_t sclk, uint8_t load)
  : _sdi(sdi), _sclk(sclk), _load(load), _left(0xFF), _right(0xFF) {}

void Easy7Seg595::begin() {
  pinMode(_sdi, OUTPUT);
  pinMode(_sclk, OUTPUT);
  pinMode(_load, OUTPUT);

  digitalWrite(_load, HIGH);
  clear();
}

uint8_t Easy7Seg595::encodeRaw(bool a, bool b, bool c, bool d,
                               bool e, bool f, bool g, bool dot) {
  // User API: 1 means ON.
  // Hardware output: 0 means ON (active-LOW).
  uint8_t on =
      (a   ? 0x01 : 0) |
      (b   ? 0x02 : 0) |
      (c   ? 0x04 : 0) |
      (d   ? 0x08 : 0) |
      (e   ? 0x10 : 0) |
      (f   ? 0x20 : 0) |
      (g   ? 0x40 : 0) |
      (dot ? 0x80 : 0);

  return ~on;
}

uint8_t Easy7Seg595::encodeDigit(uint8_t digit) {
  static const uint8_t digits[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
  };
  return digit < 10 ? digits[digit] : 0xFF;
}

void Easy7Seg595::print(int number) {
  number = constrain(number, 0, 99);

  if (number < 10) {
    _left = 0xFF;
    _right = encodeDigit(number);
  } else {
    _left = encodeDigit(number / 10);
    _right = encodeDigit(number % 10);
  }

  writeDisplay();
}

void Easy7Seg595::dotLeft(bool on) {
  if (on) _left &= ~0x80;
  else    _left |=  0x80;
  writeDisplay();
}

void Easy7Seg595::dotRight(bool on) {
  if (on) _right &= ~0x80;
  else    _right |=  0x80;
  writeDisplay();
}

void Easy7Seg595::rawLeft(bool a, bool b, bool c, bool d,
                          bool e, bool f, bool g, bool dot) {
  _left = encodeRaw(a, b, c, d, e, f, g, dot);
  writeDisplay();
}

void Easy7Seg595::rawRight(bool a, bool b, bool c, bool d,
                           bool e, bool f, bool g, bool dot) {
  _right = encodeRaw(a, b, c, d, e, f, g, dot);
  writeDisplay();
}

void Easy7Seg595::clear() {
  _left = 0xFF;
  _right = 0xFF;
  writeDisplay();
}

void Easy7Seg595::writeDisplay() {
  digitalWrite(_load, LOW);

  // Daisy chain: first shifted byte reaches the farther 74HC595.
  shiftOut(_sdi, _sclk, MSBFIRST, _left);
  shiftOut(_sdi, _sclk, MSBFIRST, _right);

  digitalWrite(_load, HIGH);
}
