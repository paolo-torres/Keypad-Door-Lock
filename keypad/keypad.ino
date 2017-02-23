#include <keypad.h> //header file with keypad definitions

const int buzzerPin = 13; //buzzerPin in pin 13
const int lockPin = 12; //lockPin in pin 12
const int redPin = 11; //redPin in pin 11
const int bluePin = 10; //bluePin in pin 10
const int greenPin = 9; //greenPin in pin 9

const byte rows = 4; //number of rows on keypad
const byte cols = 4; //number of columns on keypad
char* secretCode = "1234"; //variable that keeps the secret code
char keys[rows][cols] = { //2D array that holds the rows and columns
  {'1', '2', '3', 'A'}, //first row has 1, 2, 3, and A
  {'4', '5', '6', 'B'}, //second row has 4, 5, 6, and B
  {'7', '8', '9', 'C'}, //third row has 7, 8, 9, and C
  {'*', '0', '#', 'D'} //fourth row has *, 0, #, and D
};
byte rowPins[rows] = {7, 6, 5, 4}; //pins 7, 6, 5, and 4 for the rows
byte colPins[cols] = {3, 2, 1, 0}; //pins 3, 2, 1, and 0 for the columns
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols); //sets up keypad

void setup()
{
  pinMode(lockPin, OUTPUT); //lockPin outputs
  pinMode(redPin, OUTPUT); //redPin outputs
  pinMode(bluePin, OUTPUT); //bluePin outputs
  pinMode(greenPin, OUTPUT); //greenPin outputs
}

void loop()
{
  boolean wrong = false; //no wrong flags (wrong starts out as false)
  while(waitForKey() != '*'){}; //while the “*” key is not pressed, do nothing
  for(int i = 0; i < 4; i++) //if "*" is pressed, loops 4 times, 1 for each digit of the secret code
  {
    digitalWrite(bluePin, HIGH); //blue light to indicate inputting of code
    char key = waitForKey(); //variable key equals the keys pressed
    if(key != secretCode[i]) wrong = true; //if your input is incorrect, set a wrong flag
  }
  if(!wrong) //if there are no wrong flags (if you input the secret code correctly)
  {
    unlockDoor(); //unlock the door
  }
  else //if there is a wrong flag (if you do not input the secret code correctly)
  {
    lockDoor();//keep the door locked
  }
}

void unlockDoor() //unlock door function
{
  digitalWrite(bluePin, LOW); //turn off the blue light
  for(int i = 0; i < 3; i++){ //loops 3 times
    digitalWrite(greenPin, HIGH); //turns on green light
    delay(1000); //for 1 second
    digitalWrite(greenPin, LOW); //turns off green light
    delay(1000); //for 1 second
  }
  digitalWrite(greenPin, HIGH); //keeps green light on
  digitalWrite(lockPin, HIGH); //allow current to flow thereby releasing the lock
  tone(buzzerPin, 500); //play the buzzer sound with a frequency of 500 Hertz
  delay(5000); //keep the green light on, the lock open, and the piezo buzzing for 5 seconds
  digitalWrite(greenPin, LOW); //turn off the green light
  digitalWrite(lockPin, LOW); //prevent current to flow thereby securing the lock
  noTone(buzzerPin); //stop the buzzer sound
}

void lockDoor()//lock door function
{
  digitalWrite(bluePin, LOW); //turn off the blue light
  digitalWrite(lockPin, LOW); //no current flow keeps the door locked
  for(int i = 0; i < 3; i++) //loops 3 times
  {
    digitalWrite(redPin, HIGH); //turn on the red light
    delay(1000); //for 1 second
    digitalWrite(redPin, LOW); //turn off the red light
    delay(1000); //for 1 second
  }
  digitalWrite(redPin, HIGH); //keep the red light on
  tone(buzzerPin, 1000); //play the buzzer sound with a frequency of 1000 Hertz
  delay(5000); //keep the red light on and the piezo buzzing for 5 seconds
  digitalWrite(redPin, LOW); //LED is red
  noTone(buzzerPin); //stop the buzzer sound
}

char waitForKey() //key condition function
{
  char key; //variable key
  while((key = keypad.getKey()) == 0){}; //waits for the key to be pressed
  while(!keypad.getKey() == 0){}; //waits for the key to be released
  delay(10); //does this for 10 milliseconds
  return key; //return key to prevent false key presses as a result of key bounce (key debouncing)
}

