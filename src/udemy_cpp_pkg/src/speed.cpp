#include "ros/ros.h"
#include "std_msgs/Float32.h"
// Subscribe to rpm publisher and publish speed

float WHEEL_DIA;

ros::Publisher speed_pub;

void subCallback(const std_msgs::Float32::ConstPtr& rpm)
{
    ros::NodeHandle callback_node_handle;

    if (callback_node_handle.getParam("wheel_dia", WHEEL_DIA))
    {
        std_msgs::Float32 speed;

        speed.data = 3.14 * WHEEL_DIA * (rpm->data / 60);

        speed_pub.publish(speed);
    }
    else
    {
        ROS_WARN("No Diameter Input");
    }
    
    
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "speed_node");

    ros::NodeHandle node_handle;

    speed_pub = node_handle.advertise<std_msgs::Float32>("speed", 10);

    ros::Subscriber rpm_sub = node_handle.subscribe("rpm", 10, subCallback);

    ros::spin();

    return 0;
}