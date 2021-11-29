#ifndef HERMES_STEPPER_H
#define HERMES_STEPPER_H

#include <AquaboxProto.h>
#include "TimesProperty.h"


extern aquabox::proto::CachedSlaveProperty<uint32_t> TimesTimeoutProperty;
extern aquabox::proto::CachedSlaveProperty<char*> ClassProperty;
extern aquabox::proto::CachedSlaveProperty<char*> TypeProperty;
extern aquabox::proto::CachedSlaveProperty<bool> CacheProperty;
extern aquabox::proto::CachedSlaveProperty<int32_t> PingTimeoutProperty;

class HermesStepper
{
    struct Slave: public aquabox::proto::EasySlave<6>
    {
      friend class HermesStepper;

      inline Slave(SlavePropertyPtr *props, aquabox::proto::IO *io, const aquabox::proto::byte_t* serial, const aquabox::proto::byte_t* token)
        : aquabox::proto::EasySlave<6>(props, io, serial, token) {  setProps(props); }
      virtual bool processNextMessage() override
      {
          bool getResult = false;
          aquabox::proto::Message rcv;
          getResult = m_io->get(rcv);
          //yield();
          aquabox::proto::Message rpl;
          if (dispatch(&rcv, &rpl))
          {
              yield();
              m_io->send(rpl);
              yield();
          }
          return getResult;
      }

      inline void setSerial(const aquabox::proto::byte_t* serial) { memcpy(const_cast<aquabox::proto::byte_t*>(m_serial), serial, SERIAL_LEN);  }
      inline void setToken(const aquabox::proto::byte_t* token) { memcpy(m_token, token, TOKEN_LEN);  }
    };
    
    Slave::SlavePropertyPtr Props[6];
    Slave Impl;
    
public:
    inline HermesStepper(Times& TimesProperty, aquabox::proto::IO* io, aquabox::proto::byte_t* Token, aquabox::proto::byte_t* Serial)
      : Props({ &TimesProperty, &TimesTimeoutProperty, &ClassProperty, &TypeProperty, &CacheProperty, &PingTimeoutProperty })
      , Impl(Props, io, Serial, Token)
    {}

    inline void setSerial(const aquabox::proto::byte_t* serial) { Impl.setSerial(serial);  }
    inline void setToken(const aquabox::proto::byte_t* token) { Impl.setToken(token);  }
    inline bool handshake() { return Impl.handshake(); }
    inline bool processNextMessage() { return Impl.processNextMessage(); }
};


#endif // HERMES_STEPPER_H
