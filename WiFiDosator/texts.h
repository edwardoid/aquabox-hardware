#ifndef TEXTS_H
#define TEXTS_H

#include <Arduino.h>

#define TXT_DISPLAY_ID 0
#define TXT_NETWORK_ID 1
#define TXT_FILL_ID 2
#define TXT_CALIBRATE_ID 3
#define TXT_RESET_ID 4
#define TXT_BACK_ID 5
#define TXT_SCAN_ID 6
#define TXT_SCANNING_ID 7
#define TXT_FILL_NOTIFY_ID 8
#define TXT_FILL_IN_PROGRESS_ID 9
#define TXT_NO_WIFI_CONNECTION 10
#define TXT_ERROR_RESTART_ID 0xFF

extern const __FlashStringHelper * textById(uint8_t id);

#endif // TEXTS_H