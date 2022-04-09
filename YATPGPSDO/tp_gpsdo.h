/*
   (c) Copyright Szabolcs Szigeti 2020-2021

   Redistribution under GPL V3. See the LICENSE file for details.

*/
/*
   Configuration section
*/

#define VERSION "V1.14 2022/04/09"

#define GPSDO_BAUD  9600     // GPSDO serial speed: 9600 do not change

#define BTN_MODE  PB15       // mode button
#define BTN_SEL   PB14       // select button
#define LED_ONBOARD  PC13    // BluePill onboard LED - used for heartbeat indication
#define LED_HOLDOVER PB6     // Yellow LED for holdover
#define LED_LOCK  PB5        // Green LED for lock
#define LED_ALARM PB7        // Red LED for failure
#define LED_BACKLIGHT PB8    // Port for controlling display backlight

#define EEConfAddr  0x00      // Config address in EEPROM

#define DEBOUNCE  40         // Button debounce time in miliseconds. Shorter presses are not registred.
#define SHORTPRESS 500       // Limit for long button press.

#define NOMSGTIME 10000       // timeout if no GPS message for 10 seconds
#define PERIODICMSG 60000     // Position report every 60 seconds
#define BLINKTIME 500         // How fast things on the LEDs and display blink.
#define BACKLIGTHOFF  10000   // Backlight for 10 sec in auto mode

#define TIMEOFFSET  315964800L   // Magic correction for the 10 years off time from the gps. My TP reports time about 10 years off

#define NUMSAT 8               // Max number of satellites to track
#define MSGMAX  60             // Max msg size in chars

enum DisplayModes {STATUS, TIME, SATS, POSITION, CONFIG, ENDOFMODES};     // Display screens to flip with the Mode button
enum MenuModes {SHOWSURVEY, SETSURVEY, SETBACKLIGHT, SETOFFSET, SAVECONFIG, TRAINO}; // Various sub modes for the sreens

void ProcessGPSMsg();
bool GetGPSMsg();

void SetupDisplay();
void UpdateDisplay();
void handleButtons();
void PressBtnMode(int);
void PressBtnSel(int);
void handleLEDs();
void nextDisplay();

unsigned long millis();

/*
   System comfguration
*/
struct CONFIG {
  int timeoffset;             // Timezone settings in hours
  unsigned int surveytime;    // Default survey time
  unsigned int backlight;     // Backlight mode
  bool saved;                 // Hack for displaying ###FIX ME###
};

/*
   Data from the CLOCK message
*/
struct CLOCK {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int weekday;
  int quality;                // Time quality reported by the GPS
  uint32_t ticks;             // Unixtime ticks
};

/*
   General status of the system, mostly form the STATUS, EXTATUS messages
*/
struct STATUS {
  bool tenmhz;              // 10MHz is good. Is it ever bad???
  bool onepps;              // 1PPS id good. Same as above
  bool antenna;             // Antenna is correctly connected.
  int holdover;             // Holdover time
  int status;               // TruePosition status
  bool initialized;         // Has the TruePosition booted up?
  int nsats;                // Number of sats seen
  int tsats;                // Number of sats tracked
  float dop;                // DOP value
  float temp;               // Temperature of the unit
  int phaseoffset;          // Phase offset
  long lat;                 // Latitude
  long lon;                 // Longitude
  int elev;                 // Elevation
  bool surveying;           // Survey is in progress
  bool surveyed;            // Survey was run since last reboot
  int surveytime;           // Survey length
  float dac;                // DAC value for the OCXO steering
  char TPversion[11];       // Version string from the TruePosition board
  uint32_t lockedSince;     // Start time of current locked status, 0 if not locked
};

/*
   Data on satellites
*/
struct SATS {
  int satnum;               // Satellite PRN number
  int elevation;            // Elevation in degrees
  int azimuth;              // Azimuth in degrees
  int snr;                  // SNR value
  bool iswaas;              // Is it a WAAS/EGNOS sat?
};

/*
   Current alerts
*/
struct ALERTS {
  bool tenmhz;              // 10MHz is bad
  bool onepps;              // 1PPS is bad
  bool antenna;             // Antenna not detected
  bool nogps;               // Lost connection with TruePosition board
};
