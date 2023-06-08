/*
Lock with Servo Motor and Secret Knock
When the system starts, the lock opens and waits for the input of a secret combination.
If the combination is not entered within 5 seconds, the lock opens with a single "knock".
After entering the combination (with a timeout of 5 seconds), the buzzer plays the combination and closes the lock.
To open the lock, simply knock the combination.
To close it again, either knock once or press the internal button.

The system utilizes hardware interrupts, allowing it to enter sleep mode and accurately detect "knocks" with minimal errors.
I intended to add EEPROM recording, but not today =)
*//*
Lock with Servo Motor and Secret Knock
When the system starts, the lock opens and waits for the input of a secret combination.
If the combination is not entered within 5 seconds, the lock opens with a single "knock".
After entering the combination (with a timeout of 5 seconds), the buzzer plays the combination and closes the lock.
To open the lock, simply knock the combination.
To close it again, either knock once or press the internal button.

The system utilizes hardware interrupts, allowing it to enter sleep mode and accurately detect "knocks" with minimal errors.
I intended to add EEPROM recording, but not today =)
*/

//----- Settings -----
#define difficulty 100  //  milliseconds for reaction time (plus/minus)
#define max_knock 30    // number of stored "knocks"
#define close_angle 85  // closing angle
#define open_angle 180  // opening angle
#define debug 1         // debug mode - output process information to the serial port
//----- Settings -----

#include <Servo.h>
Servo servo;
#define buzzPin 7       // speker pin
#define buzzGND 6       // speaker ground
#define sensGND 5       // speaker ground
#define sensVCC 4       // sensor power
#define servoVCC 8      // servo power
#define servoPin 11     // servo

#include <TimerOne.h>
#include <LowPower.h>      // sleep library
byte fade_count, knock;
volatile byte mode;
boolean cap_flag, write_start;
volatile boolean debonce_flag, threshold_flag;
volatile unsigned long debounce_time;
unsigned long last_fade, last_try, last_knock, knock_time, button_time;

byte count, try_count;
int wait_time[max_knock], min_wait[max_knock], max_wait[max_knock];

void setup() {
  Serial.begin(9600);
  if (debug) Serial.println("system start");
  delay(50);
  pinMode(2, INPUT);              // vibration sensor or button pin
  pinMode(3, INPUT_PULLUP);       // vibration sensor or button pin

  servo.attach(servoPin);

  // configure power pins as outputs
  pinMode(buzzPin, OUTPUT);
  pinMode(buzzGND, OUTPUT);
  pinMode(sensGND, OUTPUT);
  pinMode(sensVCC, OUTPUT);
  pinMode(servoVCC, OUTPUT);

  //  set the required signals
  digitalWrite(buzzPin, 0);
  digitalWrite(buzzGND, 0);
  digitalWrite(sensGND, 0);
  digitalWrite(sensVCC, 1); 

  digitalWrite(servoVCC, 1);
  servo.write(open_angle);
  delay(1000);
  digitalWrite(servoVCC, 0);
  
  attachInterrupt(0, threshold, RISING);     // sensor interrupt
  attachInterrupt(1, buttonPress, FALLING);  // button OFF interrupt
  threshold_flag = 0;

  knockWrite();

  delay(50);
  close_cap();
  good_night();                              // go to sleep immediately
}

void knockWrite() {                                 //  knock recording mode
  if (debug) Serial.println("knock write mode");
  last_knock = millis();
  knock = 0;
  while (1) {                                     // wait for the first knock
    if (millis() - last_knock > 5000) {           // if no knock within 5 seconds
      write_start = 0;                            // reset everything and exit the mode
      break;
    }
    if (threshold_flag) {                         // if a knock is detected
      write_start = 1;                            // allow start recording knocks
      tone(buzzPin, 400, 50);                 
      last_knock = millis();
      threshold_flag = 0;
      if (debug) Serial.println("knock");
      break;
    }
  }

  if (write_start) {                                  // if recording has started
    while (1) {
      if (threshold_flag) {
        knock_time = millis() - last_knock;           // counting the time between the knocks
        wait_time[knock] = knock_time;                // record
        min_wait[knock] = knock_time - difficulty;    // determine the time taking into the reaction 
        max_wait[knock] = knock_time + difficulty;    // determine the time taking into the reaction
        knock++;                                      // get to the next
        tone(buzzPin, 400, 50);                                 
        last_knock = millis();
        threshold_flag = 0;
        if (debug) Serial.println("knock");
      }
      if (millis() - last_knock > 3000) {
        break;
      }
    }
    // to show the round combination
    tone(buzzPin, 400, 50);                      
    for (byte i = 0; i < knock; i++) {
      delay(wait_time[i]);                          // get to the next
      tone(buzzPin, 400, 50);                      
      if (debug) Serial.println(wait_time[i]);
    }
    mode = 0;                          
  }

}

void loop() {
  if (threshold_flag && mode == 0) {
    threshold_flag = 0;
    if (knock == 0) {
      mode = 3;
      goto openCap;
    }
    debounce_time = millis();
    last_try = millis();      // reset the timer 
    tone(buzzPin, 400, 50);
    try_count = 0;
    threshold_flag = 0;
    while (1) {

      // if hasn't pressed within a specific established time, then error
      if (millis() - last_try > max_wait[try_count]) {
        // мигнуть красным два раза
        tone(buzzPin, 400, 50);
        delay(1000);
        mode = 0;             // get back to the beginning! Start again!
        if (debug) Serial.println("too slow");
        threshold_flag = 0;
        break;
      }
      if (threshold_flag) {

        // if the click falls within the time range (correct click)
        if (millis() - last_try > min_wait[try_count] && millis() - last_try < max_wait[try_count]) {
          tone(buzzPin, 400, 50);               // blink
          try_count++;               // increase the counter of correct clicks
          last_try = millis();       // reset the counter to remove the impact of delays
          threshold_flag = 0;        // reset the flag
          if (debug) Serial.println("good");

          // if pressed too early (error)
        } else if (millis() - last_try < min_wait[try_count] && threshold_flag) {
          tone(buzzPin, 400, 50);
          delay(100);
          tone(buzzPin, 400, 50);        // blink red twice
          delay(1000);
          mode = 0;            // get back to the beginning!
          if (debug) Serial.println("too fast");
          threshold_flag = 0;
          break;
        }

        // if the number of correct clicks has coincided 
        if (try_count == knock) {
          // blink 3 times
          delay(200);
          tone(buzzPin, 400, 50);
          delay(200);
          tone(buzzPin, 400, 50);
          delay(200);
          tone(buzzPin, 400, 50);
          delay(200);
          mode = 3;   // move on
          if (debug) Serial.println("victory");
          break;
        }
      }
    }
  }


  if (mode == 3) {
openCap:
    mode = 4;
    delay(500);
    open_cap();
    good_night();
  }


  if ((threshold_flag && mode == 4) || mode == 5) {
    mode = 0;
    delay(500);
    close_cap();
    good_night();
  }

  if (millis() - debounce_time > 10000 || mode == 4) {
    good_night();
  }
}

void threshold() {
  if (millis() - debounce_time > 50) debonce_flag = 1;
  if (debonce_flag) {
    debounce_time = millis();
    threshold_flag = 1;
    debonce_flag = 0;
  }
}

void buttonPress() {
  if (mode == 4) {
    mode = 5;
  }
}

void good_night() {
  if (debug) {
    Serial.println("good night");
    delay(50);
  }
  delay(5);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);    // sleep. mode POWER_OFF
}

void open_cap() {
  if (debug) Serial.println("open cap");
  digitalWrite(servoVCC, 1);
  for (int i = close_angle; i < open_angle; i++) {
    servo.write(i);
    Serial.println(i);
    delay(12);
  }
  delay(100);
  digitalWrite(servoVCC, 0);
}

void close_cap() {
  if (debug) Serial.println("close cap");
  digitalWrite(servoVCC, 1);
  for (int i = open_angle; i > close_angle; i--) {
    servo.write(i);
    Serial.println(i);
    delay(12);
  }
  delay(100);
  digitalWrite(servoVCC, 0);
}
