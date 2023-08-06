#pragma once

#include "AP_Math.h"

// A homogonous transform type that matches ROS 2 geometry_msg/msg/TransformStamped
struct TransformF {
    Vector3F translation;
    QuaternionF rotation;
};
