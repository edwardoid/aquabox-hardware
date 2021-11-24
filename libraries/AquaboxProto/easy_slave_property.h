#ifndef AQUABOX_EASY_SLAVE_PROPERTY_T
#define AQUABOX_EASY_SLAVE_PROPERTY_T

#include "value_data.h"
#include <string.h>

namespace aquabox {
namespace proto {
    struct SlaveProperty {
        SlaveProperty(const char* nm)
            : name(nm) {};
        const char* name;
        virtual ValueType type() const = 0;
        virtual bool set(const ValueData& in) = 0;
        virtual bool get(ValueData& out) const = 0;
    };

    template <typename BasicT>
    struct BasicType {
        static const ValueType type;
    };

    template <typename CachedT>
    struct CachedSlaveProperty : public SlaveProperty {
        CachedSlaveProperty(const char* nm, CachedT v = CachedT())
            : SlaveProperty(nm)
            , value(v)
        {
        }
        CachedT value;

        virtual ValueType type() const
        {
            return BasicType<CachedT>::type;
        }

        virtual bool set(const ValueData& in)
        {
            if (in.type != type())
                return false;
            return true;
        }
        virtual bool get(ValueData& out) const
        {
            out.type = type();

            return true;
        }
    };

    template <>
    bool CachedSlaveProperty<bool>::set(const ValueData& in);

    template <>
    bool CachedSlaveProperty<bool>::get(ValueData& out) const;

    template <>
    bool CachedSlaveProperty<int32_t>::set(const ValueData& in);

    template <>
    bool CachedSlaveProperty<int32_t>::get(ValueData& out) const;

    template <>
    bool CachedSlaveProperty<uint32_t>::set(const ValueData& in);

    template <>
    bool CachedSlaveProperty<uint32_t>::get(ValueData& out) const;

    template <>
    bool CachedSlaveProperty<char*>::set(const ValueData& in);

    template <>
    bool CachedSlaveProperty<char*>::get(ValueData& out) const;

    template <>
    bool CachedSlaveProperty<float>::set(const ValueData& in);

    template <>
    bool CachedSlaveProperty<float>::get(ValueData& out) const;

    struct Method: public CachedSlaveProperty<bool>
    {
        typedef void (*callback_t)(bool);

        callback_t callback;
        inline Method(const char* nm, callback_t cb = nullptr)
            : CachedSlaveProperty<bool>(nm, false)
            , callback(cb)
        {
        }

        inline virtual bool set(const ValueData& in) override
        {
            if (callback != nullptr) {
                (*callback)(in.value.B != 0);
                return CachedSlaveProperty<bool>::set(in);
            }
            return false;
        }
    };
}
}

#endif // AQUABOX_EASY_SLAVE_PROPERTY_T
