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
      case TXT_FILL_NOTIFY_ID: return F("  Press > button to    start filling");
      case TXT_FILL_IN_PROGRESS_ID: return F("Press > again to stop");
      case TXT_NO_WIFI_CONNECTION_ID: return F("Not connectected");
      case TXT_CHANNEL_1_ID: return F("Channel 1");
      case TXT_CHANNEL_2_ID: return F("Channel 2");
      case TXT_SELECT_CHANNEL_ID: return F("Select channel:");
      case TXT_ERROR_RESTART_ID: return F("Something went wrong. Please restart the device");
      case TXT_CALIBRATE_NOTIFY_5ML_ID: return F("  Press > button to    start measuring 5ml");
      case TXT_CALIBRATE_NOTIFY_10ML_ID: return F("  Press > button to    start measuring 10ml");
      case TXT_CALIBRATE_NOTIFY_20ML_ID: return F("  Press > button to    start measuring 20ml");
      case TXT_CALIBRATE_IN_PROGRESS_ID: return F("Press > again to stop");
      case TXT_SAVE_CALIBRATION_RESULT_QUESTION_ID: return F(TXT_SAVE_CALIBRATION_RESULT_QUESTION_FMT);
      default: {}
    }
    return F("<id>");
}