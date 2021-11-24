#ifndef GLOBAL_CONFIGS_H
#define GLOBAL_CONFIGS_H


#include <Arduino.h>

#define MOTOR_PIN D5
#define CALIBRATION_PRECISION 5
#define SCREENS_HISTORY 5

// [ WIFI
#define WIFI_NETWORK "Sargsyans24"
#define WIFI_PASSWORD "azazello"
#define AQUABOX_IP "192.168.1.133"
#define AQUABOX_PORT 1800
// WIFI ]

// [ UI
#define UI_ENABLED



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// UI ]

#define BTTN_UP D6
#define BTTN_DOWN D7


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
