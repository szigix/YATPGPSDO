/*
   (c) Copyright Szabolcs Szigeti 2020-2021

   Redistribution under GPL V3. See the LICENSE file for details.

*/
/*
   This file contains most of he code to process the messages from the TruePosition
   boards.
   Messages are read as available the parameters are identified
   and pocessed according to the message.
*/

void ProcessGETVER();
void ProcessCLOCK(uint32_t, int);
void ProcessSTATUS();
void ProcessEXTSTATUS();
void ProcessSURVEY(long, long, int, int);
void ProcessSAT(int chan, int sat, int elevation, int azimuth, int snr, bool iswaas);

#define MAXPARAM  8                 // Maximum number of GPS message parameters
static char* params[MAXPARAM];      // This indexes the parameters in the message

/*
   Read GPS serial line and push read text into the GPSmsg buffer for a maximum length of MSGMAX
   Return true if at the end of message, so that the main loop knows to dispatch message for processing
*/
bool GetGPSMsg() {
  static int current = 0;
  int Incoming;

  while (Serial2.available() > 0) {
    Incoming = Serial2.read();

    if (Incoming == '\n' || current >= MSGMAX - 1) {
      GPSmsg[current] = '\0';
      current = 0;
      return true;
    }

    if (Incoming == '\r') continue; // Skip NewLine

    GPSmsg[current++] = Incoming;

  }
  return false;
}

/*
   Procerss the message in the GPSmsg buffer

   First check for validity by verifying the starting $
   Then break up into substrings at the parameters and put the pointers to the parameters
   into the params array.
   Then depending on the message type do whatever action is required.
   Set alert condition if no message for some time
   Also handle the special case of booting, when the TruePosition needs the $PROCEED command.
*/

void ProcessGPSMsg() {
  int i = 1;
  int parn = 0;

  if (GPSmsg[0] != '$') {

    return;
  }
  refresh = true;
  lastMsgTime = millis();

  while (i < MSGMAX && GPSmsg[i] != '\0') {
    if (GPSmsg[i] == ' ') {
      GPSmsg[i] = '\0';
      params[parn++] = &GPSmsg[i + 1];
      if (parn >= MAXPARAM)
        break;
    }
    i++;
  }
  /*
     Kickstart the TruePosition.
     It keeps sending the GETVER message with BOOT as second parameter
     This triggers the code to send the PROCEED command which will make the board boot.
     Also, initialize a couple of things.
  */
  if (strcmp(&GPSmsg[1], "GETVER") == 0) {
    if (strcmp(params[1], "BOOT") == 0) {
      Serial2.println("$PROCEED");
   
      gpsdoStatus.TPversion[0] = 0;
      strncpy(gpsdoStatus.TPversion, params[0], 10);
      gpsdoStatus.TPversion[10] = 0;
      gpsdoStatus.status = atoi(params[2]);
      gpsdoAlerts.nogps = true;
      gpsdoAlerts.tenmhz = true;
      gpsdoAlerts.onepps = true;
      gpsdoStatus.status = 24;
      gpsdoStatus.initialized = false;
      gpsdoStatus.surveyed = false;
      initPPSDBG = false;

    }
    return; // don't process further after PROCEED
  }

  /*
     Send the PPSDBG command to periodically provide additional status
  */
  if (!gpsdoStatus.initialized) {
    if (!initPPSDBG) {
      Serial2.println("$PPSDBG 1");
      initPPSDBG = true;
    }
  }


  /*
     From here on verious messages are identified and processed either
     in this loop or via calling a function to process.
  */

  if (strcmp(&GPSmsg[1], "CLOCK") == 0) {
    ProcessCLOCK(atol(params[0]), atoi(params[1]), atoi(params[2]));
    return;
  }

  if (strcmp(&GPSmsg[1], "STATUS") == 0) {

    gpsdoStatus.initialized = true;                           // after first STATUS we consider the GPSDO fully initilaized and working
    gpsdoAlerts.tenmhz = (gpsdoStatus.tenmhz = atoi(params[0]));
    gpsdoAlerts.onepps = (gpsdoStatus.onepps = atoi(params[1]));
    gpsdoAlerts.antenna = (gpsdoStatus.antenna = atoi(params[2]));
    gpsdoStatus.holdover = atoi(params[3]);
    gpsdoStatus.nsats = atoi(params[4]);

    if (!initPPSDBG) gpsdoStatus.status = atoi(params[5]);  // we only use the status from here if PPSDBG has not been initialized
    return;
  }

  if (strcmp(&GPSmsg[1], "EXTSTATUS") == 0) {
    gpsdoStatus.surveying = (atoi(params[0]) == 1);
    gpsdoStatus.tsats = atoi(params[1]);
    gpsdoStatus.dop = atoi(params[2]);
    gpsdoStatus.temp = atof(params[3]);

    if (!gpsdoStatus.surveyed && gpsdoStatus.surveying) {
      gpsdoStatus.surveyed=true;
    }
    return;
  }

  if (strcmp(&GPSmsg[1], "SURVEY") == 0) {
    ProcessSURVEY(atol(params[0]), atol(params[1]), atoi(params[2]), atoi(params[4]));
    return;
  }

  if (strcmp(&GPSmsg[1], "SAT") == 0) {
    ProcessSAT(atoi(params[0]), atoi(params[1]), atoi(params[2]), atoi(params[3]), atoi(params[4]), false);
    return;
  }
  if (strcmp(&GPSmsg[1], "WSAT") == 0) {
    ProcessSAT(atoi(params[0]), atoi(params[1]), atoi(params[2]), atoi(params[3]), atoi(params[4]), true);
    return;
  }
  if (strcmp(&GPSmsg[1], "GETPOS") == 0) {
    ProcessGETPOS(atol(params[0]), atol(params[1]), atoi(params[2]));
    return;
  }
  if (strcmp(&GPSmsg[1], "PPSDBG") == 0) {
    gpsdoStatus.status = atoi(params[1]);
    gpsdoStatus.dac = atof(params[2]) * 6.25E-5;
    return;
  }
  if (strcmp(&GPSmsg[1], "SET1PPS") == 0) {
    return;
  }

  refresh = false;
}

void ProcessGETVER() {

}

/*
   This processes the CLOCK message
   We save the ticks and also we save the date nad time components for simpler displaying later
   The user configurable timezone offset is added as well as the magic TIMEOFFSET to correct the
   ~10 year time difference reported by the GPSDO
*/
void ProcessCLOCK(uint32_t ti, int leapsec, int quality) {
  gpsdoClock.ticks = ti = ti - leapsec + TIMEOFFSET + 3600 * gpsdoConfig.timeoffset;
  gpsdoClock.year = year(ti);
  gpsdoClock.month = month(ti);
  gpsdoClock.day = day(ti);
  gpsdoClock.weekday = weekday(ti);
  gpsdoClock.hour = hour(ti);
  gpsdoClock.minute = minute(ti);
  gpsdoClock.second = second(ti);
  gpsdoClock.quality = 8 - quality;


}

/*
   Starightforward saving of the position data.
*/
void ProcessSURVEY(long lat, long lon, int elev, int stime) {
  gpsdoStatus.lat = gpsdoSurvey.lat = lat;
  gpsdoStatus.lon = gpsdoSurvey.lon = lon;
  gpsdoStatus.elev = gpsdoSurvey.elev = elev;
  gpsdoSurvey.surveytime = stime;

}

/*
   The same function is used to store sat data for normal and for WAAS sats, the last parameter
   tells the type of the satellite
*/
void ProcessSAT(int chan, int sat, int elevation, int azimuth, int snr, bool iswaas) {
  if (chan >= NUMSAT)
    return;
  gpsdoSats[chan].satnum = sat;
  gpsdoSats[chan].elevation = elevation;
  gpsdoSats[chan].azimuth = azimuth;
  gpsdoSats[chan].snr = snr;
  gpsdoSats[chan].iswaas = iswaas;
}

void ProcessGETPOS(long lat, long lon, int elev) {
  gpsdoStatus.lat = lat;
  gpsdoStatus.lon = lon;
  gpsdoStatus.elev = elev;

}
