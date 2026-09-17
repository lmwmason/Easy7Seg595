#include <Easy7Seg595.h>

Easy7Seg595 display(7, 6, 5); // SDI, SCLK, LOAD

void setup() {
  display.begin();

  display.print(42);          // 42
  delay(1000);

  display.dotLeft(true);      // 4.2
  delay(1000);

  display.dotLeft(false);
  display.dotRight(true);     // 42.
  delay(1000);

  // A B C D E F G DOT
  // Show "-" on the left and "0" on the right.
  display.rawLeft (0,0,0,0,0,0,1,0);
  display.rawRight(1,1,1,1,1,1,0,0);
}

void loop() {
}
