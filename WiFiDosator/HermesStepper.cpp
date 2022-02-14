#include "HermesStepper.h"
#include "GlobalConfigs.h"

aquabox::proto::CachedSlaveProperty<uint32_t> TimesTimeoutProperty("_times", 20);
aquabox::proto::CachedSlaveProperty<char*> ClassProperty("class", "step");
aquabox::proto::CachedSlaveProperty<char*> TypeProperty("type", DEVICE_TYPE);
aquabox::proto::CachedSlaveProperty<bool> CacheProperty("_cache", true);
aquabox::proto::CachedSlaveProperty<int32_t> PingTimeoutProperty("_timeout", 5000);