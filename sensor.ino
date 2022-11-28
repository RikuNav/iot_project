/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-motion-sensor
 */

const int PIN_TO_SENSOR = 2;   // the pin that OUTPUT pin of sensor is connected to
int pinStateCurrent   = LOW; // current state of pin
int pinStatePrevious  = LOW; // previous state of pin
const unsigned long DELAY_TIME_MS = 30000; // 30000 miliseconds ~ 30 seconds
bool delayEnabled = false;
unsigned long delayStartTime;

void setup() {
  Serial.begin(9600);            // initialize serial
  pinMode(PIN_TO_SENSOR, INPUT); // set arduino pin to input mode to read value from OUTPUT pin of sensor
}

void loop() {
  pinStatePrevious = pinStateCurrent; // store state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    Serial.println("Turning on / activating");
    delayEnabled = false; // disable delay
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    delayEnabled = true; // enable delay
    delayStartTime = millis(); // set start time
  }

  if (delayEnabled == true && (millis() - delayStartTime) >= DELAY_TIME_MS) {
    Serial.println("Turning off / deactivating");
    delayEnabled = false; // disable delay
    // TODO: turn off alarm, light or deactivate a device ... here
  }
}
