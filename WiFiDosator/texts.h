#ifndef TEXTS_H
#define TEXTS_H

#include <Arduino.h>

#define TXT_SAVE_CALIBRATION_RESULT_QUESTION_FMT "Channel %d\nCurrent %.2f sec/ml\nNew %.2f sec/ml\n      Save?\n"

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
#define TXT_NO_WIFI_CONNECTION_ID 10
#define TXT_CHANNEL_1_ID 11
#define TXT_CHANNEL_2_ID 12
#define TXT_SELECT_CHANNEL_ID 13
#define TXT_CALIBRATE_NOTIFY_5ML_ID 14
#define TXT_CALIBRATE_NOTIFY_10ML_ID 15
#define TXT_CALIBRATE_NOTIFY_20ML_ID 16
#define TXT_CALIBRATE_IN_PROGRESS_ID 17
#define TXT_SAVE_CALIBRATION_RESULT_QUESTION_ID 18
#define TXT_CALIBRATION_ML_SEC 19
#define TXT_ERROR_RESTART_ID 0xFF

extern const __FlashStringHelper * textById(uint8_t id);

#endif // TEXTS_H