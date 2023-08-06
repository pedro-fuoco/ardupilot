#pragma once

#if AP_DDS_ENABLED

#include "geometry_msgs/msg/TransformStamped.h"
#include "tf2_msgs/msg/TFMessage.h"

class AP_DDS_External_Odom
{
public:

    // subscription handler for external position localization
    static void handle_external_odom(const tf2_msgs_msg_TFMessage& msg);

    // Checks the child and parent frames match a set needed for external odom.
    // Since multiple different transforms can be sent, this validates the specific transform is
    // for odometry.
    static bool is_odometry_frame(const geometry_msgs_msg_TransformStamped& msg); 

};
#endif // AP_DDS_ENABLED