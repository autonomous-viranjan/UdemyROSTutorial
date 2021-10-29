#include "ros/ros.h"
#include "std_msgs/String.h"
// Writing a subscriber node for ros

void subCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("%s", msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "hello_world_sub_node");

    ros::NodeHandle node_handle;

    ros::Subscriber hello_world_sub = node_handle.subscribe("hello", 10, subCallback);

    ros::spin();

    return 0;
}