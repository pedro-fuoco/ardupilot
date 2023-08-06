#pragma once

#if AP_DDS_ENABLED

#include "geometry_msgs/msg/TransformStamped.h"
#include "tf2_msgs/msg/TFMessage.h"
#include <AP_Math/transform.h>

class AP_DDS_External_Odom
{
public:

    // Handler for external position localization
    static void handle_external_odom(const tf2_msgs_msg_TFMessage& msg);

    // Checks the child and parent frames match a set needed for external odom.
    // Since multiple different transforms can be sent, this validates the specific transform is
    // for odometry.
    static bool is_odometry_frame(const geometry_msgs_msg_TransformStamped& msg); 

    // Helper to convert from ROS transform to AP transform
    static void convert_transform(const geometry_msgs_msg_Transform& ros_transform, TransformF& ap_transform);

};
#endif // AP_DDS_ENABLED
