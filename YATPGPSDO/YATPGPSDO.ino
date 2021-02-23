/*
   (c) Copyright Szabolcs Szigeti 2020-2021

   Redistribution under GPL V3. See the LICENSE file for details.


  Board: Generic STM32F103C series
  Display: 128x64 ST7920 based bitmap display

  Additional libraries: Time and U8G2

*/
/*
   Main program for the TruePosition GPSDO
*/
#include <Time.h>
#include <TimeLib.h>
#include <EEPROM.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "TP_GPSDO.h"

struct CLOCK gpsdoClock;        // Clock related data
struct STATUS gpsdoStatus;      // Everything about the status of the GPSDO
struct SURVEY gpsdoSurvey;      // Survey status
struct SATS gpsdoSats[NUMSAT];  // Data on the tracked satellites
struct ALERTS gpsdoAlerts;      // Alerts
struct CONFIG gpsdoConfig;      // COnfiguration settings

char GPSmsg[MSGMAX];            // buffer for TruePosition messages

bool refresh = false;           // do we need to redraw the display?

unsigned long lastMsgTime, periodicMsgTime, blinkTime, backlTime; // timers for messages, blinking and backlight
unsigned long lastBtnModeTime, lastBtnSelTime, btnPress;          // timers for the buttons
int lastBtnMode = 1, lastBtnSel = 1;                              // button state for the Mode and Select buttons
enum DisplayModes displayMode = STATUS;                           // current display mode
enum MenuModes menuMode = SETSURVEY;                              // current menu mode
bool heartBeat = false;                                           // heart beat led
bool initPPSDBG = false;                                          // PPSDBG command sent at init
int surveySetTime = 1;                                            // Default survey time
bool inAlert = false;                                             // is there any alert?
bool blink;                                                       // The global blink used for any kind of blinking

void setup() {

  /*
     Set up software serial port to GPSDO.

     Serial2 for TruePosition communications

  */

  Serial2.begin(GPSDO_BAUD);

  /*
     Set up button inputs with pull-up
  */
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_SEL, INPUT_PULLUP);
  /*
     Setup LEDs for output
  */
  pinMode(LED_ONBOARD, OUTPUT);
  pinMode(LED_HOLDOVER, OUTPUT);
  pinMode(LED_LOCK, OUTPUT);
  pinMode(LED_ALARM, OUTPUT);
  pinMode(LED_BACKLIGHT, OUTPUT);

  digitalWrite(LED_HOLDOVER, HIGH);
  digitalWrite(LED_LOCK, HIGH);
  digitalWrite(LED_ALARM, HIGH);
  digitalWrite(LED_BACKLIGHT, HIGH);

  EEPROM.init();
  gpsdoStatus.status = 24;
  gpsdoAlerts.tenmhz = gpsdoAlerts.onepps = true;
  gpsdoStatus.surveyed = false;
  periodicMsgTime = lastMsgTime = blinkTime = backlTime = millis();
  SetupDisplay();
  readConfig();

}

void loop() {

  for (;;) {

    if (GetGPSMsg()) {
      ProcessGPSMsg();
      lastMsgTime = millis();
      gpsdoAlerts.nogps = false;
    }

    /*
       This will detect if there is no message from the GPS for longer than NOMSGTIME
       If triggered, it will cause a GPS lost alert.
    */
    if (millis() - lastMsgTime > NOMSGTIME && gpsdoAlerts.nogps == false) {
      gpsdoAlerts.nogps = true;
      gpsdoAlerts.tenmhz = true;
      gpsdoAlerts.onepps = true;
      gpsdoStatus.status = 24;
      gpsdoStatus.initialized = false;
      gpsdoStatus.surveyed = false;
      initPPSDBG = false;
    }
    
    /*
       We force the GPS to provide position report every PERIODICMSG time
       TruePosition normally only reports position during survey.
    */
    if (millis() - periodicMsgTime > PERIODICMSG) {
      periodicMsgTime = millis();
      Serial2.println("$GETPOS");
    }

    /*
       Fancy blinking. This does two things:
        1 - sets the blink variable to use for blinking wherever needed.
        2 - blinks the onboard led for heartbeat.
    */
    if (millis() - blinkTime > BLINKTIME) {
      blinkTime = millis();
      blink = !blink;
      refresh = true;
      digitalWrite(LED_ONBOARD, blink ? HIGH : LOW);
    }

    /*
           Check for button presesses and do the needed action
    */
    handleButtons();

    /*
            Set the LEDS to the current status
    */
    handleLEDs();

    /*
       This handles the lock timer. Every time the GPSDO locks, it will start the timer to show
       how long it is in lock. Any other status clears the timer.
    */
    if (gpsdoStatus.lockedSince == 0 && (gpsdoStatus.status == 0 )) {
      gpsdoStatus.lockedSince = gpsdoClock.ticks;
    } else {
      if (gpsdoStatus.status != 0 ) {
        gpsdoStatus.lockedSince = 0;
      }
    }
    /*
       Any failure sets the alert status.
       Not sure if the 10 MHz and the 1PPS alert is ever activated by the TP.
    */
    if (gpsdoAlerts.nogps || gpsdoAlerts.tenmhz || gpsdoAlerts.onepps || gpsdoAlerts.antenna) {
      if (!inAlert) {
        inAlert = true;
        refresh = true;
      }
    }
    else {
      if (inAlert) {
        inAlert = false;
        refresh = true;
      }

    }
    /*
             Only refresh display if there is a reason to refresh
    */
    if (refresh == true) {
      refresh = false;
      UpdateDisplay();
    }

  }
}

/*
   Based on the status the front panel LEDs are lit.
*/
void handleLEDs() {

  digitalWrite(LED_ALARM, inAlert ? HIGH : LOW);   // If there is an alert, light the red LED.

  switch (gpsdoStatus.status) {
    case 0:                                        // Locked: Green lock LED on
      digitalWrite(LED_LOCK, HIGH);
      digitalWrite(LED_HOLDOVER, LOW);
      break;
    case 1:                                        // Acquisition: Blink yellow holdover LED.
      digitalWrite(LED_LOCK, LOW);
      digitalWrite(LED_HOLDOVER, blink ? HIGH : LOW);
      break;
    case 2:                                          // During startup both Lock and Holdover LEDs blink
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 19:
      digitalWrite(LED_LOCK, blink ? HIGH : LOW);
      digitalWrite(LED_HOLDOVER, blink ? HIGH : LOW);
      break;
    case 3:                                       // Holdover: yellow Holdover LED is on.
    case 4:
    case 5:
    case 8:
      digitalWrite(LED_HOLDOVER, HIGH);
      digitalWrite(LED_LOCK, LOW);
      break;

    case 6:                                       // No ackquisition, both LEDs are off
      digitalWrite(LED_LOCK, LOW);
      digitalWrite(LED_HOLDOVER, LOW);
      break;
    case 7:                                       // OCXO training, both LED blinks in opposite
      digitalWrite(LED_LOCK, blink ? HIGH : LOW);
      digitalWrite(LED_HOLDOVER, blink ? LOW : HIGH);
      break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:                                        // Transition to lock: Lock LED on, Holdover LED blinks
      digitalWrite(LED_LOCK, HIGH);
      digitalWrite(LED_HOLDOVER, blink ? LOW : HIGH);
      break;
    case 20:
    case 21:
    case 22:                                       // Transition to acquisition: Lock LED blinks, Holdover LED on
      digitalWrite(LED_LOCK, blink ? LOW : HIGH);
      digitalWrite(LED_HOLDOVER, HIGH);
      break;
    default:  digitalWrite(LED_ALARM, blink ? LOW : HIGH); // anything else is a strange situation

  }

  /*
     Control the backlight.
     off (0)  - always off
     auto (1) - turns on with button press, automatically off after BACKLIGHTOFF ticks.
     on (2)   - always on
  */
  if (gpsdoConfig.backlight == 0) {
    digitalWrite(LED_BACKLIGHT, LOW);
  } else {
    if (gpsdoConfig.backlight == 2) {
      digitalWrite(LED_BACKLIGHT, HIGH);
    } else {
      digitalWrite(LED_BACKLIGHT, (millis() - backlTime > BACKLIGTHOFF) ? LOW : HIGH);
    }
  }
}

/*
   Save configuration to the EEPROM (emualted EEPROM)
   Simply writes the gpsdoConfig struct.
*/
void saveConfig() {
  int i;
  byte *p;
  gpsdoConfig.magic = 0x1ea7;
  gpsdoConfig.lat = gpsdoStatus.lat;
  gpsdoConfig.lon = gpsdoStatus.lon;
  gpsdoConfig.elev = gpsdoStatus.elev;
  p = (byte*)&gpsdoConfig;
  for (i = 0; i < sizeof(struct CONFIG); i++) {
    EEPROM.update(i, *p++);
    delay(50);
  }

}

/*
   Read back config from EEPROM and do some sanitiy checking
*/
void readConfig() {
  int i;
  byte *p;
  struct CONFIG conf;
  p = (byte*)&conf;
  for (i = 0; i < sizeof(struct CONFIG); i++) {
    *p++ = EEPROM.read(i);
  }
  if (conf.magic != 0x1ea7)
    return;
  if (conf.timeoffset > 12 || conf.timeoffset < -12)
    conf.timeoffset = 0;
  if (conf.backlight > 2)
    conf.backlight = 1;
  gpsdoConfig = conf;

}
