

#if AP_DDS_ENABLED

#include "AP_DDS_External_Odom.h"
#include <AP_VisualOdom/AP_VisualOdom.h>

void AP_DDS_External_Odom::handle_external_odom(const tf2_msgs_msg_TFMessage& msg)
{
    //! @todo guard with #if HAL_VISUALODOM_ENABLED and specific visual odom type

    AP_VisualOdom *visual_odom = AP::visualodom();
    if (visual_odom != nullptr) {
        // TODO loop through each TF message
        // for (transfrom in msg)
        //     if (is_odometry_frame(transform))
        //        normalize_rot()
        //        visual_odom->handle_vision_position_estimate(pos, normalize(rot), ...);
    }

}

bool AP_DDS_External_Odom::is_odometry_frame(const geometry_msgs_msg_TransformStamped& msg)
{
    // TODO
    return true;
}


#endif // AP_DDS_ENABLED