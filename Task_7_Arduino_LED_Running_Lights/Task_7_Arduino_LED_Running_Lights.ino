// Task 7 Arduino LED Running Lights
// LEDs use pins 2 to 11. Button uses pin 12 and connects to GND.

const int ledPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int buttonPin = 12;

const unsigned long debounceTime = 50;
const unsigned long doubleClickTime = 400;
const unsigned long holdTime = 800;
const unsigned long stepTime = 100;
const unsigned long pauseTime = 300;

// Number of steps in patterns 1 to 10.
const int patternLength[10] = {10, 10, 19, 9, 5, 5, 18, 10, 11, 20};

bool running = false;
bool patternPaused = false;
int currentPattern = 1;
int patternStep = 0;
unsigned long lastStepTime = 0;
unsigned long pauseStarted = 0;

int buttonState = HIGH;
int lastButtonReading = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long buttonDownTime = 0;
unsigned long lastClickTime = 0;
int clickCount = 0;
bool holdDone = false;

void setup() {
  for (int i = 0; i < 10; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buttonPin, INPUT_PULLUP);
  clearLeds();

  buttonState = digitalRead(buttonPin);
  lastButtonReading = buttonState;
  buttonDownTime = millis();
}

void loop() {
  checkButton();

  if (!running) {
    return;
  }

  unsigned long now = millis();

  if (patternPaused) {
    if (now - pauseStarted < pauseTime) {
      return;
    }

    patternPaused = false;
    currentPattern++;
    if (currentPattern > 10) {
      currentPattern = 1;
    }
    patternStep = 0;
    lastStepTime = now - stepTime;
  }

  if (now - lastStepTime < stepTime) {
    return;
  }

  lastStepTime = now;

  if (currentPattern == 1) pattern1();
  if (currentPattern == 2) pattern2();
  if (currentPattern == 3) pattern3();
  if (currentPattern == 4) pattern4();
  if (currentPattern == 5) pattern5();
  if (currentPattern == 6) pattern6();
  if (currentPattern == 7) pattern7();
  if (currentPattern == 8) pattern8();
  if (currentPattern == 9) pattern9();
  if (currentPattern == 10) pattern10();

  patternStep++;

  if (patternStep >= patternLength[currentPattern - 1]) {
    clearLeds();
    patternPaused = true;
    pauseStarted = now;
  }
}

void checkButton() {
  int reading = digitalRead(buttonPin);
  unsigned long now = millis();

  // Reset the debounce timer when the reading changes.
  if (reading != lastButtonReading) {
    lastDebounceTime = now;
  }

  // Accept the new button state after 50 ms.
  if (now - lastDebounceTime >= debounceTime && reading != buttonState) {
    buttonState = reading;

    if (buttonState == LOW) {
      buttonDownTime = now;
      holdDone = false;
    } else if (!holdDone) {
      clickCount++;
      lastClickTime = now;

      if (clickCount == 2) {
        stopPattern();
        clickCount = 0;
      }
    }
  }

  lastButtonReading = reading;

  // Hold: reset to pattern 1 after 800 ms.
  if (buttonState == LOW && !holdDone &&
      now - buttonDownTime >= holdTime) {
    holdDone = true;
    clickCount = 0;
    resetToPattern1();
  }

  // Single click: wait 400 ms for a second click, then start or resume.
  if (buttonState == HIGH && clickCount == 1 &&
      now - lastClickTime >= doubleClickTime) {
    clickCount = 0;
    resumePattern();
  }
}

void resumePattern() {
  running = true;
  lastStepTime = millis() - stepTime;
}

void stopPattern() {
  running = false;
  clearLeds();
}

void resetToPattern1() {
  running = false;
  patternPaused = false;
  currentPattern = 1;
  patternStep = 0;
  clearLeds();
  lastStepTime = millis() - stepTime;
}

void clearLeds() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

// Pattern 1: left to right
void pattern1() {
  clearLeds();
  digitalWrite(ledPins[patternStep], HIGH);
}

// Pattern 2: right to left
void pattern2() {
  clearLeds();
  digitalWrite(ledPins[9 - patternStep], HIGH);
}

// Pattern 3: bounce from side to side
void pattern3() {
  int led = patternStep;
  if (patternStep >= 10) {
    led = 18 - patternStep;
  }
  clearLeds();
  digitalWrite(ledPins[led], HIGH);
}

// Pattern 4: two LEDs move together
void pattern4() {
  clearLeds();
  digitalWrite(ledPins[patternStep], HIGH);
  digitalWrite(ledPins[patternStep + 1], HIGH);
}

// Pattern 5: center to outside
void pattern5() {
  clearLeds();
  digitalWrite(ledPins[4 - patternStep], HIGH);
  digitalWrite(ledPins[5 + patternStep], HIGH);
}

// Pattern 6: outside to center
void pattern6() {
  clearLeds();
  digitalWrite(ledPins[patternStep], HIGH);
  digitalWrite(ledPins[9 - patternStep], HIGH);
}

// Pattern 7: even LEDs and odd LEDs
void pattern7() {
  int group = (patternStep / 3) % 2;
  clearLeds();

  for (int i = group; i < 10; i = i + 2) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Pattern 8: fill the LEDs from left to right
void pattern8() {
  clearLeds();

  for (int i = 0; i <= patternStep; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

// Pattern 9: clear the LEDs from left to right
void pattern9() {
  if (patternStep == 0) {
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
  } else {
    digitalWrite(ledPins[patternStep - 1], LOW);
  }
}

// Pattern 10: random LED
void pattern10() {
  clearLeds();
  int randomLed = random(0, 10);
  digitalWrite(ledPins[randomLed], HIGH);
}
