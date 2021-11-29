/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#ifndef Button_h
#define Button_h
#include "GlobalConfigs.h"

#define HOLD_TIMEOUT 800
#define SINGLE_TIMEOUT 400
#define DOUBLE_TIMEOUT 200

#define GESTURE_IDLE 0
#define GESTURE_SINGLE 1
#define GESTURE_DOUBLE 2
#define GESTURE_HOLD 4

class Button
{
	public:
		Button(uint8_t pin, uint16_t debounce_ms = 100);
		void begin();
		bool read();
		bool toggled();
		bool pressed();
		bool released();
		bool has_changed();
		
		const static bool PRESSED = LOW;
		const static bool RELEASED = HIGH;
	
	protected:
		uint8_t  _pin;
  private:
		uint16_t _delay;
		bool     _state;
		uint32_t _ignore_until;
		bool     _has_changed;
};

class GestureHandler: public Button
{
public:
    typedef void (*CallbackFunction)(uint8_t /*pin */, uint8_t /*state*/);
    inline GestureHandler(uint8_t pin, uint16_t debounce_ms = 50): Button(pin, debounce_ms) {}
    inline void loop()
    {
        unsigned long now = millis();
        
        unsigned long delta = now - m_gestureBegin;        
        
        if (read() && toggled()) {
          if(m_pressedCount == 0)
            m_gestureBegin = now;
          ++m_pressedCount;
        } else {
          if (m_pressedCount == 2 && delta > DOUBLE_TIMEOUT) {
            setGesture(GESTURE_DOUBLE);
            m_pressedCount = 0;            
          } else if (m_pressedCount == 1 && delta > SINGLE_TIMEOUT) {
            setGesture(GESTURE_SINGLE);
            m_pressedCount = 0;
          } else if (m_gesture != GESTURE_IDLE && delta > HOLD_TIMEOUT) {
            setGesture(GESTURE_IDLE);
            m_pressedCount = 0;
          }
        }
    }
    inline void setHandler(CallbackFunction f) { m_cb = f; }
    inline uint8_t count() { return m_pressedCount; }
    inline uint8_t gesture() { return m_gesture; }
private:
    inline void setGesture(uint8_t gesture) {
      if (m_gesture == gesture) {
        return;
      }
      m_gesture = gesture;
      if(m_cb != NULL) {
        m_cb(_pin, m_gesture);
      }
    }
private:
    uint8_t m_gesture = GESTURE_IDLE;
    unsigned long m_gestureBegin = 0;
    uint8_t m_pressedCount = 0;
    CallbackFunction m_cb = NULL;
};

#endif