#include "easy_slave_property.h"

namespace aquabox {
namespace proto {

    template <>
    const ValueType BasicType<bool>::type = ValueType::Boolean;

    template <>
    const ValueType BasicType<int32_t>::type = ValueType::Integer;

    template <>
    const ValueType BasicType<uint32_t>::type = ValueType::UnsignedInteger;

    template <>
    const ValueType BasicType<char*>::type = ValueType::String;

    template <>
    const ValueType BasicType<float>::type = ValueType::Float;

    template <>
    bool CachedSlaveProperty<bool>::set(const ValueData& in)
    {
        if (in.type != type())
            return false;

        value = in.value.B != 0;
        return true;
    }

    template <>
    bool CachedSlaveProperty<bool>::get(ValueData& out) const
    {
        out.value.B = value ? 1 : 0;
        return true;
    }

    template <>
    bool CachedSlaveProperty<int32_t>::set(const ValueData& in)
    {
        if (in.type != type())
            return false;

        value = in.value.I;
        return true;
    }

    template <>
    bool CachedSlaveProperty<int32_t>::get(ValueData& out) const
    {
        out.value.I = value;
        return true;
    }

    template <>
    bool CachedSlaveProperty<uint32_t>::set(const ValueData& in)
    {
        if (in.type != type())
            return false;

        value = in.value.U;
        return true;
    }

    template <>
    bool CachedSlaveProperty<uint32_t>::get(ValueData& out) const
    {
        out.value.U = value;
        return true;
    }

    template <>
    bool CachedSlaveProperty<char*>::set(const ValueData& in)
    {
        if (in.type != type())
            return false;

        strcpy(value, in.value.S);
        return true;
    }

    template <>
    bool CachedSlaveProperty<char*>::get(ValueData& out) const
    {
        strcpy(out.value.S, value);
        return true;
    }

    template <>
    bool CachedSlaveProperty<float>::set(const ValueData& in)
    {
        if (in.type != type())
            return false;

        value = (float)in.value.F.V;
        value /= (float)in.value.F.Precision;

        return true;
    }

    template <>
    bool CachedSlaveProperty<float>::get(ValueData& out) const
    {
        out.value.F.Precision = 100;
        out.value.F.V = (int32_t)(value * 100);
        return true;
    }

}
}

