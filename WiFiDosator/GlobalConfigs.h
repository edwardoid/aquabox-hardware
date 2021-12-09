#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H


#include <Arduino.h>
#include <Scheduler.h>


#define DOWN_BUTTON_PIN D5
#define MIDDLE_BUTTON_MIN D4
#define UP_BUTTON_PIN D3

#define PUMP_PIN_1 D6
#define PUMP_PIN_2 D7
#define CALIBRATION_PRECISION 5.0
#define SCREENS_HISTORY 5

// [ WIFI
#define WIFI_NETWORK "Sargsyans24"
#define WIFI_PASSWORD "azazello"
#define AQUABOX_IP "192.168.1.22"
#define AQUABOX_PORT 2159
// WIFI ]

// [ UI
#define UI_ENABLED


#define UI_RENDER_FPS 5
#define UI_RENDER_WAIT_MS (1000 / UI_RENDER_FPS)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MAX_VISIBLE_MENU_ENTRIES 4
// UI ]

#define BTTN_UP D6
#define BTTN_DOWN D7


#define DEVICE_TYPE "feeder"

enum class DeviceState
{
    NotReady = -1,
    Starting = 0,
    ConnectingToNetwork = 1,
    ConnectingToAquabox = 2,
    ConnectionToAquaboxLost = 3,
    ConnectionToNetworkLost = 4,
    Working = 5,
    HandshakeFailed = 6,
    Idle = 7
};

extern volatile DeviceState CurrentState;

#endif // GLOBAL_CONFIGS_H
