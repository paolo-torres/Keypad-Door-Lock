#include <keypad.h>

const int buzzerPin = 13;
const int lockPin = 12;
const int redPin = 11;
const int bluePin = 10;
const int greenPin = 9;

const byte rows = 4;
const byte cols = 4;
char* secretCode = "1234";
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {7, 6, 5, 4};
byte colPins[cols] = {3, 2, 1, 0};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
  pinMode(lockPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  boolean wrong = false;
  while (waitForKey() != '*') {};
  for (int i = 0; i < 4; i++) {
    digitalWrite(bluePin, HIGH);
    char key = waitForKey();
    if (key != secretCode[i])
      wrong = true;
  }
  if (!wrong)
    unlockDoor();
  else
    lockDoor();
}

void unlockDoor() {
  digitalWrite(bluePin, LOW);
  for (int i = 0; i < 3; i++){
    digitalWrite(greenPin, HIGH);
    delay(1000);
    digitalWrite(greenPin, LOW);
    delay(1000);
  }
  digitalWrite(greenPin, HIGH);
  digitalWrite(lockPin, HIGH);
  tone(buzzerPin, 500);
  delay(5000);
  digitalWrite(greenPin, LOW);
  digitalWrite(lockPin, LOW);
  noTone(buzzerPin);
}

void lockDoor() {
  digitalWrite(bluePin, LOW);
  digitalWrite(lockPin, LOW);
  for (int i = 0; i < 3; i++) {
    digitalWrite(redPin, HIGH);
    delay(1000);
    digitalWrite(redPin, LOW);
    delay(1000);
  }
  digitalWrite(redPin, HIGH);
  tone(buzzerPin, 1000);
  delay(5000);
  digitalWrite(redPin, LOW);
  noTone(buzzerPin);
}

char waitForKey() {
  char key;
  while ((key = keypad.getKey()) == 0){};
  while (!keypad.getKey() == 0){};
  delay(10);
  return key;
}
