

#if AP_DDS_ENABLED && defined(HAL_VISUALODOM_ENABLED)

#include "AP_DDS_External_Odom.h"
#include <AP_VisualOdom/AP_VisualOdom.h>

void AP_DDS_External_Odom::handle_external_odom(const tf2_msgs_msg_TFMessage& msg)
{
    AP_VisualOdom *visual_odom = AP::visualodom();
    if (visual_odom != nullptr) {
        for (size_t i = 0; i < msg.transforms_size; i++) {
            const auto ros_transform_stamped = msg.transforms[i];
            if (is_odometry_frame(ros_transform_stamped)) {
                const uint64_t remote_time_us {0}; // TODO
                const uint32_t time_ms {0}; // TODO
                Vector3f ap_position {};
                Quaternion ap_rotation {};

                convert_transform(ros_transform_stamped.transform, ap_position, ap_rotation);
                ap_rotation.normalize();

                // No error is available in TF, trust the data as-is
                const float posErr {0.0};
                const float angErr {0.0};
                const uint8_t reset_counter {0}; // TODO

                visual_odom->handle_vision_position_estimate(remote_time_us, time_ms, ap_position.x, ap_position.y, ap_position.z, ap_rotation, posErr, angErr, reset_counter);
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

void AP_DDS_External_Odom::convert_transform(const geometry_msgs_msg_Transform& ros_transform, Vector3f& translation, Quaternion& rotation)
{
    translation.x = static_cast<float>(ros_transform.translation.x);
    translation.y = static_cast<float>(ros_transform.translation.y);
    translation.z = static_cast<float>(ros_transform.translation.z);

    // In AP, q1 is the quaternion's scalar component.
    // In ROS, w is the quaternion's scalar component.
    // https://docs.ros.org/en/humble/Tutorials/Intermediate/Tf2/Quaternion-Fundamentals.html#components-of-a-quaternion
    rotation.q1 = ros_transform.rotation.w;
    rotation.q2 = ros_transform.rotation.x;
    rotation.q3 = ros_transform.rotation.y;
    rotation.q4 = ros_transform.rotation.z;
}

#endif // AP_DDS_ENABLED && defined(HAL_VISUALODOM_ENABLED)