#include "ChannelHandler.h"
#include "TimeTables.h"
#include "Wire.h"
#include "uRTCLib.h"

/* Pin assignment */
const int pinWhite = 5;
const int pinRed = 9;
const int pinBlue = 6;
const int pinButton1 = 2;

/* Instances of channel handlers */
ChannelHandler whiteChannel(valueTableWhite);
ChannelHandler redChannel(valueTableRed);
ChannelHandler blueChannel(valueTableBlue);
/* Instance of the realtime clock */
uRTCLib rtc;

bool blinkerState = true;
long currentTime = 0;
volatile bool simulationRunning = false;
volatile bool isInMaintenance = false;
volatile bool maintenanceStateChangeHandled = true;
unsigned long previousMillis = 0;


/* Initial configuration */
void setup() {
  /* Configuration of inputs and outputs */
  pinMode(pinWhite, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinButton1, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  /* Set initial values */
  analogWrite(pinWhite, 0);
  analogWrite(pinRed, 0);
  analogWrite(pinBlue, 0);
  /* Configure serial interface */
  delay(1000);
  Serial.begin(57600);
  delay(500);
  /* Eventually set time */
  // rtc.set(0, 0, 22, 6, 25, 8, 17); // RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  /* Configure button interrupt */
  attachInterrupt(digitalPinToInterrupt(pinButton1), button1Pressed, FALLING);
  Serial.println("TankControl started!");
}


/* The loop */
void loop() {
  unsigned long currentMillis = millis();

  /* Check if the loop has to run and determine current time - either simulated or from rtc */
  if (simulationRunning) {
    if (currentMillis - previousMillis < 5) {
      return;
    }
    /* In simulating mode the time ist increased by 15 seconds per step */
    currentTime += MINUTE / 4;
    currentTime %= (24 * HOUR);
  } else {
    if (currentMillis - previousMillis < 1000) {
      return;
    }
    /* Get the time from the attached real time clock */
    rtc.refresh();
    currentTime = rtc.hour() * HOUR + rtc.minute() * MINUTE + rtc.second();
  }
  /* Save the time of the last run */
  previousMillis = currentMillis;

  /* Blink each second */
  digitalWrite(LED_BUILTIN, blinkerState);
  blinkerState = !blinkerState;

  SetLedOutput(currentTime);
}


/* Handles the interrupt for button 1 pressed */
void button1Pressed() {
  if (maintenanceStateChangeHandled) {
    isInMaintenance = !isInMaintenance;
    maintenanceStateChangeHandled = false;
  }
}


/* Handles the incoming serial data event */
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == 's') {
      simulationRunning = true;
    } else if (inChar == 'r') {
      simulationRunning = false;
    }
  }
}


/* Set the LED output for the given time */
void SetLedOutput(long timestamp) {
  /* Get LED values for the given time */
  float percentageValueWhite = whiteChannel.GetPercentageAtTime(timestamp);
  float percentageValueRed = redChannel.GetPercentageAtTime(timestamp);
  float percentageValueBlue = blueChannel.GetPercentageAtTime(timestamp);

  /* Override values if we are in maintenance mode */
  if (isInMaintenance) {
    digitalWrite(LED_BUILTIN, true);
    percentageValueWhite = maintenancePercentageValue;
    percentageValueRed = maintenancePercentageValue;
    percentageValueBlue = maintenancePercentageValue;
    Serial.println("Maintenance mode active");
  }
  maintenanceStateChangeHandled = true;

  /* Convert percentage values to raw PWM values */
  int rawValueWhite = GetRawFromPercentage(GammaCorrect(percentageValueWhite));
  int rawValueRed = GetRawFromPercentage(GammaCorrect(percentageValueRed));
  int rawValueBlue = GetRawFromPercentage(GammaCorrect(percentageValueBlue));

  /* Set PWM values to the LED outputs */
  analogWrite(pinWhite, rawValueWhite);
  analogWrite(pinRed, rawValueRed);
  analogWrite(pinBlue, rawValueBlue);

  PrintSerialOutput(currentTime, percentageValueWhite, percentageValueRed, percentageValueBlue);  
}


/* Performs a simple gamma correction of the given percentage value */
float GammaCorrect(float percentageValue) {
  return percentageValue * percentageValue / 100;
  // return pow(percentageValue, 2.7) / 2512;
}


/* Converts the percentage value into a raw PWM value */
int GetRawFromPercentage(float percentageValue) {
  int rawValue = percentageValue * 2.55 + 0.5;
  /* Set the raw value to 1 if it would be to small to have a guaranteed output if the percentage value is greater zero */
  if (percentageValue > 0 && rawValue == 0) {
    rawValue = 1;
  }
  return rawValue;
}


/* Prints the current time and values */
void PrintSerialOutput(long timer, float vWhite, float vRed, float vBlue) {
  char output[60];

  sprintf(output, "[%02d:%02d:%02d] White: %02d.%01d%% Red: %02d.%01d%% Blue: %02d.%01d%%",
          (int)(timer / HOUR),
          (int)((timer % HOUR) / MINUTE),
          (int)(timer % MINUTE),
          (int)vWhite,
          (int)(vWhite * 10) % 10,
          (int)vRed,
          (int)(vRed * 10) % 10,
          (int)vBlue,
          (int)(vBlue * 10) % 10);
  Serial.println(output);
}

