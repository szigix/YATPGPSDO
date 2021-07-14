/*
   (c) Copyright Szabolcs Szigeti 2020-2021

   Redistribution under GPL V3. See the LICENSE file for details.

*/
/*
   This file contains the display related functions.
   Basically there are a number of screens, which can be selected by the Mode button.
   Pressing the button will cycle trough the general status, the clock, the satellites,
   the position, and the config screens.

   The display is a 128x64 pixel LCD with an ST7920 driver.
   No attempt is made to accomodate any other display, most of the text and graphics
   positions are hard coded.

   However the U8G2 library is used so other similar sized bitmap display might be used.
   All display related stuff are in this file, so to use other display, make changes here.
*/

/*
   Printable strings for date and for the TruePosition status.
*/
char *weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char *gpsstatus[] = {"Locked", "Acquisition", "Init 5/6", "Holdover",         //  0  1  2  3
                     "Force HO", "Soft HO", "No position", "Train OCXO",      //  4  5  6  7
                     "Holdover", "Init 0/6", "Init 1/6", "Init 2/6",          //  8  9 10 11
                     "Init 3/6", "Init 4/6", "Lock 1/5", "Lock 2/5",          // 12 13 14 15
                     "Lock 3/5", "Lock 4/5", "Lock 5/5", "Init 6/6",          // 16 17 18 19
                     "Acquire 1/3", "Acquire 2/3", "Acquire 3/3", "23"        // 20 21 22 23
                    };

/*
   Various bitmaps for the status bar on the main page
*/
uint8_t bitmapAnt[] = {16, 146, 84, 56, 16, 16, 16, 16, 16, 16, 16};              // Antenna symbol
uint8_t bitmapIAnt[] = {170, 84, 170, 84, 170, 84, 170, 84, 170, 84, 170};        // Checkerboard for antenna error
uint8_t bitmap10MHz[] = {73, 84, 0, 213, 213, 224, 85, 92, 64, 85, 84, 128, 73, 85, 224};       // 10Mhz
uint8_t bitmapI10MHz[] = {170, 170, 170, 85, 85, 85, 170, 170, 170, 85, 85, 85, 170, 170, 170}; // Bad 10Mhz
uint8_t bitmap1PPS[] = {89, 140, 213, 80, 89, 136, 81, 4, 81, 24};                // 1 PPS
uint8_t bitmapI1PPS[] = {170, 170, 85, 84, 170, 170, 85, 84, 170, 170};           // Bad 1PPS
uint8_t bitmapSurv1[] = {16, 16, 16, 16, 16, 254, 124, 56, 16, 254};              // Survey needed
uint8_t bitmapSurv2[] = {16, 254, 124, 56, 16, 0, 0, 0, 0, 254};                  // Animation during survey
uint8_t bitmapSurveyed[] = {56, 108, 198, 238, 254, 124, 56, 56, 16, 16};         // Location has been surveyed
#define clockface_width 49
#define clockface_height 47
uint8_t clockface_bits[] = {
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F,
  0xE3, 0x01, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x06, 0x00, 0x00, 0x00,
  0x30, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x14, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00,
  0x88, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x90, 0x00, 0x00,
  0x00, 0x00, 0x12, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00,
  0x00, 0x01, 0x00, 0x40, 0x00, 0x1F, 0x00, 0x80, 0x02, 0x00, 0xF0, 0x01,
  0x04, 0x00, 0x00, 0x01, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x50, 0x00, 0x00, 0x00,
  0x00, 0x14, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x42, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x24, 0x00,
  0x00, 0x48, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x80, 0x01, 0x01, 0x03, 0x00,
  0x00, 0x00, 0x00, 0x0E, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00,
};
/*
   Initialize the display. It is in HW SPI mode, so uses the HW SPI pins
   PA4 is used for CS and PB0 is connected as resert.
*/
U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ PA4, /* reset=*/ PB0 /*U8X8_PIN_NONE */);

/*
   Let's do some fancy initialization with Display and LED test.
*/
void SetupDisplay() {


  u8g2.begin();
  u8g2.enableUTF8Print();               // that is required to properly display the degree symbol
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.clearBuffer();
  u8g2.drawBox(0, 0, 128, 64);          // all pixels dark
  u8g2.sendBuffer();
  delay(500);                           // and wait a little bit for fancyness
}

/*
   Print the current time in HH:MM:SS format, with blinking :
   This prints at the current positoion with the current font
*/
void printTime() {
  if (gpsdoClock.hour < 10)
    u8g2.print(" ");
  u8g2.print(gpsdoClock.hour);
  u8g2.print(blink ? ":" : " ");
  if (gpsdoClock.minute < 10)
    u8g2.print("0");
  u8g2.print(gpsdoClock.minute);
  u8g2.print(blink ? ":" : " ");
  if (gpsdoClock.second < 10)
    u8g2.print("0");
  u8g2.print(gpsdoClock.second);
}

/*
   Print a time lenght in DDD|HH:MM.SS format supressing
   leading zero days, hours and minutes
   This also prints at the current positoion with the current font
*/
void printInterval(uint32_t secs) {
  unsigned int days, hours, minutes, seconds;
  days = secs / 86400;
  secs -= days * 86400;
  hours = secs / 3600;
  secs -= hours * 3600;
  minutes = secs / 60;
  seconds = secs % 60;
  if (days > 0) {
    u8g2.print(days);
    u8g2.print("|");
  }
  if (hours > 0 || days > 0) {
    if (hours < 10)
      u8g2.print(" ");
    u8g2.print(hours);
    u8g2.print(":");
  }
  if ( minutes > 0 || hours > 0 || days > 0) {
    if (minutes < 10)
      u8g2.print("0");
    u8g2.print(minutes);
    u8g2.print(".");
  }
  if (seconds < 10)
    u8g2.print("0");
  u8g2.print(seconds);
}
/*
   Display general status of the unit
*/
void displayStatusPage() {
  int shour, smin, ssec;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont12_tf);

  /*
     Print the status line with the TruePosition status and some
     icons for 10Mhz, 1PPS status
  */
  u8g2.setCursor(0, 10);
  if (gpsdoAlerts.nogps)
    u8g2.print(blink ? "GPS Lost" : " ");
  else if (gpsdoStatus.status < 23)
    u8g2.print(gpsstatus[gpsdoStatus.status]);
  else
    u8g2.print("No status");

  u8g2.drawBitmap(95, 00, 1, 11, !gpsdoAlerts.antenna ? bitmapAnt : blink ? bitmapIAnt : bitmapAnt);
  u8g2.drawBitmap(105, 06, 3, 5, !gpsdoAlerts.tenmhz ? bitmap10MHz : blink ? bitmapI10MHz : bitmap10MHz);
  u8g2.drawBitmap(105, 00, 2, 5, !gpsdoAlerts.onepps ? bitmap1PPS : blink ? bitmapI1PPS : bitmap1PPS);

  u8g2.drawHLine(0, 12, 128);

  /*
     If the TruePosition is up and runing print the icon for survey or normal mode
     Print the time
     Lock and holdover duration if applicable
     Number of satellites, DOP, DAC value and temperature.
  */
  if (gpsdoStatus.initialized) {
    u8g2.drawBitmap(85, 0, 1, 10, gpsdoStatus.surveying ? blink ? bitmapSurv1 : bitmapSurv2 : gpsdoStatus.surveyed ? bitmapSurveyed : bitmapSurv1);
    u8g2.setCursor(0, 27);
    u8g2.setFont(u8g2_font_profont17_tf);
    printTime();
    u8g2.setFont(u8g2_font_profont10_tf);
    if (gpsdoStatus.holdover > 0) {
      u8g2.setCursor(0, 40);
      u8g2.print("Holdover:");
      printInterval(gpsdoStatus.holdover);
    }
    if (gpsdoStatus.lockedSince > 0) {
      u8g2.setCursor(0, 40);
      u8g2.print("Locked:");
      printInterval(gpsdoClock.ticks - gpsdoStatus.lockedSince);
    }

    u8g2.setCursor(0, 50);
    u8g2.print("Sat:"); u8g2.print(gpsdoStatus.nsats); u8g2.print("/"); u8g2.print(gpsdoStatus.tsats);
    if (gpsdoStatus.dop > 0.0) {
      u8g2.print(" DOP:"); u8g2.print(gpsdoStatus.dop, 2);
    } else
    {
      u8g2.print (" No fix");
    }
    if (gpsdoStatus.phaseoffset != -253) {
      u8g2.print(" phi:"); u8g2.print(gpsdoStatus.phaseoffset);
    }

    u8g2.setCursor(0, 58);
    u8g2.print("DAC:"); u8g2.print(gpsdoStatus.dac, 6); u8g2.print("V");
    u8g2.print(" T:"); u8g2.print(gpsdoStatus.temp, 2); u8g2.print("°C");
  } else {

    /*
       If the TruePosition is not yet up, print a splash screen
    */

    u8g2.setFont(u8g2_font_profont17_tf);
    u8g2.drawStr(10, 30, "YATPGPSDO");
    u8g2.setFont(u8g2_font_profont10_tf);
    u8g2.drawStr(5, 40, "(c) Szabolcs Szigeti");
    u8g2.setFont(u8g2_font_profont12_tf);
    u8g2.drawStr(10, 52, VERSION);
    u8g2.drawStr(10, 62, gpsdoStatus.TPversion);
  }
  u8g2.sendBuffer();
}

/*
   Display current time, date, time quality reported and an analog clock
*/

void displayTimePage() {
  float hourdeg, mindeg, secdeg, tickdeg;
  int i;

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont17_tf);
  u8g2.setCursor(0, 15);
  printTime();
  u8g2.setCursor(0, 29);
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.print(gpsdoClock.year);
  u8g2.print(" ");
  u8g2.print(months[gpsdoClock.month - 1]);
  u8g2.print(" ");
  u8g2.print(gpsdoClock.day);
  u8g2.print(" ");
  u8g2.setCursor(0, 39);
  u8g2.println(weekdays[gpsdoClock.weekday - 1]);
  u8g2.setCursor(0, 53);
  u8g2.setFont(u8g2_font_profont10_tf);
  u8g2.print("Quality:");
  u8g2.print(gpsdoClock.quality);
  u8g2.drawFrame(0, 57, 70, 7);
  u8g2.drawBox(1, 58, gpsdoClock.quality * 10, 5);
  /*
     Draw the analog clock. The STM32 is fast enough to simply use trigonometrics instead of look-up tables
     or some approximation. This is a pretty simple and ugly looking clock.
  */
  u8g2.drawXBM(80, 9, clockface_width, clockface_height, clockface_bits);
  hourdeg = (gpsdoClock.hour * 5 + gpsdoClock.minute / 12 - 15) * 0.104719755;    // magic number to convert 6 degrees to radians.
  mindeg = (gpsdoClock.minute - 15) * 0.104719755;
  secdeg = (gpsdoClock.second - 15) * 0.104719755;
  u8g2.drawLine(105, 32, 105 + 20 * cos(secdeg), 32 + 20 * sin(secdeg));
  u8g2.drawLine(105, 32, 105 + 18 * cos(mindeg), 32 + 18 * sin(mindeg));
  u8g2.drawLine(105, 32, 105 + 13 * cos(hourdeg), 32 + 13 * sin(hourdeg));

  u8g2.sendBuffer();
}

/*
   Display satellite info.
   Anything with non 0 SNR is listed on the right and the constellation is drawn on the left.
   Normal sats are drawn as a circle, WAAS/EGNOS as a square.
   Again, STM32 can handle trig functions just fine.
*/
void displaySatsPage() {
  int i, row;
  int x, y, r, snr;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont10_tf);
  u8g2.setCursor(60, 63);
  u8g2.print(gpsdoStatus.nsats); u8g2.print("/"); u8g2.println(gpsdoStatus.tsats);
  u8g2.print(" DOP:"); u8g2.println(gpsdoStatus.dop, 2);
  row = 6;
  for (i = 0; i < NUMSAT; i++)
    if (gpsdoSats[i].snr > 0) {

      snr = (gpsdoSats[i].snr - 30) / 2;    // Seems like SNR values are about in the 30-45 dB range
      if (snr <0) snr = 0;
      if (snr > 7) snr = 7;                 // so we transform it into the height of one row. Yes, it could be better.
      u8g2.drawLine(64, row, 64, row - snr);

      u8g2.setCursor(67, row);
      u8g2.print(i);
      u8g2.print(":");
      u8g2.print(gpsdoSats[i].satnum);
      u8g2.print(">");
      u8g2.print(gpsdoSats[i].elevation);
      u8g2.print("/");
      u8g2.print(gpsdoSats[i].azimuth);
      row += 7;
      /*
         Start graphic
      */
      r = 30 * cos(0.017453 * (gpsdoSats[i].elevation));
      x = 32 + r * cos(0.017453 * (gpsdoSats[i].azimuth - 90));
      y = 32 + r * sin(0.017453 * (gpsdoSats[i].azimuth - 90));

      if (gpsdoSats[i].iswaas) {          // Circle for normal, box for WAAS satellites
        u8g2.drawFrame(x - 5, y - 5, 10, 10);
      } else {
        u8g2.drawCircle(x, y, 5);
      }

      u8g2.setCursor(x - 2, y + 3);
      u8g2.print(i);
    }

  u8g2.drawCircle(32, 32, 30, U8G2_DRAW_ALL);
  u8g2.drawCircle(32, 32, 10, U8G2_DRAW_ALL);
  u8g2.drawVLine(32, 0, 64);
  u8g2.drawHLine(0, 32, 64);
  u8g2.drawTriangle(32, 0, 29, 6, 35, 6);
  u8g2.sendBuffer();
}

/*
   Display position and start survey.
   Short press of the select button will increment the survey time, long press will start the survey.
*/
void displayPosPage() {
  long lat, lon;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.setCursor(0, 10);
  u8g2.print("Position ");
  printTime();

  u8g2.setCursor(0, 24);

  lat = gpsdoStatus.lat;
  lon = gpsdoStatus.lon;
  u8g2.setFont(u8g2_font_profont17_tf);

  if (lat < 0) {
    u8g2.print("S");
    lat = -lat;
  } else {
    u8g2.print("N");
  }
  u8g2.print(lat / 1000000);
  u8g2.print("°");
  u8g2.print((lat % 1000000) * 6E-5, 4);
  u8g2.print("'");
  u8g2.setCursor(0, 38);

  if (lon < 0) {
    u8g2.print("W");
    lon = -lon;
  } else {
    u8g2.print("E");
  }
  u8g2.print(lon / 1000000);
  u8g2.print("°");
  u8g2.print((lon % 1000000) * 6E-5, 4);
  u8g2.print("'");
  u8g2.setCursor(0, 50);
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.print("Elev:");
  u8g2.println(gpsdoStatus.elev);
  u8g2.print("   Sats:");
  u8g2.print(gpsdoStatus.nsats);
  u8g2.print("/");
  u8g2.println(gpsdoStatus.tsats);

  u8g2.setCursor(0, 60);
  u8g2.setFont(u8g2_font_profont10_tf);
  if (menuMode == SHOWSURVEY) {
    u8g2.print("Survey ");
    u8g2.print(gpsdoStatus.surveytime);
    u8g2.print("s remain");
  }
  else if (menuMode == SETSURVEY) {
    u8g2.print("Survey for ");
    u8g2.print(gpsdoConfig.surveytime);
    u8g2.print(gpsdoConfig.surveytime == 1 ? " hour" : " hours");
  }

  u8g2.sendBuffer();
}

/*
   Configuration page. Select selects the items, long press changes them.
   Save config to make it permanent.
*/
void displayConfigPage() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont12_tf);
  u8g2.setCursor(0, 8);
  u8g2.print("Config ");
  u8g2.setFont(u8g2_font_profont10_tf);
  u8g2.print(VERSION);


  u8g2.setCursor(00, 20);
  u8g2.print(menuMode == SETOFFSET ? ">" : " ");
  u8g2.print("Time offset:");
  u8g2.print(gpsdoConfig.timeoffset);

  u8g2.setCursor(00, 28);
  u8g2.print(menuMode == SETBACKLIGHT ? ">" : " ");
  u8g2.print("Backlight:");
  switch (gpsdoConfig.backlight) {
    case 0:
      u8g2.print("Off"); break;
    case 1:
      u8g2.print("Auto"); break;
    case 2:
      u8g2.print("On"); break;
  }
  u8g2.setCursor(00, 36);
  u8g2.print(menuMode == SAVECONFIG ? ">" : " ");
  u8g2.print("Save config ");
  if (gpsdoConfig.saved)
    u8g2.print("Saved");

  u8g2.setCursor(00, 44);
  u8g2.print(menuMode == TRAINO ? ">" : " ");
  u8g2.print("Train OCXO");

  u8g2.setCursor(00, 63);
  u8g2.print("Uptime: ");
  printInterval(millis() / 1000);
  u8g2.sendBuffer();
}

/*
   Select the page on the display mode.
*/
void UpdateDisplay() {
  switch (displayMode) {

    case STATUS: displayStatusPage();     // General Status
      break;
    case TIME: displayTimePage();         // Time
      break;
    case SATS: displaySatsPage();          // Sats
      break;
    case POSITION: displayPosPage();       // Position and survey
      break;
    case CONFIG: displayConfigPage();     // Config
      break;
    default: displayStatusPage();
  }

}

/*
   Advance to next display on the press of the Mode button
*/
void nextDisplay() {
  switch (displayMode) {
    case STATUS: displayMode = TIME;
      break;
    case TIME: displayMode = SATS;
      break;
    case SATS: displayMode = POSITION;
      menuMode = gpsdoStatus.surveying ? SHOWSURVEY : SETSURVEY;
      break;
    case POSITION: displayMode = CONFIG;
      menuMode = SETOFFSET;
      gpsdoConfig.saved = false;
      break;
    case CONFIG: displayMode = STATUS;
      break;
    default: displayMode = STATUS;
  }
  refresh = true;                     // redraw
}
