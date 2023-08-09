#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL_Boards.h>
#include <AP_VisualOdom/AP_VisualOdom_config.h>

#ifndef AP_DDS_VISUALODOM_ENABLED
    #define AP_DDS_VISUALODOM_ENABLED HAL_VISUALODOM_ENABLED && AP_DDS_ENABLED
#endif
