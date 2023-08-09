// Class for handling type conversions for DDS.

#pragma once

#if AP_DDS_ENABLED

#include "builtin_interfaces/msg/Time.h"

class AP_DDS_Type_Conversions
{
public:

    // Convert ROS time to a uint64_t [μS]
    static uint64_t time_u64_micros(const builtin_interfaces_msg_Time& ros_time) {
        return uint64_t(ros_time.sec) * 1E6 + ros_time.nanosec * 1E-3;
    }
};

#endif // AP_DDS_ENABLED