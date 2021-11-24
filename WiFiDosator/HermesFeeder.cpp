#include "HermesFeeder.h"

aquabox::proto::CachedSlaveProperty<uint32_t> HermesFeeder::TimesTimeoutProperty("_times", 1000);
aquabox::proto::CachedSlaveProperty<char*> HermesFeeder::ClassProperty("class", "step");
aquabox::proto::CachedSlaveProperty<char*> HermesFeeder::TypeProperty("type", "feeder");
aquabox::proto::CachedSlaveProperty<bool> HermesFeeder::CacheProperty("_cache", false);
aquabox::proto::CachedSlaveProperty<int32_t> HermesFeeder::PingTimeoutProperty("_timeout", 5000);