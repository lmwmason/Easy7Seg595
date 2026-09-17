#include <Easy7Seg595.h>

// SDI, SCLK, LOAD
Easy7Seg595 display(7, 6, 5);

void setup() {
  display.begin();

  // ==================================================
  // 1. Display a two-digit number
  // ==================================================

  display.print(42);
  delay(1500);


  // ==================================================
  // 2. Display a single-digit number
  //    Left digit is automatically blank
  // ==================================================

  display.print(7);
  delay(1500);


  // ==================================================
  // 3. Left decimal point
  // ==================================================

  display.print(42);

  display.dotLeft(true);
  delay(1500);

  display.dotLeft(false);
  delay(1000);


  // ==================================================
  // 4. Right decimal point
  // ==================================================

  display.dotRight(true);
  delay(1500);

  display.dotRight(false);
  delay(1000);


  // ==================================================
  // 5. Both decimal points
  // ==================================================

  display.dotLeft(true);
  display.dotRight(true);
  delay(1500);

  display.dotLeft(false);
  display.dotRight(false);


  // ==================================================
  // 6. Turn the whole display OFF
  //
  //    off() does NOT erase the current value.
  // ==================================================

  display.print(42);
  delay(1000);

  display.off();
  delay(1500);


  // ==================================================
  // 7. Turn the display back ON
  //
  //    The previous value (42) is restored.
  // ==================================================

  display.on();
  delay(1500);


  // ==================================================
  // 8. Raw LEFT digit control
  //
  //    Order:
  //    A, B, C, D, E, F, G, DOT
  //
  //    1 = ON
  //    0 = OFF
  //
  //    This example draws "-"
  // ==================================================

  display.rawLeft(
    0, 0, 0, 0,
    0, 0, 1, 0
  );

  delay(1500);


  // ==================================================
  // 9. Raw RIGHT digit control
  //
  //    This example draws "0"
  // ==================================================

  display.rawRight(
    1, 1, 1, 1,
    1, 1, 0, 0
  );

  delay(1500);


  // ==================================================
  // 10. Raw pattern with decimal point
  //
  //     Displays:
  //
  //       - 0.
  // ==================================================

  display.rawRight(
    1, 1, 1, 1,
    1, 1, 0, 1
  );

  delay(1500);


  // ==================================================
  // 11. Clear everything
  //
  //     Unlike off(), clear() ERASES the stored
  //     display contents.
  // ==================================================

  display.clear();
  delay(1500);


  // ==================================================
  // 12. Display something again
  // ==================================================

  display.print(99);
}


void loop() {
  // Nothing here.
  // The example runs once in setup().
}
