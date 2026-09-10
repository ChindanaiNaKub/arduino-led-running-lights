// Task 6 Arduino LED Running Lights
// Connect one LED and one 220 ohm resistor to each pin from 2 to 11.
// Connect all LED cathodes to GND.

const int ledPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  pattern1();
  delay(300);

  pattern2();
  delay(300);

  pattern3();
  delay(300);

  pattern4();
  delay(300);

  pattern5();
  delay(300);

  pattern6();
  delay(300);

  pattern7();
  delay(300);

  pattern8();
  delay(300);

  pattern9();
  delay(300);

  pattern10();
  delay(300);
}

// Pattern 1: left to right
void pattern1() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}

// Pattern 2: right to left
void pattern2() {
  for (int i = 9; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}

// Pattern 3: bounce from side to side
void pattern3() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }

  for (int i = 8; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}

// Pattern 4: two LEDs move together
void pattern4() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[i + 1], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[i + 1], LOW);
  }
}

// Pattern 5: center to outside
void pattern5() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[4 - i], HIGH);
    digitalWrite(ledPins[5 + i], HIGH);
    delay(100);
    digitalWrite(ledPins[4 - i], LOW);
    digitalWrite(ledPins[5 + i], LOW);
  }
}

// Pattern 6: outside to center
void pattern6() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], HIGH);
    digitalWrite(ledPins[9 - i], HIGH);
    delay(100);
    digitalWrite(ledPins[i], LOW);
    digitalWrite(ledPins[9 - i], LOW);
  }
}

// Pattern 7: even LEDs and odd LEDs
void pattern7() {
  for (int repeat = 0; repeat < 3; repeat++) {
    for (int i = 0; i < 10; i = i + 2) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(300);

    for (int i = 0; i < 10; i = i + 2) {
      digitalWrite(ledPins[i], LOW);
    }

    for (int i = 1; i < 10; i = i + 2) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(300);

    for (int i = 1; i < 10; i = i + 2) {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

// Pattern 8: fill the LEDs from left to right
void pattern8() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(100);
  }
}

// Pattern 9: clear the LEDs from left to right
void pattern9() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], HIGH);
  }

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], LOW);
    delay(100);
  }
}

// Pattern 10: random LED
void pattern10() {
  for (int i = 0; i < 20; i++) {
    int randomLed = random(0, 10);
    digitalWrite(ledPins[randomLed], HIGH);
    delay(100);
    digitalWrite(ledPins[randomLed], LOW);
  }
}
