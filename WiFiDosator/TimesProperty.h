#ifndef TIMES_PROPERTY_H
#define TIMES_PROPERTY_H
#include <AquaboxProto.h>

struct Times: public aquabox::proto::CachedSlaveProperty<int32_t>
{
public:
    volatile int32_t CurrentValue;

    Times(uint8_t pin) : aquabox::proto::CachedSlaveProperty<int32_t>("times", (int32_t) CurrentValue), CurrentValue(0), m_pin(pin) { pinMode(m_pin, OUTPUT); }
    
    virtual bool set(const aquabox::proto::ValueData& in) override
    {
        if (aquabox::proto::CachedSlaveProperty<int32_t>::set(in))
        {
          Serial.print("Updated value to ");
          Serial.println(value);
          CurrentValue = value;
          if (value == 0) {
            digitalWrite(m_pin, LOW);
          }
          return true;
        }
        return false;
    }

    void update()
    {
        aquabox::proto::ValueData vd;
        vd.type = type();
        vd.value.I = CurrentValue;
        aquabox::proto::CachedSlaveProperty<int32_t>::set(vd);
    }
    
    virtual bool get(aquabox::proto::ValueData& out) const override
    {
        if(aquabox::proto::CachedSlaveProperty<int32_t>::get(out)) {
          out.value.I = CurrentValue;
          return true;
        }
        return false;
    }
private:
  uint8_t m_pin;
};

#endif // TIMES_PROPERTY_H
