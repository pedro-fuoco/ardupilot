

#if AP_DDS_ENABLED

#include "AP_DDS_External_Odom.h"
#include <AP_VisualOdom/AP_VisualOdom.h>

void AP_DDS_External_Odom::handle_external_odom(const tf2_msgs_msg_TFMessage& msg)
{
    //! @todo guard with #if HAL_VISUALODOM_ENABLED and specific visual odom type

    AP_VisualOdom *visual_odom = AP::visualodom();
    if (visual_odom != nullptr) {
        for (size_t i = 0; i < msg.transforms_size; i++) {
            const auto ros_transform_stamped = msg.transforms[i];
            if (is_odometry_frame(ros_transform_stamped)) {
                // TODO should rotation be normalized?
                [[maybe_unused]] const uint64_t remote_time_us {0}; // TODO
                [[maybe_unused]] const uint32_t time_ms {0}; // TODO
                TransformF ap_transform {};
                [[maybe_unused]] const float posErr {0.0}; // TODO
                [[maybe_unused]] const float angErr {0.0}; // TODO
                [[maybe_unused]] const uint8_t reset_counter {0}; // TODO
                convert_transform(ros_transform_stamped.transform, ap_transform);
                // Uncommenting this causes a linker error.
                //   [1226/1226] Linking build/sitl/bin/arduplane
                //   /usr/bin/ld: lib/libArduPlane_libs.a(AP_DDS_External_Odom.cpp.0.o): in function `AP_DDS_External_Odom::handle_external_odom(tf2_msgs_msg_TFMessage const&)':
                //   AP_DDS_External_Odom.cpp:(.text._ZN20AP_DDS_External_Odom20handle_external_odomERK22tf2_msgs_msg_TFMessage+0x175): undefined reference to `AP_VisualOdom::handle_vision_position_estimate(unsigned long, unsigned int, TransformF&, float, float, unsigned char)'
                //   collect2: error: ld returned 1 exit status
                // visual_odom->handle_vision_position_estimate(remote_time_us, time_ms, ap_transform, posErr, angErr, reset_counter);
            }
        }
    }
}

bool AP_DDS_External_Odom::is_odometry_frame(const geometry_msgs_msg_TransformStamped& msg)
{
    char odom_parent[] = "map";
    char odom_child[] = "base_link";
    // Assume the frame ID's are null terminated.
    return (strlen(msg.header.frame_id) == strlen(odom_parent)) &&
            (strlen(msg.child_frame_id) == strlen(odom_child)) &&
            (strncmp(msg.header.frame_id, odom_parent, strlen(odom_parent)) == 0) && 
           (strncmp(msg.child_frame_id, odom_child, strlen(odom_child)) == 0);
}

void AP_DDS_External_Odom::convert_transform(const geometry_msgs_msg_Transform& ros_transform, TransformF& ap_transform)
{
    ap_transform.translation.x = ros_transform.translation.x;
    ap_transform.translation.y = ros_transform.translation.y;
    ap_transform.translation.z = ros_transform.translation.z;

    // In AP, q1 is the quaternion's scalar component.
    // In ROS, w is the quaternion's scalar component.
    // https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Quaternion-Fundamentals.html#components-of-a-quaternion
    ap_transform.rotation.q1 = ros_transform.rotation.w;
    ap_transform.rotation.q2 = ros_transform.rotation.x;
    ap_transform.rotation.q3 = ros_transform.rotation.y;
    ap_transform.rotation.q4 = ros_transform.rotation.z;
}

#endif // AP_DDS_ENABLED