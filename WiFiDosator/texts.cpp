#include "texts.h"

const __FlashStringHelper * textById(uint8_t id)
{
    switch(id) {
      case TXT_DISPLAY_ID: return F("Display");
      case TXT_NETWORK_ID: return F("Network");
      case TXT_FILL_ID: return F("Fill");
      case TXT_CALIBRATE_ID: return F("Calibrate");
      case TXT_RESET_ID: return F("Reset");
      case TXT_SCAN_ID: return F("       Scan");
      case TXT_SCANNING_ID: return F("      Scanning"); 
      case TXT_FILL_NOTIFY_ID: return F("Press <DOWN> button to start filling");
      case TXT_FILL_IN_PROGRESS_ID: return F("Press <DOWN> again to stop");
      case TXT_NO_WIFI_CONNECTION: return F("Not connectected");

      case TXT_ERROR_RESTART_ID: return F("Something went wrong. Please restart the device");
      default: {}
    }
    return F("<id>");
}